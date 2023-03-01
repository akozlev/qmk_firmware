#include QMK_KEYBOARD_H

#include "swapper.h"
#include "oneshot.h"

#define HOME KC_HOME
#define END KC_END

#define WSTRL G(C(A(KC_LEFT)))
#define WSTRR G(C(A(KC_RGHT)))
#define WSTRU G(C(A(KC_UP)))
#define WSTRD G(C(A(KC_DOWN)))

#define ZONEL G(KC_PGDN)
#define ZONER G(KC_PGUP)

#define SPC_L C(G(KC_LEFT))
#define SPC_R C(G(KC_RGHT))

#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)

#define TO_GAME TO(GAME)
#define TO_DEF TO(DEF)

#define ALT_F4 A(KC_F4)
#define S_TAB S(KC_TAB)
// #define CW_TOGG QK_CAPS_WORD_TOGGLE

// Power Toys Run
#define PT_RUN MEH(KC_SPC)

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    DEF,
    SYM,
    NAV,
    NUM,
    GAME,
};

enum custom_keycodes {
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    SW_WIN,  // Switch to next window         (cmd-tab)
    SW_LANG, // Switch to next input language (ctl-spc)

    ARROW,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [DEF] = LAYOUT(
      // KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    TO_GAME,
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      KC_DEL,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
      KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
      _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_MUTE,  KC_MPLY, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
                        _______, _______, KC_LALT,  KC_SPC, LA_NAV,  LA_SYM,  KC_LSFT, KC_LGUI, _______, _______
  ),

  [SYM] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, KC_CAPS, KC_LBRC, KC_LCBR, KC_LPRN, KC_GRV,                    KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, _______, _______,
      _______, KC_MINS, KC_ASTR, KC_EQL,  KC_UNDS, KC_DLR,                    KC_HASH, OS_CTRL, OS_SHFT, OS_ALT,  OS_CMD,  _______,
      _______, KC_PLUS, KC_PIPE, KC_AT,   KC_BSLS, KC_PERC, _______, _______, KC_TILD, KC_AMPR, KC_SCLN, KC_COLN, KC_EXLM, _______,
                        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, ALT_F4,  SW_WIN,  ZONEL,   ZONER,   PT_RUN,                    KC_PSCR, HOME,    KC_UP,   END,     CW_TOGG, _______,
      _______, OS_CMD,  OS_ALT,  OS_SHFT, OS_CTRL, _______,                   S_TAB,   KC_LEFT, KC_DOWN, KC_RGHT, KC_TAB,  _______,
      _______, SPC_L,   SPC_R,   WSTRL,   WSTRR,   _______, KC_MPRV, KC_MNXT, KC_APP,  KC_PGDN, KC_PGUP, SW_LANG, ARROW,  _______,
                        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [NUM] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______,
      _______, KC_7,    KC_5,    KC_3,    KC_1,    KC_9,                     KC_8,    KC_0,    KC_2,    KC_4,    KC_6,    _______,
      _______, OS_CMD,  OS_ALT,  OS_SHFT, OS_CTRL, KC_F11,                   KC_F10,  OS_CTRL, OS_SHFT, OS_ALT,  OS_CMD,  _______,
      _______, KC_F7,   KC_F5,   KC_F3,   KC_F1,   KC_F9,  _______, _______, KC_F8,   KC_F12,  KC_F2,   KC_F4,   KC_F6,   _______,
                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
};

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("MODE"), false);
    oled_write_ln_P(PSTR(""), false);
    if (keymap_config.swap_lctl_lgui) {
        oled_write_ln_P(PSTR("MAC"), false);
    } else {
        oled_write_ln_P(PSTR("WIN"), false);
    }

    switch (get_highest_layer(default_layer_state)) {
        case DEF:
            oled_write_ln_P(PSTR("DEF"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case DEF:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case SYM:
            oled_write_P(PSTR("SYM\n"), false);
            break;
        case NAV:
            oled_write_P(PSTR("NAV\n"), false);
            break;
        case NUM:
            oled_write_P(PSTR("NUM\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();

    if(led_usb_state.caps_lock)
    {
        oled_write_ln_P(PSTR("CPSLK"), false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
}

#endif

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

bool sw_win_active = false;
bool sw_lang_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, KC_LALT, KC_TAB, SW_WIN,
        keycode, record
    );
    update_swapper(
        &sw_lang_active, KC_LGUI, KC_SPC, SW_LANG,
        keycode, record
    );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );
    switch (keycode) {
        case ARROW:
            if (record->event.pressed) {
                SEND_STRING("->");
            }
            return false;
    }

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}

#endif
