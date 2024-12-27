#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif
#include "gpio.h"

#include "x_rgb.h"

void keyboard_pre_init_user(void) {
    gpio_set_pin_output(24); // Disable the power LED
    gpio_write_pin_high(24);
    x_rgb_set_layer();
}

enum layer_names {
    _BASE,
    _SYM,
    _NUM,
    _SET,
};

enum custom_keycodes {
    CKC_FLASH = SAFE_RANGE,
    CKC_RGB_WHITE,
    CKC_RGB_CYCLE,
    CKC_RGB_LAYER,
};

const key_override_t sft_comma_parenthesis_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMMA, S(KC_9));
const key_override_t sft_dot_parenthesis_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, S(KC_0));
const key_override_t sft_del_prnt_override = ko_make_basic(MOD_MASK_SHIFT, KC_DEL, KC_PSCR);
const key_override_t sft_esc_lock_override = ko_make_basic(MOD_MASK_SHIFT, KC_ESC, G(KC_L));
const key_override_t sft_asterisk_at_override = ko_make_basic(MOD_MASK_SHIFT, S(KC_8), S(KC_2));
const key_override_t sft_question_exclamation_override = ko_make_basic(MOD_MASK_SHIFT, S(KC_SLASH), S(KC_1));
const key_override_t ctl_del_capsword_override = ko_make_basic(MOD_MASK_CTRL, KC_DEL, CW_TOGG);
const key_override_t ctl_esc_sleep_override = ko_make_basic(MOD_MASK_CTRL, KC_ESC, KC_SLEP);
const key_override_t sft_cd_ca_override = ko_make_with_layers(MOD_MASK_SHIFT, C(KC_D), C(KC_A), 1 << _SYM);
const key_override_t sft_cv_gv_override = ko_make_with_layers(MOD_MASK_SHIFT, C(KC_V), G(KC_V), (1 << _SYM)|(1 << _NUM));
const key_override_t sft_f2_f5_override = ko_make_basic(MOD_MASK_SHIFT, KC_F2, KC_F5);
const key_override_t sft_caret_tilde_override = ko_make_basic(MOD_MASK_SHIFT, S(KC_6), S(KC_GRAVE));
const key_override_t sft_dollar_percent_override = ko_make_basic(MOD_MASK_SHIFT, S(KC_4), S(KC_5));
const key_override_t ctl_dollar_euro_override = ko_make_basic(MOD_MASK_CTRL, S(KC_4), A(C(KC_5)));
const key_override_t sft_2_parenthesis_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_KP_2, S(KC_9), 1 << _NUM);
const key_override_t sft_3_parenthesis_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_KP_3, S(KC_0), 1 << _NUM);

const key_override_t *key_overrides[] = {
    &sft_comma_parenthesis_override,
    &sft_dot_parenthesis_override,
	&sft_del_prnt_override,
    &sft_esc_lock_override,
    &sft_asterisk_at_override,
    &sft_question_exclamation_override,
    &ctl_del_capsword_override,
    &ctl_esc_sleep_override,
    &sft_cd_ca_override,
    &sft_cv_gv_override,
    &sft_f2_f5_override,
    &sft_caret_tilde_override,
    &sft_dollar_percent_override,
    &ctl_dollar_euro_override,
    &sft_2_parenthesis_override,
    &sft_3_parenthesis_override
};

const uint16_t PROGMEM ctl_combo[] = {KC_BACKSPACE, OSM(MOD_LSFT), COMBO_END};
const uint16_t PROGMEM gui_combo[] = {OSM(MOD_LSFT), TO(_SYM), COMBO_END};
const uint16_t PROGMEM alt_combo[] = {OSM(MOD_LSFT), KC_SPACE, COMBO_END};
const uint16_t PROGMEM num_combo[] = {TO(_SYM), KC_SPACE, COMBO_END};
//TODO fix capsword

