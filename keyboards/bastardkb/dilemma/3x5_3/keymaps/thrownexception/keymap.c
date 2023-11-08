/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "x_osm.h"
#include "x_rgb.h"
#include <transactions.h>

typedef struct { } transaction_pointer_down_request;
typedef struct { bool is_down; } transaction_pointer_down_response;
void get_pointer_is_down_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    report_mouse_t fake = { .x = 0, .y = 0, .v = 0, .h = 0 };
    transaction_pointer_down_response *s2m = (transaction_pointer_down_response*)out_data;
    s2m->is_down = auto_mouse_activation(fake);
}

void keyboard_post_init_user(void) {
    x_rgb_set_layer();
    rgb_matrix_set_speed(48);
    transaction_register_rpc(GET_POINTER_IS_DOWN, get_pointer_is_down_handler);
}

bool layer_enabled(layer_state_t layer) {
    // (base layer mask | additional layer masks) & requested layer mask
    // base layer might be unset, in which case it defaults to 00000001 aka 0th layer.
    return (((default_layer_state == 0 ? 1 : default_layer_state) | layer_state) & ((layer_state_t)1 << layer)) != 0;
}

bool layer_mask_enabled_any(layer_state_t layer_mask) {
    return (((default_layer_state == 0 ? 1 : default_layer_state) | layer_state) & layer_mask) != 0;
}

bool layer_mask_enabled_all(layer_state_t layer_mask) {
    return (((default_layer_state == 0 ? 1 : default_layer_state) | layer_state) & layer_mask) == layer_mask;
}

bool any_layer_enabled(layer_state_t layer1, layer_state_t layer2) {
    return layer_enabled(layer1) || layer_enabled(layer2);
}

// ===== DEFINES =====
enum dilemma_keymap_layers {
    LAYER_CLMKDH = 0,
    LAYER_GAME,
    LAYER_SYMBOLS,
    LAYER_NAV_BAR,
    LAYER_MODS,
    LAYER_SET,
    LAYER_NAV,
    LAYER_MOUSE
};
enum keys {
    CC_LTG_SYM = SAFE_RANGE,
    CC_LTG_NAV,
    CC_CAPS_WORD,
    CC_TOGGLE_BASE,
    CC_RGB_WHITE,
    CC_RGB_RAINBOW,
    CC_RGB_LAYER,
};

const int LAYER_ALPHA_MASK = (1 << LAYER_CLMKDH);
const int LAYER_SYM_MASK = (1 << LAYER_SYMBOLS) | (1 << LAYER_NAV_BAR) | (1 << LAYER_MODS);

// ===== KEY OVERRIDES =====
const key_override_t shift_comma_parenthesis_open = {.layers = LAYER_ALPHA_MASK, .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = KC_COMMA, .suppressed_mods = (uint8_t) 0, .replacement = KC_9, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };
const key_override_t shift_dot_parenthesis_close = {.layers = LAYER_ALPHA_MASK, .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = KC_DOT, .suppressed_mods = (uint8_t) 0, .replacement = KC_0, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };
const key_override_t shift_quote_colon = {.layers = LAYER_ALPHA_MASK, .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = KC_QUOTE, .suppressed_mods = (uint8_t) 0, .replacement = KC_SEMICOLON, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };

const key_override_t shift_lock_sleep = {.layers = (1 << LAYER_SYMBOLS), .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = LGUI(KC_L), .suppressed_mods = (uint8_t) MOD_MASK_SHIFT, .replacement = KC_SLEP, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };

const key_override_t shift_six_dash = {.layers = (1 << LAYER_NAV), .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = KC_6, .suppressed_mods = (uint8_t) 0, .replacement = KC_MINUS, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };
const key_override_t shift_nine_comma = {.layers = (1 << LAYER_NAV), .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = KC_9, .suppressed_mods = (uint8_t) MOD_MASK_SHIFT, .replacement = KC_COMMA, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };
const key_override_t shift_dot_colon = {.layers = (1 << LAYER_NAV), .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = KC_DOT, .suppressed_mods = (uint8_t) 0, .replacement = KC_SEMICOLON, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };
const key_override_t shift_zero_minus = {.layers = (1 << LAYER_NAV), .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = KC_0, .suppressed_mods = (uint8_t) MOD_MASK_SHIFT, .replacement = KC_MINUS, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };

