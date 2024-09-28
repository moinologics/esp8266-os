#include <ESP8266WiFi.h>
#include <ElegantOTA.h>
#include <WebSerial.h>

const char* ssid = "LANister";
const char* password = "d4ef482a";

void setup_ap() {
  String ssid = WiFi.macAddress();
  bool success = WiFi.softAP(ssid);
  if (!success) {
    Serial.println("unable to setup AP");
    return;
  }
  Serial.printf("Basic AP is up with ssid %s and IP Address %s\r\n", ssid.c_str(), WiFi.softAPIP().toString().c_str());
}

void setup_wifi() {
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
}

void setup_webserial(AsyncWebServer* server) {
  WebSerial.begin(server, "/");
  Serial.println("WebSerial route /");
}

void setup_ota(AsyncWebServer* server) {
  ElegantOTA.setAutoReboot(true);

  ElegantOTA.onStart([]() {
    Serial.println("OTA update process started.");
  });
  ElegantOTA.onProgress([](size_t current, size_t final) {
    Serial.printf("Progress: %u%%\r\n", (current * 100) / final);
  });
  ElegantOTA.onEnd([](bool success) {
    if (success) {
      Serial.println("OTA update completed successfully.");
    } else {
      Serial.println("OTA update failed.");
    }
  });

  ElegantOTA.begin(server);
  Serial.println("ElegantOTA route /update");
}