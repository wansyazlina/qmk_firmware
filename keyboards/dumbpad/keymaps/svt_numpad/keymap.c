/* Copyright 2019 imchipwood
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

#define _BASE     0
#define _SUB      1
#define _MEDIA    2
#define _GITEMO   3


enum {
    DIFF_LAYR, // Our custom tap dance key; add any other tap dance keys to this enum
};

enum custom_keycodes {
    BYE = SAFE_RANGE,
    GITPUSH,
    GITADD,
    GITSTATUS,
    GITCOMMIT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
        BASE LAYER
   /-----------------------------------------------------`
   |             |    7    |    8    |    9    |  Bkspc  |
   |             |---------|---------|---------|---------|
   |             |    4    |    5    |    6    |  +      |
   |             |---------|---------|---------|---------|
   |             |    1    |    2    |    3    |  -      |
   |-------------|---------|---------|---------|---------|
   | Play/Pause  | TT(_SUB)|    0    |    .    |  =      |
   \-----------------------------------------------------'
  */
  [_BASE] = LAYOUT(
                   KC_P7,    KC_P8,  KC_P9,   KC_BSPC,
                   KC_P4,    KC_P5,  KC_P6,   KC_KP_PLUS,
                   KC_P1,    KC_P2,  KC_P3,   KC_KP_MINUS,
    KC_MPLY,       TD(DIFF_LAYR), KC_P0,  KC_PDOT, KC_EQL
  ),
  /*
        SUB LAYER
   /-----------------------------------------------------`
   |             |         |RGB_M_SW | RGB_M_T | Numlock |
   |             |---------|---------|---------|---------|
   |             |         | RGB_M_B | RGB_M_R | RGB_MOD |
   |             |---------|---------|---------|---------|
   |             |         | RGB_HUI | RGB_HUD | RGB RMOD|
   |-------------|---------|---------|---------|---------|
   |  MO(_MEDIA) |         | RGB_VAI | RGB_VAD | RGB_TOG |
   \-----------------------------------------------------'
  */
  [_SUB] = LAYOUT(
                 _______,     RGB_M_SW,    RGB_M_T,     KC_NLCK,
                 _______,     RGB_M_B,     RGB_M_R,     RGB_MOD,
                 _______,     RGB_HUI,     RGB_HUD,     RGB_RMOD,
    MO(_MEDIA),    TD(DIFF_LAYR),     RGB_VAI,     RGB_VAD,      RGB_TOG
  ),
  /*
        MEDIA & CTRL LAYER
   /-----------------------------------------------------`
   |             |shareSC  |showVideo| string  |         |
   |             |---------|---------|---------|---------|
   |             |         |         |unmute   |leaveMeet|
   |             |---------|---------|---------|---------|
   |             | Chrome  | Save    | Redo    | Undo    |
   |-------------|---------|---------|---------|---------|
   |             |         |  Cut    | Paste   | Copy    |
   \-----------------------------------------------------'
  */
  [_MEDIA] = LAYOUT(
                  RCS(KC_D),    RCS(KC_V),           BYE,       XXXXXXX,
                  KC_MPRV ,     KC_MNXT   ,   LCTL(KC_M),    LCTL(KC_L),
                  LCA(KC_I),      LCTL(KC_S),   LCTL(KC_Y),    LCTL(KC_Z),
    _______,     TD(DIFF_LAYR), LCTL(KC_X) ,   LCTL(KC_V),    LCTL(KC_C)
  ),

   /*
        GIT COMMANDS AND EMOTICONs
   /-----------------------------------------------------`
   |             | emoji   |  emoji  |  emoji  | emoji   |
   |             |---------|---------|---------|---------|
   |             | emoji   | emoji   | emoji   | emoji   |
   |             |---------|---------|---------|---------|
   |             |gitpush  |gitadd   |gitstatus|gitcommit|
   |-------------|---------|---------|---------|---------|
   |             |         |         |         |         |
   \-----------------------------------------------------'
  */
  [_GITEMO] = LAYOUT(
                RALT(KC_A),   RALT(KC_B),   RALT(KC_C) ,   RALT(KC_D),
                RALT(KC_E),    RALT(KC_F),   RALT(KC_G),   RALT(KC_H),
                GITPUSH,          GITADD,       _______,    GITCOMMIT,
    _______,     _______,       _______,        _______,      _______
  ),
};


