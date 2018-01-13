/* David Robillard's ErgoDox EZ layout.
 *
 * Inspired by the Kinesis Advantage, with some modifications:
 *
 * - All standard US 104 IBM keys can be modified with Ctrl, Alt, Shift, and Gui
 * - Symmetrical modifiers
 * - Various additional keys including all common media keys
 * - Full mouse control with either hand
 * - LEDs show layer 1, layer 2, and lock status, in that order
 */

#include "action_layer.h"
#include "debug.h"
#include "ergodox_ez.h"
#include "version.h"

enum custom_keycodes
{
	PLACEHOLDER = SAFE_RANGE,
	VRSN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* Layer 0: Basic.
	 *
	 * Minus and equals are currently duplicated because I am experimenting
	 * with moving these to follow the usual column wraparound like the F keys.
	 *
	 * ,-----------------------------------.  ,-----------------------------------.
	 * |  =  | 1  | 2  | 3  | 4  | 5  | -  |  |  = | 6  | 7  | 8  | 9  | 0  |  -  |
	 * |-----+----+----+----+----+---------|  |----+----+----+----+----+----+-----|
	 * | Tab | Q  | W  | E  | R  | T  |Back|  | Fwd| Y  | U  | I  | O  | P  |  \  |
	 * |-----+----+----+----+----+----|    |  |    |----+----+----+----+----+-----|
	 * | Esc | A  | S  | D  | F  | G  |----|  |----| H  | J  | K  | L  | ;  |  '  |
	 * |-----+----+----+----+----+----|Menu|  |Menu|----+----+----+----+----+-----|
	 * |Shift| Z  | X  | C  | V  | B  |    |  |    | N  | M  | ,  | .  | /  |Shift|
	 * `-----+----+----+----+----+---------'  `---------+----+----+----+----+-----'
	 *  | L3 | `  |Ins |Lft |Rgt |                      | Up | Dwn| [  |  ] | L3 |
	 *  `------------------------'                      `------------------------'
	 *                           ,---------.  ,---------.
	 *                           |Ctl |Alt |  |Alt |Ctl |
	 *                      ,----|----|----|  |----+----+----.
	 *                      |    |    |Gui |  |Gui |    |    |
	 *                      |BSpc|Del |----|  |----|Ent |Spc |
	 *                      |    |    | L2 |  | L2 |    |    |
	 *                      `--------------'  `--------------'
	 */
	[0] = KEYMAP(
		KC_EQL,  KC_1,    KC_2,   KC_3,    KC_4,    KC_5,    KC_MINS,
		KC_TAB,  KC_Q,    KC_W,   KC_E,    KC_R,    KC_T,    KC_WBAK,
		KC_ESC,  KC_A,    KC_S,   KC_D,    KC_F,    KC_G,
		KC_LSFT, KC_Z,    KC_X,   KC_C,    KC_V,    KC_B,    KC_LBRC,
		MO(2),   KC_GRV,  KC_INS, KC_LEFT, KC_RGHT,

		/* */                                       KC_LCTL, KC_LALT,
		/* */                                                KC_LGUI,
		/* */                              KC_BSPC, KC_DEL,  MO(1),

		KC_EQL,  KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS,
		KC_WFWD, KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_BSLS,
		/* */    KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
		KC_APP,  KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
		/* */             KC_UP,  KC_DOWN, KC_LBRC, KC_RBRC, MO(2),

		KC_RALT, KC_RCTL,
		KC_RGUI,
		MO(1),   KC_ENT,  KC_SPC),

	/* Layer 1: Media, system, locks, coarse navigation.
	 *
	 * - Modifiers are the same as base layer so all keys can be modified
	 * - The second row roughly corresponds to Macbook function keys:
	 *     - F14 and F15 dim and brighten the screen (F1 and F2)
	 *     - Volume down and up correpond to F11 and F12
	 *     - Top right is power
	 * - Home, End, PgUp, PgDown correpond to arrows like on a Macbook
	 * - Media is spatial and corresponds to the base layer thumbs, except mnemonic mute
	 * - Lock keys are mnemonic (s = scroll lock, c = caps lock, n = num lock)
	 * - Eject is like escape
	 *
	 * ,-----------------------------------.  ,-----------------------------------.
	 * | RST | F1 | F2 | F3 | F4 | F5 |F11 |  |F12 | F6 | F7 | F8 | F9 |F10 |Power|
	 * |-----+----+----+----+----+---------|  |----+----+----+----+----+----+-----|
	 * | F13 |F14 |F15 |F16 |F17 |F18 |VolD|  |VolU|F19 |F20 |F21 |F22 |F23 |Wake |
	 * |-----+----+----+----+----+----|    |  |    |----+----+----+----+----+-----|
	 * |Eject|    |ScLk|    |File|    |----|  |----|    |    |    |    |    |Sleep|
	 * |-----+----+----+----+----+----|Rwnd|  |FFwd|----+----+----+----+----+-----|
	 * |Shift|    |    |CpLk|Vrsn|    |    |  |    |NmLk|Mute|    |    |    |Shift|
	 * `-----+----+----+----+----+---------'  `---------+----+----+----+----+-----'
	 *  |    |Pr/S|    |Home|End |                      |PgUp|PgDn|    |P/Bk|    |
	 *  `------------------------'                      `------------------------'
	 *                           ,---------.  ,---------.
	 *                           |Ctl |Alt |  |Alt |Ctl |
	 *                      ,----|----|----|  |----+----+----.
	 *                      |    |    |Gui |  |Gui |    |    |
	 *                      |Prev|Stop|----|  |----|Play|Next|
	 *                      |    |    | L2 |  | L2 |    |    |
	 *                      `--------------'  `--------------'
	 */
	[1] = KEYMAP(
		RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,
		KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_VOLD,
		KC_EJCT, _______, KC_SLCK, _______, KC_MYCM, _______,
		KC_LSFT, _______, _______, KC_CLCK, VRSN,    _______, KC_MUTE,
		_______, KC_PSCR, _______, KC_HOME, KC_END,

		/* */                                        _______, _______,
		/* */                                                 KC_MRWD,
		/* */                               KC_MPRV, KC_MSTP, _______,

		KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PWR,
		KC_VOLU, KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_WAKE,
		/* */    _______, _______, _______, _______, _______, KC_SLEP,
		KC_MUTE, KC_NLCK, KC_MUTE, _______, _______, _______, KC_RSFT,
		/* */             KC_PGUP, KC_PGDN, _______, KC_PAUS, _______,

		KC_RALT, KC_RCTL,
		KC_MFFD,
		_______, KC_MPLY, KC_MNXT),

