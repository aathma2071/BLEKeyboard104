#ifndef PINOUTS_H
#define PINOUTS_H

#include <Arduino.h>

class JPinouts
{
public:

    //for OLED screen
    uint8_t I2C_ADDRESS = 0x3c;
    uint8_t PIN_SDA = 0;
    uint8_t PIN_SCL = 1;
    //For battery monitoring
    uint8_t PIN_BATMON = 2;

    //For rows and columns
    uint8_t PIN_0 = 0;
    uint8_t PIN_1 = 1;
    uint8_t PIN_2 = 2;
    uint8_t PIN_3 = 3;
    uint8_t PIN_4 = 4;
    uint8_t PIN_5 = 5;
    uint8_t PIN_12 = 12;
    uint8_t PIN_13 = 13;
    uint8_t PIN_14 = 14;
    uint8_t PIN_15 = 15;
    uint8_t PIN_16 = 16;
    uint8_t PIN_17 = 17;
    uint8_t PIN_18 = 18;
    uint8_t PIN_19 = 19;
    uint8_t PIN_21 = 21;
    uint8_t PIN_22 = 22;
    uint8_t PIN_23 = 23;
    uint8_t PIN_25 = 25;
    uint8_t PIN_26 = 26;
    uint8_t PIN_27 = 27;
    uint8_t PIN_32 = 32;
    uint8_t PIN_33 = 33;
    uint8_t PIN_34 = 34;
    uint8_t PIN_35 = 35;
    ;
    uint8_t PIN_36 = 36;
    uint8_t PIN_39 = 39;

    //For FN Key modifier
    uint8_t KEY_MOD_FN_ROW = 22;
    uint8_t KEY_MOD_FN_COL = 33;
};

extern JPinouts pinouts;

#endif //PINOUTS_H