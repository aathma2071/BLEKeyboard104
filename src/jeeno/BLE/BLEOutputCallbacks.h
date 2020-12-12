#ifndef BLEOUTPUTCALLBACKS_H
#define BLEOUTPUTCALLBACKS_H

#include <BLEServer.h>
#include "BLE2902.h"
#include "BLECharacteristic.h"

class BLEOutputCallbacks : public BLECharacteristicCallbacks
{
public:
  BLEOutputCallbacks(void);
  void onWrite(BLECharacteristic* me);
};

#endif //BLEOUTPUTCALLBACKS_H