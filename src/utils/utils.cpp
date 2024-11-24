#include <ESP8266WiFi.h>

String getLastNChars(String str, unsigned int n) {
  if (str.length() < n) {
    return str;
  }
  return str.substring(str.length() - n);
}

String getChipMacAddress() {
  return WiFi.macAddress();
}

String getHostName() {
  String hostName = getChipMacAddress();
  hostName.replace(":", "");
  hostName.toLowerCase();
  hostName = "esp-" + getLastNChars(hostName, 6);
  return hostName;
}