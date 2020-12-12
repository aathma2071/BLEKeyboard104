#include "JDisplay.h"
#include "pinouts.h"

SSD1306Wire screen(pinouts.I2C_ADDRESS, pinouts.PIN_SDA, pinouts.PIN_SCL,GEOMETRY_128_32);

void JDisplay::begin(){
   //screen.init();
}

JDisplay display;