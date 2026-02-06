#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "key_scan.h"
#include "main.h"
#include "cc1200.h"
#include "ui.h"
#include "24LC02.h"

struct KEY_INFO Key_Info;
void (*key_case_array[25])();


void Key_Scan(void);
void key_case_init(void);

void key_page_logo(void);
void key_page_main(void);
void key_page_dev(void);
void key_page_ad(void);
void key_page_thr(void);
void key_page_snd(void);
void key_page_dur(void);
void key_page_fla(void);
void key_page_bri(void);
void key_page_unt(void);
void key_page_nod(void);

void key_case_init(void)
{
	key_case_array[0] = key_page_main;
	key_case_array[1] = key_page_dev;
	key_case_array[2] = key_page_ad;
	key_case_array[3] = key_page_thr;
	key_case_array[4] = key_page_snd;
	key_case_array[5] = key_page_dur;
	key_case_array[6] = key_page_fla;
	key_case_array[7] = key_page_bri;
	key_case_array[8] = key_page_unt;
	key_case_array[9] = key_page_nod;
}


void Key_Scan(void)
{

	/* UP key pressed */
	if (Key_Info.key_st[UP_KEY_HOLD]) {

		if (UP_KEY) {

			if ((~Key_Info.key_bit & UP_KEY_BIT) &&((Key_Info.key_lock_bit & UP_KEY_BIT) == 0))  {
				Key_Info.key_bit |= UP_KEY_BIT;
				Key_Info.key_lock_bit |= UP_KEY_BIT;
				Key_Info.key_hold_cn[UP_KEY_HOLD] = 0;


			} else {

				Key_Info.key_hold_cn[UP_KEY_HOLD]++;

				if ((info.current_page == PAGE_AD) && (ui_select.page_dev_select.sub_screen_index == ITEM_SELECT)) {

					if(Key_Info.key_hold_cn[UP_KEY_HOLD] >= FAST_SETTING_HOLD_TIME) {
						Key_Info.key_bit |= UP_KEY_BIT;
						Key_Info.fast_setting_mode = ON;
					}
				}
			}

		} else {

			Key_Info.key_lock_bit &= ~UP_KEY_BIT;
			Key_Info.key_hold_cn[UP_KEY_HOLD] = 0;
			Key_Info.fast_setting_mode = OFF;
		}
	}


	/* Down key pressed */
	if (Key_Info.key_st[Down_KEY_HOLD]) {

		if (DOWN_KEY) {

			if ((~Key_Info.key_bit & Down_KEY_BIT) &&((Key_Info.key_lock_bit & Down_KEY_BIT) == 0)) {
				Key_Info.key_bit |= Down_KEY_BIT;
				Key_Info.key_lock_bit |= Down_KEY_BIT;
				Key_Info.key_hold_cn[Down_KEY_HOLD] = 0;


			} else {

				Key_Info.key_hold_cn[Down_KEY_HOLD]++;

				if ((info.current_page == PAGE_AD) && (ui_select.page_dev_select.sub_screen_index == ITEM_SELECT)) {

					if(Key_Info.key_hold_cn[Down_KEY_HOLD] >= FAST_SETTING_HOLD_TIME) {
						Key_Info.key_bit |= Down_KEY_BIT;
						Key_Info.fast_setting_mode = ON;
					}
				}
			}
		} else {

			Key_Info.key_lock_bit &= ~Down_KEY_BIT;
			Key_Info.key_hold_cn[Down_KEY_HOLD] = 0;
			Key_Info.fast_setting_mode = OFF;
		}
	}


	/* Power key pressed */
	if (Key_Info.key_st[Power_KEY_HOLD]) {

		if (POW_KEY) {

			if ((~Key_Info.key_bit & Power_KEY_BIT) && ((Key_Info.key_lock_bit & Power_KEY_BIT) == 0)) {
				Key_Info.key_bit |= Power_KEY_BIT;
				Key_Info.key_lock_bit |= Power_KEY_BIT;
				Key_Info.key_hold_cn[Power_KEY_HOLD] = 0;


			} else {
				Key_Info.key_hold_cn[Power_KEY_HOLD]++;
			}

		} else {
			Key_Info.key_lock_bit &= ~Power_KEY_BIT;

			if ((Key_Info.had_turn_on_pkey_release == 0) && (info.power_on == ON))
				Key_Info.had_turn_on_pkey_release = 1;

			Key_Info.key_hold_cn[Power_KEY_HOLD] = 0;
		}


	}


	/* Enter key pressed */
	if (Key_Info.key_st[Enter_KEY_HOLD]) {

		if (CONFIRM_KEY) {

			if ((~Key_Info.key_bit & Enter_KEY_BIT) && ((Key_Info.key_lock_bit & Enter_KEY_BIT) == 0)) {
				Key_Info.key_bit |= Enter_KEY_BIT;
				Key_Info.key_lock_bit |= Enter_KEY_BIT;
				Key_Info.key_hold_cn[Enter_KEY_HOLD] = 0;

			} else {
				Key_Info.key_hold_cn[Enter_KEY_HOLD]++;
			}
		} else {

			Key_Info.key_lock_bit &= ~Enter_KEY_BIT;
			Key_Info.key_hold_cn[Enter_KEY_HOLD] = 0;
		}
	}


	/* Cancel key pressed */
	if (Key_Info.key_st[Cancel_KEY_HOLD]) {

		if (CANCEL_KEY) {

			if ((~Key_Info.key_bit & Cancel_KEY_BIT) && ((Key_Info.key_lock_bit & Cancel_KEY_BIT) == 0)) {
				Key_Info.key_bit |= Cancel_KEY_BIT;
				Key_Info.key_lock_bit |= Cancel_KEY_BIT;
				Key_Info.key_hold_cn[Cancel_KEY_HOLD] = 0;

			} else {
				Key_Info.key_hold_cn[Cancel_KEY_HOLD]++;
			}
		} else {

			Key_Info.key_lock_bit &= ~Cancel_KEY_BIT;
			Key_Info.key_hold_cn[Cancel_KEY_HOLD] = 0;
		}
	}


	if (Key_Info.had_turn_on_pkey_release) {

		/* Power key hold over 2.5 Sec for power off */
		if ((Key_Info.key_hold_cn[Power_KEY_HOLD] > 25 ) && (POW_KEY) ) {

			info.power_on = OFF;

//				if ((info.current_page == MAIN_Page) || (info.current_page == AVG_MAX_Page) ||
//				    (info.current_page == CHART_Page) || (info.current_page == HISTORY_1_Page) ||
//				    (info.current_page == HISTORY_2_Page) || (info.current_page == HISTORY_3_Page)) {

//					info.power_on = OFF;

//				    } else {

//					    __NOP();
//				    }
		}
	}

	/* 按下任一Key立即離開休眠 */
	if (Key_Info.key_bit) {

		info.exit_sleep_flag = 1;
	}
}