const key_override_t **key_overrides = (const key_override_t *[]) {
    &shift_comma_parenthesis_open, &shift_dot_parenthesis_close, &shift_quote_colon, &shift_lock_sleep, &shift_six_dash, &shift_nine_comma, &shift_dot_colon, &shift_zero_minus, NULL
};

// ====================== COMBOS ===========================
enum combos {
    COMBO_CAPS_WORD,
    COMBO_ENTER,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;
const uint16_t PROGMEM combo_keys_caps_word[] = {CC_LTG_SYM, OSM(MOD_LSFT), COMBO_END};
const uint16_t PROGMEM combo_keys_enter[] = {KC_BACKSPACE, KC_SPACE, COMBO_END};
combo_t key_combos[] = {
    [COMBO_CAPS_WORD] = COMBO(combo_keys_caps_word, CC_CAPS_WORD),
    [COMBO_ENTER] = COMBO(combo_keys_enter, KC_ENTER),
};

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    switch (combo_index) {
        case COMBO_CAPS_WORD: return layer_state == 0;
        case COMBO_ENTER: return !layer_enabled(LAYER_MODS);
        default: return true;
    }
}

// ========================= LAYOUT ========================

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_CLMKDH] = LAYOUT_split_3x5_3(
        KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_QUOTE,
        KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O,
        KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMMA, KC_DOT, CC_LTG_NAV,
        XXXXXXX, KC_SPACE, CC_LTG_SYM, OSM(MOD_LSFT), KC_BACKSPACE, OSL(LAYER_SET)
    ),
    [LAYER_GAME] = LAYOUT_split_3x5_3(
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_Y, KC_U, KC_I, KC_O, KC_P,
        KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON,
        KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH,
        KC_ESC, KC_SPACE, CC_LTG_SYM, XXXXXXX, KC_SPACE, OSL(LAYER_SET)
    ),
    [LAYER_NAV_BAR] = LAYOUT_split_3x5_3(
        KC_ESC, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_TAB, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_DEL, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______
    ),
    [LAYER_MODS] = LAYOUT_split_3x5_3(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_ENTER, OSM(MOD_LCTL), OSM(MOD_LSFT), OSM(MOD_LALT), _______
    ),
    [LAYER_SYMBOLS] = LAYOUT_split_3x5_3(
        _______, LSFT(KC_BACKSLASH), LSFT(KC_7), LSFT(KC_GRAVE), LSFT(KC_6), KC_PSCR, LSFT(KC_MINUS), KC_SLASH, KC_BACKSLASH, LSFT(KC_SLASH),
        _______, LSFT(KC_8), KC_SEMICOLON, LSFT(KC_QUOTE), LSFT(KC_4), LSFT(KC_2), KC_MINUS, LSFT(KC_LEFT_BRACKET), LSFT(KC_COMMA), KC_LEFT_BRACKET,
        _______, LSFT(KC_3), LSFT(KC_EQUAL), KC_GRAVE, OSM(MOD_LGUI), LSFT(KC_1), KC_EQUAL, LSFT(KC_RIGHT_BRACKET), LSFT(KC_DOT), KC_RIGHT_BRACKET,
        LGUI(KC_L), KC_SPACE, _______, _______, _______, CC_TOGGLE_BASE
    ),
    [LAYER_SET] = LAYOUT_split_3x5_3(
        KC_INS, CC_RGB_WHITE, RGB_VAI, KC_VOLU, XXXXXXX, KC_SCRL, KC_F9, KC_F10, KC_F11, KC_F12,
        XXXXXXX, CC_RGB_RAINBOW, CC_RGB_LAYER, KC_MPLY, XXXXXXX, XXXXXXX, KC_F5, KC_F6, KC_F7, KC_F8,
        XXXXXXX, XXXXXXX, RGB_VAD, KC_VOLD, XXXXXXX, XXXXXXX, KC_F1, KC_F2, KC_F3, KC_F4,
        _______, XXXXXXX, KC_NUM_LOCK, KC_CAPS_LOCK, XXXXXXX, _______
    ),
    [LAYER_NAV] = LAYOUT_split_3x5_3(
        KC_LALT, KC_HOME, KC_UP, KC_END, KC_ESC, LCA(KC_5), KC_7, KC_8, KC_9, KC_DOT,
        KC_LSFT, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TAB, LSFT(KC_4), KC_4, KC_5, KC_6, KC_0,
        KC_LCTL, LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_DEL, LSFT(KC_5), KC_1, KC_2, KC_3, CC_LTG_NAV,
        _______, _______, _______, _______, _______, _______
    ),
    [LAYER_MOUSE] = LAYOUT_split_3x5_3(
        KC_DEL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_TAB, KC_LALT, KC_LSFT, KC_LCTL, KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_ESC, LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, KC_MS_BTN1, KC_MS_BTN2, XXXXXXX, XXXXXXX, _______
    ),

    /*
    [EMPTY] = LAYOUT_split_3x5_3(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______
    ),
    */
};
const uint32_t PROGMEM rgbmaps[MAX_LAYER][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_CLMKDH] = LAYOUT_split_3x5_3(
        OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO,
        OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO,
        OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO,
        XXXXXXXX, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, XXXXXXXX
    ),
    [LAYER_GAME] = LAYOUT_split_3x5_3(
        XXXXXXXX, XXXXXXXX, OOOOOOOO, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
        XXXXXXXX, OOOOOOOO, OOOOOOOO, OOOOOOOO, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
        XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
        XXXXXXXX, OOOOOOOO, XXXXXXXX, XXXXXXXX, OOOOOOOO, XXXXXXXX
    ),
    [LAYER_NAV_BAR] = LAYOUT_split_3x5_3(
        0x81f1ff, ________, ________, ________, ________, ________, ________, ________, ________, ________,
        0x81f1ff, ________, ________, ________, ________, ________, ________, ________, ________, ________,
        0x81f1ff, ________, ________, ________, ________, ________, ________, ________, ________, ________,
        ________, ________, ________, ________, ________, ________
    ),
    [LAYER_MODS] = LAYOUT_split_3x5_3(
        ________, ________, ________, ________, ________, ________, ________, ________, ________, ________,
        ________, ________, ________, ________, ________, ________, ________, ________, ________, ________,
        ________, ________, ________, ________, ________, ________, ________, ________, ________, ________,
        ________, ________, 0xffd14f, 0xffd14f, 0xffd14f, ________
    ),
    [LAYER_SYMBOLS] = LAYOUT_split_3x5_3(
        ________, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO,
        ________, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO,
        ________, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO,
        XXXXXXXX, ________, ________, ________, ________, XXXXXXXX
    ),
    [LAYER_SET] = LAYOUT_split_3x5_3(
        XXXXXXXX, 0xffffff, 0xffffff, 0x7aff66, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
        XXXXXXXX, 0xff17ce, 0x81f1ff, 0x54af47, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
        XXXXXXXX, XXXXXXXX, 0x666666, 0x38752f, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
        XXXXXXXX, XXXXXXXX, 0xffc111, 0xffc111, XXXXXXXX, XXXXXXXX
    ),
    [LAYER_NAV] = LAYOUT_split_3x5_3(
        0xffd14f, XXXXXXXX, OOOOOOOO, XXXXXXXX, 0x81f1ff, XXXXXXXX, OOOOOOOO, OOOOOOOO, OOOOOOOO, XXXXXXXX,
        0xffd14f, OOOOOOOO, OOOOOOOO, OOOOOOOO, 0x81f1ff, XXXXXXXX, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO,
        0xffd14f, XXXXXXXX, XXXXXXXX, XXXXXXXX, 0x81f1ff, XXXXXXXX, OOOOOOOO, OOOOOOOO, OOOOOOOO, 0x4f4dff,
        ________, ________, ________, ________, ________, XXXXXXXX
    ),
    [LAYER_MOUSE] = LAYOUT_split_3x5_3(
        0x666666, 0x666666, 0x666666, 0x666666, 0x666666, 0x666666, 0x666666, 0x666666, 0x666666, 0x666666,
        0x666666, 0xffd14f, 0xffd14f, 0xffd14f, 0xffd14f, 0x666666, 0x666666, 0x666666, 0x666666, 0x666666,
        0x666666, 0x666666, 0x666666, 0x666666, 0x666666, 0x666666, 0x666666, 0x666666, 0x666666, 0x666666,
        XXXXXXXX, OOOOOOOO, OOOOOOOO, XXXXXXXX, XXXXXXXX, XXXXXXXX
    ),

    /*
    [EMPTY] = LAYOUT_split_3x5_3(
        ________, ________, ________, ________, ________, ________, ________, ________, ________, ________,
        ________, ________, ________, ________, ________, ________, ________, ________, ________, ________,
        ________, ________, ________, ________, ________, ________, ________, ________, ________, ________,
        ________, ________, ________, ________, ________, ________
    ),
    */
};
// clang-format on

