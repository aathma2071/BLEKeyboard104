#include "BLEKeyboard.h"
#include "BLECallbacks.h"
#include "BLEOutputCallbacks.h"
#include "HIDKeys.h"
#include "BLEDevice.h"

//from T-vK as we are using the HID descriptor from T-vK libraries.
#define KEYBOARD_ID 0x01
#define MEDIA_KEYS_ID 0x02

//from https://github.com/T-vK/ESP32-BLE-Keyboard/blob/master/BleKeyboard.cpp
// Thanks to T-vK
static const uint8_t _hidReportDescriptor[] = {
    USAGE_PAGE(1), 0x01, // USAGE_PAGE (Generic Desktop Ctrls)
    USAGE(1), 0x06,      // USAGE (Keyboard)
    COLLECTION(1), 0x01, // COLLECTION (Application)
    // ------------------------------------------------- Keyboard
    REPORT_ID(1), KEYBOARD_ID, //   REPORT_ID (1)
    USAGE_PAGE(1), 0x07,       //   USAGE_PAGE (Kbrd/Keypad)
    USAGE_MINIMUM(1), 0xE0,    //   USAGE_MINIMUM (0xE0)
    USAGE_MAXIMUM(1), 0xE7,    //   USAGE_MAXIMUM (0xE7)
    LOGICAL_MINIMUM(1), 0x00,  //   LOGICAL_MINIMUM (0)
    LOGICAL_MAXIMUM(1), 0x01,  //   Logical Maximum (1)
    REPORT_SIZE(1), 0x01,      //   REPORT_SIZE (1)
    REPORT_COUNT(1), 0x08,     //   REPORT_COUNT (8)
    HIDINPUT(1), 0x02,         //   INPUT (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    REPORT_COUNT(1), 0x01,     //   REPORT_COUNT (1) ; 1 byte (Reserved)
    REPORT_SIZE(1), 0x08,      //   REPORT_SIZE (8)
    HIDINPUT(1), 0x01,         //   INPUT (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    REPORT_COUNT(1), 0x05,     //   REPORT_COUNT (5) ; 5 bits (Num lock, Caps lock, Scroll lock, Compose, Kana)
    REPORT_SIZE(1), 0x01,      //   REPORT_SIZE (1)
    USAGE_PAGE(1), 0x08,       //   USAGE_PAGE (LEDs)
    USAGE_MINIMUM(1), 0x01,    //   USAGE_MINIMUM (0x01) ; Num Lock
    USAGE_MAXIMUM(1), 0x05,    //   USAGE_MAXIMUM (0x05) ; Kana
    HIDOUTPUT(1), 0x02,        //   OUTPUT (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    REPORT_COUNT(1), 0x01,     //   REPORT_COUNT (1) ; 3 bits (Padding)
    REPORT_SIZE(1), 0x03,      //   REPORT_SIZE (3)
    HIDOUTPUT(1), 0x01,        //   OUTPUT (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    REPORT_COUNT(1), 0x06,     //   REPORT_COUNT (6) ; 6 bytes (Keys)
    REPORT_SIZE(1), 0x08,      //   REPORT_SIZE(8)
    LOGICAL_MINIMUM(1), 0x00,  //   LOGICAL_MINIMUM(0)
    LOGICAL_MAXIMUM(1), 0x65,  //   LOGICAL_MAXIMUM(0x65) ; 101 keys
    USAGE_PAGE(1), 0x07,       //   USAGE_PAGE (Kbrd/Keypad)
    USAGE_MINIMUM(1), 0x00,    //   USAGE_MINIMUM (0)
    USAGE_MAXIMUM(1), 0x65,    //   USAGE_MAXIMUM (0x65)
    HIDINPUT(1), 0x00,         //   INPUT (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    END_COLLECTION(0),         // END_COLLECTION
    // ------------------------------------------------- Media Keys
    USAGE_PAGE(1), 0x0C,         // USAGE_PAGE (Consumer)
    USAGE(1), 0x01,              // USAGE (Consumer Control)
    COLLECTION(1), 0x01,         // COLLECTION (Application)
    REPORT_ID(1), MEDIA_KEYS_ID, //   REPORT_ID (3)
    USAGE_PAGE(1), 0x0C,         //   USAGE_PAGE (Consumer)
    LOGICAL_MINIMUM(1), 0x00,    //   LOGICAL_MINIMUM (0)
    LOGICAL_MAXIMUM(1), 0x01,    //   LOGICAL_MAXIMUM (1)
    REPORT_SIZE(1), 0x01,        //   REPORT_SIZE (1)
    REPORT_COUNT(1), 0x10,       //   REPORT_COUNT (16)
    USAGE(1), 0xB5,              //   USAGE (Scan Next Track)     ; bit 0: 1
    USAGE(1), 0xB6,              //   USAGE (Scan Previous Track) ; bit 1: 2
    USAGE(1), 0xB7,              //   USAGE (Stop)                ; bit 2: 4
    USAGE(1), 0xCD,              //   USAGE (Play/Pause)          ; bit 3: 8
    USAGE(1), 0xE2,              //   USAGE (Mute)                ; bit 4: 16
    USAGE(1), 0xE9,              //   USAGE (Volume Increment)    ; bit 5: 32
    USAGE(1), 0xEA,              //   USAGE (Volume Decrement)    ; bit 6: 64
    USAGE(2), 0x23, 0x02,        //   Usage (WWW Home)            ; bit 7: 128
    USAGE(2), 0x94, 0x01,        //   Usage (My Computer) ; bit 0: 1
    USAGE(2), 0x92, 0x01,        //   Usage (Calculator)  ; bit 1: 2
    USAGE(2), 0x2A, 0x02,        //   Usage (WWW fav)     ; bit 2: 4
    USAGE(2), 0x21, 0x02,        //   Usage (WWW search)  ; bit 3: 8
    USAGE(2), 0x26, 0x02,        //   Usage (WWW stop)    ; bit 4: 16
    USAGE(2), 0x24, 0x02,        //   Usage (WWW back)    ; bit 5: 32
    USAGE(2), 0x83, 0x01,        //   Usage (Media sel)   ; bit 6: 64
    USAGE(2), 0x8A, 0x01,        //   Usage (Mail)        ; bit 7: 128
    HIDINPUT(1), 0x02,           //   INPUT (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    END_COLLECTION(0)            // END_COLLECTION
};

