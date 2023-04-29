#include "x_rgb.h"
#include <rgb_matrix.h>
#include <action_layer.h>
#include "print.h"

void x_rgb_set_white(void) {
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(0, 0, rgb_matrix_get_val());
}

void x_rgb_set_cycle_left_right(void) {
    rgb_matrix_mode(RGB_MATRIX_CYCLE_LEFT_RIGHT);
    rgb_matrix_sethsv(0, 255, rgb_matrix_get_val());
}

void x_rgb_set_layer(void) {
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_X_LAYER_EFFECT);
}

typedef struct RgbArgs {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RgbArgs;

const uint32_t PROGMEM rgbmaps[MAX_LAYER][MATRIX_ROWS][MATRIX_COLS];

uint32_t find_rgb_in_map(uint8_t row, uint8_t col) {
    layer_state_t layers = layer_state | (default_layer_state == 0 ? 1 : default_layer_state);
    for (int8_t i = MAX_LAYER - 1; i >= 0; i--) {
        layer_state_t i_bit = (layer_state_t)1 << i;
        if ((layers & i_bit) != i_bit) continue;

        uint32_t rgb = rgbmaps[i][row][col];
        if (rgb != ________) return rgb;
    }
    return XXXXXXXX;
}

RgbArgs convert_bits_to_rgb(uint32_t rgb) {
    uint8_t r = (rgb >> 16) & 0xFF;
    uint8_t g = (rgb >> 8) & 0xFF;
    uint8_t b = (rgb >> 0) & 0xFF;

    float brightness = ((float)rgb_matrix_get_val()) / RGB_MATRIX_MAXIMUM_BRIGHTNESS;
    r *= brightness;
    g *= brightness;
    b *= brightness;

    return (RgbArgs) { r = r, g = g, b = b };
}

#ifndef X_LAYER_EFFECT_UNDERGLOW
    #define X_LAYER_EFFECT_UNDERGLOW XXXXXXXX
#endif

bool X_LAYER_EFFECT(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        if (g_led_config.flags[i] == LED_FLAG_NONE || (g_led_config.flags[i] & (LED_FLAG_UNDERGLOW | LED_FLAG_INDICATOR)) != 0) {
            RgbArgs rgbObj = convert_bits_to_rgb(X_LAYER_EFFECT_UNDERGLOW);
            rgb_matrix_set_color(i, rgbObj.r, rgbObj.g, rgbObj.b);
        }
    }

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (index < led_min || index >= led_max || index == NO_LED) continue;

            uint32_t rgb = find_rgb_in_map(row, col);
            if (rgb == ________ || rgb == XXXXXXXX) {
                rgb_matrix_set_color(index, 0, 0, 0);
                continue;
            }

            RgbArgs rgbObj = convert_bits_to_rgb(rgb);
            rgb_matrix_set_color(index, rgbObj.r, rgbObj.g, rgbObj.b);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}
