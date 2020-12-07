#ifndef HIDKEYS
#define HIDKEYS

//Modifiers
#define KEY_MOD_LCTRL  0x01
#define KEY_MOD_LSHIFT 0x02
#define KEY_MOD_LALT   0x04
#define KEY_MOD_LMETA  0x08
#define KEY_MOD_RCTRL  0x10
#define KEY_MOD_RSHIFT 0x20
#define KEY_MOD_RALT   0x40
#define KEY_MOD_RMETA  0x80

#define IS_KEY_MOD_FN(row,col,fn_row,fn_col) ((row == fn_row) && (col == fn_col))



#endif //HIDKEYS