// APRS Message format: 
// `/GPSTIMEhLAT/LON_DIR/SPEED/A=ALT COMMENT`
// GPSTime = DDHHmmz
// LAT = Latitude in Seconds - 3513.84N (Fixed 8 Char Size)
// LON = Longtitude in Seconds - 11140.39W (Fixed 9 Char Size)
// _ - This is they type O = Ballon, f= Fire Truck, s = Ship (See http://www.aprs.org/doc/APRS101.PDF Apx 2)
// DIR = Direction in Degrees (%03d)
// Speed = Speed in Knots (%03d)
// ALT = Altitude in feet (%06ld)

float meters_to_feet(float m)
{
  // 10000 ft = 3048 m
  return m / 0.3048;
}

void printConsole(void)
{    
  long alt;
  char buffer[255];
  char *comment = "Comment";
  char gpslat[8], gpslong[9];
  
  if (nmea.getAltitude(alt))
    alt = (int)(meters_to_feet(alt / 1000) + 0.5);
  else
    alt = 0;

  snprintf(gpslat, 8, "%s", nmea.getMinLatitude());
  snprintf(gpslong, 9, "%s", nmea.getMinLongitude());

  snprintf(buffer, sizeof(buffer),"/%02d%02d%02dh%7s%c/%8s%c%s%03d/%03d/A=%06ld ", 
      int(nmea.getDay()), 
      int(nmea.getHour()), 
      int(nmea.getMinute()), 
      gpslat,
      nmea.getDirLat(),
      gpslong,
      nmea.getDirLong(),
      "s", 
      (int)((nmea.getCourse() / 1000.) + .5), 
      (int)((nmea.getSpeed() / 1000.) + .5), 
      alt,
      comment
      );
  console.println(buffer);
}
