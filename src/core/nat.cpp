#include <HardwareSerial.h>

// #if LWIP_FEATURES && !LWIP_IPV6

#include <ESP8266WiFi.h>
#include <lwip/napt.h>
#include <lwip/dns.h>

#include "../utils/utils.h"

#define NAPT 1000
#define NAPT_PORT 10

#define STA_SSID "extender"

const char* AP_PSK = "18273645";

void setup_nat() {
  Serial.printf("---NAPT Range extender setup---\r\n");
  Serial.printf("Heap on start: %d\r\n", ESP.getFreeHeap());

  // assuming wifi is connected before this

  Serial.printf("STA: %s (dns: %s / %s)\r\n", WiFi.localIP().toString().c_str(), WiFi.dnsIP(0).toString().c_str(), WiFi.dnsIP(1).toString().c_str());

  String AP_SSID = getHostName();
  IPAddress AP_IP = IPAddress(10, 3, 0, 1);
  IPAddress AP_SUBNET = IPAddress(255, 255, 255, 0);

  auto& server = WiFi.softAPDhcpServer();
  server.setDns(WiFi.dnsIP(0));

  WiFi.softAPConfig(AP_IP, AP_IP, AP_SUBNET);
  WiFi.softAP(AP_SSID);
  Serial.printf("AP: %s\r\n", WiFi.softAPIP().toString().c_str());

  Serial.printf("Heap before: %d\r\n", ESP.getFreeHeap());
  err_t ret = ip_napt_init(NAPT, NAPT_PORT);
  Serial.printf("ip_napt_init(%d,%d): ret=%d (OK=%d)\r\n", NAPT, NAPT_PORT, (int)ret, (int)ERR_OK);
  if (ret == ERR_OK) {
    ret = ip_napt_enable_no(SOFTAP_IF, 1);
    Serial.printf("ip_napt_enable_no(SOFTAP_IF): ret=%d (OK=%d)\r\n", (int)ret, (int)ERR_OK);
    if (ret == ERR_OK) {
      Serial.printf("WiFi AP Network '%s' is up with Password '%s'\r\n", AP_SSID.c_str(), AP_PSK);
    }
  }
  Serial.printf("Heap after napt init: %d\r\n", ESP.getFreeHeap());
  if (ret != ERR_OK) {
    Serial.printf("NAPT initialization failed\r\n");
  }
  Serial.printf("---NAPT Range extender setup end---\r\n");
}

// #else

// void setup_nat() {
//   Serial.printf("NAPT not supported in this configuration\r\n");
// }

// #endif