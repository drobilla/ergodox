/* This is the Ergodox layout for drobilla.
 *
 * Inspired by the Kinesis Advantage and standard US layout. Generally strives
 * to preserve or relate to Kinesis/US muscle memory where reasonable, but
 * strives for a more symmetric layout with less shifted programming keys.
 *
 * - All standard IBM US keys can be modified with Ctrl, Alt, Shift, and Gui
 * - Symmetrical modifiers
 * - No dual-purpose hold/tap keys
 * - Various additional keys including all common media keys
 * - German ä, ö, ü, and ß on second layer
 * - Full mouse control with either hand
 * - LEDs show layer 1, layer 2, and lock status, in that order
 *
 * German characters use Mac style input with right alt which can also work on
 * Linux while retaining left alt as a pure modifier.
 */

#include "action_util.h"
#include "ergodox_ez.h"
#include "version.h"

#define SS_RALT(string) SS_DOWN(X_RALT) string SS_UP(X_RALT)

/* Aliases that start with KC_ for use with ERGOMAP macro. */
enum keycode_aliases
{
	KC_MO1  = MO(1),   /* Momentary layer 1 */
	KC_MO2  = MO(2),   /* Momentary layer 2 */
	KC_RSET = RESET,   /* Reset (flash) */
	KC_____ = KC_TRNS, /* Transparent (for 4 character wide ____) */
};

enum custom_keycodes
{
	PLACEHOLDER = SAFE_RANGE,
	KC_VRSN, /* Print version */
	KC_UMA,  /* A with umlaut */
	KC_UMU,  /* U with umlaut */
	KC_UMO,  /* O with umlaut */
	KC_SZET, /* ß */
};