void send_keycode(uint16_t keycode, bool pressed) {
    if (pressed) register_code16(keycode);
    else unregister_code16(keycode);
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;

        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (layer_enabled(LAYER_SYMBOLS)) {
        switch (index) {
            case 0: // Left-half encoder
                break;
            case 1: // Right-half encoder
                break;
        }
    } else {
        switch (index) {
            case 0: // Left-half encoder
                break;
            case 1: // Right-half encoder
                break;
        }
    }
    return false;
}

// In the left->right, top->bottom direction.
// The left hand has cols 0->4, rows 0->3. The right hand has cols 4->0, rows 4->7.
// The thumb keys (outer->inner) have indexes 2, 0, 1
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;
    bool pressed = record->event.pressed;

    // CAPS WORD
    if (pressed && keycode == CC_CAPS_WORD) {
        caps_word_toggle();
        layer_clear();
        return false;
    }

    // RGB switching
    if (pressed && keycode == CC_RGB_RAINBOW) {
        x_rgb_set_cycle_left_right();
        return false;
    } else if (pressed && keycode == CC_RGB_WHITE) {
        x_rgb_set_white();
        return false;
    } else if (pressed && keycode == CC_RGB_LAYER) {
        x_rgb_set_layer();
        return false;
    }

    // Turning layers off
    bool releaseBeforePress = row % 4 == 3 && keycode != OSM(MOD_LSFT) && keycode != KC_BACKSPACE; // thumb buttons, except shift and backspace
    bool releaseAfterPress = keycode == KC_ENTER;
    if (layer_enabled(LAYER_NAV) && keycode != CC_LTG_NAV && ((pressed && releaseBeforePress) || (!pressed && releaseAfterPress))) {
        layer_off(LAYER_NAV);
    }

    releaseBeforePress = (row == 3 && col == 1) || (row == 7 && col < 2) || (row < 3 && col == 0);
    if (layer_enabled(LAYER_SYMBOLS) && keycode != CC_LTG_SYM && pressed == releaseBeforePress) {
        layer_off(LAYER_SYMBOLS);
    }
    releaseBeforePress = col != 0 || row >= 3; // Not in the left outer column
    releaseAfterPress = keycode == KC_ESC;
    if (layer_enabled(LAYER_NAV_BAR) && keycode != CC_LTG_SYM && ((pressed && releaseBeforePress) || (!pressed && releaseAfterPress))) {
        layer_off(LAYER_NAV_BAR);
    }
    releaseBeforePress = !(row % 4 == 3 && col <= 1); // Not a modifier key
    if (layer_enabled(LAYER_MODS) && keycode != CC_LTG_SYM && pressed && releaseBeforePress) {
        layer_off(LAYER_MODS);
    }

    // OSM
    bool osm_handled = !x_osm(keycode, pressed, record->event.time, KC_ESC);
    if (!pressed && layer_enabled(LAYER_MODS) && get_mods() == 0 && keycode != CC_LTG_SYM) layer_and(~LAYER_SYM_MASK);
    if (osm_handled) return false;

    // Turning layers on
    if (pressed && keycode == CC_LTG_SYM) {
        if (layer_mask_enabled_all(LAYER_SYM_MASK)) {
            x_osm_clear();
            layer_and(~LAYER_SYM_MASK);
        }
        else layer_or(LAYER_SYM_MASK);
        return false;
    }
    if (pressed && keycode == CC_LTG_NAV) {
        if (layer_enabled(LAYER_NAV)) layer_and(~(1 << LAYER_NAV));
        else layer_or(1 << LAYER_NAV);
        return false;
    }

    if (pressed && keycode == CC_TOGGLE_BASE) {
        if (layer_enabled(LAYER_CLMKDH)) default_layer_set(1 << LAYER_GAME);
        else if (layer_enabled(LAYER_GAME)) default_layer_set(1 << LAYER_CLMKDH);
    }
    return true;
}