//Task handles for connect and disconnect
xTaskHandle bleTask;

BLEKeyboard::BLEKeyboard(std::string deviceName, std::string deviceManufacturer, uint8_t batteryLevel, bool multiDevice) : hid(0)
{
    this->deviceName = deviceName;
    this->deviceManufacturer = deviceManufacturer;
    this->batteryPercentage = batteryLevel;
    this->multiDevice = multiDevice;
    this->conStatus = new BLECallbacks();
}

void BLEKeyboard::connect(uint8_t deviceNum)
{
    this->deviceNum = deviceNum;
    xTaskCreate(this->taskServer, "server", 20000, (void *)this, 5, &bleTask);
}

void BLEKeyboard::disconnect(void)
{
    // delete all the server instances
    vTaskDelay(200);
    vTaskDelete(bleTask);
}

bool BLEKeyboard::isConnected(void)
{
    return this->conStatus->connected;
}

void BLEKeyboard::setBattery(uint8_t level)
{
    this->batteryPercentage = level;
    if (hid != 0)
        this->hid->setBatteryLevel(this->batteryPercentage);
}

void BLEKeyboard::taskServer(void *pvParam)
{
    //create a ble device and the ble server
    BLEKeyboard *bleKBInstance = (BLEKeyboard *)pvParam;
    BLEDevice::init(bleKBInstance->deviceName);
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(bleKBInstance->conStatus);

    //define the HID instance 
    bleKBInstance->hid = new BLEHIDDevice(pServer);
    bleKBInstance->inputkb = bleKBInstance->hid->inputReport(KEYBOARD_ID);
    bleKBInstance->outputkb = bleKBInstance->hid->outputReport(KEYBOARD_ID);
    bleKBInstance->mediakb = bleKBInstance->hid->inputReport(MEDIA_KEYS_ID);
    bleKBInstance->conStatus->inputKeyboard = bleKBInstance->inputkb;
    bleKBInstance->conStatus->outputKeyboard = bleKBInstance->outputkb;
    bleKBInstance->conStatus->inputMediaKeys = bleKBInstance->mediakb;

    bleKBInstance->outputkb->setCallbacks(new BLEOutputCallbacks());

    bleKBInstance->hid->manufacturer()->setValue(bleKBInstance->deviceManufacturer);

    bleKBInstance->hid->pnp(0x02, 0xe502, 0xa111, 0x0210);
    bleKBInstance->hid->hidInfo(0x00, 0x01);

    BLESecurity *pSecurity = new BLESecurity();

    pSecurity->setAuthenticationMode(ESP_LE_AUTH_BOND);

    bleKBInstance->hid->reportMap((uint8_t *)_hidReportDescriptor, sizeof(_hidReportDescriptor));
    bleKBInstance->hid->startServices();

    bleKBInstance->onStarted(pServer);

    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->setAppearance(HID_KEYBOARD);
    pAdvertising->addServiceUUID(bleKBInstance->hid->hidService()->getUUID());
    pAdvertising->setScanResponse(false);
    pAdvertising->start();
    bleKBInstance->hid->setBatteryLevel(bleKBInstance->batteryPercentage);

    vTaskDelay(portMAX_DELAY); //delay(portMAX_DELAY);
}

