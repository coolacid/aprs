void WebServer_Root() {
  String message = "Hello World!\n\n";
  message += "URI: ";
  message += webServer.uri();

  webServer.send(404, "text/plain", message);
}

void WebServer_NotFound() {
  String message = "I'm sorry, Dave. I'm afraid I can't do that.\n\n";
  message += "URI: ";
  message += webServer.uri();
  message += "\nMethod: ";
  message += ( webServer.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += webServer.args();
  message += "\n";

  for ( uint8_t i = 0; i < webServer.args(); i++ ) {
    message += " " + webServer.argName ( i ) + ": " + webServer.arg ( i ) + "\n";
  }

  webServer.send(404, "text/plain", message);
}

void SetupWebServer()
{
  webServer.on( "/", WebServer_Root );
  webServer.onNotFound( WebServer_NotFound );
  webServer.begin();
}

void SetupDNSServer() {
  // Setup some DNS
  dnsServer.setTTL(300);
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
  dnsServer.start(DNS_Port, DNS_Name, apIP);
}

void setupWiFi()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(WiFiSSID, WiFiAPPSK);
}