void key_page_logo(void)
{

	Key_Info.key_bit = 0;
	Key_Info.key_hold_cn[UP_KEY_HOLD] = 0;
	Key_Info.key_hold_cn[Down_KEY_HOLD] = 0;
	Key_Info.key_hold_cn[Power_KEY_HOLD] = 0;
	Key_Info.key_hold_cn[Enter_KEY_HOLD] = 0;
	Key_Info.key_hold_cn[Cancel_KEY_HOLD] = 0;


	Key_Info.key_st[UP_KEY_HOLD] = 1;
	Key_Info.key_st[Down_KEY_HOLD] = 1;
	Key_Info.key_st[Power_KEY_HOLD] = 1;
	Key_Info.key_st[Enter_KEY_HOLD] = 1;
	Key_Info.key_st[Cancel_KEY_HOLD] = 1;


}


void key_page_main (void)
{
	switch(Key_Info.key_bit) {

		case UP_KEY_BIT:

			Key_Info.key_bit &= ~UP_KEY_BIT;

			info.current_page = PAGE_NOD;
			info.page_step = INIT;

		break;

		case Down_KEY_BIT:

			Key_Info.key_bit &= ~Down_KEY_BIT;

			info.current_page = PAGE_DEV;
			info.page_step = INIT;

		break;

		case Power_KEY_BIT:

			Key_Info.key_bit &= ~Power_KEY_BIT;

		break;

		case Enter_KEY_BIT:

			Key_Info.key_bit &= ~Enter_KEY_BIT;

		break;

		case Cancel_KEY_BIT:

			Key_Info.key_bit &= ~Cancel_KEY_BIT;

		break;

		default:
			Key_Info.key_bit = 0;
			__NOP();

	}

}

