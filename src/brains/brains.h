#ifndef BRAINS_H_
#define BRAINS_H_

void ppsHandler(void);
void gpsHardwareReset();

//////////////////////
// WiFi Definitions //
//////////////////////
const char WiFiAPPSK[] = "sparkfun";
const char WiFiSSID[] = "findme-aprs";
const char DNS_Name[] = "configure.me";
const byte DNS_Port = 53;

extern SoftwareSerial ss_gps;
extern SoftwareSerial ss_radio;

extern HardwareSerial& console;

extern TinyGPSPlus gps;
extern TinyGPSCustom RawLat;
extern TinyGPSCustom RawLatDir;
extern TinyGPSCustom RawLong;
extern TinyGPSCustom RawLongDir;

#endif // BRAINS_H_
