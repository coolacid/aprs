#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Ticker.h>

SoftwareSerial ss_gps(D3, D2); // RX, TX
HardwareSerial& console = Serial;

TinyGPSPlus gps;
TinyGPSCustom RawLat(gps, "GPGGA", 2);
TinyGPSCustom RawLatDir(gps, "GPGGA", 3);
TinyGPSCustom RawLong(gps, "GPGGA", 4);
TinyGPSCustom RawLongDir(gps, "GPGGA", 5);


Ticker tPrintConsole;
Ticker tPrintAPRS;
Ticker tGPSUpdate;

volatile bool ppsTriggered = false;

void ppsHandler(void)
{
  ppsTriggered = true;
}

void gpsHardwareReset()
{
  // Empty input buffer
  while (ss_gps.available())
    ss_gps.read();

  delay(50);
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  ss_gps.begin(9600);

  console.println("Resetting GPS module ...");
  gpsHardwareReset();
  console.println("... done");

  // Trigger a GPS update every Second
  tGPSUpdate.attach(1, ppsHandler);

  // Print to the Console every 5 seconds
  tPrintConsole.attach(5, printConsole);
  tPrintAPRS.attach(5, printAPRS);

  // TODO: Print to web clients every X seconds

}

void loop(void)
{
  if (ppsTriggered) {
    ppsTriggered = false;
    digitalWrite(LED_BUILTIN, gps.location.isValid());
  }

  while (!ppsTriggered && ss_gps.available()) {
    gps.encode(ss_gps.read());
  }
}