void key_page_dev (void)
{
	if (ui_select.page_dev_select.sub_screen_index == ITEM_CHECK) {

		Key_Info.key_bit &= ~UP_KEY_BIT;
		Key_Info.key_bit &= ~Down_KEY_BIT;
		Key_Info.key_bit &= ~Power_KEY_BIT;
		Key_Info.key_bit &= ~Enter_KEY_BIT;
		Key_Info.key_bit &= ~Cancel_KEY_BIT;

	} else {
		__NOP();
	}

	switch(Key_Info.key_bit) {

		case UP_KEY_BIT:

			Key_Info.key_bit &= ~UP_KEY_BIT;

			if (info.page_step == INIT) {

				info.current_page = PAGE_MAIN;
				info.page_step = INIT;

			} else {

				if (ui_select.page_dev_select.dev_type == DEV_WR3)
					ui_select.page_dev_select.dev_type = DEV_WR3_EX;
				else if (ui_select.page_dev_select.dev_type == DEV_WL21)
					ui_select.page_dev_select.dev_type = DEV_WR3;
				else if (ui_select.page_dev_select.dev_type == DEV_WR3_EX)
					ui_select.page_dev_select.dev_type = DEV_WL21;
				else
					__NOP();
			}

		break;

		case Down_KEY_BIT:

			Key_Info.key_bit &= ~Down_KEY_BIT;

			if (info.page_step == INIT) {

				info.current_page = PAGE_AD;
				info.page_step = INIT;

			} else {

				if (ui_select.page_dev_select.dev_type == DEV_WR3)
					ui_select.page_dev_select.dev_type = DEV_WL21;
				else if (ui_select.page_dev_select.dev_type == DEV_WL21)
					ui_select.page_dev_select.dev_type = DEV_WR3_EX;
				else if (ui_select.page_dev_select.dev_type == DEV_WR3_EX)
					ui_select.page_dev_select.dev_type = DEV_WR3;
				else
					__NOP();
			}

		break;

		case Power_KEY_BIT:

			Key_Info.key_bit &= ~Power_KEY_BIT;

		break;

		case Enter_KEY_BIT:

			Key_Info.key_bit &= ~Enter_KEY_BIT;

			if (info.page_step == INIT) {

				info.page_step = WORK;
				ui_select.page_dev_select.sub_screen_index = ITEM_SELECT;
				ui_select.page_dev_select.dev_type = DEV_WR3;


			} else {

				if(ui_select.page_dev_select.sub_screen_index == ITEM_SELECT) {

					//下述二行順序需注意
					ui_select.ui_pause_100ms_cnt = 0;
					ui_select.page_dev_select.sub_screen_index = ITEM_CHECK;

					eerom2402_w_uint8(EEP_WINDV_TYPE,ui_select.page_dev_select.dev_type);

					windview_eeprom_read();

				} else {
					__NOP();
				}
			}

		break;

		case Cancel_KEY_BIT:

			Key_Info.key_bit &= ~Cancel_KEY_BIT;

			if (info.page_step == INIT) {

					__NOP();
			} else {

				if(ui_select.page_dev_select.sub_screen_index == ITEM_SELECT) {

					info.page_step = INIT;

				} else {
					__NOP();
				}
			}

		break;

		default:

			Key_Info.key_bit = 0;
			__NOP();

	}
}