	/* Layer 2: Mouse
	 *
	 * A mirrored WASD-like layout with wheel on the outside and thumb buttons,
	 * plus the base layer arrow keys which retain their usual meaning.
	 *
	 * ,-----------------------------------.  ,-----------------------------------.
	 * |Accl2|    |    | WU |    |    |    |  |    |    |    | WU |    |    |Accl2|
	 * |-----+----+----+----+----+---------|  |----+----+----+----+----+----+-----|
	 * |Accl1|    |    | MU |    |    |    |  |    |    |    | MU |    |    |Accl1|
	 * |-----+----+----+----+----+----|    |  |    |----+----+----+----+----+-----|
	 * |Accl0| WL | ML | MD | MR | WR |----|  |----| WL | ML | MD | MR | WR |Accl0|
	 * |-----+----+----+----+----+----|    |  |    |----+----+----+----+----+-----|
	 * |     |    |    | WD |    |    |    |  |    |    |    | WD |    |    |     |
	 * `-----+----+----+----+----+---------'  `---------+----+----+----+----+-----'
	 *  |    |    |    | ML | MR |                      | MU | MD |    |    |    |
	 *  `------------------------'                      `------------------------'
	 *                           ,---------.  ,---------.
	 *                           |But4|But5|  |But5|But4|
	 *                      ,----|----|----|  |----+----+----.
	 *                      |    |    |But3|  |But3|    |    |
	 *                      |But1|But2|----|  |----|But2|But1|
	 *                      |    |    |    |  |    |    |    |
	 *                      `--------------'  `--------------'
	 */
	[2] = KEYMAP(
		_______, _______, _______, KC_WH_U, _______, _______, KC_ACL2,
		_______, _______, _______, KC_MS_U, _______, _______, KC_ACL1,
		_______, KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R,
		_______, _______, _______, KC_WH_D, _______, _______, KC_ACL0,
		_______, _______, _______, KC_MS_L, KC_MS_R,

		/* */                                        KC_BTN4, KC_BTN5,
		/* */                                                 KC_BTN3,
		/* */                               KC_BTN1, KC_BTN2, _______,

		KC_ACL2, _______, _______, KC_WH_U, _______, _______, _______,
		KC_ACL1, _______, _______, KC_MS_U, _______, _______, _______,
		/* */    KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R, _______,
		KC_ACL0, _______, _______, KC_WH_D, _______, _______, _______,
		/* */             KC_MS_U, KC_MS_D, _______, _______, _______,

		KC_BTN5, KC_BTN4,
		KC_BTN3,
		_______, KC_BTN2, KC_BTN1),

};

const uint16_t PROGMEM fn_actions[] = {[1] = ACTION_LAYER_TAP_TOGGLE(1)};

void matrix_init_user(void)
{
};

bool process_record_user(const uint16_t keycode, keyrecord_t* const record)
{
	switch (keycode) {
	case VRSN:
		if (record->event.pressed) {
			SEND_STRING(QMK_KEYBOARD ":" QMK_KEYMAP " " QMK_VERSION);
		}
		return false;
	}
	return true;
}

void led_set_user(const uint8_t usb_led)
{
	/* LED 3: Lock */
	if ((usb_led & (1 << USB_LED_CAPS_LOCK)) ||
	    (usb_led & (1 << USB_LED_NUM_LOCK)) ||
	    (usb_led & (1 << USB_LED_SCROLL_LOCK))) {
		ergodox_right_led_3_on();
	} else {
		ergodox_right_led_3_off();
	}
}

uint32_t layer_state_set_user(const uint32_t state)
{
	const uint8_t layer = biton32(state);

	/* LED 1: Layer 1 */
	if (layer == 1) {
		ergodox_right_led_1_on();
	} else {
		ergodox_right_led_1_off();
	}

	/* LED 2: Layer 2 */
	if (layer == 2) {
		ergodox_right_led_2_on();
	} else {
		ergodox_right_led_2_off();
	}

	return state;
};
