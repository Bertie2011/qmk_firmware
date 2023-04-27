#include "x_pad.h"
#include <digitizer.h>
#include <math.h>

#define X_PAD_STEP_COUNT_X_DEFAULT 12
#define X_PAD_STEP_COUNT_Y_DEFAULT 3
#define X_PAD_STEP_MIN 0.01

float x_pad_min_x = 0;
float x_pad_min_y = 0;
float x_pad_max_x = 1;
float x_pad_max_y = 1;
float x_pad_prev_min_x = 0;
float x_pad_prev_min_y = 0;
float x_pad_prev_max_x = 1;
float x_pad_prev_max_y = 1;
uint8_t x_pad_step_count_x;
uint8_t x_pad_step_count_y;
uint8_t x_pad_prev_step_count_x;
uint8_t x_pad_prev_step_count_y;

void x_pad_reset(void) {
    x_pad_min_x = 0;
    x_pad_min_y = 0;
    x_pad_max_x = 1;
    x_pad_max_y = 1;
    x_pad_prev_min_x = 0;
    x_pad_prev_min_y = 0;
    x_pad_prev_max_x = 1;
    x_pad_prev_max_y = 1;
    x_pad_step_count_x = X_PAD_STEP_COUNT_X_DEFAULT;
    x_pad_step_count_y = X_PAD_STEP_COUNT_Y_DEFAULT;
    x_pad_prev_step_count_x = X_PAD_STEP_COUNT_X_DEFAULT;
    x_pad_prev_step_count_y = X_PAD_STEP_COUNT_Y_DEFAULT;
}

bool x_pad_has_key(uint8_t row, uint8_t col) {
    return row % 4 < 3 && col >= 2;
}

uint8_t x_pad_get_x_index(uint8_t row, uint8_t col) {
    if (row <= 3) {
        return 7 - col;
    } else {
        return 6 + (col - 2);
    }
}

uint8_t x_pad_get_y_index(uint8_t row, uint8_t col) {
    return row % 4;
}

void x_pad_select(uint8_t x_index, uint8_t y_index) {
    x_pad_prev_min_x = x_pad_min_x;
    x_pad_prev_min_y = x_pad_min_y;
    x_pad_prev_max_x = x_pad_max_x;
    x_pad_prev_max_y = x_pad_max_y;
    x_pad_prev_step_count_x = x_pad_step_count_x;
    x_pad_prev_step_count_y = x_pad_step_count_y;

    x_index %= x_pad_step_count_x;
    float step_x = (x_pad_max_x - x_pad_min_x) / x_pad_step_count_x;
    float step_y = (x_pad_max_y - x_pad_min_y) / x_pad_step_count_y;

    float x = x_pad_min_x + (step_x * 0.5) + (x_index * step_x);
    float y = x_pad_min_y + (step_y * 0.5) + (y_index * step_y);
    digitizer_set_position(x, y);

    if (x_pad_step_count_x == X_PAD_STEP_COUNT_X_DEFAULT) {
        x_pad_step_count_x /= 2;
    }
    float new_step_x = fmax(X_PAD_STEP_MIN, step_x / x_pad_step_count_x);
    float new_step_y = fmax(X_PAD_STEP_MIN, step_y / x_pad_step_count_y);
    x_pad_min_x = x - ((x_pad_step_count_x/2.0) * new_step_x);
    x_pad_min_y = y - ((x_pad_step_count_y/2.0) * new_step_y);
    x_pad_max_x = x + ((x_pad_step_count_x/2.0) * new_step_x);
    x_pad_max_y = y + ((x_pad_step_count_y/2.0) * new_step_y);
}

bool x_pad_process(uint16_t keycode, keyrecord_t *record) {
    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;
    bool pressed = record->event.pressed;

    if (keycode == TG(x_pad_layer)) {
        if (!pressed) return true;

        if (IS_LAYER_ON(x_pad_layer)) {
            digitizer_in_range_off();
        } else {
            x_pad_reset();
            digitizer_in_range_on();
        }
        return true;
    }

    if (!digitizer_state.in_range) return true;
    if (!x_pad_has_key(row, col)) return true;
    if (!pressed) return false;

    x_pad_select(x_pad_get_x_index(row, col), x_pad_get_y_index(row, col));

    return false;
}