void key_page_ad (void)
{
	if (ui_select.page_dev_select.sub_screen_index == ITEM_CHECK) {

		Key_Info.key_bit &= ~UP_KEY_BIT;
		Key_Info.key_bit &= ~Down_KEY_BIT;
		Key_Info.key_bit &= ~Power_KEY_BIT;
		Key_Info.key_bit &= ~Enter_KEY_BIT;
		Key_Info.key_bit &= ~Cancel_KEY_BIT;

	} else {
		__NOP();
	}

	switch(Key_Info.key_bit) {

		case UP_KEY_BIT:

			Key_Info.key_bit &= ~UP_KEY_BIT;

			if (info.page_step == INIT) {

				info.current_page = PAGE_DEV;
				info.page_step = INIT;

			} else {

				ui_select.page_ad_select.ad--;

				if (info.windv_type == DEV_WR3) {

					if (ui_select.page_ad_select.ad < 3)
						ui_select.page_ad_select.ad = 80;
					else
						__NOP();

				} else if (info.windv_type == DEV_WL21) {

					if (ui_select.page_ad_select.ad < 1)
						ui_select.page_ad_select.ad = 80;
					else
						__NOP();

				} else if (info.windv_type == DEV_WR3_EX) {

					__NOP();
				}

			}

		break;

		case Down_KEY_BIT:

			Key_Info.key_bit &= ~Down_KEY_BIT;

			if (info.page_step == INIT) {

				info.current_page = PAGE_THR;
				info.page_step = INIT;

			} else {


				ui_select.page_ad_select.ad++;

				if (info.windv_type == DEV_WR3) {

					if (ui_select.page_ad_select.ad > 80)
						ui_select.page_ad_select.ad = 3;
					else
						__NOP();

				} else if (info.windv_type == DEV_WL21) {

					if (ui_select.page_ad_select.ad > 80)
						ui_select.page_ad_select.ad = 1;
					else
						__NOP();

				} else if (info.windv_type == DEV_WR3_EX) {

					__NOP();
				}

			}

		break;

		case Power_KEY_BIT:

			Key_Info.key_bit &= ~Power_KEY_BIT;

		break;

		case Enter_KEY_BIT:

			Key_Info.key_bit &= ~Enter_KEY_BIT;

			if (info.page_step == INIT) {

				info.page_step = WORK;
				ui_select.page_ad_select.sub_screen_index = ITEM_SELECT;
				ui_select.page_ad_select.ad = 40;

			} else {

				if(ui_select.page_dev_select.sub_screen_index == ITEM_SELECT) {

					//下述二行順序需注意
					ui_select.ui_pause_100ms_cnt = 0;
					ui_select.page_ad_select.sub_screen_index = ITEM_CHECK;

					eerom2402_w_uint8(EEP_WINDV_AD,ui_select.page_ad_select.ad);

					windview_eeprom_read();

				} else {
					__NOP();
				}
			}

		break;

		case Cancel_KEY_BIT:

			Key_Info.key_bit &= ~Cancel_KEY_BIT;

			if (info.page_step == INIT) {

					__NOP();
			} else {

				if(ui_select.page_dev_select.sub_screen_index == ITEM_SELECT) {

					info.page_step = INIT;

				} else {
					__NOP();
				}
			}

		break;

		default:
			Key_Info.key_bit = 0;
			__NOP();

	}
}

void key_page_thr (void)
{
	if (ui_select.page_dev_select.sub_screen_index == ITEM_CHECK) {

		Key_Info.key_bit &= ~UP_KEY_BIT;
		Key_Info.key_bit &= ~Down_KEY_BIT;
		Key_Info.key_bit &= ~Power_KEY_BIT;
		Key_Info.key_bit &= ~Enter_KEY_BIT;
		Key_Info.key_bit &= ~Cancel_KEY_BIT;

	} else {
		__NOP();
	}

	switch(Key_Info.key_bit) {

		case UP_KEY_BIT:

			Key_Info.key_bit &= ~UP_KEY_BIT;

			if (info.page_step == INIT) {

				info.current_page = PAGE_AD;
				info.page_step = INIT;

			} else {


			}

		break;

		case Down_KEY_BIT:

			Key_Info.key_bit &= ~Down_KEY_BIT;

			if (info.page_step == INIT) {

				info.current_page = PAGE_SND;
				info.page_step = INIT;

			} else {


			}

		break;

		case Power_KEY_BIT:

			Key_Info.key_bit &= ~Power_KEY_BIT;

		break;

		case Enter_KEY_BIT:

			Key_Info.key_bit &= ~Enter_KEY_BIT;

		break;

		case Cancel_KEY_BIT:

			Key_Info.key_bit &= ~Cancel_KEY_BIT;

		break;

		default:
			Key_Info.key_bit = 0;
			__NOP();

	}
}

