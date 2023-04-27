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

// ===== DEFINES =====
enum layers {
    LAYER_CLMKDH = 0,
    LAYER_QWERTY,
    LAYER_GAME,
    LAYER_SYMBOLS,
    LAYER_NUMBERS,
    LAYER_MODS_LEFT,
    LAYER_MODS_RIGHT,
    LAYER_SET,
    LAYER_NAV
};

enum keys {
    CC_LTG_SYM = SAFE_RANGE,
    CC_LTG_NUM,
    CC_LTG_NAV
};

const int LAYER_ALPHA_MASK = (1 << LAYER_QWERTY) | (1 << LAYER_CLMKDH);
const int LAYER_SYM_MASK = (1 << LAYER_SYMBOLS) | (1 << LAYER_MODS_LEFT) | (1 << LAYER_MODS_RIGHT);

// ===== KEY OVERRIDES =====
const key_override_t shift_comma_parenthesis_open = {.layers = LAYER_ALPHA_MASK, .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = KC_COMMA, .suppressed_mods = (uint8_t) 0, .replacement = KC_9, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };
const key_override_t shift_dot_parenthesis_close = {.layers = LAYER_ALPHA_MASK, .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = KC_DOT, .suppressed_mods = (uint8_t) 0, .replacement = KC_0, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };
const key_override_t shift_slash_exclamation = {.layers = LAYER_ALPHA_MASK, .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = LSFT(KC_SLASH), .suppressed_mods = (uint8_t) 0, .replacement = KC_1, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };
const key_override_t shift_quote_colon = {.layers = LAYER_ALPHA_MASK, .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = KC_QUOTE, .suppressed_mods = (uint8_t) 0, .replacement = KC_SEMICOLON, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };

const key_override_t shift_comma_minus = {.layers = (1 << LAYER_NUMBERS), .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = KC_COMMA, .suppressed_mods = (uint8_t) MOD_MASK_SHIFT, .replacement = KC_MINUS, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };
const key_override_t shift_dot_colon = {.layers = (1 << LAYER_NUMBERS), .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = KC_DOT, .suppressed_mods = (uint8_t) 0, .replacement = KC_SEMICOLON, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };
const key_override_t shift_zero_dash = {.layers = (1 << LAYER_NUMBERS), .trigger_mods = MOD_MASK_SHIFT, .negative_mod_mask = (uint8_t) ~MOD_MASK_SHIFT, .trigger = KC_0, .suppressed_mods = (uint8_t) 0, .replacement = KC_MINUS, .options = ko_options_default, .custom_action = NULL, .context = NULL, .enabled = NULL };

const key_override_t **key_overrides = (const key_override_t *[]) {
    &shift_comma_parenthesis_open, &shift_dot_parenthesis_close, &shift_slash_exclamation, &shift_quote_colon, &shift_comma_minus, &shift_dot_colon, &shift_zero_dash, NULL
};

