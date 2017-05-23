void printConsole(void)
{
  if (gps.location.isUpdated())
  {
    console.print(F("LOCATION   Fix Age="));
    console.print(gps.location.age());
    console.print(F("ms Raw Lat="));
    console.print(gps.location.rawLat().negative ? "-" : "+");
    console.print(gps.location.rawLat().deg);
    console.print("[+");
    console.print(gps.location.rawLat().billionths);
    console.print(F(" billionths],  Raw Long="));
    console.print(gps.location.rawLng().negative ? "-" : "+");
    console.print(gps.location.rawLng().deg);
    console.print("[+");
    console.print(gps.location.rawLng().billionths);
    console.print(F(" billionths],  Lat="));
    console.print(gps.location.lat(), 6);
    console.print(F(" Long="));
    console.println(gps.location.lng(), 6);
  }

  if (gps.date.isUpdated())
  {
    console.print(F("DATE       Fix Age="));
    console.print(gps.date.age());
    console.print(F("ms Raw="));
    console.print(gps.date.value());
    console.print(F(" Year="));
    console.print(gps.date.year());
    console.print(F(" Month="));
    console.print(gps.date.month());
    console.print(F(" Day="));
    console.println(gps.date.day());
  }

  if (gps.time.isUpdated())
  {
    console.print(F("TIME       Fix Age="));
    console.print(gps.time.age());
    console.print(F("ms Raw="));
    console.print(gps.time.value());
    console.print(F(" Hour="));
    console.print(gps.time.hour());
    console.print(F(" Minute="));
    console.print(gps.time.minute());
    console.print(F(" Second="));
    console.print(gps.time.second());
    console.print(F(" Hundredths="));
    console.println(gps.time.centisecond());
  }

  if (gps.speed.isUpdated())
  {
    console.print(F("SPEED      Fix Age="));
    console.print(gps.speed.age());
    console.print(F("ms Raw="));
    console.print(gps.speed.value());
    console.print(F(" Knots="));
    console.print(gps.speed.knots());
    console.print(F(" MPH="));
    console.print(gps.speed.mph());
    console.print(F(" m/s="));
    console.print(gps.speed.mps());
    console.print(F(" km/h="));
    console.println(gps.speed.kmph());
  }

  if (gps.course.isUpdated())
  {
    console.print(F("COURSE     Fix Age="));
    console.print(gps.course.age());
    console.print(F("ms Raw="));
    console.print(gps.course.value());
    console.print(F(" Deg="));
    console.println(gps.course.deg());
  }

  if (gps.altitude.isUpdated())
  {
    console.print(F("ALTITUDE   Fix Age="));
    console.print(gps.altitude.age());
    console.print(F("ms Raw="));
    console.print(gps.altitude.value());
    console.print(F(" Meters="));
    console.print(gps.altitude.meters());
    console.print(F(" Miles="));
    console.print(gps.altitude.miles());
    console.print(F(" KM="));
    console.print(gps.altitude.kilometers());
    console.print(F(" Feet="));
    console.println(gps.altitude.feet());
  }

  if (gps.satellites.isUpdated())
  {
    console.print(F("SATELLITES Fix Age="));
    console.print(gps.satellites.age());
    console.print(F("ms Value="));
    console.println(gps.satellites.value());
  }
}

