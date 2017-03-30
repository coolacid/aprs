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
  if (nmea.getAltitude(alt))
    alt = meters_to_feet(alt / 1000.);
  else
    alt = 0;

  snprintf(buffer, sizeof(buffer),"%d%d%dh%s%c/%s%c%s%03d/%03d/A=%06ld ", 
      int(nmea.getDay()), 
      int(nmea.getHour()), 
      int(nmea.getMinute()), 
      nmea.getMinLatitude(),
      nmea.getDirLat(), 
      nmea.getMinLongitude(), 
      nmea.getDirLong(), 
      "s", 
      nmea.getCourse() / 1000., 
      nmea.getSpeed() / 1000., 
      alt,
      comment
      );
  console.println(buffer);
}
