#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>

#include "../logger/logger.h"
#include "functions.h"
#include "nat.h"

AsyncWebServer server(80);

void setup_core() {
  Serial.begin(115200);
  Serial.println("");

  WiFi.mode(WIFI_STA);

  setup_ap();    // this will setup simple AP to reach to this device
  setup_wifi();
  setup_nat();  // this will re-setup AP with internet access 
  setup_webserial(&server);
  setup_ota(&server);

  server.begin();
  logln("HTTP server started");
}

void loop_core() {
  ElegantOTA.loop();
}