void BLEKeyboard::sendReport(InputReport* k)
{
    if (this->isConnected())
    {
        this->inputkb->setValue((uint8_t *)k, sizeof(InputReport));
        this->inputkb->notify();
    }
}

void BLEKeyboard::sendReport(MediaReport* k)
{
    if (this->isConnected())
    {
        this->mediakb->setValue((uint8_t *)k, sizeof(MediaReport));
        this->mediakb->notify();
    }
}

size_t BLEKeyboard::press(uint8_t k)
{
    uint8_t i;
    bool modifierFound = false;
    // check if the pressed key is a modifier or key
    //if modifier add to modifier array else add to the keys

    for (i = 0; i < sizeof(HIDKeys.BLE_KEY_MODIFIERS); i++)
    {
        if (k == HIDKeys.BLE_KEY_MODIFIERS[i])
        {
            modifierFound = true;
            break;
        }
    }

    if (modifierFound)
    {
        _inReport.modifiers |= k;
    }

    if (_inReport.keys[0] != k && _inReport.keys[1] != k &&
        _inReport.keys[2] != k && _inReport.keys[3] != k &&
        _inReport.keys[4] != k && _inReport.keys[5] != k)
    {

        for (i = 0; i < 6; i++)
        {
            if (_inReport.keys[i] == 0x00)
            {
                _inReport.keys[i] = k;
                break;
            }
        }
    }

    sendReport(&_inReport);
    return 1;
}

size_t BLEKeyboard::release(uint8_t k)
{

    uint8_t i;
    bool modifierFound = false;
    // check if the pressed key is a modifier or key
    //if modifier add to modifier array else add to the keys

    for (i = 0; i < sizeof(HIDKeys.BLE_KEY_MODIFIERS); i++)
    {
        if (k == HIDKeys.BLE_KEY_MODIFIERS[i])
        {
            modifierFound = true;
            break;
        }
    }

    if (modifierFound)
    {
        _inReport.modifiers &= ~k;
    }

    for (i = 0; i < 6; i++)
    {
        if (0 != k && _inReport.keys[i] == k)
        {
            _inReport.keys[i] = 0x00;
        }
    }

    sendReport(&_inReport);
    return 1;
}

size_t BLEKeyboard::press(const MediaReport k)
{
    uint16_t k_16 = k[1] | (k[0] << 8);
    uint16_t mediaKeyReport_16 = _mediaReport[1] | (_mediaReport[0] << 8);

    mediaKeyReport_16 |= k_16;
    _mediaReport[0] = (uint8_t)((mediaKeyReport_16 & 0xFF00) >> 8);
    _mediaReport[1] = (uint8_t)(mediaKeyReport_16 & 0x00FF);

    sendReport(&_mediaReport);
    return 1;
}

size_t BLEKeyboard::release(const MediaReport k)
{
    uint16_t k_16 = k[1] | (k[0] << 8);
    uint16_t mediaKeyReport_16 = _mediaReport[1] | (_mediaReport[0] << 8);
    mediaKeyReport_16 &= ~k_16;
    _mediaReport[0] = (uint8_t)((mediaKeyReport_16 & 0xFF00) >> 8);
    _mediaReport[1] = (uint8_t)(mediaKeyReport_16 & 0x00FF);

    sendReport(&_mediaReport);
    return 1;
}

void BLEKeyboard::releaseAll(void)
{
    _inReport.keys[0] = 0;
    _inReport.keys[1] = 0;
    _inReport.keys[2] = 0;
    _inReport.keys[3] = 0;
    _inReport.keys[4] = 0;
    _inReport.keys[5] = 0;
    _inReport.modifiers = 0;
    sendReport(&_inReport);
}