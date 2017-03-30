#include <SoftwareSerial.h>
#include <MicroNMEA.h>
#include <Timer.h>

// Libraries
// https://github.com/stevemarple/MicroNMEA
// https://github.com/JChristensen/Timer

SoftwareSerial gps(D2, D3); // RX, TX
HardwareSerial& console = Serial;

char nmeaBuffer[200];
MicroNMEA nmea(nmeaBuffer, sizeof(nmeaBuffer));

Timer t;
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
  // Clear the list of messages which are sent.
  MicroNMEA::sendSentence(gps, "$PORZB");

  // Send only RMC and GGA messages.
  MicroNMEA::sendSentence(gps, "$PORZB,RMC,1,GGA,1");

  // Disable compatability mode (NV08C-CSM proprietary message) and
  // adjust precision of time and position fields
  MicroNMEA::sendSentence(gps, "$PNVGNME,2,9,1");
  // MicroNMEA::sendSentence(gps, "$PONME,2,4,1,0");
  
  // Trigger a GPS update every Second
  t.every(1000, ppsHandler);

  // Print to the Console every 5 seconds
  t.every(5000, printConsole);
}

void printConsole(void)
{
    // Output GPS information from previous second
    console.print("Valid fix: ");
    console.println(nmea.isValid() ? "yes" : "no");

    console.print("Nav. system: ");
    if (nmea.getNavSystem())
      console.println(nmea.getNavSystem());
    else
      console.println("none");

    console.print("Num. satellites: ");
    console.println(nmea.getNumSatellites());

    console.print("HDOP: ");
    console.println(nmea.getHDOP()/10., 1);
    
    console.print("Date/time: ");
    console.print(nmea.getYear());
    console.print('-');
    console.print(int(nmea.getMonth()));
    console.print('-');
    console.print(int(nmea.getDay()));
    console.print('T');
    console.print(int(nmea.getHour()));
    console.print(':');
    console.print(int(nmea.getMinute()));
    console.print(':');
    console.println(int(nmea.getSecond()));

    long latitude_mdeg = nmea.getLatitude();
    long longitude_mdeg = nmea.getLongitude();
    console.print("Latitude (deg): ");
    console.println(latitude_mdeg / 1000000., 6);

    console.print("Longitude (deg): ");
    console.println(longitude_mdeg / 1000000., 6);

    long alt;
    console.print("Altitude (m): ");
    if (nmea.getAltitude(alt))
      console.println(alt / 1000., 3);
    else
      console.println("not available");

    console.print("Speed: ");
    console.println(nmea.getSpeed() / 1000., 3);
    console.print("Course: ");
    console.println(nmea.getCourse() / 1000., 3);
    console.println("-----------------------");    
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
  t.update();
}
