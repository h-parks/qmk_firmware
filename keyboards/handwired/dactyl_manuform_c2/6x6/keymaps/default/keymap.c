#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "wait.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _COLEMAK 1
#define _RAISE 2
#define CO_PA M(0)                  // hold copy, tap paste
#define W_CUT    LCTL(KC_X)         // C-x Cut
#define W_COPY   LCTL(KC_C)         // C-c Copy
#define W_PASTE  LCTL(KC_V)         // C-v Paste
#define W_UNDO   LCTL(KC_Z)         // C-z Undo
#define W_FIND   LCTL(KC_F)         // C-v Find

#define RAISE MO(_RAISE)
#define LOWER MO(_COLEMAK)

//Tap Dance Declarations
enum {
  COLEWARP,
  QWERWARP,
  RESETWARP
};

void cole_count (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {         
    layer_on (_COLEMAK);        //define double tap here
    layer_off (_RAISE);
  } 
  else {    
    register_code (KC_MUTE);    //define single tap or hold here
  }
}

void cole_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {         
    layer_on (_COLEMAK);        //define double tap here
    layer_off (_RAISE);
  } 
  else {    
    unregister_code (KC_MUTE);    //define single tap or hold here
  }
}

void qwer_count (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {         
    layer_off (_COLEMAK);        //define double tap here
    layer_off (_RAISE);
  } 
  else {    
    register_code (KC_MUTE);    //define single tap or hold here
  }
}

void qwer_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {         
    layer_off (_COLEMAK);        //define double tap here
    layer_off (_RAISE);
  } 
  else {    
    unregister_code (KC_MUTE);    //define single tap or hold here
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [COLEWARP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cole_count, cole_reset)
  // tap for paste, tap twice for colemak layer
  ,[QWERWARP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, qwer_count, qwer_reset)
  ,[RESETWARP] = ACTION_TAP_DANCE_DOUBLE(KC_F4, RESET)
  // tap for paste, tap twice for qwerty layer
  // Other declarations would go here, separated by commas, if you have them
};

//In Layer declaration, add tap dance item in place of a key code

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


  [_QWERTY] = LAYOUT_6x6(
KC_6  , KC_7   , KC_8   , KC_9   , KC_0  ,KC_MINS,
KC_Y  , KC_U   , KC_I   , KC_O   , KC_P  ,KC_BSLS,
KC_H  , KC_J   , KC_K   , KC_L   ,KC_SCLN,KC_QUOT,
KC_N  , KC_M   ,KC_COMM , KC_DOT ,KC_SLSH,KC_RSFT,
KC_NO , KC_ENT , KC_LEFT, KC_UP, KC_DOWN,KC_RIGHT,
RALT_T(KC_ENT),KC_EQL, 
TD(COLEWARP),
TD(RESETWARP), CTL_T(KC_TAB), KC_SPC
                                                             
  ),


  [_COLEMAK] = LAYOUT_6x6(
        _______,_______,_______,_______,_______,_______,
        KC_J,KC_L,KC_U,KC_Y,KC_SCLN,_______,
        _______,KC_N,KC_E,KC_I,KC_O,_______,
        KC_K,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,             
        _______,_______,TD(QWERWARP),_______,_______,_______
),

  [_RAISE] = LAYOUT_6x6(
        KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL,
        KC_RBRC, KC_P7 , KC_P8 , KC_P9 ,_______,KC_PLUS,
        KC_RPRN, KC_P4 , KC_P5 , KC_P6 ,KC_MINS,KC_PIPE,
        KC_P0  , KC_P1 , KC_P2 , KC_P3 ,KC_EQL ,KC_UNDS,
        _______,_______,_______,_______,_______,_______,             
        _______,_______,_______,_______,_______,_______
  ),

  };
