/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
//#include "x_pad.h"
//#include "print.h"

bool layer_enabled(uint8_t layer) {
    // (base layer mask | additional layer masks) & requested layer mask
    // base layer might be unset, in which case it defaults to 00000001 aka 0th layer.
    return (((default_layer_state == 0 ? 1 : default_layer_state) | layer_state) & ((layer_state_t)1 << layer)) != 0;
}

bool any_layer_enabled(uint8_t layer1, uint8_t layer2) {
    return layer_enabled(layer1) || layer_enabled(layer2);
}

// ===== DEFINES =====
enum layers {
    LAYER_CLMKDH = 0,
    LAYER_GAME,
    LAYER_SYMBOLS,
    LAYER_MODS_LEFT,
    LAYER_MODS_RIGHT,
    LAYER_SET,
    LAYER_NAV
};

enum keys {
    CC_LTG_SYM = SAFE_RANGE,
    CC_LTG_NAV,
    CC_LTG_SET,
    CC_CAPS_WORD,
    CC_TOGGLE_BASE,
};

const int LAYER_ALPHA_MASK = (1 << LAYER_CLMKDH);
const int LAYER_SYM_MASK = (1 << LAYER_SYMBOLS) | (1 << LAYER_MODS_LEFT) | (1 << LAYER_MODS_RIGHT);

// ===== KEY OVERRIDES =====
const key_override_t shift_comma_parenthesis_open = {.layers = LAYER_ALPHA_MASK, .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = KC_COMMA, .suppressed_mods = (uint8_t) 0, .replacement = KC_9, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };
const key_override_t shift_dot_parenthesis_close = {.layers = LAYER_ALPHA_MASK, .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = KC_DOT, .suppressed_mods = (uint8_t) 0, .replacement = KC_0, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };
const key_override_t shift_slash_exclamation = {.layers = LAYER_ALPHA_MASK, .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = LSFT(KC_SLASH), .suppressed_mods = (uint8_t) 0, .replacement = KC_1, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };
const key_override_t shift_quote_colon = {.layers = LAYER_ALPHA_MASK, .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = KC_QUOTE, .suppressed_mods = (uint8_t) 0, .replacement = KC_SEMICOLON, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };

const key_override_t shift_comma_dash = {.layers = (1 << LAYER_NAV), .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = KC_COMMA, .suppressed_mods = (uint8_t) 0, .replacement = KC_MINUS, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };
const key_override_t shift_dot_colon = {.layers = (1 << LAYER_NAV), .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = KC_DOT, .suppressed_mods = (uint8_t) 0, .replacement = KC_SEMICOLON, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };
const key_override_t shift_zero_minus = {.layers = (1 << LAYER_NAV), .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = KC_0, .suppressed_mods = (uint8_t) MOD_MASK_SHIFT, .replacement = KC_MINUS, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };

const key_override_t **key_overrides = (const key_override_t *[]) {
    &shift_comma_parenthesis_open, &shift_dot_parenthesis_close, &shift_slash_exclamation, &shift_quote_colon, &shift_comma_dash, &shift_dot_colon, &shift_zero_minus, NULL
};