void key_page_snd (void)
{
	if (ui_select.page_dev_select.sub_screen_index == ITEM_CHECK) {

		Key_Info.key_bit &= ~UP_KEY_BIT;
		Key_Info.key_bit &= ~Down_KEY_BIT;
		Key_Info.key_bit &= ~Power_KEY_BIT;
		Key_Info.key_bit &= ~Enter_KEY_BIT;
		Key_Info.key_bit &= ~Cancel_KEY_BIT;

	} else {
		__NOP();
	}

	switch(Key_Info.key_bit) {

		case UP_KEY_BIT:

			Key_Info.key_bit &= ~UP_KEY_BIT;

			if (info.page_step == INIT) {

				info.current_page = PAGE_THR;
				info.page_step = INIT;

			} else {


			}

		break;

		case Down_KEY_BIT:

			Key_Info.key_bit &= ~Down_KEY_BIT;

			if (info.page_step == INIT) {

				info.current_page = PAGE_DUR;
				info.page_step = INIT;

			} else {


			}

		break;

		case Power_KEY_BIT:

			Key_Info.key_bit &= ~Power_KEY_BIT;

		break;

		case Enter_KEY_BIT:

			Key_Info.key_bit &= ~Enter_KEY_BIT;

		break;

		case Cancel_KEY_BIT:

			Key_Info.key_bit &= ~Cancel_KEY_BIT;

		break;

		default:
			Key_Info.key_bit = 0;
			__NOP();

	}
}

void key_page_dur (void)
{
	if (ui_select.page_dev_select.sub_screen_index == ITEM_CHECK) {

		Key_Info.key_bit &= ~UP_KEY_BIT;
		Key_Info.key_bit &= ~Down_KEY_BIT;
		Key_Info.key_bit &= ~Power_KEY_BIT;
		Key_Info.key_bit &= ~Enter_KEY_BIT;
		Key_Info.key_bit &= ~Cancel_KEY_BIT;

	} else {
		__NOP();
	}

	switch(Key_Info.key_bit) {

		case UP_KEY_BIT:

			Key_Info.key_bit &= ~UP_KEY_BIT;

			if (info.page_step == INIT) {

				info.current_page = PAGE_SND;
				info.page_step = INIT;

			} else {


			}
		break;

		case Down_KEY_BIT:

			Key_Info.key_bit &= ~Down_KEY_BIT;

			if (info.page_step == INIT) {

				info.current_page = PAGE_FLA;
				info.page_step = INIT;

			} else {


			}

		break;

		case Power_KEY_BIT:

			Key_Info.key_bit &= ~Power_KEY_BIT;

		break;

		case Enter_KEY_BIT:

			Key_Info.key_bit &= ~Enter_KEY_BIT;

		break;

		case Cancel_KEY_BIT:

			Key_Info.key_bit &= ~Cancel_KEY_BIT;

		break;

		default:
			Key_Info.key_bit = 0;
			__NOP();

	}
}

