#include <Arduino.h>
#include <BleKeyboard.h>
#include "keymap.h"
#include <driver/rtc_cntl.h>
#include <driver/rtc_io.h>
#include <driver/gpio.h>
#include <Wire.h>
#include "SSD1306Wire.h"
#include "OLEDDisplayUi.h"

BleKeyboard bleKeyboard("2071Keyboard", "aathma2071");

SSD1306Wire display(0x3c, 18, 19);

OLEDDisplayUi ui(&display);

const uint8_t PHYSDELAY = 40;
const uint8_t BATLEVEL = 5;

uint16_t physicalDelay = 0;

//Key state for detecting presses
// when presses this will be set to true and at release it will be set to false.
bool keystates[ROWS][COLS] = {false};

//modifiers
bool shiftPressed = false;
bool capsLockOn = false;
bool numLockOn = false;
bool scrlLockOn = false;

bool setupDone = false;

//battery charging animation
uint16_t batteryLevel = 5;
uint16_t chargingLevel = 0;




void setup()
{
  delay(1000);
  Serial.begin(9600);
  Serial.write("Started Serial Monitoring in 9600 bauds");

  /*
   *Initialize the OLED display for dashboard
   * The Display is 128x64 (Safe size would be 123x63)
   */
  ui.setTargetFPS(60);
  ui.setIndicatorPosition(BOTTOM);
  ui.setIndicatorDirection(LEFT_RIGHT);
  ui.init();
  display.flipScreenVertically();

  // battery charging 
  chargingLevel = batteryLevel;

  //Pin initialization for Key matrix scan
  for (uint8_t i = 0; i < ROWS; i++)
  {
    pinMode(rowp[i], INPUT);
  }
  for (uint8_t i = 0; i < COLS; i++)
  {
    pinMode(colp[i], OUTPUT);
  }

  for (uint8_t i = 0; i < ROWS; i++)
  {
    for (uint8_t j = 0; j < COLS; j++)
    {
      keystates[i][j] = false;
    }
  }
  capsLockOn = false;
  numLockOn = false;
  scrlLockOn = false;

  bleKeyboard.begin();
  setupDone = true;
}

/*
 * Function to Draw the Bluetooth Symbol
 * Icon size : 15x32 to fit in 16x32
 */

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

/* Function to draw the battery Symbol 32x32 */
void drawBattery(uint16_t x,uint16_t y,uint16_t level)
{
  y = y+15;
  uint8_t w = 24;
  uint8_t h = 17;
  //max levels are 6
  display.drawRect(x, y, w, h);
  display.fillRect(x+w+1, y + 4, 2, 10);
  for (uint16_t i = 0; i <= level; i++)
  {
    uint16_t xVal = x+3 + (4 * (i - 1));
    Serial.println(xVal);
    display.fillRect(xVal, y + 4, 2, 10);
  }
}

/* to monitor battery and update the screen */
void monitorBattery(uint16_t x,uint16_t y,bool charging)
{
  if(charging){
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
  drawBattery(x,y,chargingLevel);
  } else {
    drawBattery(x,y, batteryLevel);
  }
}

void drawCaps(uint16_t x,uint16_t y,bool enabled)
{
  if (enabled)
  {
    display.setFont(ArialMT_Plain_24);
    display.drawString(x+2, y+2, "A");
    //display.drawRect(x, y, 20, 31);
  }
}

void drawNum(uint16_t x,uint16_t y,bool enabled)
{
  if (enabled)
  {
    display.setFont(ArialMT_Plain_24);
     display.drawString(x+2, y+2, "1");
    //display.drawRect(x, y, 20, 31);
  }
}

void drawScrl(uint16_t x,uint16_t y,bool enabled)
{
  if (enabled)
  {
    display.setFont(ArialMT_Plain_24);
     display.drawString(x+2, y+2, "S");
    //display.drawRect(x, y, 20, 31);
  }
}
void loop()
{
  display.clear();
  monitorBattery(96,0,true);
  drawNum(18,0,true);
  drawCaps(39,0,true);
  drawScrl(60,0,true);
  if (bleKeyboard.isConnected())
  {
    drawBluetooth(0,0,true);
    if (setupDone)
    {
      if (capsLockOn)
      {
        bleKeyboard.press(KEY_CAPS_LOCK);
        bleKeyboard.release(KEY_CAPS_LOCK);
      }

      /* commenting this as the T-vk's ble keyboard framework does not have sufficient key codes for the firmware
will try to fork from T-vk's library to get more stuff
      if (numLockOn)
      {
        bleKeyboard.press(KEY_NUM_LOCK);
        bleKeyboard.release(KEY_NUM_LOCK);
      }

      if (scrlLockOn)
      {
        bleKeyboard.press(KEY_SCRL_LOCK);
        bleKeyboard.release(KEY_SCRL_LOCK);
      }
    }
*/
      /*Scanning mechanism
    The mechanism is simple, we set the output pins (rows) to high one by one 
    and try to see whether the circuit closes. For anti-ghosting we need to include
    switching diodes (1N4148) between the switches.
    */
      for (uint8_t col = 0; col < COLS; col++)
      {
        //set the col pins high for scanning
        digitalWrite(colp[col], HIGH);

        //start scannign rows
        for (uint8_t row = 0; row < ROWS; row++)
        {
          //reading the state of the pressed key
          bool pressedKeyState = digitalRead(rowp[row]);

          //for debouncing and ensuring that the key is pressed only once
          if (pressedKeyState != keystates[row][col])
          {
            keystates[row][col] = pressedKeyState;
            //proceed only if pressedkeystate is true
            if (pressedKeyState)
            {
              String str = "Pressed ";
              Serial.println(str + rowp[row] + ":" + colp[col] + ":" + pressedKeyState);
              keystates[row][col] = true;
            }
            else
            {
              String str = "Released";
              //Serial.println(str +row + ":" + col);
              keystates[row][col] = false;
            }
          }
        }
        //scanning rows end
        //reset the col pin after scanning
        digitalWrite(colp[col], LOW);
      }
    }
    else
    {
      capsLockOn = false;
      numLockOn = false;
      scrlLockOn = false;
      setupDone = true;
    }
  }
  display.display();
}
