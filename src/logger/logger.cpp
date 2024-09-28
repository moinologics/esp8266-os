#include <WebSerial.h>

void log(const char* value) {
  Serial.print(value);
  WebSerial.print(value);
}

void logln(const char* value) {
  Serial.println(value);
  WebSerial.println(value);
}

void logf(const char* format, ...) {
  va_list args;
  va_start(args, format);  
  Serial.printf(format, args);
  WebSerial.printf(format, args);
}