combo_t key_combos[] = {
    COMBO(ctl_combo, OSM(MOD_LCTL)),
    COMBO(gui_combo, OSM(MOD_LGUI)),
    COMBO(alt_combo, OSM(MOD_LALT)),
    COMBO(num_combo, TO(_NUM))
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        KC_ESC, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SEMICOLON, KC_DEL,
        KC_ENTER, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, KC_TAB,
        S(KC_8), KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_QUOTE, S(KC_SLASH),
        XXXXXXX, KC_BACKSPACE, OSM(MOD_LSFT), TO(_SYM), KC_SPACE, TO(_SET)
    ),
    [_SYM] = LAYOUT_split_3x6_3(
        _______, KC_F2, KC_HOME, KC_UP, KC_END, KC_SLASH, KC_BACKSLASH, S(KC_EQUAL), S(KC_RIGHT_BRACKET), S(KC_DOT), KC_RIGHT_BRACKET, S(KC_4),
        _______, C(KC_Z), KC_LEFT, KC_DOWN, KC_RIGHT, C(KC_Y), S(KC_MINUS), KC_MINUS, S(KC_LEFT_BRACKET), S(KC_COMMA), KC_LEFT_BRACKET, _______,
        XXXXXXX, C(KC_D), C(KC_X), C(KC_C), C(KC_V), XXXXXXX, S(KC_3), KC_EQUAL, S(KC_7), S(KC_BACKSLASH), KC_GRAVE, S(KC_6),
        _______, _______, _______, TG(_SYM), _______, _______
    ),
    [_NUM] = LAYOUT_split_3x6_3(
        _______, C(KC_R), C(KC_Q), C(KC_P), C(KC_M), XXXXXXX, A(C(KC_5)), KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_DOT, S(KC_SEMICOLON),
        _______, KC_SLASH, KC_ASTERISK, KC_MINUS, KC_PLUS, XXXXXXX, S(KC_4), KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_0, _______,
        XXXXXXX, XXXXXXX, S(KC_6), C(KC_C), C(KC_V), XXXXXXX, S(KC_5), KC_KP_1, KC_KP_2, KC_KP_3, KC_MINUS, S(KC_MINUS),
        _______, _______, _______, _______, _______, _______
    ),
    [_SET] = LAYOUT_split_3x6_3(
        XXXXXXX, KC_INS, CKC_RGB_WHITE, QK_RGB_MATRIX_VALUE_UP, KC_VOLU, XXXXXXX, XXXXXXX, KC_F9, KC_F10, KC_F11, KC_F12, XXXXXXX,
        XXXXXXX, CKC_FLASH, CKC_RGB_CYCLE, CKC_RGB_LAYER, KC_MPLY, XXXXXXX, XXXXXXX, KC_F5, KC_F6, KC_F7, KC_F8, XXXXXXX,
        XXXXXXX, KC_SCRL, XXXXXXX, QK_RGB_MATRIX_VALUE_DOWN, KC_VOLD, XXXXXXX, XXXXXXX, KC_F1, KC_F2, KC_F3, KC_F4, XXXXXXX,
        XXXXXXX, XXXXXXX, KC_CAPS, KC_NUM, XXXXXXX, TG(_SET)
    )
};

const uint32_t PROGMEM rgbmaps[MAX_LAYER][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO,
        OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO,
        OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO,
        XXXXXXXX, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, XXXXXXXX
    ),
    [_SYM] = LAYOUT_split_3x6_3(
        XXXXXXXX, XXXXXXXX, XXXXXXXX, OOOOOOOO, XXXXXXXX, XXXXXXXX, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO,
        XXXXXXXX, XXXXXXXX, OOOOOOOO, OOOOOOOO, OOOOOOOO, XXXXXXXX, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO,
        XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO,
        XXXXXXXX, OOOOOOOO, OOOOOOOO, 0x4f4dff, OOOOOOOO, XXXXXXXX
    ),
    [_NUM] = LAYOUT_split_3x6_3(
        XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, OOOOOOOO, OOOOOOOO, OOOOOOOO, XXXXXXXX, XXXXXXXX,
        XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, OOOOOOOO, OOOOOOOO, OOOOOOOO, OOOOOOOO, XXXXXXXX,
        XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, OOOOOOOO, OOOOOOOO, OOOOOOOO, XXXXXXXX, XXXXXXXX,
        XXXXXXXX, OOOOOOOO, OOOOOOOO, 0x4f4dff, 0x4f4dff, XXXXXXXX
    ),
    [_SET] = LAYOUT_split_3x6_3(
        XXXXXXXX, XXXXXXXX, 0xffffff, 0xffffff, 0x7aff66, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
        XXXXXXXX, XXXXXXXX, 0xff17ce, 0x81f1ff, 0x54af47, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
        XXXXXXXX, XXXXXXXX, XXXXXXXX, 0x666666, 0x38752f, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
        XXXXXXXX, XXXXXXXX, 0xffc111, 0xffc111, XXXXXXXX, 0x4f4dff
    )
};

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

// In the left->right, top->bottom direction.
// The left hand has cols 0->5, rows 0->3. The right hand has cols 5->0, rows 4->7.
// The thumb keys (outer->inner) have indexes 3->5.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool pressed = record->event.pressed;

    if (keycode == CKC_FLASH && pressed) {
        send_string("qmk flash\n");
        reset_keyboard();
        return false;
    }
    if (keycode == CKC_RGB_WHITE && pressed) {
        x_rgb_set_white();
        return false;
    }
    if (keycode == CKC_RGB_CYCLE && pressed) {
        x_rgb_set_cycle_left_right();
        return false;
    }
    if (keycode == CKC_RGB_LAYER && pressed) {
        x_rgb_set_layer();
        return false;
    }

    if (layer_state_is(_NUM) && pressed && keycode == TO(_NUM)) {
        layer_off(_NUM);
        return false;
    }
    return true;
}
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;
    bool pressed = record->event.pressed;

    bool shouldRelease = (row > 3) || (col == 0) || (row == 3 && col <= 4) || (row == 0 && col == 1) || (row == 0 && col == 5);
    if (layer_state_is(_SYM) && keycode != TO(_SYM) && (!pressed && shouldRelease)) {
        layer_off(_SYM);
    }
    bool shouldRemain = (row == 0 && col == 3) || (row == 0 && col == 4) || (row == 2 && col == 3) || (row == 2 && col == 4);
    if (layer_state_is(_SET) && keycode != TO(_SET) && (!pressed && !shouldRemain)) {
        layer_off(_SET);
    }
}

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C
