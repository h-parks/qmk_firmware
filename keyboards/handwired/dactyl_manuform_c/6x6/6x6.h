#pragma once

#include "dactyl_manuform_c.h"
#include "quantum.h"


#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
  #include <avr/io.h>
  #include <avr/interrupt.h>
#endif
#endif

#define LAYOUT_6x6(\
  L00, L01, L02, L03, L04, L05, \
  L10, L11, L12, L13, L14, L15, \
  L20, L21, L22, L23, L24, L25, \
  L30, L31, L32, L33, L34, L35, \
  L40, L41, L42, L43, L44, L45, \
  L50, L51, L52, L53,           \
                      L60, L61  \
                                  ) \
  { \
    { L00,   L01,   L02, L03, L04, L05 }, \
    { L10,   L11,   L12, L13, L14, L15 }, \
    { L20,   L21,   L22, L23, L24, L25 }, \
    { L30,   L31,   L32, L33, L34, L35 }, \
    { L40,   L41,   L42, L43, L44, L45 }, \
    { L50,   L51,   L52, L53, KC_NO, KC_NO }, \
    { L60, L61, KC_NO, KC_NO, KC_NO, KC_NO }  \
}
