#include <Arduino.h>
#include <AsyncTask.h>

#include "core/core.h"
#include "logger/logger.h"
#include "sr04/sr04.h"
#include "utils/utils.h"

AsyncTask asyncTask;

void setup_main() {
  setup_core();
  setup_sr04();

  // async tasks
  asyncTask.repeat(loop_sr04, 3000);

  logln("setup end");
}

void loop_main() {
  loop_core();
  asyncTask.loop();
  // delay(1000);
}