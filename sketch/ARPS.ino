// APRS Message format: 
// `/GPSTIMEhLAT/LON_DIR/SPEED/A=ALT COMMENT`
// GPSTime = DDHHmmz
// LAT = Latitude in Seconds - 3513.84N (Fixed 8 Char Size)
// LON = Longtitude in Seconds - 11140.39W (Fixed 9 Char Size)
// _ - This is they type O = Ballon, f= Fire Truck, s = Ship (See http://www.aprs.org/doc/APRS101.PDF Apx 2)
// DIR = Direction in Degrees (%03d)
// Speed = Speed in Knots (%03d)
// ALT = Altitude in feet (%06ld)

void printAPRS(void)
{    
  char APRSMessage[255];
  GenAPRS(APRSMessage);

  console.println(APRSMessage);
}

void GenAPRS(char *dest)
{
  char buffer[255];
  char *comment = "Comment";
  char RawStringLat[8], RawStringLong[9];

  strncpy(RawStringLat, RawLat.value(), 7);
  RawStringLat[7]= '\0';

  strncpy(RawStringLong, RawLong.value(), 8);
  RawStringLong[8]= '\0';

  snprintf(buffer, sizeof(buffer),"/%02d%02d%02dh%s%s/%s%s%s%03d/%03d/A=%06d ",
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
      (int)gps.altitude.feet()
      );
  strcpy(dest, buffer);
}

