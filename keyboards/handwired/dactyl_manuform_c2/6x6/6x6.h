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
  R00, R01, R02, R03, R04, R05, \
  R10, R11, R12, R13, R14, R15, \
  R20, R21, R22, R23, R24, R25, \
  R30, R31, R32, R33, R34, R35, \
  R40, R41, R42, R43, R44, R45, \
  R50, R51, R52, R53,           \
                      R60, R61  \
                                  ) \
  { \
    { R00,   R01,   R02, R03, R04, R05 }, \
    { R10,   R11,   R12, R13, R14, R15 }, \
    { R20,   R21,   R22, R23, R24, R25 }, \
    { R30,   R31,   R32, R33, R34, R35 }, \
    { R40,   R41,   R42, R43, R44, R45 }, \
    { KC_NO,   KC_NO,   R52, R53, R51, R50 }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, R61, R60 }  \
}