#define ERGOMAP( \
	k00, k01, k02, k03, k04, k05, k06, /**/ k07, k08, k09, k0A, k0B, k0C, k0D, \
	k10, k11, k12, k13, k14, k15, k16, /**/ k17, k18, k19, k1A, k1B, k1C, k1D, \
	k20, k21, k22, k23, k24, k25,      /**/      k28, k29, k2A, k2B, k2C, k2D, \
	k30, k31, k32, k33, k34, k35, k36, /**/ k37, k38, k39, k3A, k3B, k3C, k3D, \
	k40, k41, k42, k43, k44,           /**/           k49, k4A, k4B, k4C, k4D, \
	/**/                               /**/                               /**/ \
	/**/                     k55, k56, /**/ k57, k58,                     /**/ \
	/**/                          k54, /**/ k59,                          /**/ \
	/**/                k53, k52, k51, /**/ k5C, k5B, k5A)                /**/ \
 \
	{ \
		{ KC_##k00, KC_##k10, KC_##k20, KC_##k30, KC_##k40, KC_NO }, \
		{ KC_##k01, KC_##k11, KC_##k21, KC_##k31, KC_##k41, KC_##k51 }, \
		{ KC_##k02, KC_##k12, KC_##k22, KC_##k32, KC_##k42, KC_##k52 }, \
		{ KC_##k03, KC_##k13, KC_##k23, KC_##k33, KC_##k43, KC_##k53 }, \
		{ KC_##k04, KC_##k14, KC_##k24, KC_##k34, KC_##k44, KC_##k54 }, \
		{ KC_##k05, KC_##k15, KC_##k25, KC_##k35, KC_NO,    KC_##k55 }, \
		{ KC_##k06, KC_##k16, KC_NO,    KC_##k36, KC_NO,    KC_##k56 }, \
  \
		{ KC_##k07, KC_##k17, KC_NO,    KC_##k37, KC_NO,    KC_##k57 }, \
		{ KC_##k08, KC_##k18, KC_##k28, KC_##k38, KC_NO,    KC_##k58 }, \
		{ KC_##k09, KC_##k19, KC_##k29, KC_##k39, KC_##k49, KC_##k59 }, \
		{ KC_##k0A, KC_##k1A, KC_##k2A, KC_##k3A, KC_##k4A, KC_##k5A }, \
		{ KC_##k0B, KC_##k1B, KC_##k2B, KC_##k3B, KC_##k4B, KC_##k5B }, \
		{ KC_##k0C, KC_##k1C, KC_##k2C, KC_##k3C, KC_##k4C, KC_##k5C }, \
		{ KC_##k0D, KC_##k1D, KC_##k2D, KC_##k3D, KC_##k4D, KC_NO } \
	}

/* Layer template. */
#define EMPTY_LAYER() ERGOMAP( \
	____,____,____,____,____,____,____, /**/ ____,____,____,____,____,____,____, \
	____,____,____,____,____,____,____, /**/ ____,____,____,____,____,____,____, \
	____,____,____,____,____,____,      /**/      ____,____,____,____,____,____, \
	____,____,____,____,____,____,____, /**/ ____,____,____,____,____,____,____, \
	____,____,____,____,____,           /**/           ____,____,____,____,____, \
	/**/                                /**/                                /**/ \
	/**/                     ____,____, /**/ ____,____,                     /**/ \
	/**/                          ____, /**/ ____,                          /**/ \
	/**/                ____,____,____, /**/ ____,____,____)                /**/

/* Base layer.
 *
 * Minus and equals are currently duplicated because I am experimenting
 * with moving these to follow the usual column wraparound like the F keys.
 *
 * ,-----------------------------------.  ,-----------------------------------.
 * | Esc | 1  | 2  | 3  | 4  | 5  | _  |  | +  | 6  | 7  | 8  | 9  | 0  | Ins |
 * |-----+----+----+----+----+---------|  |----+----+----+----+----+----+-----|
 * | Tab | Q  | W  | E  | R  | T  | (  |  | )  | Y  | U  | I  | O  | P  |  \  |
 * |-----+----+----+----+----+----|    |  |    |----+----+----+----+----+-----|
 * |  `  | A  | S  | D  | F  | G  |----|  |----| H  | J  | K  | L  | ;  |  '  |
 * |-----+----+----+----+----+----| {  |  | }  |----+----+----+----+----+-----|
 * |Shift| Z  | X  | C  | V  | B  |    |  |    | N  | M  | ,  | .  | /  |Shift|
 * `-----+----+----+----+----+---------'  `---------+----+----+----+----+-----'
 *  | L2 | -  | =  |Lft |Rgt |                      | Up |Dwn | [  | ]  | L2 |
 *  `------------------------'                      `------------------------'
 *                           ,---------.  ,---------.
 *                           |Ctl |Alt |  |Alt |Ctl |
 *                      ,----|----|----|  |----+----+----.
 *                      |    |    |Gui |  |Gui |    |    |
 *                      |BSpc|Del |----|  |----|Ent |Spc |
 *                      |    |    | L1 |  | L1 |    |    |
 *                      `--------------'  `--------------'
 */
#define BASE_LAYER() ERGOMAP( \
	ESC , 1  , 2  , 3  , 4  , 5  ,UNDS, /**/ PLUS, 6  , 7  , 8  , 9  , 0  ,INS , \
	TAB , Q  , W  , E  , R  , T  ,LPRN, /**/ RPRN, Y  , U  , I  , O  , P  ,BSLS, \
	GRV , A  , S  , D  , F  , G  ,      /**/       H  , J  , K  , L  ,SCLN,QUOT, \
	LSFT, Z  , X  , C  , V  , B  ,LBRC, /**/ RBRC, N  , M  ,COMM,DOT ,SLSH,RSFT, \
	MO2 ,MINS,EQL ,LEFT,RGHT,           /**/           UP  ,DOWN,LBRC,RBRC,MO2 , \
	/**/                                /**/                                /**/ \
	/**/                     LCTL,LALT, /**/ RALT,RCTL,                     /**/ \
	/**/                          LGUI, /**/ RGUI,                          /**/ \
	/**/                BSPC,DEL ,MO1 , /**/ MO1 ,ENT,SPC  )                /**/


/* System and coarse navigation layer.
 *
 * - Modifiers are the same as base layer so all keys can be modified
 * - The second row roughly corresponds to Macbook function keys:
 *     - F14 and F15 dim and brighten the screen (F1 and F2)
 *     - Volume down and up correspond to F11 and F12
 *     - Top right is power
 * - Home, End, PgUp, PgDown correpond to arrows like on a Macbook
 * - Media is spatial and corresponds to the base thumbs, except mnemonic mute
 * - German ä, ö, ü, and ß are on corresponding ASCII keys
 * - Mnemonics:
 *     - *C*aps Lock
 *     - Scroll *L*ock
 *     - *N*um Lock
 *     - *M*
 *     - Pause / *B*reak
 *     - *P*rint Screen / SysRq
 *     - Menu is where vi users put escape (M and A are taken)
 *
 * ,-----------------------------------.  ,-----------------------------------.
 * | RST | F1 | F2 | F3 | F4 | F5 |F11 |  |F12 | F6 | F7 | F8 | F9 |F10 |Power|
 * |-----+----+----+----+----+---------|  |----+----+----+----+----+----+-----|
 * | F13 |F14 |F15 |F16 |F17 |F18 |VolD|  |VolU|F19 |F20 | Ü  | Ö  |Pr/S|Wake |
 * |-----+----+----+----+----+----|    |  |    |----+----+----+----+----+-----|
 * |Menu | Ä  | ß  |    |File|    |----|  |----|    |    |    |    |ScLk|Sleep|
 * |-----+----+----+----+----+----|Rwnd|  |FFwd|----+----+----+----+----+-----|
 * |Shift|    |    |CpLk|Vrsn|P/Bk|    |  |    |NmLk|Mute|    |    |    |Shift|
 * `-----+----+----+----+----+---------'  `---------+----+----+----+----+-----'
 *  |    |    |    |Home|End |                      |PgUp|PgDn|    |    |    |
 *  `------------------------'                      `------------------------'
 *                           ,---------.  ,---------.
 *                           |Ctl |Alt |  |Alt |Ctl |
 *                      ,----|----|----|  |----+----+----.
 *                      |    |    |Gui |  |Gui |    |    |
 *                      |Prev|Stop|----|  |----|Play|Next|
 *                      |    |    |    |  |    |    |    |
 *                      `--------------'  `--------------'
 */
#define SYS_LAYER() ERGOMAP( \
	RSET, F1 , F2 , F3 , F4 , F5 ,F11 , /**/ F12,  F6 , F7 , F8 , F9 , F10,PWR , \
	F13 ,F14 ,F15 , F16, F17,F18 ,VOLD, /**/ VOLU,F19 ,UMU ,F21 ,UMO ,PSCR,WAKE, \
	APP ,UMA ,SZET,____,MYCM,____,      /**/      ____,____,____,____,SLCK,SLEP, \
	LSFT,____,____,CLCK,VRSN,PAUS,MRWD, /**/ MFFD,NLCK,MUTE,____,____,____,RSFT, \
	____,____,____,HOME,END,            /**/           PGUP,PGDN,____,____,____, \
	/**/                                /**/                                /**/ \
	/**/                     LCTL,LALT, /**/ RALT,RCTL,                     /**/ \
	/**/                          LGUI, /**/ RGUI,                          /**/ \
	/**/                MPRV,MSTP,____, /**/ ____,MPLY,MNXT)                /**/

/* Mouse layer.
 *
 * A mirrored WASD-like layout with wheel on the outside and buttons on thumbs,
 * plus the base layer arrow keys which retain their usual directions.
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
#define MOUSE_LAYER() ERGOMAP( \
	ACL2,____,____,WH_U,____,____,____, /**/ ____,____,____,WH_U,____,____,ACL2, \
	ACL1,____,____,MS_U,____,____,____, /**/ ____,____,____,MS_U,____,____,ACL1, \
	ACL0,WH_L,MS_L,MS_D,MS_R,WH_R,      /**/      WH_L,MS_L,MS_D,MS_R,WH_R,ACL0, \
	____,____,____,WH_D,____,____,____, /**/ ____,____,____,WH_D,____,____,____, \
	____,____,____,MS_L,MS_R,           /**/           MS_U,MS_D,____,____,____, \
	/**/                                /**/                                /**/ \
	/**/                     BTN4,BTN5, /**/ BTN5,BTN4,                     /**/ \
	/**/                          BTN3, /**/ BTN3,                          /**/ \
	/**/                BTN1,BTN2,____, /**/ ____,BTN2,BTN1)                /**/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	BASE_LAYER(),
	SYS_LAYER(),
	MOUSE_LAYER(),
};

void matrix_init_user(void)
{
};

bool process_record_user(const uint16_t keycode, keyrecord_t* const record)
{
	if (record->event.pressed) {
		const uint8_t mods    = get_mods();
		const bool    shifted = mods & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
		bool          ret     = false;

		clear_mods();
		switch (keycode) {
		case KC_VRSN:
			SEND_STRING(QMK_KEYBOARD ":" QMK_KEYMAP " " QMK_VERSION);
			ret = false;
			break;
		case KC_UMA:
 			SEND_STRING(SS_RALT("u"));
			send_char('a' - (shifted * 32));
			ret = false;
			break;
		case KC_UMU:
 			SEND_STRING(SS_RALT("u"));
			send_char('u' - (shifted * 32));
			ret = false;
			break;
		case KC_UMO:
 			SEND_STRING(SS_RALT("u"));
			send_char('o' - (shifted * 32));
			ret = false;
			break;
		case KC_SZET:
 			SEND_STRING(SS_RALT("s"));
			ret = false;
			break;
		default:
			ret = true;
		}
		set_mods(mods);

		return ret;
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