void key_page_fla (void)
{
	if (ui_select.page_dev_select.sub_screen_index == ITEM_CHECK) {

		Key_Info.key_bit &= ~UP_KEY_BIT;
		Key_Info.key_bit &= ~Down_KEY_BIT;
		Key_Info.key_bit &= ~Power_KEY_BIT;
		Key_Info.key_bit &= ~Enter_KEY_BIT;
		Key_Info.key_bit &= ~Cancel_KEY_BIT;

	} else {
		__NOP();
	}

	switch(Key_Info.key_bit) {

		case UP_KEY_BIT:

			Key_Info.key_bit &= ~UP_KEY_BIT;

			if (info.page_step == INIT) {

				info.current_page = PAGE_DUR;
				info.page_step = INIT;

			} else {


			}

		break;

		case Down_KEY_BIT:

			Key_Info.key_bit &= ~Down_KEY_BIT;

			if (info.page_step == INIT) {

				info.current_page = PAGE_BRI;
				info.page_step = INIT;

			} else {


			}

		break;

		case Power_KEY_BIT:

			Key_Info.key_bit &= ~Power_KEY_BIT;

		break;

		case Enter_KEY_BIT:

			Key_Info.key_bit &= ~Enter_KEY_BIT;

		break;

		case Cancel_KEY_BIT:

			Key_Info.key_bit &= ~Cancel_KEY_BIT;

		break;

		default:
			Key_Info.key_bit = 0;
			__NOP();

	}
}

void key_page_bri (void)
{
	if (ui_select.page_dev_select.sub_screen_index == ITEM_CHECK) {

		Key_Info.key_bit &= ~UP_KEY_BIT;
		Key_Info.key_bit &= ~Down_KEY_BIT;
		Key_Info.key_bit &= ~Power_KEY_BIT;
		Key_Info.key_bit &= ~Enter_KEY_BIT;
		Key_Info.key_bit &= ~Cancel_KEY_BIT;

	} else {
		__NOP();
	}

	switch(Key_Info.key_bit) {

		case UP_KEY_BIT:

			Key_Info.key_bit &= ~UP_KEY_BIT;

			if (info.page_step == INIT) {

				info.current_page = PAGE_FLA;
				info.page_step = INIT;

			} else {

				if (ui_select.page_bri_select.bri_level == LIGHT_HI)
					ui_select.page_bri_select.bri_level = LIGHT_LO;
				else
					ui_select.page_bri_select.bri_level--;
			}

		break;

		case Down_KEY_BIT:

			Key_Info.key_bit &= ~Down_KEY_BIT;

			if (info.page_step == INIT) {

				info.current_page = PAGE_UNT;
				info.page_step = INIT;

			} else {

				if (ui_select.page_bri_select.bri_level == LIGHT_LO)
					ui_select.page_bri_select.bri_level = LIGHT_HI;
				else
					ui_select.page_bri_select.bri_level++;
			}

		break;

		case Power_KEY_BIT:

			Key_Info.key_bit &= ~Power_KEY_BIT;

		break;

		case Enter_KEY_BIT:

			Key_Info.key_bit &= ~Enter_KEY_BIT;


			if (info.page_step == INIT) {

				info.page_step = WORK;
				ui_select.page_bri_select.sub_screen_index = ITEM_SELECT;
				ui_select.page_bri_select.bri_level = LIGHT_HI;

			} else {

				if(ui_select.page_bri_select.sub_screen_index == ITEM_SELECT) {

					//下述二行順序需注意
					ui_select.ui_pause_100ms_cnt = 0;
					ui_select.page_bri_select.sub_screen_index = ITEM_CHECK;

					eerom2402_w_uint8(EEP_WINDV_LIGHT_LEVEL,ui_select.page_bri_select.bri_level);

					windview_eeprom_read();

				} else {
					__NOP();
				}
			}

		break;

		case Cancel_KEY_BIT:

			Key_Info.key_bit &= ~Cancel_KEY_BIT;

			if (info.page_step == INIT) {

					__NOP();
			} else {

				if(ui_select.page_bri_select.sub_screen_index == ITEM_SELECT) {

					info.page_step = INIT;

					led_light_level(info.windv_light_level );		//取消設定設定回原本亮度

				} else {
					__NOP();
				}
			}

		break;

		default:
			Key_Info.key_bit = 0;
			__NOP();

	}
}