uint32_t x_rgb_get_default_color_user(led_data* data) {
    if (layer_enabled(LAYER_MOUSE)) return 0x444444;
    if (layer_enabled(LAYER_NAV)) return 0x5b00cc;
    if (layer_mask_enabled_any(LAYER_SYM_MASK)) return 0x008a74;
    return 0x0b0bff;
}
uint32_t x_rgb_get_override_color_user(led_data* data) {
    led_t state = host_keyboard_led_state();
    uint8_t mods = get_oneshot_mods() | get_oneshot_locked_mods() | get_mods();

    if (data->row == 6 && data->col == 0 && !state.num_lock) return 0xff9e12;
    if (data->row == 7 && data->col == 1 && (state.caps_lock || is_caps_word_on())) return 0xff9e12;
    if (data->row == 7 && data->col == 1 && (mods & MOD_MASK_SHIFT) != 0) return 0xffc111;

    if (layer_enabled(LAYER_MODS) || layer_state == 0) {
        if (data->row == 3 && data->col == 1 && (mods & MOD_MASK_CTRL) != 0) return 0xffc111;
        if (data->row == 7 && data->col == 0 && (mods & MOD_MASK_ALT) != 0) return 0xffc111;
    } else if (layer_enabled(LAYER_NAV)) {
        if (data->row == 0 && data->col == 0 && (mods & MOD_MASK_ALT) != 0) return 0xffc111;
        if (data->row == 1 && data->col == 0 && (mods & MOD_MASK_SHIFT) != 0) return 0xffc111;
        if (data->row == 2 && data->col == 0 && (mods & MOD_MASK_CTRL) != 0) return 0xffc111;
    } else if (layer_enabled(LAYER_MOUSE)) {
        if (data->row == 1 && data->col == 1 && (mods & MOD_MASK_ALT) != 0) return 0xffc111;
        if (data->row == 1 && data->col == 2 && (mods & MOD_MASK_SHIFT) != 0) return 0xffc111;
        if (data->row == 1 && data->col == 3 && (mods & MOD_MASK_CTRL) != 0) return 0xffc111;
    }

    return ________;
}

bool current_pointer_is_down = false;
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    bool pointer_is_down = auto_mouse_activation(mouse_report);

    if (current_pointer_is_down && !pointer_is_down && is_keyboard_left()) {
        // If we are about to toggle pointer_is_down to false on the left side, request trackpad driver status from the right side.
        // Only the right side knows about is_touch_down driver status, the left side only has movement info which is not enough.
        transaction_pointer_down_request m2s;
        transaction_pointer_down_response s2m = { false };
        if (transaction_rpc_exec(GET_POINTER_IS_DOWN, sizeof(m2s), &m2s, sizeof(s2m), &s2m)) {
            pointer_is_down = s2m.is_down;
        }
    }
    if (pointer_is_down == current_pointer_is_down) return mouse_report;
    current_pointer_is_down = pointer_is_down;

    if (pointer_is_down) layer_on(LAYER_MOUSE);
    else layer_off(LAYER_MOUSE);
    return mouse_report;
}
