#include "BLECallbacks.h"

BLECallbacks::BLECallbacks(void){
    //empty constructor
}

void BLECallbacks::onConnect(BLEServer* pServer){
    this->connected = false;
    BLE2902* desc = (BLE2902*)this->inputKeyboard->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
    desc->setNotifications(true);
}

void BLECallbacks::onDisconnect(BLEServer* pServer){
    this->connected = false;
    BLE2902* desc = (BLE2902*)this->inputKeyboard->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
    desc->setNotifications(false);
}