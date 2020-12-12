#ifndef JEENO_H
#define JEENO_H

#include <Arduino.h>
#include "BLE/BLEKeyboard.h"
#include "keymap.h"



class Jeeno{
    private:
        bool keystates[ROWS][COLS];
        void scanMatrix1(void);
    public:
        Jeeno(void);
        void begin(void);
        void loop(void);
        void scanMatrix(void);

};

extern Jeeno jeeno;

#endif //JEENO_H