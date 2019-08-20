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
    register_code (KC_LCTL);    //define single tap or hold here
    register_code (KC_V);
  }
}

void cole_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {         
    layer_on (_COLEMAK);        //define double tap here
    layer_off (_RAISE);
  } 
  else {    
    unregister_code (KC_V);    //define single tap or hold here
    unregister_code (KC_LCTL);
  }
}

void qwer_count (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {         
    layer_off (_COLEMAK);        //define double tap here
    layer_off (_RAISE);
  } 
  else {    
    register_code (KC_LCTL);    //define single tap or hold here
    register_code (KC_V);
  }
}

void qwer_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {         
    layer_off (_COLEMAK);        //define double tap here
    layer_off (_RAISE);
  } 
  else {    
    unregister_code (KC_V);    //define single tap or hold here
    unregister_code (KC_LCTL);
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [COLEWARP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cole_count, cole_reset)
  // tap for paste, tap twice for colemak layer
  ,[QWERWARP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, qwer_count, qwer_reset)
  // tap for paste, tap twice for qwerty layer
  ,[RESETWARP] = ACTION_TAP_DANCE_DOUBLE(KC_VOLU, RESET)
  // Other declarations would go here, separated by commas, if you have them
};

//In Layer declaration, add tap dance item in place of a key code

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


  [_QWERTY] = LAYOUT_6x6(
     KC_ESC  ,  KC_1  , KC_2  , KC_3  ,  KC_4  , KC_5  ,     
    KC_F12,  KC_Q  , KC_W  , KC_E  ,  KC_R  , KC_T  ,    
  GUI_T(KC_CAPS),  KC_A  , KC_S  , KC_D  ,  KC_F  , KC_G  ,     
         KC_LSFT,  KC_Z, KC_X  , KC_C  ,  KC_V  , KC_B  ,      
          W_UNDO,        W_CUT,        CO_PA, TD(COLEWARP),     KC_LGUI, RAISE ,      
                      W_FIND,KC_VOLD,
                               KC_VOLU,
                 KC_ESC,KC_DEL,KC_BSPC     
                                                             
  ),


  [_COLEMAK] = LAYOUT_6x6(
     KC_TILD,_______,_______,_______,_______,_______,         
     _______,_______,_______,KC_F,KC_P,KC_G,        
     _______,_______,KC_R,KC_S,KC_T,KC_D,         
     _______,_______,_______,_______,_______,_______,        
     _______,_______,_______,TD(QWERWARP),_______,_______,                
             _______,_______,_______,_______,_______,_______      
),

  [_RAISE] = LAYOUT_6x6(
     KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,     
     _______,_______,_______,_______,_______,KC_LBRC,     
     _______,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,KC_LPRN,      
     _______,_______,_______,_______,_______,_______,      
     _______,_______,_______,_______,_______,_______,       
             _______,_______,_______,_______,_______,_______    
  ),

  };

static uint16_t key_timer;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0: {
            if (record->event.pressed) {
                key_timer = timer_read(); // if the key is being pressed, we start the timer.
            }
            else { // this means the key was just released, so we can figure out how long it was pressed for (tap or "held down").
                if (timer_elapsed(key_timer) > 150) { // 150 being 150ms, the threshhold we pick for counting something as a tap.
                    return MACRO( D(LCTL), T(C), U(LCTL), END  );
                }
                else {
                    return MACRO( D(LCTL), T(V), U(LCTL), END  );
                }
            }
            break;
        }
      }
    return MACRO_NONE;
};