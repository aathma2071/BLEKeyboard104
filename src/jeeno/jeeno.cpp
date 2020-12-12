#include "jeeno.h"

BLEKeyboard bleKeyboard("2071", "aathma2071", 100, false);

Jeeno::Jeeno(void)
{
    //Constructor for initializing certain values such as
}

void Jeeno::begin()
{
    //Serial.begin(9600);
    //Serial.write("Started Serial Monitoring in 9600 bauds");

    for (uint8_t i = 0; i < ROWS; i++)
    {
        pinMode(keymap.rowp[i], INPUT);
    }
    for (uint8_t i = 0; i < COLS; i++)
    {
        pinMode(keymap.colp[i], OUTPUT);
    }

    for (uint8_t i = 0; i < ROWS; i++)
    {
        for (uint8_t j = 0; j < COLS; j++)
        {
            keystates[i][j] = false;
        }
    }

    bleKeyboard.connect(1); // have to decide on how to handle the keys and 
}

void Jeeno::loop()
{
    if(bleKeyboard.isConnected()){
        scanMatrix();
    }
    
}

void Jeeno::scanMatrix()
{
    for (uint8_t col = 0; col < COLS; col++)
    {
        digitalWrite(keymap.colp[col], HIGH);

        for (uint8_t row = 0; row < ROWS; row++)
        {
            bool pressedKeyState = digitalRead(keymap.rowp[row]);
            if (pressedKeyState != keystates[row][col])
            {
                keystates[row][col] = pressedKeyState;
                if (pressedKeyState)
                {
                    bleKeyboard.press(keymap.SCAN_CODES[row][col]);
                    //String str = "Pressed : (";
                    //Serial.println(str + (row+1) + ":" + (col+1) + ")("+keymap.rowp[row] + ":" + keymap.colp[col]+")("+keymap.SCAN_CODES[row][col]+")");
                    keystates[row][col] = true;
                    delay(50); // for debounce -- have to check with key matrix
                }
                else
                {
                    bleKeyboard.release(keymap.SCAN_CODES[row][col]);
                    keystates[row][col] = false;
                }
            }
        }
        digitalWrite(keymap.colp[col], LOW);
    }
}

Jeeno jeeno;