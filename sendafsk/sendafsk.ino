
// Some code from:
// http://forum.arduino.cc/index.php?topic=396450
// 
#include "config.h"
#include "ax25.h"
#include "afsk_avr.h"
#include "afsk_pic32.h"

const byte numChars = 255;
char receivedChars[numChars];   // an array to store the received data

boolean newData = false;

void setup() {
    Serial.begin(115200);
    Serial.println("<Arduino is ready>");
    afsk_setup();
}

void loop() {
    recvWithEndMarker();
    HandleData();
}

void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    while (Serial.available() && newData == false) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

void HandleData() {
    if (newData == true) {
        Serial.print("First Char: ");
        Serial.println(receivedChars[0]);
        if (receivedChars[0] == '+') {
          Serial.print("Control Code: ");
          Serial.println(receivedChars);
        } else {
          char* path = strtok(receivedChars, ":");
          char* message = strtok(0, ":");
          Serial.print("Sending: ");
          Serial.println(message);
          Serial.print("To: ");
          Serial.println(path);
          
          const struct s_address addresses[] = {
            {D_CALLSIGN, D_CALLSIGN_ID},  // Destination callsign
            {S_CALLSIGN, S_CALLSIGN_ID},  // Source callsign (-11 = balloon, -9 = car)
//            #ifdef DIGI_PATH1
//            {DIGI_PATH1, DIGI_PATH1_TTL}, // Digi1 (first digi in the chain)
//            #endif
//            #ifdef DIGI_PATH2
//            {DIGI_PATH2, DIGI_PATH2_TTL}, // Digi2 (second digi in the chain)
//            #endif
          };
  
           ax25_send_header(addresses, sizeof(addresses)/sizeof(s_address));

           ax25_send_string(receivedChars);
           ax25_send_footer();
           ax25_flush_frame();
           while (afsk_flush()) {
//              power_save();
           }
        }
        newData = false;
    }
}
