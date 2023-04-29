/*
To use:
- Add to rules.mk: SRC += x_osm.c
- Add to rules.mk: RGB_MATRIX_CUSTOM_USER = yes
- Add to config.h:
#define ENABLE_RGB_MATRIX_SOLID_COLOR
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define X_LAYER_EFFECT_UNDERGLOW 0xRRGGBB (hex color code without #)

- Add new file rgb_matrix_user.inc:
RGB_MATRIX_EFFECT(X_LAYER_EFFECT)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
bool X_LAYER_EFFECT(effect_params_t* params);
#endif
- In keymap.c add:
#include "x_rgb.h"

void keyboard_post_init_user(void) {
    // Use one of the x_rgb_set_ methods below to set the initial mode. Use custom keycodes to switch between modes.
}


const uint32_t PROGMEM rgbmaps[MAX_LAYER][MATRIX_ROWS][MATRIX_COLS] = {
    // Use the same structure as your keymaps here, but instead of keycodes, use color codes using the pattern 0xRRGGBB, e.g. 0xFF0000 for red.
    // See the #defines below for aliases. Note that the color code aliases are 8 characters wide as opposed to the 7 wide keycode aliases.
}
*/

void x_rgb_set_white(void);
void x_rgb_set_cycle_left_right(void);
void x_rgb_set_layer(void);

#define XXXXXXXX 0x000000 // black
#define OOOOOOOO 0xFFFFFF // white
#define ________ 0x000001 // transparent (use the color on the layer below)
