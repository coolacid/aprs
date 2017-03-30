void printNEMA(void)
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

    console.print("Latitude: ");
    console.print(nmea.getMinLatitude());
    console.println(nmea.getDirLat());
    console.print("Longitude: ");
    console.print(nmea.getMinLongitude());
    console.println(nmea.getDirLong());

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

