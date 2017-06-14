#ifndef WEBSERVER_H_
#define WEBSERVER_H_

void WebServer_Root();
void WebServer_NotFound();
void SetupWebServer();
void SetupDNSServer();
void setupWiFi();

extern IPAddress apIP;
extern ESP8266WebServer webServer;
extern DNSServer dnsServer;

#endif // WEBSERVER_H_
