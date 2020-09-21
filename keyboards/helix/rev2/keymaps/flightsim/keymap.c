#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _MODE1 = 0,
    _MODE2
};

enum custom_keycodes {
  MODE1 = SAFE_RANGE,
  MODE2,
  LALT9,
  LALT4,
  RALTI,
  RSFTI,
  LALT5,
  LALT1,
  RALTMIN,
  RALTEQ,
  LALT6,
  LALT2,
  RCTLMIN,
  RCTLEQ,
  LSFTA,
  LALT3
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

#if MATRIX_ROWS == 8 // HELIX_ROWS == 4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* MODE1
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   I  |LAlt+9|LAlt+4|   A  |   5  |   1  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |RAlt+I|RSft+I|LAlt+5|LAlt+1|   6  |   2  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |RAlt+-|RAlt+=|LAlt+6|LAlt+2|   7  |   3  |             |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |RCtl+-|RCtl-=|LSft+A|LAlt+3|   8  |   4  | Mode2|Space |      |       | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_MODE1] = LAYOUT( \
      KC_I,    LALT9,   LALT4,   KC_A,    KC_5,    KC_1,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
      RALTI,   RSFTI,   LALT5,   LALT1,   KC_6,    KC_2,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      RALTMIN, RALTEQ,  LALT6,   LALT2,   KC_7,    KC_8,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
      RCTLMIN, RCTLEQ,  LSFTA,   LALT3,   KC_8,    KC_4,   MODE2,  KC_SPC,  KC_SPC,  KC_SPC ,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
      ),

   /* MODE2
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   I  |LAlt+9|LAlt+4|   A  |   5  |   1  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |RAlt+I|RSft+I|LAlt+5|LAlt+1|   6  |   2  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |RAlt+-|RAlt+=|LAlt+6|LAlt+2|   7  |   3  |             |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |RCtl+-|RCtl-=|LSft+A|LAlt+3|   8  |   4  | Mode1|Space |      |      | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_MODE2] = LAYOUT( \
      KC_I,    LALT9,   LALT4,   KC_A,    KC_5,    KC_1,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
      RALTI,   RSFTI,   LALT5,   LALT1,   KC_6,    KC_2,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      RALTMIN, RALTEQ,  LALT6,   LALT2,   KC_7,    KC_8,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
      RCTLMIN, RCTLEQ,  LSFTA,   LALT3,   KC_8,    KC_4,   MODE1,  KC_SPC, KC_SPC ,  KC_SPC ,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
      )
};

#else
#error "undefined keymaps"
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MODE1:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_MODE1);
      }
      return false;
      break;
    case MODE2:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_MODE2);
      }
      return false;
      break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case LALT9:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT("9"));
      }
      return false;
      break;
    case LALT1:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT("1"));
      }
      return false;
      break;
    case LALT2:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT("2"));
      }
      return false;
      break;
    case LALT3:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT("3"));
      }
      return false;
      break;
    case LALT4:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT("4"));
      }
      return false;
      break;
    case LALT5:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT("5"));
      }
      return false;
      break;
    case LALT6:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT("6"));
      }
      return false;
      break;
    case RALTI:
      if (record->event.pressed) {
        SEND_STRING(SS_RALT("i"));
      }
      return false;
      break;
    case RALTMIN:
      if (record->event.pressed) {
        SEND_STRING(SS_RALT("-"));
      }
      return false;
      break;
    case RALTEQ:
      if (record->event.pressed) {
        SEND_STRING(SS_RALT("="));
      }
      return false;
      break;
    case RSFTI:
      if (record->event.pressed) {
        SEND_STRING(SS_RSFT("i"));
      }
      return false;
      break;
    case LSFTA:
      if (record->event.pressed) {
        SEND_STRING(SS_LSFT("a"));
      }
      return false;
      break;
    case RCTLEQ:
      if (record->event.pressed) {
        SEND_STRING(SS_RCTL("="));
      }
      return false;
      break;
    case RCTLMIN:
      if (record->event.pressed) {
        SEND_STRING(SS_RCTL("-"));
      }
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

static void render_logo(struct CharacterMatrix *matrix) {

  static const char helix_logo[] PROGMEM ={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write_P(matrix, helix_logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}

static void render_rgbled_status(bool full, struct CharacterMatrix *matrix) {
#ifdef RGBLIGHT_ENABLE
  char buf[30];
  if (RGBLIGHT_MODES > 1 && rgblight_config.enable) {
      if (full) {
          snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ",
                   rgblight_config.mode,
                   rgblight_config.hue/RGBLIGHT_HUE_STEP,
                   rgblight_config.sat/RGBLIGHT_SAT_STEP,
                   rgblight_config.val/RGBLIGHT_VAL_STEP);
      } else {
          snprintf(buf, sizeof(buf), "[%2d] ",rgblight_config.mode);
      }
      matrix_write(matrix, buf);
  }
#endif
}

static void render_layer_status(struct CharacterMatrix *matrix) {
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[10];
  matrix_write_P(matrix, PSTR("Layer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        case L_RAISE:
           matrix_write_P(matrix, PSTR("Raise"));
           break;
        case L_LOWER:
           matrix_write_P(matrix, PSTR("Lower"));
           break;
        case L_ADJUST:
        case L_ADJUST_TRI:
           matrix_write_P(matrix, PSTR("Adjust"));
           break;
        default:
           matrix_write_P(matrix, PSTR("Undef-"));
           snprintf(buf,sizeof(buf), "%ld", layer_state);
           matrix_write(matrix, buf);
    }
}

void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static const char os_logo[][2][3] PROGMEM  ={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write_P(matrix, os_logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write_P(matrix, os_logo[0][1]);
  }else{
    matrix_write_P(matrix, os_logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write_P(matrix, os_logo[1][1]);
  }

  matrix_write_P(matrix, PSTR(" "));
  render_layer_status(matrix);
  matrix_write_P(matrix, PSTR("\n"));

  // Host Keyboard LED Status
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ?
                 PSTR("NUMLOCK") : PSTR("       "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ?
                 PSTR("CAPS") : PSTR("    "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ?
                 PSTR("SCLK") : PSTR("    "));
  matrix_write_P(matrix, PSTR("\n"));
  render_rgbled_status(true, matrix);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
    render_rgbled_status(false, &matrix);
    render_layer_status(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
