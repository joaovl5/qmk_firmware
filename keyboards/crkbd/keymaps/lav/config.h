#pragma once

#define TAPPING_TERM 180
#undef FLOW_TAP_TERM
#define FLOW_TAP_TERM 150
#undef CHORDAL_HOLD
#define CHORDAL_HOLD
#undef RETRO_TAPPING
#define RETRO_TAPPING

// #define USE_MATRIX_I2C
#ifdef KEYBOARD_crkbd_rev1_legacy
#    undef USE_I2C
#    define USE_SERIAL
#endif

/* Select hand configuration */

#define MASTER_LEFT

#define USE_SERIAL_PD2

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
