Firmware for ESP32 based devkit boards.

# Why this project?
Well, I had a cheap and busted mechanical keyboard which I did not want to throw away just because it is a mechanical keyboard (Although the key switches are not that great). Initially I thought of salvaging the key switches to make some kind of bluetooth macro keyboard that can be used in tandem with my main keyboard. However I did not have the time nor patience to design a keyboard for my needs, instead I thought of converting the entire 104 key standard keyboard to wireless via ESP32.

**This project is still early in development and not all listed features are present**

## Progress 07-Dec-2020 :
Parts arrived late last week and I have started working with ESP32's GPIO. I have to say not everything in the datasheets are supposed to work the way it is meant. I realized with a frustrating amount of testing, that the pins 36,39,1,3,0 are internally tied to other sensors in the board such as Hall effect sensor and Touch sensors, which means I cannot use those as digital inputs without them actuating all the time. So, lesson learnt. Don't use more than 15 GPIO's. Now I have to figure out how to accomodate the required 23 pins. I could use a shift register but it too needs a large amount of pins and the speed is not reliable for this application. After a bit of poking around, I found that MCP23017 can be used to expand the GPIO of  ESP32, and the good thing is that, it is I2C compatible. I can daisy chain multiple chips to get as much as IO as I want. I have ordered some to test out. Will resume work once it arrives. Till then. Cheers.

## Progress 30-Nov-2020: 
Waiting for parts to arrive, ESP32 and a cheap I2C OLED screen. In the meanwhile, I'm gathering resources to see how to setup the key scan matrix. I wanted to use the least number of pins on the board as I also wanted to have battery monitoring and OLED Screen connected. The least amount of pins I want to get the key matrix working would be 23, as I was going to do a 11x12 key matrix which would give me a theoritical 122 keys. I have also started to get some code scaffolding going on and started scourging on Github to look for potential keyboard firmwares to understand them better. Fingers crossed.

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

## Credits and thanks to:
- Asterics for a detailed implementation of esp_32_mouse keyboard: https://github.com/asterics/esp32_mouse_keyboard/blob/master/README.md
- T-vK for the awesome ESP32 BLE Keyboard library: https://github.com/T-vK/ESP32-BLE-Keyboard
- BAN0008 for an arduino based keyboard firmware: https://github.com/BAN0008/Keyboard-Firmware
