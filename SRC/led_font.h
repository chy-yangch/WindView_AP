#include <stdint.h>
#include "NuMicro.h"

extern void unit_show(uint8_t on_off,uint8_t unit_type);
extern void rssi_show(uint8_t on_off,uint8_t rss_level);
extern void led_7seg_number_show(uint8_t on_off,uint16_t value);
extern void led_7seg_text_show(uint8_t on_off,uint8_t word);

enum symbol_item {

	COLON_SYMBOL,		// :
	MINUS_SYMBOL,		// -
	PERCENT_SYMBOL,	// %
	EQUAL_SYMBOL,		// =
	FRENCH_e_SYMBOL,	//e'
	GERMAN_U_SYMBOL,	//U"
	GERMAN_u_SYMBOL,	//u"

};

enum font_text {

	TEXT_A,
	TEXT_B,
	TEXT_C,
	TEXT_D,
	TEXT_E,
	TEXT_F,
	TEXT_G,
	TEXT_H,
	TEXT_I,
	TEXT_J,
	TEXT_K,
	TEXT_L,
	TEXT_M,
	TEXT_N,
	TEXT_O,
	TEXT_P,
	TEXT_Q,
	TEXT_R,
	TEXT_S,
	TEXT_T,
	TEXT_U,
	TEXT_V,
	TEXT_W,
	TEXT_X,
	TEXT_Y,
	TEXT_Z,

};

enum rssi_level {

	RSSI_LV0,
	RSSI_LV1,
	RSSI_LV2,
	RSSI_LV3,
	RSSI_LV4,
};

enum unit_typel {

	UNIT_MS,
	UNIT_KM,
	UNIT_MP,

};

enum led_7seg_text_item {

	TEXT_DEV,
	TEXT_AD,
	TEXT_THR,
	TEXT_SND,
	TEXT_DUR,
	TEXT_FLA,
	TEXT_BRL,
	TEXT_UNT,
	TEXT_NOD,

};



