#include <Arduino.h>

#include "../logger/logger.h"
#include "../water-level/water-level.h"

#define SOUND_VELOCITY 0.034  // cm/uS

#define TRIG 4  // GPIO5 (D2 in esp-12f)
#define ECHO 5  // GPIO4 (D1 in esp-12f)

float distance = 0.0;

void setup_sr04() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop_sr04() {
  digitalWrite(TRIG, LOW);  // Clears the trigPin condition
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  u_long timeout_us = 1000000;  // 1s

  u_long duration_us = pulseIn(ECHO, HIGH, timeout_us);

  if (duration_us == 0) {
    logf("sensor not connected?? TRIG=GPIO%d ECHO=GPIO%d\r\n", TRIG, ECHO);
    return;
  }

  distance = (duration_us * SOUND_VELOCITY) / 2;  // actual distance divided by 2 (go and back)

  logf("duration_us %lu, distance: %.2f cm\r\n", duration_us, distance);

  show_level(distance);
}