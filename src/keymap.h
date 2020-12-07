#ifndef KEYMAP_H
#define KEYMAP_H

//For 104 key standard keyboard
#define ROWS 12
#define COLS 11

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARRAY_LEN(x) (sizeof(x)/sizeof(x)[0])

const uint8_t rowp[ROWS] = {36,39,34,35,23,22,21,19,18,5,4,2};
const uint8_t colp[COLS] = {13,12,14,27,26,25,33,32,15,16,17};


//Fn key pin numbers
// should be changed for other keyboards depending on the matrix
#define KEY_MOD_FN_ROW 22
#define KEY_MOD_FN_COL 33

//debouncing delay
#define DEBOUNCE_DELAY 5 // value in ms (milliseconds)

//startup Parameters
//#define STARTUP_DELAY 2500 //Seems to be a standard startup delay. Have to investigate

//keycodes
//uint8_t keycodes[ROWS][COLS] = {{},}


//Structures for keys and layers
struct key{
    uint8_t keycode;
    void (*function)(bool pressed);
};

struct layer{
    uint8_t priority;
    struct key keymap[ROWS][COLS];
};

void generate(struct layer *layers[]);

#endif //KEYMAP_H