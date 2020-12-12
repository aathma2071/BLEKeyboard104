#ifndef BLECALLBACKS_H
#define BLECALLBACKS_H

#include <BLEServer.h>
#include "BLE2902.h"
#include "BLECharacteristic.h"

class BLECallbacks : public BLEServerCallbacks
{

public:
    BLECallbacks(void);
    bool connected = false;
    void onConnect(BLEServer *pServer);
    void onDisconnect(BLEServer *pServer);
    BLECharacteristic *inputKeyboard;
    BLECharacteristic *outputKeyboard;
    BLECharacteristic *inputMediaKeys;
};

#endif //BLECALLBACKS_H