void key_page_unt (void)
{
	if (ui_select.page_dev_select.sub_screen_index == ITEM_CHECK) {

		Key_Info.key_bit &= ~UP_KEY_BIT;
		Key_Info.key_bit &= ~Down_KEY_BIT;
		Key_Info.key_bit &= ~Power_KEY_BIT;
		Key_Info.key_bit &= ~Enter_KEY_BIT;
		Key_Info.key_bit &= ~Cancel_KEY_BIT;

	} else {
		__NOP();
	}

	switch(Key_Info.key_bit) {

		case UP_KEY_BIT:

			Key_Info.key_bit &= ~UP_KEY_BIT;

			if (info.page_step == INIT) {

				info.current_page = PAGE_BRI;
				info.page_step = INIT;

			} else {

				if (ui_select.page_unit_select.unit == UNIT_MPH)
					ui_select.page_unit_select.unit = UNIT_MS;
				else
					ui_select.page_unit_select.unit--;

			}

		break;

		case Down_KEY_BIT:

			Key_Info.key_bit &= ~Down_KEY_BIT;

			if (info.page_step == INIT) {

				info.current_page = PAGE_NOD;
				info.page_step = INIT;

			} else {

				if (ui_select.page_unit_select.unit == UNIT_MS)
					ui_select.page_unit_select.unit = UNIT_MPH;
				else
					ui_select.page_unit_select.unit++;

			}

		break;

		case Power_KEY_BIT:

			Key_Info.key_bit &= ~Power_KEY_BIT;

		break;

		case Enter_KEY_BIT:

			Key_Info.key_bit &= ~Enter_KEY_BIT;

			if (info.page_step == INIT) {

				info.page_step = WORK;
				ui_select.page_unit_select.sub_screen_index = ITEM_SELECT;
				ui_select.page_unit_select.unit = UNIT_MPH;

			} else {

				if(ui_select.page_unit_select.sub_screen_index == ITEM_SELECT) {

					//下述二行順序需注意
					ui_select.ui_pause_100ms_cnt = 0;
					ui_select.page_unit_select.sub_screen_index = ITEM_CHECK;

					eerom2402_w_uint8(EEP_WINDV_UNIT,ui_select.page_unit_select.unit);

					windview_eeprom_read();

				} else {
					__NOP();
				}
			}

		break;

		case Cancel_KEY_BIT:

			Key_Info.key_bit &= ~Cancel_KEY_BIT;

			if (info.page_step == INIT) {

					__NOP();
			} else {

				if(ui_select.page_unit_select.sub_screen_index == ITEM_SELECT) {

					info.page_step = INIT;

				} else {
					__NOP();
				}
			}

		break;

		default:
			Key_Info.key_bit = 0;
			__NOP();

	}
}

void key_page_nod (void)
{
	if (ui_select.page_dev_select.sub_screen_index == ITEM_CHECK) {

		Key_Info.key_bit &= ~UP_KEY_BIT;
		Key_Info.key_bit &= ~Down_KEY_BIT;
		Key_Info.key_bit &= ~Power_KEY_BIT;
		Key_Info.key_bit &= ~Enter_KEY_BIT;
		Key_Info.key_bit &= ~Cancel_KEY_BIT;

	} else {
		__NOP();
	}

	switch(Key_Info.key_bit) {

		case UP_KEY_BIT:

			Key_Info.key_bit &= ~UP_KEY_BIT;

			if (info.page_step == INIT) {

				info.current_page = PAGE_UNT;
				info.page_step = INIT;

			} else {


			}

		break;

		case Down_KEY_BIT:

			Key_Info.key_bit &= ~Down_KEY_BIT;

			if (info.page_step == INIT) {

				info.current_page = PAGE_MAIN;
				info.page_step = INIT;

			} else {


			}

		break;

		case Power_KEY_BIT:

			Key_Info.key_bit &= ~Power_KEY_BIT;

		break;

		case Enter_KEY_BIT:

			Key_Info.key_bit &= ~Enter_KEY_BIT;

		break;

		case Cancel_KEY_BIT:

			Key_Info.key_bit &= ~Cancel_KEY_BIT;

		break;

		default:
			Key_Info.key_bit = 0;
			__NOP();

	}
}
