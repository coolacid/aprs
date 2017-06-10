
// Some code from:
// http://forum.arduino.cc/index.php?topic=396450
// 
#include "config.h"
#include "ax25.h"
#include "afsk_avr.h"
#include "afsk_pic32.h"
#include <SoftwareSerial.h>

const byte numChars = 255;
char receivedChars[numChars];   // an array to store the received data

boolean newData = false;
boolean newRadioData = false;

const int SquPin = 6;
int buttonState = 0;
int lastButtonState = 0;

SoftwareSerial RadioSerial(10, 11); // RX, TX

void setup_radio() {
// Setup the Radio
  char rc;
  char endMarker = '\n';

  Serial.println("Radio Setup");
  RadioSerial.begin(9600);
  RadioSerial.print("AT+DMOCONNECT\r\n");
  newRadioData = false;
  while (newRadioData == false) {
    if (RadioSerial.available()) {
      rc = RadioSerial.read();
      Serial.write(rc);
      if (rc == endMarker) {
        newRadioData = true;
      }
    }
  }

  RadioSerial.print("AT+DMOSETGROUP=1,144.3900,144.3900,0000,5,0000\r\n");
  newRadioData = false;
  while (newRadioData == false) {
    if (RadioSerial.available()) {
      rc = RadioSerial.read();
      Serial.write(rc);
      if (rc == endMarker) {
        newRadioData = true;
      }
    }
  }
  RadioSerial.print("AT+SETFILTER=1,1,1\r\n");
  newRadioData = false;
  while (newRadioData == false) {
    if (RadioSerial.available()) {
      rc = RadioSerial.read();
      Serial.write(rc);
      if (rc == endMarker) {
        newRadioData = true;
      }
    }
  }
}

void setup() {
    Serial.begin(9600);
    pinMode(SquPin, INPUT);
    setup_radio();
    afsk_setup();
    Serial.println("<Arduino is ready>");
}

void loop() {
    recvWithEndMarker();
    HandleData();
    buttonState = digitalRead(SquPin);
    if (buttonState != lastButtonState) {
      lastButtonState = buttonState;
      if (buttonState == 0) {
        Serial.println("Receiving");
      }
    }
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

void p(char *fmt, ... ){
        char buf[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 128, fmt, args);
        va_end (args);
        Serial.print(buf);
}

void parseHeader(char *headerStr) {
    char *tok1;
    char *tok2;
    char *fromCall = strtok_r(headerStr, ">", &tok1);
    fromCall = strtok_r(fromCall, "-", &tok2);
    char *fromCallId = strtok_r(NULL, "-", &tok2);
    p("From Call: %s ID: %s\n", fromCall, fromCallId);
    char *toCall = strtok_r(NULL, ",", &tok1);
    toCall = strtok_r(toCall, "-", &tok2);
    char *toCallId = strtok_r(NULL, "-", &tok2);
    p("To Call: %s ID: %s\n", toCall, toCallId);
    char *pathItem;
    while ((pathItem = strtok_r(NULL, ",", &tok1)) != NULL) {
        p("PathItem: %s\n", pathItem);
        char *pathCall = strtok_r(pathItem, "-", &tok2);
        char *pathCallId = strtok_r(NULL, "-", &tok2);

        p("\tCall: %s ID: %s\n", pathCall, pathCallId);
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
            #ifdef DIGI_PATH1
            {DIGI_PATH1, DIGI_PATH1_TTL}, // Digi1 (first digi in the chain)
            #endif
            #ifdef DIGI_PATH2
            {DIGI_PATH2, DIGI_PATH2_TTL}, // Digi2 (second digi in the chain)
            #endif
          };
  
           ax25_send_header(addresses, sizeof(addresses)/sizeof(s_address));

           ax25_send_string(message);
           ax25_send_footer();
           ax25_flush_frame();
           while (afsk_flush()) {
//              power_save();
           }
        }
        newData = false;
    }
}
