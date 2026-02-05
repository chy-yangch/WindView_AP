#include <stdint.h>
#include "NuMicro.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern uint8_t unit_show(uint8_t on_off,uint8_t unit_type);
extern uint8_t rssi_show(uint8_t on_off,uint8_t rss_level);
extern uint8_t led_7seg_number_show(uint8_t on_off,uint16_t value);
extern uint8_t led_7seg_text_show(uint8_t on_off,uint8_t word);

struct LED_Font{

	 //void (*p_read_RTC)();
	uint8_t (*unit_show)(uint8_t on_off,uint8_t unit_type);
	uint8_t (*rssi_show)(uint8_t on_off,uint8_t rss_level);
	uint8_t (*led_7seg_number_show)(uint8_t on_off,uint16_t value);
	uint8_t (*led_7seg_text_show)(uint8_t on_off,uint8_t word);
	uint8_t (*led_7seg_pic_show)(uint8_t on_off,uint8_t pic_item,uint8_t item_index);
	uint8_t (*led_n1_text)(uint8_t on_off,uint8_t text);
	uint8_t (*led_n2_text)(uint8_t on_off,uint8_t text);
	uint8_t (*led_n3_text)(uint8_t on_off,uint8_t text);
	uint8_t (*led_n1_number)(uint8_t on_off,uint8_t no);
	uint8_t (*led_n2_number)(uint8_t on_off,uint8_t no);
	uint8_t (*led_n3_number)(uint8_t on_off,uint8_t no);
};

extern void led_font_init(void);
extern struct LED_Font led_font_fun;

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

//enum unit_typel {

//	UNIT_MS,
//	UNIT_KM,
//	UNIT_MP,

//};

enum led_7seg_text_item {

	TEXT_DEV,
	TEXT_AD,
	TEXT_THR,
	TEXT_SND,
	TEXT_DUR,
	TEXT_FLA,
	TEXT_BRI,
	TEXT_UNT,
	TEXT_NOD,
	TEXT_YES,

};

enum led_7seg_pic_item {

	PIC_ALL_ON,
	PIC_TURN_ON_MOVE,
	PIC_NO_LINK,
	PIC_RESET_ROLL,

};

