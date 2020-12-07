# BLEKeyboard104

Firmware for ESP32 based devkit boards.

**This project is still early in development and not all listed features are present**

## Features
- 2 layers (1 layer for standard keyboard layout and the other for Fn modified functions)
- Software debouncing
- Macros
- In device macro management
- support for OLED or LCD screens
- Support for media keys
- Support for OTA firmware updates
- Possibily better support for iOS and Android

## Building
- clone or download the repository.
- Open the repository in Platform IO
- open src/main.cpp and run build.
- Upload the code to connected ESP-32 Board

## TODO
- [ ] Implement a key map/matrix generator
- [ ] Implement a key matrix scanner
- [x] Implement BLE connectivity
- [x] Implement screen functionality
- [ ] Implement Macro functionality
- [ ] Implement Keyboard modes (basically for setting the macros or updating the firmware)


## Current key matrix pin config



## Credits and thanks to:
- Asterics for a detailed implementation of esp_32_mouse keyboard: https://github.com/asterics/esp32_mouse_keyboard/blob/master/README.md
- T-vK for the awesome ESP32 BLE Keyboard library: https://github.com/T-vK/ESP32-BLE-Keyboard
- BAN0008 for an arduino based keyboard firmware: https://github.com/BAN0008/Keyboard-Firmware
- rokrodic for usb keyboard firmware: https://github.com/rokrodic/USB-Keyboard
- blahlicus for an awesome keyboard firmware: https://github.com/blahlicus/animus-family