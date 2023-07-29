 /* Copyright 2021 Dane Evans
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
  // SOFLE RGB
#include <stdio.h>

#include QMK_KEYBOARD_H

enum sofle_layers {
    _DEFAULTS = 0,
    _QWERTY = 0,
    _LOWER,
    _UPPER,
    _ADJUST
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_SWTCH,
    KC_MUTE_MIC
};

// 0: MacOS, 1 : Windows
static bool platform = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| MUTE  |    |MUTEMIC|------+------+------+------+------+------|
 * | LCTR |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  | Enter|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | ALT  |      | GUI  | LOWER| /Space  /       \Lunch \  |UPPER | Tmux |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */
  [_QWERTY] = LAYOUT(
  //,------------------------------------------------.                           ,-----------------------------------------------------.
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //|------+-------+--------+--------+--------+------|                           |--------+--------+--------+--------+--------+--------|
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_GRV,
  //|------+-------+--------+--------+--------+------|                           |--------+--------+--------+--------+--------+--------|
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //|------+-------+--------+--------+--------+------|  ===  |     |  =========  |--------+--------+--------+--------+--------+--------|
  KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_MUTE,      KC_MUTE_MIC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  //|------+-------+--------+--------+--------+------|  ===  |     |  =========  |--------+--------+--------+--------+--------+--------|
                 KC_LALT, KC_NO,   TL_LOWR, KC_LGUI,  KC_SPC,       HYPR(KC_GRV), TL_UPPR, C(KC_B), KC_NO,   KC_NO
  //            \--------+--------+--------+---------+-------|     |-------------+--------+--------+--------+-------/
),

/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | trans|  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | trans|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|   !  |   @  |   #  |   (  |   )  |-------.    ,-------|   =  |   -  |   _  |   &  |   *  |   \  |
 * |------+------+------+------+------+------| trans |    | trans |------+------+------+------+------+------|
 * | trans|      |   <  |   >  |   {  |   }  |-------|    |-------|   ]  |   [  |   $  |   %  |      | trans|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | trans| trans| trans| trans| / trans /       \ trans\  | trans| trans| trans| trans|
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */
[_LOWER] = LAYOUT(
  //,------------------------------------------------.                     ,-----------------------------------------------------.
  _______,  KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  _______,
  //|------+-------+--------+--------+--------+--------|                   |--------+-------+--------+--------+--------+---------|
  _______,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_NO,
  //|------+-------+--------+--------+--------+--------|                   |--------+-------+--------+--------+--------+---------|
  _______,  KC_EXLM,KC_AT,   KC_HASH, KC_LPRN, KC_RPRN,                     KC_EQL,  KC_MINS,KC_UNDS, KC_AMPR, KC_ASTR, KC_NUHS,
  //|------+-------+--------+--------+--------+--------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  _______,  KC_NO,  KC_LABK, KC_RABK, KC_LCBR, KC_RCBR, _______,    _______,KC_LBRC, KC_RBRC,KC_DLR,  KC_PERC, KC_NO,   _______,
  //|------+-------+--------+--------+--------+--------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                   _______, _______, _______, _______,  _______,    _______,  _______, _______,  _______, _______
  //              \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),

/* UPPER
 * ,----------------------------------------.                    ,-----------------------------------------.
 * | trans| trans| trans| trans| trans| trans|                    | trans| trans| trans| trans| trans| trans|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|      | WinL | WinC | WinR |      |                    | WH_D |      |  Up  |      | PSCR |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|      |      | Del  | Bspc |      |-------.    ,-------| WH_U | Left | Down | Rigth|      |      |
 * |------+------+------+------+------+------| trans |    | trans |------+------+------+------+------+------|
 * | trans|      | Prev | Play | Next |      |-------|    |-------|      |      |      |      |      | trans|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | trans| trans| trans| trans| / trans /       \ trans\  | trans| trans| trans| trans|
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */
[_UPPER] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  _______, _______,_______, _______, _______, _______,                    _______, _______,_______, _______, _______, _______,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  _______,  KC_NO,G(KC_LBRC),G(A(KC_GRV)),G(KC_RBRC),KC_NO,               KC_WH_D, KC_NO,  KC_UP,   KC_NO,   KC_PSCR, KC_NO,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  _______,  KC_NO,  KC_NO,   KC_DEL,  KC_BSPC, KC_NO,                     KC_WH_U, KC_LEFT,KC_DOWN, KC_RIGHT,KC_NO,   KC_NO,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  _______,  KC_NO,  KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, _______,    _______,KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   _______,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),

/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | trans| trans| trans| trans| trans| trans|                    | trans| trans| trans| trans| trans| BOOT |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|SWITCH|      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------| trans |    | trans |------+------+------+------+------+------|
 * | trans|      |      |      |      |      |-------|    |-------|      |      |      |      |      | trans|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | trans| trans| trans| trans| / trans /       \ trans\  | trans| trans| trans| trans|
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */
  // layer switcher
[_ADJUST] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  _______, _______,_______, _______, _______, _______,                    _______, _______,_______, _______, _______, QK_BOOT,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  _______, KC_SWTCH,KC_NO,   KC_NO,   KC_NO,  DB_TOGG,                    KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  _______,  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  _______,  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,      KC_NO, KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                  KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO, KC_NO,   KC_NO,  KC_NO,   KC_NO
  //            \--------+--------+--------+---------+-------|   |-------+--------+-------+--------+-------/

	),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_SWTCH:
            if (record->event.pressed) {
                platform = !platform;
                // Swap Option and GUI
                process_magic(AG_TOGG, record);
            }
            break;

        case KC_MUTE_MIC:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LSFT));
                register_mods(mod_config(MOD_LGUI));
                register_code(KC_M);
            } else {
                unregister_mods(mod_config(MOD_LSFT));
                unregister_mods(mod_config(MOD_LGUI));
                unregister_code(KC_M);
            }
            break;

        case KC_WH_D:
            if (record->event.pressed) {
                register_code(platform ? KC_WH_U : KC_WH_D);
            } else {
                unregister_code(platform ? KC_WH_U : KC_WH_D);
            }
            break;

        case KC_WH_U:
            if (record->event.pressed) {
                register_code(platform ? KC_WH_D : KC_WH_U);
            } else {
                unregister_code(platform ? KC_WH_D : KC_WH_U);
            }
            break;

        default:
            return true;
    }

    // do not process default functionality
    return false;
}

#ifdef ENCODER_ENABLE

static int8_t ticks = 0;

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (platform ? !clockwise : clockwise) { ++ticks; } else { --ticks; };
    if (abs(ticks) >= 2) {
        tap_code(clockwise ? KC_VOLU : KC_VOLD);
        ticks = 0;
    }

    return false;
}

#endif
