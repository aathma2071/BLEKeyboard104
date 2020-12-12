#ifndef JDISPLAY_H
#define JDISPLAY_H

#include <Wire.h>
#include <SSD1306Wire.h>
#include <OLEDDisplayUi.h>


class JDisplay
{
private:
    
public:
    void begin(void);
    void drawBluetooth(uint16_t x, uint16_t y, bool enabled);
    void drawBattery(uint16_t x, uint16_t y, uint16_t level);
    void drawCaps(uint16_t x, uint16_t y, bool enabled);
    void drawNum(uint16_t x, uint16_t y, bool enabled);
    void drawScrl(uint16_t x, uint16_t y, bool enabled);
};
extern JDisplay display;
/*

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

*/



#endif //JDISPLAY_H