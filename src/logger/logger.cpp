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

  // Estimate the required buffer size
  size_t size = vsnprintf(nullptr, 0, format, args) + 1; // Get required size (+1 for null terminator)

  va_end(args);  // End the va_list to reset it before using again

  // Dynamically allocate buffer for formatted string
  char* buffer = (char*)malloc(size);
  if (buffer == nullptr) {
    // Memory allocation failed, handle error
    const char* message = "Memory allocation failed in logf";
    Serial.println(message);
    WebSerial.println(message);
    return;
  }

  // Start the va_list again to format the string into the buffer
  va_start(args, format);
  vsnprintf(buffer, size, format, args);
  va_end(args);

  // Send the formatted string to Serial and WebSerial
  Serial.print(buffer);
  WebSerial.print(buffer);

  // Free the allocated memory
  free(buffer);
}