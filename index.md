Firmware for ESP32 based devkit boards.

# Why this project?
Well, I had a cheap and busted mechanical keyboard which I did not want to throw away just because it is a mechanical keyboard (Although the key switches are not that great). Initially I thought of salvaging the key switches to make some kind of bluetooth macro keyboard that can be used in tandem with my main keyboard. However I did not have the time nor patience to design a keyboard for my needs, instead I thought of converting the entire 104 key standard keyboard to wireless via ESP32.

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
- [ ] Implement screen functionality
- [ ] Implement Macro functionality
- [ ] Implement Keyboard modes (basically for setting the macros or updating the firmware)

## Credits and thanks to:
- Asterics for a detailed implementation of esp_32_mouse keyboard: https://github.com/asterics/esp32_mouse_keyboard/blob/master/README.md
- T-vK for the awesome ESP32 BLE Keyboard library: https://github.com/T-vK/ESP32-BLE-Keyboard
- BAN0008 for an arduino based keyboard firmware: https://github.com/BAN0008/Keyboard-Firmware
