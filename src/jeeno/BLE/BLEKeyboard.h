#ifndef BLEKEYBOARD_H
#define BLEKEYBOARD_H

#include "BLECallbacks.h"
#include "BLEHIDDevice.h"
#include "BLECharacteristic.h"


typedef struct
{
    uint8_t modifiers;
    uint8_t reserved;
    uint8_t keys[6];
} InputReport;

//THanks for manuelbl for this :)
typedef struct
{
    uint8_t led; //bitmask 1 for numlock, 2 for capslock, 4 for scrolllock; compose 8; kana 16
} OutputReport;

//Media key reports
typedef uint8_t MediaReport[2];

const MediaReport KEY_MEDIA_NEXT_TRACK = {1, 0};
const MediaReport KEY_MEDIA_PREVIOUS_TRACK = {2, 0};
const MediaReport KEY_MEDIA_STOP = {4, 0};
const MediaReport KEY_MEDIA_PLAY_PAUSE = {8, 0};
const MediaReport KEY_MEDIA_MUTE = {16, 0};
const MediaReport KEY_MEDIA_VOLUME_UP = {32, 0};
const MediaReport KEY_MEDIA_VOLUME_DOWN = {64, 0};
const MediaReport KEY_MEDIA_WWW_HOME = {128, 0};
const MediaReport KEY_MEDIA_LOCAL_MACHINE_BROWSER = {0, 1}; // Opens "My Computer" on Windows
const MediaReport KEY_MEDIA_CALCULATOR = {0, 2};
const MediaReport KEY_MEDIA_WWW_BOOKMARKS = {0, 4};
const MediaReport KEY_MEDIA_WWW_SEARCH = {0, 8};
const MediaReport KEY_MEDIA_WWW_STOP = {0, 16};
const MediaReport KEY_MEDIA_WWW_BACK = {0, 32};
const MediaReport KEY_MEDIA_CONSUMER_CONTROL_CONFIGURATION = {0, 64}; // Media Selection
const MediaReport KEY_MEDIA_EMAIL_READER = {0, 128};

class BLEKeyboard
{
private:
    BLECallbacks *conStatus;
    BLEHIDDevice *hid;
    BLECharacteristic *inputkb;
    BLECharacteristic *outputkb;
    BLECharacteristic *mediakb;
    InputReport _inReport;
    OutputReport _outReport;
    MediaReport _mediaReport;
    static void taskServer(void *pvParam);

public:
    BLEKeyboard(std::string deviceName = "2071 Keyboard", std::string deviceManufacturer = "Aathma2071", uint8_t batteryLevel = 100, bool multiDevice=false);
    void connect(uint8_t deviceNum);
    void disconnect(void);
    void sendReport(InputReport* keys);
    void sendReport(MediaReport* keys);
    size_t press(uint8_t k);
    size_t press(const MediaReport k);
    size_t release(uint8_t k);
    size_t release(const MediaReport k);
    void releaseAll(void);
    bool isConnected(void);
    void setBattery(uint8_t batteryPercentage);

    std::string deviceManufacturer;
    std::string deviceName;
    uint8_t deviceNum;
    uint8_t batteryPercentage;

    bool multiDevice;


protected:
    virtual void onStarted(BLEServer *pServer){};
};

#endif //BLEKEYBOARD_H