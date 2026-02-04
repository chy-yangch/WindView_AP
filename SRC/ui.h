#include "NuMicro.h"
#ifdef __cplusplus
extern "C"
{
#endif

#define UI_PAUSE_2_SEC	20

enum ui_item {

	PAGE_MAIN,
	PAGE_DEV,
	PAGE_AD,
	PAGE_THR,
	PAGE_SND,
	PAGE_DUR,
	PAGE_FLA,
	PAGE_BRL,
	PAGE_UNT,
	PAGE_NOD,

};

enum sub_screen_status {

	ITEM_SELECT,
	ITEM_CHECK,
};

enum yes_no_item {

	NO,
	YES,
};

enum dev_item {

	DEV_WR3,
	DEV_WL21,
	DEV_WR3_EX,
};

struct PAGE_DEV_SELECT
{
	__IO uint8_t sub_screen_index;
	__IO uint8_t dev_type;
	__IO uint8_t yes_no;
};

struct UI_SELECT
{
	struct PAGE_DEV_SELECT page_dev_select;
	uint16_t  ui_pause_100ms_cnt;

};

extern void (*ui_fun_array[25])();
extern void ui_init(void);

extern struct UI_SELECT ui_select;
