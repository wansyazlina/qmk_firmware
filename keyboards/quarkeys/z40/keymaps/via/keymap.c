/* Copyright 2020 Nathan Spears
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
#include "z40.h"

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

#define SD_LTYPE_01		  0, 223, 252     	// KM_Light_red
#define SD_LTYPE_02		 31, 208, 234    	// KM_Light_yellow
#define SD_LTYPE_03		 97, 231, 230    	// KM_dirty_green
#define SD_LTYPE_04		 32, 191, 236    	// LM_golden_yellow
#define SD_LTYPE_05		255, 246, 238   	// LM_Slight_dark_red
#define SD_LTYPE_06		166, 240, 228   	// LM_Blue
#define SD_LTYPE_07		  0, 183, 238     	// LM_LightOrange
#define SD_LTYPE_08		130, 255, 255  		// LM_Cyan
#define SD_LTYPE_09		 42, 248, 240   	// LM_Yellow
#define SD_LTYPE_10		  0,   0,   0       // NULL
#define SD_LTYPE_11		216, 123, 238   	// LM_Light_pink
#define SD_LTYPE_12		  0,   0, 255       // LM_White
#define SD_LTYPE_13		  6, 240, 224     	// LM_Red_Blood
#define SD_LTYPE_14		 82, 247, 246  	  	// LM_NeonGreen
#define SD_LTYPE_15		178, 231, 238   	// LM_LighterBlue
#define SD_LTYPE_16		 36, 230, 248    	// LM_darker_Yellow
#define SD_LTYPE_17		 31, 255, 255    	// LM_Light_orange
#define SD_LTYPE_18		  0, 242, 205     	// LM_Blooder_Red
#define SD_LTYPE_19		 19, 150, 185    	// LM_LightBrown
#define SD_LTYPE_20		 13, 237, 253    	// LM_Orange
#define SD_LTYPE_21		124,  62, 253    	// LM_skyBlue
#define SD_LTYPE_22		115, 255, 248   	// LM_Toirquise
#define SD_LTYPE_23		195, 255, 251   	// LM_Purple
#define SD_LTYPE_24		178, 183, 238   	// LM_Light_blue_purple

enum custom_keycodes{
	SD_KC_1,
	SD_KC_2
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* [0]
     * ,-------------------------------------------------------------------------------------.
     * |------------+------+------+------+------+------+------+------+------+------+------+--|
     * | Esc   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  BS   |
     * |------------+------+------+------+------+-------------+------+------+------+------+--|
     * | Tab   |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "    |
     * |------------+------+------+------+------+------|------+------+------+------+------+--|
     * | SHIFT |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift |
     * |-------+-------+-------+-------+-------+-------+------+------+------+------+------+--|
     * | Ctrl  | Caps |  ALT |  OS  | Ly1  |    SPACE    | Ly2  |  M1  |  M2  |  M3  | Enter |
     * `-------------------------------------------------------------------------------------'
     */
    [0] = LAYOUT_planck_mit(
        KC_GESC,	KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,		KC_I,   	KC_O,   	KC_P,    	KC_BSPC, 
		KC_TAB,     KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,		KC_K,   	KC_L,   	KC_SCLN, 	KC_QUOT, 
		KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,		KC_COMM,	KC_DOT, 	KC_SLSH, 	KC_RSFT, 
		KC_LCTL,    KC_CAPS,    KC_LALT,    KC_LGUI,    TT(1),          KC_SPC,             MO(2),		MO(3),   	_______,   	_______,    	KC_ENT
    ),

    /* [1]
     *  * ,-------------------------------------------------------------------------------------.
     * |------------+------+------+------+------+------+------+------+------+------+------+--|
     * | Reset | PgUp | Home |  Up  |  End |  Del |   \  |   7  |   8  |   9  | RGBtg |  BS  |
     * |------------+------+------+------+------+-------------+------+------+------+------+--|
     * | Tab   | PgDn |  Lft |  Dn  |  Rit |   +  |   -  |   J  |   K  |   L  | RGBmod|      |
     * |------------+------+------+------+------+------|------+------+------+------+------+--|
     * | SHIFT | Vol- | Vol+ |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift |
     * |-------+-------+-------+-------+-------+-------+------+------+------+------+------+--|
     * | Ctrl  | Caps |  ALT |  OS  | Ly1  |    SPACE    | Ly2  |  M1  |  M2  |  M3  | Enter |
     * `-------------------------------------------------------------------------------------'
     */
     
    [1] = LAYOUT_planck_mit(
        RESET,		KC_PGUP,	KC_HOME,	KC_UP,		KC_END,		KC_DEL,		KC_BSLS,	KC_7,		KC_8,		KC_9,		RGB_TOG,	_______, 
		_______, 	KC_PGDN, 	KC_LEFT, 	KC_DOWN, 	KC_RGHT, 	KC_PLUS, 	KC_MINS, 	KC_4, 		KC_5, 		KC_6, 		RGB_MOD, 	_______, 
		_______, 	KC_VOLD, 	KC_VOLU, 	_______, 		_______, 		KC_ASTR, 	KC_SLSH, 	KC_1, 		KC_2, 		KC_3, 		RGB_HUI, 	_______,
		RGB_SAI, 	RGB_SAD, 	RGB_VAI, 	RGB_VAD, 	_______, 			KC_0, 			_______, 	_______, 	KC_DOT, 	RGB_HUD, 	KC_EQL
	),

    /* [2]
     * ,-------------------------------------------------------------------------------------.
     * |------------+------+------+------+------+------+------+------+------+------+------+--|
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11  |  F12  |
     * |------------+------+------+------+------+-------------+------+------+------+------+--|
     * |      |  &   |  |   |  (   |  )   |      |      |  {   |  }   |  [   |  ]    |       |
     * |------------+------+------+------+------+-----+-----+------+------+------+------+----|
     * |      |  !   |  @   |  #   |  ^   |      |      |  ~   |  <   |  >   |  ?   |        |
     * |-------+-------+-------+-------+-------+-------+------+------+------+------+---------|
     * |RESET |    |      |       |       |            |      |       |      |       |       |
     * `-------------------------------------------------------------------------------------'
     */
    [2] = LAYOUT_planck_mit(
        KC_F1, 		KC_F2, 		KC_F3, 		KC_F4, 		KC_F5, 		KC_F6, 		KC_F7, 		KC_F8, 		KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 
		_______, 	KC_AMPR, 	KC_PIPE, 	KC_LPRN, 	KC_RPRN, 	KC_PLUS, 	KC_MINS, 	KC_LCBR, 	KC_RCBR, 	KC_LBRC, 	KC_RBRC, 	_______, 
		_______, 	KC_EXLM, 	KC_AT, 		KC_HASH, 	KC_CIRC, 	KC_ASTR, 	KC_SLSH, 	KC_TILD, 	KC_LABK, 	KC_RABK, 	KC_QUES, 	_______, 
		_______, 	_______, 	_______, 	_______, 	_______, 			_______, 		_______, 	_______, 	_______, 	_______, 	_______
	),
}; 
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	//keyevent_t event = record->event;

	switch (id) {
		case 0:
			if (record->event.pressed) {
				return MACRO( D(LGUI), D(LSFT), D(3), U(LGUI), U(LSFT), U(3), END );
			}
			break;
		case 1:
			if (record->event.pressed) {
				return MACRO( D(LCTL), D(LALT), D(LEFT), U(LCTL), U(LALT), U(LEFT), END );
			}
			break;
		case 2:
			if (record->event.pressed) {
				return MACRO( D(LCTL), D(LALT), D(RGHT), U(LCTL), U(LALT), U(RGHT), END );
			}
			break;
		case 3:
			if (record->event.pressed) {
				return MACRO( D(LGUI), D(LSFT), D(4), U(LGUI), U(LSFT), U(4), END );
			}
			break;
		case 4:{
			if(record->event.pressed){
				SEND_STRING("Hello world!");
			}
		}
	}
	return MACRO_NONE;
}
extern rgblight_config_t rgblight_config;
const rgblight_segment_t PROGMEM my_base_layer[] = RGBLIGHT_LAYER_SEGMENTS({24, 4, HSV_CYAN}, {30, 4, HSV_CYAN});

