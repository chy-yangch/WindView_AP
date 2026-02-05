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
	PAGE_BRI,
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

struct PAGE_MAIN_SELECT
{
	__IO uint8_t sub_screen_index;
	__IO uint8_t yes_no;
};

struct PAGE_DEV_SELECT
{
	__IO uint8_t sub_screen_index;
	__IO uint8_t yes_no;
	__IO uint8_t dev_type;
};

struct PAGE_AD_SELECT
{
	__IO uint8_t sub_screen_index;
	__IO uint8_t yes_no;
	__IO uint8_t ad;
};

struct PAGE_THR_SELECT
{
	__IO uint8_t sub_screen_index;
	__IO uint8_t yes_no;
};

struct PAGE_SND_SELECT
{
	__IO uint8_t sub_screen_index;
	__IO uint8_t yes_no;
};

struct PAGE_DUR_SELECT
{
	__IO uint8_t sub_screen_index;
	__IO uint8_t yes_no;
};

struct PAGE_FLA_SELECT
{
	__IO uint8_t sub_screen_index;
	__IO uint8_t yes_no;
};

struct PAGE_BRI_SELECT
{
	__IO uint8_t sub_screen_index;
	__IO uint8_t yes_no;
};

struct PAGE_UNT_SELECT
{
	__IO uint8_t sub_screen_index;
	__IO uint8_t yes_no;
	__IO uint8_t unit;
};

struct PAGE_NOD_SELECT
{
	__IO uint8_t sub_screen_index;
	__IO uint8_t yes_no;
};

struct UI_SELECT
{
	struct PAGE_MAIN_SELECT	page_main_select;
	struct PAGE_DEV_SELECT	page_dev_select;
	struct PAGE_AD_SELECT	page_ad_select;
	struct PAGE_THR_SELECT	page_thr_select;
	struct PAGE_SND_SELECT	page_snd_select;
	struct PAGE_DUR_SELECT	page_dur_select;
	struct PAGE_FLA_SELECT	page_fla_select;
	struct PAGE_BRI_SELECT	page_bri_select;
	struct PAGE_UNT_SELECT	page_unit_select;
	struct PAGE_NOD_SELECT	page_nod_select;

	uint16_t  ui_pause_100ms_cnt;

};

extern void (*ui_fun_array[25])();
extern void ui_init(void);

extern struct UI_SELECT ui_select;