void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_enable = true;
  //debug_matrix = true;
  //debug_keyboard = true;
  //debug_mouse = true;u

}


void matrix_init_user(void) {
}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}


void encoder_update_user(uint8_t index, bool clockwise) {
  /*  Custom encoder control - handles CW/CCW turning of encoder
   *  Cusotom behavior:
   */
  // left encoder
  if (index == 0) {
    switch (biton32(layer_state)) {
      case _BASE:
        // main layer : PgDN and PgUP
        if (clockwise) {
          writePin(LAYER_INDICATOR_LED_1, true);
          wait_ms(50);
          writePin(LAYER_INDICATOR_LED_1, false);
          //tap_code(KC_PGUP);
          tap_code(KC_MS_WH_UP);
        } else {
          writePin(LAYER_INDICATOR_LED_0, true);
          wait_ms(50);
          writePin(LAYER_INDICATOR_LED_0, false);
          //tap_code(KC_PGDN);
          tap_code(KC_MS_WH_DOWN);
        }
        break;

      case _MEDIA:
        // sub layer : Vol + /-
        // built-in LED is reverse, false is on, true is off
        if (clockwise) {
          writePin(LAYER_INDICATOR_LED_2, false);
          wait_ms(50);
          writePin(LAYER_INDICATOR_LED_2, true);
          tap_code(KC_VOLU);
        } else {
          writePin(LAYER_INDICATOR_LED_3, false);
          wait_ms(50);
          writePin(LAYER_INDICATOR_LED_3, true);
          tap_code(KC_VOLD);
        }
        break;

      default:
        // any other layer (shouldn't exist..) - volume up (CW) and down (CCW)
        if (clockwise) {
          tap_code(KC_MS_WH_UP);
        } else {
          tap_code(KC_MS_WH_DOWN);
        }
        break;
    }
  }

}

//MACRO ------------------------------------------------------- https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/feature_macros

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case BYE:
        if (record->event.pressed) {
            // when keycode BYE is pressed
            SEND_STRING("Thank you and bye dr! :D");
            register_code(KC_ENTER);
        } else {
             unregister_code(KC_ENTER);
            // when keycode BYE is released
        }
        break;

    case GITPUSH:
        if (record->event.pressed) {
            SEND_STRING("git push");
            register_code(KC_ENTER);
        }else {
             unregister_code(KC_ENTER);
        }
        break;


    case GITADD:
        if (record->event.pressed) {
            SEND_STRING("git add --all");
            register_code(KC_ENTER);
        }else {
             unregister_code(KC_ENTER);
        }
        break;


    case GITCOMMIT:
        if (record->event.pressed) {
            SEND_STRING("git commit -m");
        }
        break;


    case GITSTATUS:
        if (record->event.pressed) {
            SEND_STRING("git status");
            register_code(KC_ENTER);
        }else {
             unregister_code(KC_ENTER);
        }
        break;

    }

    return true;
};


//TAPDANCE ------------------------------------------------------------------------- wan syazlina
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_DOUBLE_TAP,
    TD_TRIPLE_TAP,
    TD_FOUR_TAP,
    TD_FIVE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);


//Tap Dance ----------------------------------------------------------------------

// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
    }
    else if (state->count == 2) return TD_DOUBLE_TAP;
    else if (state->count == 3) return TD_TRIPLE_TAP;
    else if (state->count == 4) return TD_FOUR_TAP;
    else if (state->count == 5) {
        if (state->pressed) return TD_FIVE_HOLD;
    }
    return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);

//This allows the dumbpad to switch to other layers as it will turn off all active layer. I made it turn all possible layers.
//Not sure if there are better ways at handling this
            layer_off(0);
            layer_off(1);
            layer_off(2);
            layer_off(3);

    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:

            layer_on(0);
            break;
        case TD_DOUBLE_TAP:

            layer_on(1);
            break;

        case TD_TRIPLE_TAP:

            layer_on(2);
            break;

        case TD_FOUR_TAP:

            layer_on(3);
            break;

        case TD_FIVE_HOLD:
            reset_keyboard();
            break;

        default: break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {

  ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [DIFF_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275)
};

// end of Tap Dance ----------------------------------------------------------------------