const rgblight_segment_t PROGMEM my_arnumpad_layer[] = RGBLIGHT_LAYER_SEGMENTS({40, 2, HSV_WHITE});

const rgblight_segment_t PROGMEM my_symbol_layer[] = RGBLIGHT_LAYER_SEGMENTS({28, 2, HSV_WHITE});

const rgblight_segment_t PROGMEM my_game_layer[] = RGBLIGHT_LAYER_SEGMENTS({16, 2, HSV_WHITE});
 
const rgblight_segment_t PROGMEM my_macro_layer[] = RGBLIGHT_LAYER_SEGMENTS({5, 1, HSV_WHITE});

/*const rgblight_segment_t PROGMEM my_empty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
	{ 41, 1, HSV_WHITE		}
);*/
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    //my_capslock_layer,
    my_base_layer,			// Default layer
    my_arnumpad_layer,		// Arrow keys & Numpad & Operator keys (both toogle and hold mode to enter this layer)
	my_symbol_layer,		// F1-F12 keys & Symbols (hold mode to enter this layer)
	my_game_layer,			// Self-Defined hotkey layout for A game (toggle mode to enter this layer)
	my_macro_layer			// Self-Defined macro keys layer (hold mode to enter this layer)
	//my_empty_layer			// Preserved layer for customization (Self-Define way to enter this layer)
);
void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}
layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
	rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));
    //rgblight_set_layer_state(5, layer_state_cmp(state, 5));
    return state;
}