// ====================== COMBOS ===========================
enum combos {
    COMBO_NAV,
    COMBO_ESC,
    COMBO_SET,
    COMBO_CAPS_WORD,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;
const uint16_t PROGMEM combo_keys_nav[] = {KC_SPACE, KC_BACKSPACE, COMBO_END};
const uint16_t PROGMEM combo_keys_esc[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_keys_set[] = {KC_G, KC_M, COMBO_END}; // Control + dollar sign
const uint16_t PROGMEM combo_keys_caps_word[] = {KC_F, KC_U, COMBO_END}; // Both shifts
combo_t key_combos[] = {
    [COMBO_NAV] = COMBO(combo_keys_nav, CC_LTG_NAV),
    [COMBO_ESC] = COMBO(combo_keys_esc, KC_ESC),
    [COMBO_SET] = COMBO(combo_keys_set, CC_LTG_SET),
    [COMBO_CAPS_WORD] = COMBO(combo_keys_caps_word, CC_CAPS_WORD),
};

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    switch (combo_index) {
        case COMBO_SET: return layer_enabled(LAYER_NAV);
        case COMBO_CAPS_WORD: return layer_enabled(LAYER_SYMBOLS);
        default: return true;
    }
}

// ========================= LAYOUT ========================

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_CLMKDH] = LAYOUT(
        XXXXXXX, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, LSFT(KC_SLASH), XXXXXXX,
        XXXXXXX, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, XXXXXXX,
        XXXXXXX, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_LGUI, LGUI(KC_L), XXXXXXX, XXXXXXX, KC_K, KC_H, KC_COMMA, KC_DOT, KC_QUOTE, XXXXXXX,
        XXXXXXX, XXXXXXX, CC_LTG_SYM, KC_SPACE, XXXXXXX, XXXXXXX, KC_BACKSPACE, OSM(MOD_LSFT), XXXXXXX, XXXXXXX
    ),
    [LAYER_GAME] = LAYOUT(
        XXXXXXX, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BACKSPACE,
        XXXXXXX, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON, KC_ENTER,
        XXXXXXX, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, XXXXXXX,
        XXXXXXX, XXXXXXX, CC_LTG_SYM, KC_SPACE, XXXXXXX, XXXXXXX, KC_SPACE, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [LAYER_MODS_LEFT] = LAYOUT(
        _______, OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LSFT), OSM(MOD_LCTL), _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [LAYER_MODS_RIGHT] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, OSM(MOD_RCTL), OSM(MOD_RSFT), OSM(MOD_RALT), OSM(MOD_RGUI), _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [LAYER_SYMBOLS] = LAYOUT(
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LSFT(KC_6), LSFT(KC_GRAVE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, LSFT(KC_7), LSFT(KC_8), KC_SEMICOLON, LSFT(KC_QUOTE), KC_SLASH, LSFT(KC_2), KC_MINUS, LSFT(KC_LEFT_BRACKET), LSFT(KC_COMMA), KC_LEFT_BRACKET, _______,
        _______, LSFT(KC_BACKSLASH), LSFT(KC_3), KC_EQUAL, KC_GRAVE, KC_BACKSLASH, _______, _______, _______, _______, LSFT(KC_EQUAL), LSFT(KC_MINUS), LSFT(KC_RIGHT_BRACKET), LSFT(KC_DOT), KC_RIGHT_BRACKET, _______,
        _______, _______, _______, KC_DEL, _______, _______, KC_ENTER, KC_TAB, CC_TOGGLE_BASE, _______
    ),
    [LAYER_SET] = LAYOUT(
        KC_SCRL, KC_F1, KC_F2, KC_F3, KC_F4, _______, _______, KC_VOLU, KC_MNXT, KC_BRIU, _______, KC_INS,
        _______, KC_F5, KC_F6, KC_F7, KC_F8, _______, _______, KC_MUTE, KC_MPLY, KC_PSCR, KC_PGUP, KC_HOME,
        _______, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______, KC_SYSTEM_SLEEP, _______, _______, _______, KC_VOLD, KC_MPRV, KC_BRID, KC_PGDN, KC_END,
        _______, _______, TG(LAYER_SET), TG(LAYER_SET), _______, _______, KC_NUM_LOCK, KC_CAPS_LOCK, _______, _______
    ),
    [LAYER_NAV] = LAYOUT(
        _______, KC_DEL, KC_HOME, KC_UP, KC_END, LCA(KC_5), KC_LALT, KC_7, KC_8, KC_9, KC_COMMA, _______,
        _______, KC_TAB, KC_LEFT, KC_DOWN, KC_RIGHT, LSFT(KC_4), KC_LCTL, KC_4, KC_5, KC_6, KC_0, _______,
        _______, KC_ENTER, LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LSFT(KC_5), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, KC_1, KC_2, KC_3, KC_DOT, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )

    /*
    LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    */

/*
 * Layer template
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */

/*     [_LAYERINDEX] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ), */
};

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

// In the left->right, top->bottom direction. The left hand has cols 7->0, rows 0->3. The right hand has cols 0->7, rows 4->7.
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

    // LAYER SWITCHING
    bool releaseBeforePress = row % 4 == 3 && keycode != OSM(MOD_LSFT); // thumb buttons, except shift
    bool releaseAfterPress = keycode == KC_ENTER;
    if (layer_enabled(LAYER_NAV) && ((pressed && releaseBeforePress) || (!pressed && releaseAfterPress))) {
        layer_off(LAYER_NAV);
    }

    releaseBeforePress = (row % 4 == 0 && col != 2); // Not the modifiers.
    if (layer_enabled(LAYER_SYMBOLS) && keycode != CC_LTG_SYM && releaseBeforePress == pressed) {
        layer_off(LAYER_SYMBOLS);
    }
    if (layer_enabled(LAYER_MODS_LEFT) && pressed && (row != 0 || col < 3 || col == 7)) {
        layer_off(LAYER_MODS_LEFT);
    }
    if (layer_enabled(LAYER_MODS_RIGHT) && pressed && (row != 4 || col < 3 || col == 7)) {
        layer_off(LAYER_MODS_RIGHT);
    }

    if (pressed && keycode == CC_LTG_SYM) {
        if (layer_enabled(LAYER_SYMBOLS)) layer_and(~LAYER_SYM_MASK);
        else layer_or(LAYER_SYM_MASK);
        return false;
    }
    if (pressed && keycode == CC_LTG_NAV) {
        if (layer_enabled(LAYER_NAV)) layer_and(~(1 << LAYER_NAV));
        else layer_or(1 << LAYER_NAV);
        return false;
    }
    if (pressed && keycode == CC_LTG_SET) {
        layer_move(LAYER_SET);
        return false;
    }

    // OSM
    if (!x_osm(keycode, pressed, record->event.time, KC_ESC)) return false;

    if (pressed && keycode == CC_TOGGLE_BASE) {
        if (layer_enabled(LAYER_CLMKDH)) default_layer_set(1 << LAYER_GAME);
        else if (layer_enabled(LAYER_GAME)) default_layer_set(1 << LAYER_CLMKDH);
    }
    return true;
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        led_t state = host_keyboard_led_state();
        uint8_t mods = get_oneshot_mods() | get_oneshot_locked_mods() | get_mods();
        oled_write_P(PSTR("      "), false);
        if (layer_enabled(LAYER_CLMKDH)) {
            oled_write_P(PSTR(" CLMK-DH "), false);
        } else if (layer_enabled(LAYER_GAME)) {
            oled_write_P(PSTR(" GAME "), false);
        }
        oled_advance_page(true);
        oled_advance_page(true);
        oled_write_P(PSTR("MOD "), layer_enabled(LAYER_MODS_LEFT));
        oled_write_P(PSTR(" C "), (mods & MOD_MASK_CTRL) != 0);
        oled_write_P(PSTR(" S "), (mods & MOD_MASK_SHIFT) != 0);
        oled_write_P(PSTR(" A "), (mods & MOD_MASK_ALT) != 0);
        oled_write_P(PSTR(" W "), (mods & MOD_MASK_GUI) != 0);
        oled_write_P(PSTR(" MOD"), layer_enabled(LAYER_MODS_RIGHT));
        oled_advance_page(true);
        oled_advance_page(true);
        oled_write_P(PSTR("     "), false);
        oled_write_P(PSTR(" C "), state.caps_lock || is_caps_word_on());
        oled_write_P(PSTR(" N "), state.num_lock);
        oled_write_P(PSTR(" S "), state.scroll_lock);
        oled_write_P(PSTR("      "), false);
        oled_advance_page(true);
        oled_advance_page(true);
        oled_write_P(PSTR(" SYM "), layer_enabled(LAYER_SYMBOLS));
        oled_write_P(PSTR(" NAV "), layer_enabled(LAYER_NAV));
        oled_write_P(PSTR(" SET "), layer_enabled(LAYER_SET));
    }
    return false;
}
#endif

/*#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif*/
