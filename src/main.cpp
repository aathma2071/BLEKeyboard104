#include <Arduino.h>
#include "jeeno/pinouts.h"
#include "jeeno/keymap.h"
#include "SSD1306Wire.h"
#include "OLEDDisplayUi.h"
#include "jeeno/BLE/BLEKeyboard.h"
#include <Adafruit_MCP23017.h>

#define BATLEVEL 5
#define PHYSDELAY 60

//Keyboard library
BLEKeyboard bleKeyboard("2071", "aathma2071", 100, false);

//for io mux-demux
Adafruit_MCP23017 mcpr;
Adafruit_MCP23017 mcpc;

//For OLED Screen
SSD1306Wire display(pinouts.I2C_ADDRESS,pinouts.PIN_SDA,pinouts.PIN_SCL);
OLEDDisplayUi ui(&display);

bool keystates[ROWS][COLS];
uint8_t physicalDelay = 0;
uint8_t chargingLevel = 0;
uint8_t batteryLevel = 0;

void setup(){
#if defined(DEBUG)
    Serial.begin(9600);
    Serial.write("Started Serial Monitoring in 9600 bauds");
#endif

    mcpr.begin();
    mcpc.begin();

    for (uint8_t i = 0; i < ROWS; i++)
    {
        mcpr.pinMode(keymap.rowp[i], INPUT);
    }
    for (uint8_t i = 0; i < COLS; i++)
    {
        mcpc.pinMode(keymap.colp[i], OUTPUT);
    }

    for (uint8_t i = 0; i < ROWS; i++)
    {
        for (uint8_t j = 0; j < COLS; j++)
        {
            keystates[i][j] = false;
        }
    }

    //initialize OLED screen
    ui.setTargetFPS(60);
    ui.setIndicatorPosition(BOTTOM);
    ui.setIndicatorDirection(LEFT_RIGHT);
    ui.init();
    display.flipScreenVertically();
    
    bleKeyboard.connect(1); // handle multiple servers
}


void scanMatrix()
{
    //re-initialize the row pins. From keypad.h
    for (uint8_t i = 0; i < ROWS; i++)
    {
        mcpr.pinMode(keymap.rowp[i], INPUT);
    }

    for (uint8_t col = 0; col < COLS; col++)
    {
        mcpc.pinMode(keymap.colp[col], OUTPUT);
        mcpc.digitalWrite(keymap.colp[col], HIGH);

        for (uint8_t row = 0; row < ROWS; row++)
        {
            bool pressedKeyState = mcpr.digitalRead(keymap.rowp[row]);
            if (pressedKeyState != keystates[row][col])
            {
                keystates[row][col] = pressedKeyState;
                if (pressedKeyState)
                {
                    bleKeyboard.press(keymap.SCAN_CODES[row][col]);
                    String str = "Pressed : (";
                    Serial.println(str + (row + 1) + ":" + (col + 1) + ")(" + keymap.rowp[row] + ":" + keymap.colp[col] + ")(" + keymap.SCAN_CODES[row][col] + ")");
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
        mcpc.digitalWrite(keymap.colp[col], LOW);
        mcpc.pinMode(keymap.colp[col], INPUT);
    }
}

void drawBluetooth(uint16_t x, uint16_t y, bool enabled)
{
    if (enabled)
    {
        display.drawLine(x + 7, y, x + 7, y + 32);
        display.drawLine(x + 7, y, x + 15, y + 8);
        display.drawLine(x + 15, y + 8, x, y + 24);
        display.drawLine(x, y + 8, x + 15, y + 24);
        display.drawLine(x + 7, y + 32, x + 15, y + 24);
    }
}

void drawBattery(uint16_t x, uint16_t y, uint16_t level)
{
    y = y + 15;
    uint8_t w = 24;
    uint8_t h = 17;
    //max levels are 6
    display.drawRect(x, y, w, h);
    display.fillRect(x + w + 1, y + 4, 2, 10);
    for (uint16_t i = 0; i <= level; i++)
    {
        uint16_t xVal = x + 3 + (4 * (i - 1));
        Serial.println(xVal);
        display.fillRect(xVal, y + 4, 2, 10);
    }
}

void monitorBattery(uint16_t x, uint16_t y, bool charging)
{
    if (charging)
    {
        if (physicalDelay == PHYSDELAY)
        {
            physicalDelay = 0;
            if (chargingLevel == BATLEVEL)
            {
                chargingLevel = 0;
            }
            else
            {
                chargingLevel++;
            }
        }
        else
        {
            physicalDelay++;
        }
        drawBattery(x, y, chargingLevel);
    }
    else
    {
        drawBattery(x, y, batteryLevel);
    }
}

void drawCaps(uint16_t x, uint16_t y, bool enabled)
{
    if (enabled)
    {
        display.setFont(ArialMT_Plain_24);
        display.drawString(x + 2, y + 2, "A");
        display.drawRect(x, y, 20, 31);
    }
}

void drawNum(uint16_t x, uint16_t y, bool enabled)
{
    if (enabled)
    {
        display.setFont(ArialMT_Plain_24);
        display.drawString(x + 2, y + 2, "1");
        display.drawRect(x, y, 20, 31);
    }
}

void drawScrl(uint16_t x, uint16_t y, bool enabled)
{
    if (enabled)
    {
        display.setFont(ArialMT_Plain_24);
        display.drawString(x + 2, y + 2, "S");
        display.drawRect(x, y, 20, 31);
    }
}

uint8_t getBatteryLevel(void)
{

    return 0;
}


void loop(){
  monitorBattery(1, 1, false);
    if (bleKeyboard.isConnected())
    {
        scanMatrix();
    }
}