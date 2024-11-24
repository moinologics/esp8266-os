#include "../logger/logger.h"

const float DISTANCE_BW_TWO_PIPES_CM = 105;
const float MIN_DISTANCE_CM = 20;
const float MAX_DISTANCE_CM = MIN_DISTANCE_CM + DISTANCE_BW_TWO_PIPES_CM;

void show_level(float distance_cm) {
  float empty_height = distance_cm - MIN_DISTANCE_CM;
  float filled_height = DISTANCE_BW_TWO_PIPES_CM - empty_height;
  float filled_percent = (filled_height / DISTANCE_BW_TWO_PIPES_CM) * 100;

  logf("empty_height=%f filled_height=%f\r\n", empty_height, filled_height);
  logf("tank filled percentage: %.2f%\r\n", filled_percent);
}