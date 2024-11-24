#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ElegantOTA.h>
#include <WebSerial.h>

#include "../utils/utils.h"

const char* ssid = "LANister";
const char* password = "d4ef482a";

size_t ota_progress = 0;

void setup_ap() {
  String ssid = getHostName();
  ssid.toUpperCase();
  bool success = WiFi.softAP(ssid);
  if (!success) {
    Serial.println("unable to setup Basic AP");
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

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
}

void setup_mdns() {
  String hostName = getHostName();
  bool success = MDNS.begin(hostName);
  if (!success) {
    WebSerial.println("Error starting mDNS");
    return;
  }
  WebSerial.printf("mDNS started with hostname %s\r\n", hostName);
}

void setup_webserial(AsyncWebServer* server) {
  WebSerial.begin(server, "/");
  Serial.println("WebSerial route /");
}

void setup_ota(AsyncWebServer* server) {
  ElegantOTA.setAutoReboot(true);

  ElegantOTA.onStart([]() {
    Serial.println("OTA update process started.");
    ota_progress = 0;
  });
  ElegantOTA.onProgress([](size_t current, size_t total) {
    size_t progress = (current * 100) / total;
    if (progress > ota_progress) {
      Serial.printf("Progress: %u%%\r\n", progress);
      ota_progress = progress;
    }
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