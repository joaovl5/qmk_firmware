#include "action_layer.h"
#include "keycodes.h"
#include "keymap_us.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include "troll.h"
#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

#define LAYOUT LAYOUT_split_3x6_3
#define mod_override ko_make_basic
#define SHIFT MOD_MASK_SHIFT

enum LAYERS {
    _ALPHA,
    _NUM,
    _SYM_NAV,
};

enum KEYCODE_ALIASES {
    ___ = _______,
};

enum CUSTOM_KEYCODES {
    // special
    GOTO_ALPHA = SAFE_RANGE,
    // macros (sym)
    DOUBLE_AMPR,
    DOUBLE_PIPE,
    LSQB_ENTER,
    LANB_ENTER,
    LCRB_ENTER,
    LRNB_ENTER,
    COLON_ENTER_ALPHA,
    SEMICOLON_ENTER_ALPHA,
    // macros (shortcuts)
    SC_CUT,
    SC_COPY,
    SC_PASTE,
    SC_UNDO,
    SC_REDO,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_ALPHA] = LAYOUT(
 //,-----------------------------------------------------.     ,-----------------------------------------------------.
  XXX, XXX, KC_L, KC_P, KC_D, KC_F,       KC_RALT, KC_W, KC_O, KC_U, XXX, XXX,
 //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+--------|
  XXX, KC_T, KC_S, KC_N, KC_H, KC_M,       KC_G, KC_C, KC_A, KC_I, KC_E, XXX,
 //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+--------|
  XXX, KC_V, KC_Z, KC_B, KC_K, KC_Q,       KC_X, KC_Y, KC_QUOT, KC_TILDE, KC_J, XXX,
 //|--------+--------+--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------+--------+--------|
           OS_LCTL, KC_R, OS_LSFT,  OS_LGUI, KC_SPACE, OS_LALT
          //`--------------------------' `--------------------------'
  ),
    [_NUM] = LAYOUT(
 //,-----------------------------------------------------.     ,-----------------------------------------------------.
  XXX, XXX, KC_7, KC_8, KC_9, KC_F,       XXX, XXX, LCTL(KC_EQL), LCTL(KC_MINS), XXX, XXX,
 //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+--------|
  GOTO_ALPHA, XXX, KC_1, KC_2, KC_3, KC_0,XXX, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXX,
 //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+--------|
  XXX, XXX, KC_4, KC_5, KC_6, XXX,       XXX, XXX, XXX, XXX, XXX, XXX,
 //|--------+--------+--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------+--------+--------|
           ___, XXX, ___,  XXX, XXX, OS_LALT
          //`--------------------------' `--------------------------'
  ),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) { // ignore if it's key release and not press
        return true;
    }
    switch (keycode) {
        case DOUBLE_AMPR:
            SEND_STRING(" && ");
            break;
        case DOUBLE_PIPE:
            SEND_STRING(" || ");
            break;
        case LSQB_ENTER:
            SEND_STRING("[\n");
            break;
        case LANB_ENTER:
            SEND_STRING("<\n");
            break;
        case LCRB_ENTER:
            SEND_STRING("{\n");
            break;
        case LRNB_ENTER:
            SEND_STRING("(\n");
            break;
        case GOTO_ALPHA:
        case COLON_ENTER_ALPHA:
        case SEMICOLON_ENTER_ALPHA:
            if (keycode == COLON_ENTER_ALPHA) {
                SEND_STRING(":\n");
            } else if (keycode == SEMICOLON_ENTER_ALPHA) {
                SEND_STRING(";\n");
            }
            layer_move(_ALPHA);
            break;
    }
    return true;
}

const key_override_t *key_overrides[] = {
    // basic/alpha layer
    &mod_override(SHIFT, KC_BSPC, KC_DEL),
    &mod_override(SHIFT, KC_TILDE, KC_CIRCUMFLEX),
    &mod_override(SHIFT, OSL(_SYM_NAV), TG(_SYM_NAV)),

    // sym layer
    &mod_override(SHIFT, KC_AMPERSAND, DOUBLE_AMPR),
    &mod_override(SHIFT, KC_PIPE, DOUBLE_PIPE),
    &mod_override(SHIFT, KC_LEFT_BRACKET, LSQB_ENTER),
    &mod_override(SHIFT, KC_LEFT_ANGLE_BRACKET, LANB_ENTER),
    &mod_override(SHIFT, KC_LEFT_CURLY_BRACE, LCRB_ENTER),
    &mod_override(SHIFT, KC_LPRN, LRNB_ENTER),
    &mod_override(SHIFT, KC_COLON, COLON_ENTER_ALPHA),
    &mod_override(SHIFT, KC_SEMICOLON, SEMICOLON_ENTER_ALPHA),
};

// TODO: move to separate file `notifier.c`
#include <stdio.h>
const uint8_t RAW_EPSIZE = 32;
layer_state_t layer_state_set_user(layer_state_t state) {
    int highest_layer = get_highest_layer(state);

    uint8_t response[RAW_EPSIZE];
    memset(response, 0, RAW_EPSIZE);
    snprintf((char *)response, sizeof(response), "layer:%u\n", highest_layer);

    return state;
}

// TODO: move to separate file `oled.c`
/* #ifdef OLED_ENABLE */
#include "../../../../modules/drashna/bongocats/bongocats.h"
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    }
    return rotation;
}

void oled_render_layer_state(void) {
    return;
    /* oled_write_P(PSTR("Layer: "), false); */
    /* switch (layer_state) { */
    /*     case L_BASE: */
    /*         oled_write_ln_P(PSTR("Default"), false); */
    /*         break; */
    /*     case L_LOWER: */
    /*         oled_write_ln_P(PSTR("Lower"), false); */
    /*         break; */
    /*     case L_RAISE: */
    /*         oled_write_ln_P(PSTR("Raise"), false); */
    /*         break; */
    /*     case L_ADJUST: */
    /*     case L_ADJUST | L_LOWER: */
    /*     case L_ADJUST | L_RAISE: */
    /*     case L_ADJUST | L_LOWER | L_RAISE: */
    /*         oled_write_ln_P(PSTR("Adjust"), false); */
    /*         break; */
    /* } */
}

void render_bootmagic_status(bool status) {}

static void render_logo(void) {
    oled_write_raw_P(raw_troll, sizeof(raw_troll));
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_logo();
    } else {
        render_bongocats();
    }
    return false;
}

/* #endif // OLED_ENABLE */
