#include <Arduino.h>
#include "jeeno/jeeno.h"

void setup(){
    jeeno.begin();
}

void loop(){
  jeeno.loop();
}