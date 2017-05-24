#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Ticker.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

//////////////////////
// WiFi Definitions //
//////////////////////
const char WiFiAPPSK[] = "sparkfun";
const char WiFiSSID[] = "findme-aprs";
const char DNS_Name[] = "configure.me";
const byte DNS_Port = 53;

IPAddress apIP(192, 168, 1, 1);
// WiFiServer server(80);
ESP8266WebServer webServer(80);
DNSServer dnsServer;


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
}

void setup() {
  // Open serial communications and wait for port to open:
//  Serial.setDebugOutput(true);
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // set the data rate for the SoftwareSerial port
  ss_gps.begin(9600);

  console.println("Resetting GPS module ...");
  gpsHardwareReset();
  console.println("... done");

  console.println("Starting Wifi/Web ...");
  setupWiFi();
  SetupWebServer();
  SetupDNSServer();

  console.println("... done");

  // Trigger a GPS update every Second
  tGPSUpdate.attach(1, ppsHandler);

  // Print to the Console every 5 seconds
//  tPrintConsole.attach(5, printConsole);
  tPrintAPRS.attach(5, printAPRS);

  // TODO: Print to web clients every X seconds

}

void loop(void)
{
  dnsServer.processNextRequest();
  webServer.handleClient();
  
  if (ppsTriggered) {
    ppsTriggered = false;
    digitalWrite(LED_BUILTIN, gps.location.isValid());
  }

  while (!ppsTriggered && ss_gps.available()) {
    gps.encode(ss_gps.read());
  }
}
