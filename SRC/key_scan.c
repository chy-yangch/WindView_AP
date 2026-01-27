#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "key_scan.h"
#include "main.h"
#include "cc1200.h"

struct KEY_INFO Key_Info;
void (*key_case_array[25])();


void Key_Scan(void);
void key_case_init(void);

void key_page_logo(void);
void key_page_main(void);
void key_page_dev(void);

void key_case_init(void)
{
	key_case_array[0] = key_page_logo;
	key_case_array[1] = key_page_main;
	key_case_array[2] = key_page_dev;
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
			}

		} else {

			Key_Info.key_lock_bit &= ~UP_KEY_BIT;
			Key_Info.key_hold_cn[UP_KEY_HOLD] = 0;
			//Key_Info.fast_setting_mode = OFF;
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
			}
		} else {

			Key_Info.key_lock_bit &= ~Down_KEY_BIT;
			Key_Info.key_hold_cn[Down_KEY_HOLD] = 0;
			//Key_Info.fast_setting_mode = OFF;
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


//	if (Key_Info.had_turn_on_pkey_release) {

//		/* Power key hold over 2.5 Sec for power off */
//		if ((Key_Info.key_hold_cn[Power_KEY_HOLD] > 25 ) && (Power_KEY_PIN) ){


//				if ((info.current_page == MAIN_Page) || (info.current_page == AVG_MAX_Page) ||
//				    (info.current_page == CHART_Page) || (info.current_page == HISTORY_1_Page) ||
//				    (info.current_page == HISTORY_2_Page) || (info.current_page == HISTORY_3_Page)) {

//					info.power_on = OFF;

//				    } else {

//					    __NOP();
//				    }
//		}
//	}
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


void key_page_main(void)
{
	switch(Key_Info.key_bit) {

		case UP_KEY_BIT:

			Key_Info.key_bit &= ~UP_KEY_BIT;

		break;

		case Down_KEY_BIT:

			Key_Info.key_bit &= ~Down_KEY_BIT;

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

void key_page_dev(void)
{
	switch(Key_Info.key_bit) {

		case UP_KEY_BIT:

			Key_Info.key_bit &= ~UP_KEY_BIT;

		break;

		case Down_KEY_BIT:

			Key_Info.key_bit &= ~Down_KEY_BIT;

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
