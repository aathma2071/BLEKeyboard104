#ifndef HIDKEYS
#define HIDKEYS

#include <Arduino.h>

#define IS_KEY_MOD_FN(row, col, fn_row, fn_col) ((row == fn_row) && (col == fn_col))

class JHIDKeys
{
public:
    uint8_t BLE_KEY_NONE = 0x00; // when no key is pressed.

    uint8_t BLE_KEY_FN = 0xaa;

    uint8_t BLE_KEY_A = 0x04; // Keyboard a and A
    uint8_t BLE_KEY_B = 0x05; // Keyboard b and B
    uint8_t BLE_KEY_C = 0x06; // Keyboard c and C
    uint8_t BLE_KEY_D = 0x07; // Keyboard d and D
    uint8_t BLE_KEY_E = 0x08; // Keyboard e and E
    uint8_t BLE_KEY_F = 0x09; // Keyboard f and F
    uint8_t BLE_KEY_G = 0x0a; // Keyboard g and G
    uint8_t BLE_KEY_H = 0x0b; // Keyboard h and H
    uint8_t BLE_KEY_I = 0x0c; // Keyboard i and I
    uint8_t BLE_KEY_J = 0x0d; // Keyboard j and J
    uint8_t BLE_KEY_K = 0x0e; // Keyboard k and K
    uint8_t BLE_KEY_L = 0x0f; // Keyboard l and L
    uint8_t BLE_KEY_M = 0x10; // Keyboard m and M
    uint8_t BLE_KEY_N = 0x11; // Keyboard n and N
    uint8_t BLE_KEY_O = 0x12; // Keyboard o and O
    uint8_t BLE_KEY_P = 0x13; // Keyboard p and P
    uint8_t BLE_KEY_Q = 0x14; // Keyboard q and Q
    uint8_t BLE_KEY_R = 0x15; // Keyboard r and R
    uint8_t BLE_KEY_S = 0x16; // Keyboard s and S
    uint8_t BLE_KEY_T = 0x17; // Keyboard t and T
    uint8_t BLE_KEY_U = 0x18; // Keyboard u and U
    uint8_t BLE_KEY_V = 0x19; // Keyboard v and V
    uint8_t BLE_KEY_W = 0x1a; // Keyboard w and W
    uint8_t BLE_KEY_X = 0x1b; // Keyboard x and X
    uint8_t BLE_KEY_Y = 0x1c; // Keyboard y and Y
    uint8_t BLE_KEY_Z = 0x1d; // Keyboard z and Z

    uint8_t BLE_KEY_1 = 0x1e; // Keyboard 1 and !
    uint8_t BLE_KEY_2 = 0x1f; // Keyboard 2 and @
    uint8_t BLE_KEY_3 = 0x20; // Keyboard 3 and #
    uint8_t BLE_KEY_4 = 0x21; // Keyboard 4 and $
    uint8_t BLE_KEY_5 = 0x22; // Keyboard 5 and %
    uint8_t BLE_KEY_6 = 0x23; // Keyboard 6 and ^
    uint8_t BLE_KEY_7 = 0x24; // Keyboard 7 and &
    uint8_t BLE_KEY_8 = 0x25; // Keyboard 8 and *
    uint8_t BLE_KEY_9 = 0x26; // Keyboard 9 and (
    uint8_t BLE_KEY_0 = 0x27; // Keyboard 0 and )

    uint8_t BLE_KEY_ENTER = 0x28;      // Keyboard Return
    uint8_t BLE_KEY_ESC = 0x29;        // Keyboard ESCAPE
    uint8_t BLE_KEY_BACKSPACE = 0x2a;  // Keyboard DELETE (Backspace)
    uint8_t BLE_KEY_TAB = 0x2b;        // Keyboard Tab
    uint8_t BLE_KEY_SPACE = 0x2c;      // Keyboard Spacebar
    uint8_t BLE_KEY_MINUS = 0x2d;      // Keyboard - and _
    uint8_t BLE_KEY_EQUAL = 0x2e;      // Keyboard = and +
    uint8_t BLE_KEY_LEFTBRACE = 0x2f;  // Keyboard [ and {
    uint8_t BLE_KEY_RIGHTBRACE = 0x30; // Keyboard ] and }
    uint8_t BLE_KEY_BACKSLASH = 0x31;  // Keyboard \ and |
    uint8_t BLE_KEY_HASHTILDE = 0x32;  // Keyboard Non-US # and ~
    uint8_t BLE_KEY_SEMICOLON = 0x33;  // Keyboard ; and :
    uint8_t BLE_KEY_APOSTROPHE = 0x34; // Keyboard ' and "
    uint8_t BLE_KEY_GRAVE = 0x35;      // Keyboard ` and ~
    uint8_t BLE_KEY_COMMA = 0x36;      // Keyboard , and <
    uint8_t BLE_KEY_DOT = 0x37;        // Keyboard . and >
    uint8_t BLE_KEY_SLASH = 0x38;      // Keyboard /
    uint8_t BLE_KEY_CAPSLOCK = 0x39;   // Keyboard Caps Lock

