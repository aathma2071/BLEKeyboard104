#include "BLEOutputCallbacks.h"
#include "esp_log.h"
static const char *LOG_TAG = "BLEDevice";

BLEOutputCallbacks::BLEOutputCallbacks(void)
{
  //empty constructor
}

void BLEOutputCallbacks::onWrite(BLECharacteristic *me)
{
  uint8_t *value = (uint8_t *)(me->getValue().c_str());
  ESP_LOGI(LOG_TAG, "special keys: %d", *value);
}