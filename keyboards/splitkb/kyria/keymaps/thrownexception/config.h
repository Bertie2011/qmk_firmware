/* Copyright 2022 Thomas Baart <thomas@splitkb.com>
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

#pragma once

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_HUE_STEP  8
#    define RGBLIGHT_SAT_STEP  8
#    define RGBLIGHT_VAL_STEP  8
#    define RGBLIGHT_LIMIT_VAL 150
#endif

// Don't allow recursive madness
#define DYNAMIC_MACRO_NO_NESTING

// Mouse Keys
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL
#define MK_C_OFFSET_0 1
#define MK_C_INTERVAL_0 3
#define MK_C_OFFSET_UNMOD 2
#define MK_C_INTERVAL_UNMOD 3
#define MK_C_OFFSET_1 4
#define MK_C_INTERVAL_1 3
#define MK_C_OFFSET_2 9
#define MK_C_INTERVAL_2 3
#define MK_W_OFFSET_0 1
#define MK_W_INTERVAL_0 180
#define MK_W_OFFSET_1 1
#define MK_W_INTERVAL_1 90
#define MK_W_OFFSET_2 2
#define MK_W_INTERVAL_2 30

// Hold Tap
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM 250
#define HOLD_ON_OTHER_KEY_PRESS

// Combos
#define COMBO_STRICT_TIMER
#define COMBO_ONLY_FROM_LAYER 0
#define COMBO_SHOULD_TRIGGER
#define COMBO_TERM 75

// Mouse
//#define CIRQUE_PINNACLE_DIAMETER_MM 35
//#define CIRQUE_PINNACLE_ATTENUATION EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_2X
//#define CIRQUE_PINNACLE_CURVED_OVERLAY
//#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_RELATIVE_MODE
//#define CIRQUE_PINNACLE_ADDR 0x55
//#define CIRQUE_PINNACLE_TAP_ENABLE
//#define CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE
//#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
//#define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
//#define SPLIT_POINTING_ENABLE
//#define POINTING_DEVICE_RIGHT
//#define POINTING_DEVICE_DEBUG

// Disables
#define NO_MUSIC_MODE
#define OLED_UPDATE_INTERVAL 100
#define OLED_TIMEOUT 15000