    uint8_t BLE_KEY_F1 = 0x3a;  // Keyboard F1
    uint8_t BLE_KEY_F2 = 0x3b;  // Keyboard F2
    uint8_t BLE_KEY_F3 = 0x3c;  // Keyboard F3
    uint8_t BLE_KEY_F4 = 0x3d;  // Keyboard F4
    uint8_t BLE_KEY_F5 = 0x3e;  // Keyboard F5
    uint8_t BLE_KEY_F6 = 0x3f;  // Keyboard F6
    uint8_t BLE_KEY_F7 = 0x40;  // Keyboard F7
    uint8_t BLE_KEY_F8 = 0x41;  // Keyboard F8
    uint8_t BLE_KEY_F9 = 0x42;  // Keyboard F9
    uint8_t BLE_KEY_F10 = 0x43; // Keyboard F10
    uint8_t BLE_KEY_F11 = 0x44; // Keyboard F11
    uint8_t BLE_KEY_F12 = 0x45; // Keyboard F12

    uint8_t BLE_KEY_SYSRQ = 0x46;      // Keyboard Print Screen
    uint8_t BLE_KEY_SCROLLLOCK = 0x47; // Keyboard Scroll Lock
    uint8_t BLE_KEY_PAUSE = 0x48;      // Keyboard Pause
    uint8_t BLE_KEY_INSERT = 0x49;     // Keyboard Insert
    uint8_t BLE_KEY_HOME = 0x4a;       // Keyboard Home
    uint8_t BLE_KEY_PAGEUP = 0x4b;     // Keyboard Page Up
    uint8_t BLE_KEY_DELETE = 0x4c;     // Keyboard Delete Forward
    uint8_t BLE_KEY_END = 0x4d;        // Keyboard End
    uint8_t BLE_KEY_PAGEDOWN = 0x4e;   // Keyboard Page Down
    uint8_t BLE_KEY_RIGHT = 0x4f;      // Keyboard Right Arrow
    uint8_t BLE_KEY_LEFT = 0x50;       // Keyboard Left Arrow
    uint8_t BLE_KEY_DOWN = 0x51;       // Keyboard Down Arrow
    uint8_t BLE_KEY_UP = 0x52;         // Keyboard Up Arrow

    uint8_t BLE_KEY_NUMLOCK = 0x53;    // Keyboard Num Lock and Clear
    uint8_t BLE_KEY_KPSLASH = 0x54;    // Keypad /
    uint8_t BLE_KEY_KPASTERISK = 0x55; // Keypad *
    uint8_t BLE_KEY_KPMINUS = 0x56;    // Keypad -
    uint8_t BLE_KEY_KPPLUS = 0x57;     // Keypad +
    uint8_t BLE_KEY_KPENTER = 0x58;    // Keypad ENTER
    uint8_t BLE_KEY_KP1 = 0x59;        // Keypad 1 and End
    uint8_t BLE_KEY_KP2 = 0x5a;        // Keypad 2 and Down Arrow
    uint8_t BLE_KEY_KP3 = 0x5b;        // Keypad 3 and PageDn
    uint8_t BLE_KEY_KP4 = 0x5c;        // Keypad 4 and Left Arrow
    uint8_t BLE_KEY_KP5 = 0x5d;        // Keypad 5
    uint8_t BLE_KEY_KP6 = 0x5e;        // Keypad 6 and Right Arrow
    uint8_t BLE_KEY_KP7 = 0x5f;        // Keypad 7 and Home
    uint8_t BLE_KEY_KP8 = 0x60;        // Keypad 8 and Up Arrow
    uint8_t BLE_KEY_KP9 = 0x61;        // Keypad 9 and Page Up
    uint8_t BLE_KEY_KP0 = 0x62;        // Keypad 0 and Insert
    uint8_t BLE_KEY_KPDOT = 0x63;      // Keypad . and Delete

    uint8_t BLE_KEY_LEFTCTRL = 0xe0;   // Keyboard Left Control
    uint8_t BLE_KEY_LEFTSHIFT = 0xe1;  // Keyboard Left Shift
    uint8_t BLE_KEY_LEFTALT = 0xe2;    // Keyboard Left Alt
    uint8_t BLE_KEY_LEFTMETA = 0xe3;   // Keyboard Left GUI
    uint8_t BLE_KEY_RIGHTCTRL = 0xe4;  // Keyboard Right Control
    uint8_t BLE_KEY_RIGHTSHIFT = 0xe5; // Keyboard Right Shift
    uint8_t BLE_KEY_RIGHTALT = 0xe6;   // Keyboard Right Alt
    uint8_t BLE_KEY_RIGHTMETA = 0xe7;  // Keyboard Right GUI

    //modifier keys array for checking
    uint8_t BLE_KEY_MODIFIERS[8] = {BLE_KEY_LEFTCTRL,BLE_KEY_LEFTSHIFT,BLE_KEY_LEFTALT,BLE_KEY_LEFTMETA,BLE_KEY_RIGHTCTRL,BLE_KEY_RIGHTSHIFT,BLE_KEY_RIGHTALT,BLE_KEY_RIGHTMETA};
};

extern JHIDKeys HIDKeys;
#endif //HIDKEYS