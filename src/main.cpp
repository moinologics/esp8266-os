#include<Arduino.h>
#include "core/core.h"
#include "logger/logger.h"

void setup_main() {
  setup_core();

  // everything else goes here


  // setup end
  logln("setup end");
}

void loop_main() {
  loop_core();
  delay(100);
}