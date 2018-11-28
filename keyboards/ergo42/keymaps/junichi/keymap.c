#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define QWERTY 0
#define LOWER 1
#define RAISE 2
#define ADJUST 3

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,---------------------------------------------- -.,------------------------------------------------.
   * | Esc  |   Q  |   W  |   E  |   R  |   T  |   [  ||   ]  |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------+------||------+------+------+------+------+------+------|
   * |Ctl/Tb|   A  |   S  |   D  |   F  |   G  |   (  ||   )  |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+------||------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   {  ||   }  |   N  |   M  |   ,  |   .  |   /  |Shift |
   * |------+------+------+------+------+------+------||------+------+------+------+------+------+------|
   * |Adjust| Caps |      |      |GUI/MH|Lower |Space ||Enter |Raise |Alt/HK| Left | Down |  Up  |Right |
   * `--------------------------------------------------------------------------------------------------'
   */
  [QWERTY] = LAYOUT( \
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,       KC_RBRC,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
    LCTL_T(KC_TAB), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    S(KC_9),       S(KC_0),    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    S(KC_LBRC),    S(KC_RBRC), KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT), \
    MO(ADJUST), KC_CAPS, _______, _______, GUI_T(KC_INT5), MO(LOWER),   KC_SPC,        KC_ENT,     MO(RAISE),ALT_T(KC_INT4),KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),


  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |   -  |   =  |   {  |   }  |  |   |   `  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |  _   |   +  |   [  |   ]  |   \  |   ~  |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
   * `-------------------------------------------------------------------------------------------------'
   */
  [LOWER] = LAYOUT( \
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______,    KC_MINS,   KC_EQL,  KC_LCBR,  KC_RCBR,  KC_PIPE,   KC_GRV, \
      _______, _______, _______, _______, _______, _______, _______, _______,   KC_UNDS,  KC_PLUS,  KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_TILD, \
      _______, _______, _______, _______, _______, _______, _______,  _______, MO(ADJUST),_______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
    ),

    /* Raise
     * ,-----------------------------------------.             ,-----------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 |      |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |      | F11  |  F12 |  F13 |  F14 |  F15 |             |  F16 |  F17 |   ,  |   .  |   /  |      |
     * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |PageDn|PageUp|      |
     * `-------------------------------------------------------------------------------------------------'
     */
  [RAISE] = LAYOUT( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   _______, _______,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
      _______, KC_F1,   KC_F2,   KC_F3,    KC_F4,    KC_F5,  _______, _______,     KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10, _______,\
      _______, KC_F11,  KC_F12,  KC_F13,   KC_F14,   KC_F15,  _______, _______,  KC_F16,   KC_F17,  KC_COMM,   KC_DOT,  KC_SLSH,  KC_RSFT,\
      _______, _______, _______, _______, _______, MO(ADJUST), _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______\
    ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      | Reset|      |      |      |      |             |      |      |      |      |      |  Del |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |Aud on|Audoff| Mac  |             | LEFT | DOWN | UP   | RIGHT|      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |RGBRST|RGB ON| HUE+ | SAT+ | VAL+ |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | MODE | HUE- | SAT- | VAL- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [ADJUST] =  LAYOUT( \
      _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL, \
      _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
    )

};
