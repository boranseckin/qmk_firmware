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
    _QWERTY = 0,
    _CHARS,
    _EXTRAS,
    _CONFIG
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
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |Launch|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  | Tmux |
 * |------+------+------+------+------+------| MUTE  |    |MUTEMIC|------+------+------+------+------+------|
 * | LCTR |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  | Enter|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | ALT  |      | CHARS|  GUI | / Space /       \ Bspc \  |EXTRAS|CHARS |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */
  [_QWERTY] = LAYOUT(
  //,------------------------------------------------.                           ,-----------------------------------------------------.
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    HYPR(KC_GRV),
  //|------+-------+--------+--------+--------+------|                           |--------+--------+--------+--------+--------+--------|
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_GRV,
  //|------+-------+--------+--------+--------+------|                           |--------+--------+--------+--------+--------+--------|
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, C(KC_B),
  //|------+-------+--------+--------+--------+------|  ===  |     |  =========  |--------+--------+--------+--------+--------+--------|
  KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_MUTE,      KC_MUTE_MIC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  //|------+-------+--------+--------+--------+------|  ===  |     |  =========  |--------+--------+--------+--------+--------+--------|
                 TL_LOWR, KC_NO,   KC_LALT, KC_LGUI,  KC_SPC,       KC_BSPC,      TL_UPPR, TL_LOWR, KC_NO,   KC_NO
  //            \--------+--------+--------+---------+-------|     |-------------+--------+--------+--------+-------/
),

/* CHARS
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | trans| trans| trans| trans| trans| trans|                    | trans| trans| trans| trans| trans| trans|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|      |   <  |   >  |   &  |   ^  |                    |   @  |   $  |   [  |   ]  |      | trans|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|   !  |   /  |   +  |   '  |   "  |-------.    ,-------|   =  |   -  |   (  |   )  |   :  | trans|
 * |------+------+------+------+------+------| trans |    | trans |------+------+------+------+------+------|
 * | trans|      |   \  |   *  |   %  |   #  |-------|    |-------|   |  |   _  |   {  |   }  |   ?  | trans|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | trans| trans| trans| trans| / trans /       \ trans\  | trans| trans| trans| trans|
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */
[_CHARS] = LAYOUT(
  //,------------------------------------------------.                     ,-----------------------------------------------------.
  _______,  _______, _______, _______, _______, _______,                    _______,_______, _______, _______, _______, _______,
  //|------+-------+--------+--------+--------+--------|                   |--------+-------+--------+--------+--------+---------|
  _______,  KC_NO,  KC_LABK, KC_RABK, KC_AMPR, KC_CIRC,                     KC_AT,   KC_DLR, KC_LBRC, KC_RBRC, KC_NO,   _______,
  //|------+-------+--------+--------+--------+--------|                   |--------+-------+--------+--------+--------+---------|
  _______,  KC_EXLM,KC_SLSH, KC_PLUS, KC_QUOT, KC_DQUO,                     KC_EQL,  KC_MINS,KC_LPRN, KC_RPRN, KC_COLN, _______,
  //|------+-------+--------+--------+--------+--------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  _______,  KC_NO,  KC_BSLS, KC_ASTR, KC_PERC, KC_HASH, _______,    _______,KC_PIPE, KC_UNDS,KC_LCBR, KC_RCBR, KC_QUES, _______,
  //|------+-------+--------+--------+--------+--------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                   _______, _______, _______, _______,  _______,    _______,  _______, _______,  _______, _______
  //              \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),

/* EXTRAS
 * ,----------------------------------------.                    ,-----------------------------------------.
 * | trans| trans| trans| trans| trans| trans|                    | trans| trans| trans| trans| trans| trans|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|      |      |      |      |      |                    | WH_D |      |  Up  |      | PSCR |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|      |      | Del  | Bspc |      |-------.    ,-------| WH_U | Left | Down | Rigth|      |      |
 * |------+------+------+------+------+------| trans |    | trans |------+------+------+------+------+------|
 * | trans|      | Prev | Play | Next |      |-------|    |-------|      |      |      |      |      | trans|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | trans| trans| trans| trans| / trans /       \ trans\  | trans| trans| trans| trans|
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */
[_EXTRAS] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  _______, _______,_______, _______, _______, _______,                    _______, _______,_______, _______, _______, _______,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  _______,  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_WH_D, KC_NO,  KC_UP,   KC_NO,   KC_PSCR, KC_NO,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  _______,  KC_NO,  KC_NO,   KC_DEL,  KC_BSPC, KC_NO,                     KC_WH_U, KC_LEFT,KC_DOWN, KC_RIGHT,KC_NO,   KC_NO,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  _______,  KC_NO,  KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, _______,    _______,KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   _______,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),

/* CONFIG
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | trans| trans| trans| trans| trans| trans|                    | trans| trans| trans| trans| trans| BOOT |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|SWITCH|      |      |      | DEBUG|                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | trans|      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'            '------''---------------------------'
 */
[_CONFIG] = LAYOUT(
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

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _CHARS, _EXTRAS, _CONFIG);
}

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
