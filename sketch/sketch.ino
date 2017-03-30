#include <SoftwareSerial.h>
#include <MicroNMEA.h>
#include <Ticker.h>

// Libraries
// https://github.com/stevemarple/MicroNMEA

SoftwareSerial gps(D2, D3); // RX, TX
HardwareSerial& console = Serial;

char nmeaBuffer[100];
MicroNMEA nmea(nmeaBuffer, sizeof(nmeaBuffer));

Ticker tConsole;
Ticker tGPSUpdate;

volatile bool ppsTriggered = false;

void ppsHandler(void)
{
  ppsTriggered = true;
}

void gpsHardwareReset()
{
  // Empty input buffer
  while (gps.available())
    gps.read();
  
//  digitalWrite(A0, LOW);
  delay(50);
//  digitalWrite(A0, HIGH);

  // Reset is complete when the first valid message is received
  while (1) {
    while (gps.available()) {
      char c = gps.read();
      console.print(c);
      if (nmea.process(c))
        return;
    }
  }
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  gps.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, nmea.isValid());

  console.println("Resetting GPS module ...");
  gpsHardwareReset();
  console.println("... done");
  // TODO: None of these appear to work, need to read the manual and set up our GPS receiver
  // Clear the list of messages which are sent.
  // MicroNMEA::sendSentence(gps, "$PORZB");

  // Send only RMC and GGA messages.
  // MicroNMEA::sendSentence(gps, "$PORZB,RMC,1,GGA,1");

  // Disable compatability mode (NV08C-CSM proprietary message) and
  // adjust precision of time and position fields
  // MicroNMEA::sendSentence(gps, "$PNVGNME,2,9,1");
  // MicroNMEA::sendSentence(gps, "$PONME,2,4,1,0");
  
  // Trigger a GPS update every Second
  tConsole.attach(1, ppsHandler);

  // Print to the Console every 5 seconds
  tGPSUpdate.attach(5, printConsole);

  // TODO: Print to web clients every X seconds
  
}

void loop(void)
{
  if (ppsTriggered) {
    ppsTriggered = false;
    digitalWrite(LED_BUILTIN, nmea.isValid());
    nmea.clear();
  }

  while (!ppsTriggered && gps.available()) {
    char c = gps.read();
//    console.print(c);
    nmea.process(c);
  }
}
