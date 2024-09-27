#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>
#include <WebSerial.h>

const char* ssid = "LANister";
const char* password = "d4ef482a";

AsyncWebServer server(80);

void setup_core() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("connecting to wifi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());

  WebSerial.begin(&server, "/");
  Serial.println("WebSerial attached on /");
  ElegantOTA.begin(&server);
  Serial.println("ElegantOTA attached on /update");

  server.begin();
  Serial.println("HTTP server started");
}

void loop_core() {
  ElegantOTA.loop();
}