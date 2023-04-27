#include <stdint.h>
#include <stdbool.h>
#include <action.h>

bool x_pad_process(uint16_t keycode, keyrecord_t *record);
uint8_t x_pad_layer;

/*
To use, add the c file to sources, add the h file to keymap.c
Define empty layer and uint8_t x_pad_layer = LAYER_POINT;
and DIGITIZER_ENABLE = yes in rules.mk
and
    if (!x_pad_process(keycode, record)) return false;
in the user process key function.
*/
