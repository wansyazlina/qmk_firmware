#include QMK_KEYBOARD_H


// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    QUOT_LAYR, // Our custom tap dance key; add any other tap dance keys to this enum
};

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
};


//MACRO - https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/feature_macros

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case QMKBEST:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("Syasya loves harris!");
        } else {
            // when keycode QMKBEST is released
        }
        break;
    }
    return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Layer 0
     * ,-----------------------------------------------------------------------------------.
     * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  <,  |  >.  |  ?   |SEnter|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | L1   | Ctrl | Win  |  Alt |  L3  |    Space    |  L2  |  Up  | Left | Down |Right
       |                                                                              L2   |
     * `-----------------------------------------------------------------------------------'
     */
    [0] = LAYOUT_planck_mit(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH,   KC_SFTENT,
        TT(1),KC_LCTL, KC_LALT, QMKBEST,  TT(3),     KC_SPC,     TT(2), KC_LEFT, KC_UP , KC_DOWN, TD(QUOT_LAYR)
    ),

    /* Layer 1 (r_ Indicates RGB Controls)
     * ,-----------------------------------------------------------------------------------.
     * |      |      |  1   |   2  |  3   |      |      |      |      |      |      |      |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |      |  4   |  5   |  6   |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |      |  7   |  8   |  9   |      |NumL  |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |  0   |      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [1] = LAYOUT_planck_mit(
        _______,  _______, KC_P1,   KC_P2,   KC_P3,    _______,  _______,  _______,   _______,  _______,  _______, _______,
        _______,  _______, KC_P4,   KC_P5,   KC_P6,  _______, _______, _______, _______,  _______, _______, _______,
        _______, _______, KC_P7,   KC_P8,   KC_P9, _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______,  KC_P0, _______,     _______,      _______, _______, _______, _______, _______
    ),

    /* Layer 2 (r_ Indicates RGB Controls)
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   (  |   )  |   *  |      |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |  ~   | Vol+ | Vol- |Mute  |      |      |   \  |   -  |  {   |   }  |      |  \   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |Sat+  |Sat-  |rBrit+|rBrit-|rTog  |      |  =   |   +  |  [   |  ]   |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Brit+|Brit- |      | TogL1|      |      |      |  _   |r_Mode|Hue+  |Hue-  |      |
     * `-----------------------------------------------------------------------------------'
     */
    [2] = LAYOUT_planck_mit(
        KC_GRV,   KC_EXLM,    KC_AT,   KC_HASH,   KC_DLR,  KC_PERC,  KC_CIRC,   KC_AMPR,  KC_LPRN,   KC_RPRN,  KC_ASTR,   _______,
        KC_TILD,  KC_VOLU,  KC_VOLD,   KC_MUTE,  _______, _______, KC_BSLS,  KC_PMNS,   KC_LCBR,  KC_RCBR,   _______,     KC_PIPE,
        RGB_SAI, RGB_SAD,  RGB_VAI,  RGB_VAD, RGB_MOD,  RGB_TOG,  KC_EQL,  KC_PLUS,  KC_LBRC,   KC_RBRC,  _______,   _______,
        KC_BRIU,  KC_BRID,  _______,  TO(0),  _______,  _______,     KC_UNDS,    RGB_RMOD, RGB_HUI,  RGB_HUD,  _______
    ),

    /* Layer 3
     * ,-----------------------------------------------------------------------------------.
     * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | Del  |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      | F11  |  F12 |      |      |      |      |      |      |      |      | Ins  |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      | TogL1|      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [3] = LAYOUT_planck_mit(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
        _______, KC_F11, KC_F12, _______, _______, _______, _______, _______,  _______,  _______, _______, KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
         _______,   _______, _______, TO(1), _______,     _______,      _______, _______, _______, _______, _______
    )
};


//Tap Dance ----------------------------------------------------------------------

// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_RGHT);
            break;
        case TD_SINGLE_HOLD:
            layer_on(2);
            break;

        default: tap_code(KC_RGHT); break;
        // case TD_DOUBLE_TAP:
        //     // Check to see if the layer is already set
        //     if (layer_state_is(2)) {
        //         // If already set, then switch it off
        //         layer_off(2);
        //     } else {
        //         // If not already set, then switch the layer on
        //         layer_on(2);
        //     }
        //     break;

        // case TD_UNKNOWN:
        //     break;

        // case TD_NONE:
        //     break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(2);
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [QUOT_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275)
};

// end of Tap Dance ----------------------------------------------------------------------



void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}


void led_set_user(uint8_t usb_led) {

    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {

    } else {

    }

    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {

    } else {

    }

    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {

    } else {

    }

    if (IS_LED_ON(usb_led, USB_LED_COMPOSE)) {

    } else {

    }

    if (IS_LED_ON(usb_led, USB_LED_KANA)) {

    } else {

    }

}
