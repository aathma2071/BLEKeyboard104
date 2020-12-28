#ifndef KEYMAP_H
#define KEYMAP_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pinouts.h"
#include "BLE/HIDKeys.h"

#define ARRAY_LEN(x) (sizeof(x) / sizeof(x)[0])

//For 104 key standard keyboard
#define ROWS 12
#define COLS 11
#define DEBOUNCE_DELAY 5 // value in ms (milliseconds)

//Pin numbers

class JKeymap
{
public:
    const uint8_t rowp[ROWS] = {pinouts.GPA0,pinouts.GPA1,pinouts.GPA2,pinouts.GPA3,pinouts.GPA4,pinouts.GPA5,pinouts.GPA6,pinouts.GPA7,pinouts.GPB0,pinouts.GPB1,pinouts.GPB2,pinouts.GPB3};
    const uint8_t colp[COLS] = {pinouts.GPA0,pinouts.GPA1,pinouts.GPA2,pinouts.GPA3,pinouts.GPA4,pinouts.GPA5,pinouts.GPA6,pinouts.GPA7,pinouts.GPB0,pinouts.GPB1,pinouts.GPB2};

//debouncing delay


    /* switch matrix scan codes -  refer to HIDKeys.h for a complete referemce of the
scan codes. This has to be updated in tandem to the wiring of the keyboard */
    const uint8_t SCAN_CODES[ROWS][COLS] = {
                                      {HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_F2, HIDKeys.BLE_KEY_F4, HIDKeys.BLE_KEY_F6, HIDKeys.BLE_KEY_F8, HIDKeys.BLE_KEY_F10, HIDKeys.BLE_KEY_F12, HIDKeys.BLE_KEY_SCROLLLOCK, HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_NONE},
                                      {HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_1, HIDKeys.BLE_KEY_3, HIDKeys.BLE_KEY_5, HIDKeys.BLE_KEY_7, HIDKeys.BLE_KEY_9, HIDKeys.BLE_KEY_MINUS, HIDKeys.BLE_KEY_BACKSPACE, HIDKeys.BLE_KEY_HOME, HIDKeys.BLE_KEY_NUMLOCK, HIDKeys.BLE_KEY_KPASTERISK},
                                      {HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_Q, HIDKeys.BLE_KEY_E, HIDKeys.BLE_KEY_T, HIDKeys.BLE_KEY_U, HIDKeys.BLE_KEY_O, HIDKeys.BLE_KEY_LEFTBRACE, HIDKeys.BLE_KEY_BACKSLASH, HIDKeys.BLE_KEY_END, HIDKeys.BLE_KEY_KP7, HIDKeys.BLE_KEY_KP9},
                                      {HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_A, HIDKeys.BLE_KEY_D, HIDKeys.BLE_KEY_G, HIDKeys.BLE_KEY_J, HIDKeys.BLE_KEY_L, HIDKeys.BLE_KEY_APOSTROPHE, HIDKeys.BLE_KEY_ENTER, HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_KP4, HIDKeys.BLE_KEY_KP6},
                                      {HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_Z, HIDKeys.BLE_KEY_C, HIDKeys.BLE_KEY_B, HIDKeys.BLE_KEY_M, HIDKeys.BLE_KEY_DOT, HIDKeys.BLE_KEY_SLASH, HIDKeys.BLE_KEY_RIGHTSHIFT, HIDKeys.BLE_KEY_UP, HIDKeys.BLE_KEY_KP1, HIDKeys.BLE_KEY_KP3},
                                      {HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_LEFTMETA, HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_SPACE, HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_RIGHTALT, HIDKeys.BLE_KEY_FN, HIDKeys.BLE_KEY_RIGHTCTRL, HIDKeys.BLE_KEY_DOWN, HIDKeys.BLE_KEY_KP0, HIDKeys.BLE_KEY_KPDOT},
                                      {HIDKeys.BLE_KEY_ESC, HIDKeys.BLE_KEY_F1, HIDKeys.BLE_KEY_F3, HIDKeys.BLE_KEY_F5, HIDKeys.BLE_KEY_F7, HIDKeys.BLE_KEY_F9, HIDKeys.BLE_KEY_F11, HIDKeys.BLE_KEY_SYSRQ, HIDKeys.BLE_KEY_PAUSE, HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_NONE},
                                      {HIDKeys.BLE_KEY_GRAVE, HIDKeys.BLE_KEY_2, HIDKeys.BLE_KEY_4, HIDKeys.BLE_KEY_6, HIDKeys.BLE_KEY_8, HIDKeys.BLE_KEY_0, HIDKeys.BLE_KEY_EQUAL, HIDKeys.BLE_KEY_INSERT, HIDKeys.BLE_KEY_PAGEUP, HIDKeys.BLE_KEY_KPSLASH, HIDKeys.BLE_KEY_KPMINUS},
                                      {HIDKeys.BLE_KEY_TAB, HIDKeys.BLE_KEY_W, HIDKeys.BLE_KEY_R, HIDKeys.BLE_KEY_Y, HIDKeys.BLE_KEY_I, HIDKeys.BLE_KEY_P, HIDKeys.BLE_KEY_RIGHTBRACE, HIDKeys.BLE_KEY_DELETE, HIDKeys.BLE_KEY_PAGEDOWN, HIDKeys.BLE_KEY_KP8, HIDKeys.BLE_KEY_KPPLUS},
                                      {HIDKeys.BLE_KEY_CAPSLOCK, HIDKeys.BLE_KEY_S, HIDKeys.BLE_KEY_F, HIDKeys.BLE_KEY_H, HIDKeys.BLE_KEY_K, HIDKeys.BLE_KEY_SEMICOLON, HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_KP5, HIDKeys.BLE_KEY_NONE},
                                      {HIDKeys.BLE_KEY_LEFTSHIFT, HIDKeys.BLE_KEY_X, HIDKeys.BLE_KEY_V, HIDKeys.BLE_KEY_N, HIDKeys.BLE_KEY_COMMA, HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_KP2, HIDKeys.BLE_KEY_KPENTER},
                                      {HIDKeys.BLE_KEY_LEFTCTRL, HIDKeys.BLE_KEY_LEFTALT, HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_RIGHTMETA, HIDKeys.BLE_KEY_LEFT, HIDKeys.BLE_KEY_RIGHT, HIDKeys.BLE_KEY_NONE, HIDKeys.BLE_KEY_NONE}
                                      };
};

extern JKeymap keymap;
#endif //KEYMAP_H