// ====================== COMBOS ===========================
enum combos {
    COMBO_ESC,
    COMBO_TAB,
    COMBO_ENTER,
    COMBO_DEL,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;
const uint16_t PROGMEM combo_keys_esc[] = {KC_F, KC_W, COMBO_END};
const uint16_t PROGMEM combo_keys_tab[] = {KC_S, KC_R, COMBO_END};
const uint16_t PROGMEM combo_keys_enter[] = {KC_I, KC_E, COMBO_END};
const uint16_t PROGMEM combo_keys_del[] = {KC_Y, KC_U, COMBO_END};
combo_t key_combos[] = {
    [COMBO_ESC] = COMBO_ACTION(combo_keys_esc),
    [COMBO_TAB] = COMBO_ACTION(combo_keys_tab),
    [COMBO_ENTER] = COMBO_ACTION(combo_keys_enter),
    [COMBO_DEL] = COMBO_ACTION(combo_keys_del),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  if (pressed) {
    if (combo_index == COMBO_ESC) tap_code16(KC_ESC);
    if (combo_index == COMBO_TAB) tap_code16(KC_TAB);
    if (combo_index == COMBO_ENTER) tap_code16(KC_ENTER);
    if (combo_index == COMBO_DEL) tap_code16(KC_DELETE);
  } else {
    layer_clear();
    x_osm_clear();
  }
}


// ========================= LAYOUT ========================

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_QWERTY] = LAYOUT(
        XXXXXXX, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, XXXXXXX,
        XXXXXXX, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, LSFT(KC_SLASH), XXXXXXX,
        XXXXXXX, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LGUI, LGUI(KC_L), XXXXXXX, DF(LAYER_GAME), KC_N, KC_M, KC_COMMA, KC_DOT, KC_QUOTE, XXXXXXX,
        XXXXXXX, XXXXXXX, CC_LTG_SYM, KC_SPACE, XXXXXXX, XXXXXXX, KC_BACKSPACE, OSM(MOD_LSFT), XXXXXXX, MO(LAYER_SET)
    ),
    [LAYER_CLMKDH] = LAYOUT(
        XXXXXXX, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, LSFT(KC_SLASH), XXXXXXX,
        XXXXXXX, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, XXXXXXX,
        XXXXXXX, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_LGUI, LGUI(KC_L), XXXXXXX, DF(LAYER_QWERTY), KC_K, KC_H, KC_COMMA, KC_DOT, KC_QUOTE, XXXXXXX,
        XXXXXXX, XXXXXXX, CC_LTG_SYM, KC_SPACE, XXXXXXX, XXXXXXX, KC_BACKSPACE, OSM(MOD_LSFT), XXXXXXX, MO(LAYER_SET)
    ),
    [LAYER_GAME] = LAYOUT(
        KC_ESC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BACKSPACE,
        KC_CAPS_LOCK, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON, KC_ENTER,
        KC_LALT, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, XXXXXXX, XXXXXXX, XXXXXXX, DF(LAYER_CLMKDH), KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, XXXXXXX,
        KC_LGUI, XXXXXXX, XXXXXXX, KC_SPACE, XXXXXXX, XXXXXXX, KC_SPACE, XXXXXXX, CC_LTG_SYM, MO(LAYER_SET)
    ),
    [LAYER_MODS_LEFT] = LAYOUT(
        _______, OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LSFT), OSM(MOD_LCTL), _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [LAYER_MODS_RIGHT] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, OSM(MOD_LCTL), OSM(MOD_LSFT), OSM(MOD_LALT), OSM(MOD_LGUI), _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [LAYER_SYMBOLS] = LAYOUT(
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LSFT(KC_6), LSFT(KC_5), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        KC_BACKSLASH, KC_SLASH, LSFT(KC_7), LSFT(KC_8), LSFT(KC_QUOTE), KC_EQUAL, LSFT(KC_4), KC_MINUS, LSFT(KC_LEFT_BRACKET), LSFT(KC_COMMA), KC_LEFT_BRACKET, _______,
        LSFT(KC_GRAVE), LSFT(KC_2), LSFT(KC_BACKSLASH), LSFT(KC_3), KC_GRAVE, KC_SEMICOLON, _______, _______, _______, _______, LSFT(KC_EQUAL), LSFT(KC_MINUS), LSFT(KC_RIGHT_BRACKET), LSFT(KC_DOT), KC_RIGHT_BRACKET, _______,
        _______, _______, _______, _______, _______, _______, CC_LTG_NUM, CC_LTG_NAV, _______, _______
    ),
    [LAYER_NUMBERS] = LAYOUT(
        _______, _______, _______, _______, _______, _______, LSFT(KC_5), KC_7, KC_8, KC_9, KC_COMMA, _______,
        _______, _______, _______, _______, _______, _______, LSFT(KC_4), KC_4, KC_5, KC_6, KC_DOT, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LCA(KC_5), KC_1, KC_2, KC_3, KC_0, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [LAYER_SET] = LAYOUT(
        KC_SCRL, KC_F1, KC_F2, KC_F3, KC_F4, _______, _______, KC_VOLU, KC_MNXT, KC_BRIU, _______, KC_INS,
        _______, KC_F5, KC_F6, KC_F7, KC_F8, _______, _______, KC_MUTE, KC_MPLY, KC_PSCR, KC_PGUP, KC_HOME,
        _______, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______, KC_SYSTEM_SLEEP, _______, _______, _______, KC_VOLD, KC_MPRV, KC_BRID, KC_PGDN, KC_END,
        _______, _______, _______, _______, _______, _______, KC_NUM_LOCK, KC_CAPS_LOCK, _______, _______
    ),
    [LAYER_NAV] = LAYOUT(
        _______, XXXXXXX, XXXXXXX, KC_UP, XXXXXXX, XXXXXXX, XXXXXXX, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, _______,
        _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______, _______, _______, TG(LAYER_NAV), _______, _______
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

bool layer_enabled(uint8_t layer) {
    // (base layer mask | additional layer masks) & requested layer mask
    // base layer might be unset, in which case it defaults to 00000001 aka 0th layer.
    return (((default_layer_state == 0 ? 1 : default_layer_state) | layer_state) & ((layer_state_t)1 << layer)) != 0;
}

bool any_layer_enabled(uint8_t layer1, uint8_t layer2) {
    return layer_enabled(layer1) || layer_enabled(layer2);
}

void send_keycode(uint16_t keycode, bool pressed) {
    if (pressed) register_code16(keycode);
    else unregister_code16(keycode);
}

// In the left->right, top->bottom direction. The left hand has cols 7->0, rows 0->3. The right hand has cols 0->7, rows 4->7.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;
    bool pressed = record->event.pressed;

    // LAYER SWITCHING
    if (layer_enabled(LAYER_NAV) && keycode != TG(LAYER_NAV) && pressed && (row % 4 == 3 || col < 2 || col == 7)) { // Key is on thumb row/cluster, the modifier row or the outside pinky column
        layer_off(LAYER_NAV);
    }

    bool releaseBeforePress = (row % 4 == 0 && col != 2) || row % 4 == 3 || col < 2; // Not the modifiers or thumb rows.
    if (layer_enabled(LAYER_SYMBOLS) && keycode != CC_LTG_SYM && releaseBeforePress == pressed) {
        layer_off(LAYER_SYMBOLS);
    }
    if (layer_enabled(LAYER_MODS_LEFT) && pressed && (row != 0 || col < 3 || col == 7)) {
        layer_off(LAYER_MODS_LEFT);
    }
    if (layer_enabled(LAYER_MODS_RIGHT) && pressed && (row != 4 || col < 3 || col == 7)) {
        layer_off(LAYER_MODS_RIGHT);
    }

    if (layer_enabled(LAYER_NUMBERS) && keycode != TG(LAYER_NUMBERS) && keycode != OSM(MOD_LSFT) && pressed && (row < 4 || row == 7 || col < 2 || col == 7)) {
        layer_off(LAYER_NUMBERS);
    }

    if (pressed && keycode == CC_LTG_SYM) {
        if (layer_enabled(LAYER_SYMBOLS)) layer_and(~LAYER_SYM_MASK);
        else layer_or(LAYER_SYM_MASK);
        return false;
    }
    if (pressed && keycode == CC_LTG_NUM) {
        if (layer_enabled(LAYER_NUMBERS)) layer_and(~(1 << LAYER_NUMBERS));
        else layer_or(1 << LAYER_NUMBERS);
        return false;
    }
    if (pressed && keycode == CC_LTG_NAV) {
        if (layer_enabled(LAYER_NAV)) layer_and(~(1 << LAYER_NAV));
        else layer_or(1 << LAYER_NAV);
        return false;
    }

    // OSM
    if (!x_osm(keycode, pressed, record->event.time, KC_ESC)) return false;

    return true;
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        led_t state = host_keyboard_led_state();
        uint8_t mods = get_oneshot_mods() | get_oneshot_locked_mods() | get_mods();
        oled_write_P(PSTR("      "), false);
        if (layer_enabled(LAYER_QWERTY)) {
            oled_write_P(PSTR(" QWERTY "), false);
        } else if (layer_enabled(LAYER_CLMKDH)) {
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
        oled_write_P(PSTR(" C "), state.caps_lock);
        oled_write_P(PSTR(" N "), state.num_lock);
        oled_write_P(PSTR(" S "), state.scroll_lock);
        oled_write_P(PSTR("      "), false);
        oled_advance_page(true);
        oled_advance_page(true);
        oled_write_P(PSTR(" SYM "), layer_enabled(LAYER_SYMBOLS));
        oled_write_P(PSTR(" NUM "), layer_enabled(LAYER_NUMBERS));
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
