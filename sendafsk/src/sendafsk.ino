// Some code from:
// http://forum.arduino.cc/index.php?topic=396450
// 

// Debug Mode for when we're in the Arduino Board without the radio connected
// #define DEBUG

#include "config.h"
#include "ax25.h"
#include "afsk_avr.h"
#include "afsk_pic32.h"
#include <SoftwareSerial.h>
#include "Timer.h"

const int RecLED = 12;          // The receive LED pin
const int StatusLED = 13;       // The Status LED pin
const int SquPin = 6;           // The Squelch detect pin from radio

Timer t;

const byte numChars = 100;
char receivedChars[numChars];   // an array to store the received data

bool newData = false;
bool buttonState = 0;
bool lastButtonState = 0;

SoftwareSerial RadioSerial(10, 11); // RX, TX

void setup_radio() {
  // Setup the Radio
  const char endMarker = '\n';
  bool newRadioData = false;
  char rc;
  Serial.println(F("Radio Setup"));
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
  RadioSerial.print("AT+SETFILTER=0,0,0\r\n");
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
    Serial.println(F("Starting Up"));
    // Set Pin StatusLED for Status LED
    pinMode(StatusLED, OUTPUT);
    // Set Pin RecLED for Rec LED
    pinMode(RecLED, OUTPUT);
    // Set Status and Receive LED to Solid to signify bootup
    digitalWrite(StatusLED,HIGH);
    digitalWrite(RecLED,HIGH);
    pinMode(SquPin, INPUT);
#ifndef DEBUG
    setup_radio();
#else
    delay(1000);
#endif
    afsk_setup();
    Serial.println(F("<Arduino is ready>"));
    // We're done booting, so we can turn off the LEDs
    digitalWrite(StatusLED,LOW);
    digitalWrite(RecLED,LOW);
    t.oscillate(StatusLED, 1000, LOW);
}

void loop() {
    t.update();
    recvWithEndMarker();
    HandleData();
    buttonState = digitalRead(SquPin);
    if (buttonState != lastButtonState) {
      lastButtonState = buttonState;
      if (buttonState == 0) {
        Serial.println(F("Receiving"));
        // Set Rec LED on
        digitalWrite(RecLED,HIGH);
      } else {
        // Set Rec LED off
        digitalWrite(RecLED,LOW);
      }
    }
}

void recvWithEndMarker() {
    static byte ndx = 0;
    const char endMarker = '\n';
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

void p(const char fmt[], ... ){
        char buf[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 128, fmt, args);
        va_end (args);
        Serial.print(buf);
}

int parseHeader(char *headerStr, struct s_address *addresses) {
    char *tok1;
    char *tok2;
    int pathnum = 0;
    char *fromCall = strtok_r(headerStr, ">", &tok1);
    fromCall = strtok_r(fromCall, "-", &tok2);
    char *fromCallId = strtok_r(NULL, "-", &tok2);
    p("From Call: %s ID: %s\n", fromCall, fromCallId);
    strncpy(addresses[1].callsign, fromCall, 7);
    addresses[1].ssid = atoi(fromCallId);

    char *toCall = strtok_r(NULL, ",", &tok1);
    toCall = strtok_r(toCall, "-", &tok2);
    char *toCallId = strtok_r(NULL, "-", &tok2);
    p("To Call: %s ID: %s\n", toCall, toCallId);
    strncpy(addresses[0].callsign, toCall, 7);
    addresses[0].ssid = atoi(toCallId);

    char *pathItem;
    while ((pathItem = strtok_r(NULL, ",", &tok1)) != NULL and pathnum < 4) {
        pathnum++;
        p("PathItem: %s\n", pathItem);
        char *pathCall = strtok_r(pathItem, "-", &tok2);
        char *pathCallId = strtok_r(NULL, "-", &tok2);

        p("\tCall: %s ID: %s\n", pathCall, pathCallId);
        strncpy(addresses[pathnum+1].callsign, pathCall, 7);
        addresses[pathnum+1].ssid = atoi(pathCallId);

    }
    p("Number of Addresses: %d\n", pathnum+2);
    return pathnum+2;
}

void HandleData() {
    struct s_address addresses[6];
    int numaddresses;
    if (newData == true) {
        if (receivedChars[0] == 'A' && receivedChars[1] == 'T' && receivedChars[2] == '+') {
          Serial.print(F("Transceiver Control Code: "));
          Serial.println(receivedChars);
          // TODO: Send the control command on to the transceiver
        } else {
          char* path = strtok(receivedChars, ":");
          char* message = strtok(NULL, ":");
          numaddresses = parseHeader(path, addresses);
          Serial.print(F("Sending: "));
          Serial.println(message);
  
           ax25_send_header(addresses, numaddresses);

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
