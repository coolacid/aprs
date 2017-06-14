// APRS Message format: 
// `/GPSTIMEhLAT/LON_DIR/SPEED/A=ALT COMMENT`
// GPSTime = DDHHmmz
// LAT = Latitude in Seconds - 3513.84N (Fixed 8 Char Size)
// LON = Longtitude in Seconds - 11140.39W (Fixed 9 Char Size)
// _ - This is they type O = Ballon, f= Fire Truck, s = Ship (See http://www.aprs.org/doc/APRS101.PDF Apx 2)
// DIR = Direction in Degrees (%03d)
// Speed = Speed in Knots (%03d)
// ALT = Altitude in feet (%06ld)

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include "brains.h"
#include "APRS.h"

void printAPRS(void)
{    
  char CallSign[] = "VE3YCA-4";
  char Comment[] = "Testing";

  char APRSMessage[100];
 
  GenAPRS(APRSMessage, CallSign, Comment);

  if (APRSMessage[0] == '\0') {
    console.println("No GPS Fix");
  } else {
    console.print("APRSMessage: ");
    console.println(APRSMessage);
    ss_radio.write(APRSMessage);
    ss_radio.write('\n');
  }
}

void GenAPRS(char *dest, char *CallSign, char *Comment)
{
  char buffer[255];
  char RawStringLat[8], RawStringLong[9];

  char OurDest[] = "APLSR1,RELAY,WIDE1-1,WIDE2-2";

  if (strlen(RawLong.value()) == 0 or strlen(RawLat.value()) == 0) {
    dest[0] = '\0';
    return;
  }

  strncpy(RawStringLat, RawLat.value(), 7);
  RawStringLat[7]= '\0';

  strncpy(RawStringLong, RawLong.value(), 8);
  RawStringLong[8]= '\0';

  snprintf(buffer, sizeof(buffer),"%s>%s:/%02d%02d%02dh%s%s/%s%s%s%03d/%03d/A=%06d/%s",
      CallSign,
      OurDest,
      int(gps.date.day()),
      int(gps.time.hour()),
      int(gps.time.minute()),
      RawStringLat,
      RawLatDir.value(),
      RawStringLong,
      RawLongDir.value(),
      "s", 
      (int)gps.course.deg(),
      (int)gps.speed.knots(),
      (int)gps.altitude.feet(),
      Comment
      );
  strcpy(dest, buffer);
}

