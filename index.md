Firmware for ESP32 based devkit boards.

# Why this project?
Well, I had a cheap and busted mechanical keyboard which I did not want to throw away just because it is a mechanical keyboard (Although the key switches are not that great). Initially I thought of salvaging the key switches to make some kind of bluetooth macro keyboard that can be used in tandem with my main keyboard. However I did not have the time nor patience to design a keyboard for my needs, instead I thought of converting the entire 104 key standard keyboard to wireless via ESP32.

**This project is still early in development and not all listed features are present**

## Progress 27-Dec-2020:
Took a little christmas break. I have solved the problem with pins 36 and 39, it can be used a reliable digital input when we use a 47k external pulldown resistor. I learned that it is good to use external pulldown resistors for all the inputs that you have in ESP32. The pins 0, 1 and 3 can be used when serial and touch controls are not used. My shipment is still late, now it shows a delivery date in Jan 2021. So, I have utilized this time to do some house keeping in the code and design the PCB. I have to say, designing a PCB is easier said than done, I had trouble with almost all the areas. One good thing though is that I have access to a screen printing press, so I have developed a screen for the PCB and it is good so far. I still have not started manufacturing the PCB yet. I know that I can use some Chinese PCB manufacturing company to get my PCB's which is hassle free and very professional, but in the current geopolitical scene, relations between India and China are not exactly amicable. So, self manufacturing it is. I will post the entire board once I get atleast one revision correct on the board. That's it for now. Happy Holidays. Cheers.

## Progress 13-Dec-2020 :
The shipment for a I2C compatible MCP23017 is late. It would not arrive until late next week.So, what did I do, explore the board to check if I can someway use all the pins that are driving me crazy. With a little bit of digging I found out that if I donot initialize Arduino.Serial or any serial on the ESP32 for that matter we can use the 1 and 3 pins for ouput effectively (not inputs). The pin 0 is an internal touch sensor which can be used as an output pin. So, I have 3 outpins, which I can use for columns as I have the diodes on col to row configuration in my key matrix. Now about the pins 36 and 39, I got really frustrated with them and trying different combinations did not yield anything. Then it struck me, as there are no pullup or pull down resistors internally for the pins 36 and 39, why cant I externally pull down the inputs and check. It worked. I now have the required 23 pins for the key matrix (12x11). Not just 23 pins, with an extra 3 pins for the OLED screen and battery monitoring. I continued working on the firmware and it is now in a position where it is working with a sigle layer. Got a busy week ahead. I should find some time to finish the OLED functionality. Till then. Cheers.

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
