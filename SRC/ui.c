#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "main.h"
#include "ui.h"
#include "cc1200.h"
#include "led_font.h"

void (*ui_fun_array[25])();
void ui_init(void);

void page_logo (void);
void page_main (void);
void page_dev (void);
void page_ad (void);
void page_thr (void);
void page_snd (void);
void page_dur (void);
void page_fla (void);
void page_bri (void);
void page_unt (void);
void page_nod (void);



struct UI_SELECT ui_select;

void ui_init(void)
{
	ui_fun_array[0] = page_main;
	ui_fun_array[1] = page_dev;
	ui_fun_array[2] = page_ad;
	ui_fun_array[3] = page_thr;
	ui_fun_array[4] = page_snd;
	ui_fun_array[5] = page_dur;
	ui_fun_array[6] = page_fla;
	ui_fun_array[7] = page_bri;
	ui_fun_array[8] = page_unt;
	ui_fun_array[9] = page_nod;
}


void page_logo (void)
{
	uint8_t i = 0;

	switch(info.page_step) {

		case INIT:

			info.page_step = WORK;

		case WORK:

			LED_H_SW = 0;
			LED_M_SW = 0;
			LED_L_SW = 1;

			led_font_fun.led_7seg_pic_show(ON,PIC_ALL_ON,0);
			CLK_SysTickDelay(500000);
			led_font_fun.led_7seg_pic_show(OFF,PIC_ALL_ON,0);
			CLK_SysTickDelay(500000);
			led_font_fun.led_7seg_pic_show(ON,PIC_ALL_ON,0);
			CLK_SysTickDelay(500000);
			led_font_fun.led_7seg_pic_show(OFF,PIC_ALL_ON,0);

			W1_RESET = 0;
			CLK_SysTickDelay(200000);
			W1_RESET = 1;

			//cc1200_work_ch = info.wireless_ch_status = 42; // for test
			cc1200_work_ch = info.windv_ad;

			SPI_Open(SPI0, SPI_MASTER, SPI_MODE_0, 8, 2000000);
			/* Disable auto SS function, control SS signal manually. */
			SPI_DisableAutoSS(SPI0);
			SPI_SET_SS_LOW(SPI0);
			registerConfig();
			while (!SPI_GET_RX_FIFO_EMPTY_FLAG(SPI0))
				SPI_READ_RX(SPI0);

			SPI_ClearIntFlag(SPI0,SPI_FIFO_RXOV_INT_MASK);

			CLK_SysTickDelay(500000);

			for (i = 0;i < 4 ;i++) {

				led_font_fun.led_7seg_pic_show(ON,PIC_TURN_ON_MOVE,i%3);
				CLK_SysTickDelay(500000);
				runRX(SPI0);

				if (info.wr3ptx_info.wr3ptx_first_data_get)
					i = 5;
			}


			if (info.wr3ptx_info.wr3ptx_first_data_get == OFF)
				info.cc1200_timeout_cn = CC1200_TIMEOUT_SEC + 1;
			else
				info.cc1200_timeout_cn = 0;

			info.current_page = PAGE_MAIN;
			info.page_step = INIT;
			ui_select.page_dev_select.sub_screen_index = ITEM_SELECT;

		default:
			__NOP();

	}
}

void draw_Rssi(void)
{
	uint8_t reg[20] = {0};

	//Rssi距離與L700R差路約15,故修改如下
	if (info.wr3ptx_info.rssi < 60) {
		led_font_fun.rssi_show(ON,RSSI_LV4);
	} else if (info.wr3ptx_info.rssi < 70) {
		led_font_fun.rssi_show(ON,RSSI_LV3);
	} else if (info.wr3ptx_info.rssi < 80) {
		led_font_fun.rssi_show(ON,RSSI_LV2);
	} else {
		led_font_fun.rssi_show(ON,RSSI_LV1);
		__NOP();
	}
}

uint32_t wind_speed_unit_calculate(uint8_t unit,uint32_t wind_speed_c)
{
	//單位轉換參考資料
	//https://zh.wikipedia.org/wiki/%E9%80%9F%E7%8E%87
	float wind_speed_reg;

	if (unit == UNIT_KM) {

			wind_speed_reg = wind_speed_c;
			wind_speed_reg = wind_speed_reg;

	} else if (unit == UNIT_MS) {

			wind_speed_reg = wind_speed_c;
			wind_speed_reg = wind_speed_reg * 0.277778f;

	} else if (unit == UNIT_MPH) {

			/* km/hr -> ms*/
			wind_speed_reg = wind_speed_c;
			wind_speed_reg = wind_speed_reg * 0.621371f;

	} else {
		__NOP();
	}

	return wind_speed_reg;
}


void page_main (void)
{
	uint32_t wind_speed_reg = 0;

	switch(info.page_step) {

		case INIT:

			info.page_step = WORK;
			ui_select.page_main_select.sub_screen_index = ITEM_SELECT;

		case WORK:

			if (info.cc1200_timeout_cn >= CC1200_TIMEOUT_SEC) {

				led_font_fun.rssi_show(OFF,0);
				led_font_fun.led_7seg_pic_show(ON,PIC_NO_LINK,0);

			} else {

				draw_Rssi();

				led_font_fun.unit_show(ON,info.windv_unit);

				wind_speed_reg = wind_speed_unit_calculate(info.windv_unit,info.wr3ptx_info.wind_speed);

				led_font_fun.led_7seg_number_show(ON,wind_speed_reg);

//			wind_speed_reg = wind_speed_unit_calculate(info.wind_speed_unit_status,info.wr3ptx_info.wind_speed);
//			sprintf((char *)value, "%d.%d",(uint16_t) wind_speed_reg / 10,(uint16_t)wind_speed_reg % 10);

			}

		default:
			__NOP();

	}
}

void page_dev (void)
{

	switch(info.page_step) {

		case INIT:

			if (info.cc1200_timeout_cn >= CC1200_TIMEOUT_SEC)
				led_font_fun.rssi_show(OFF,0);
			else
				draw_Rssi();

			led_font_fun.led_7seg_text_show(ON,TEXT_DEV);
			led_font_fun.unit_show(ON,info.windv_unit);
			ui_select.page_dev_select.sub_screen_index = ITEM_SELECT;
		break;

		case WORK:

			if (info.cc1200_timeout_cn >= CC1200_TIMEOUT_SEC)
				led_font_fun.rssi_show(OFF,0);
			else
				draw_Rssi();

			if (ui_select.page_dev_select.sub_screen_index == ITEM_SELECT) {

				if (ui_select.page_dev_select.dev_type == DEV_WR3) {

					led_font_fun.led_n1_text(OFF,0);
					led_font_fun.led_n2_text(OFF,0);
					led_font_fun.led_n3_text(ON,'A');

				} else if (ui_select.page_dev_select.dev_type == DEV_WL21) {

					led_font_fun.led_n1_text(OFF,0);
					led_font_fun.led_n2_text(OFF,0);
					led_font_fun.led_n3_text(ON,'B');

				} else if (ui_select.page_dev_select.dev_type == DEV_WR3_EX) {

					led_font_fun.led_n1_text(OFF,0);
					led_font_fun.led_n2_text(OFF,0);
					led_font_fun.led_n3_text(ON,'C');

				} else {
					__NOP();
				}

				led_font_fun.unit_show(ON,info.windv_unit);
				draw_Rssi();


			} else if (ui_select.page_dev_select.sub_screen_index == ITEM_CHECK) {

				if (ui_select.ui_pause_100ms_cnt >= UI_PAUSE_2_SEC) {

					info.page_step = INIT;

				} else {

					led_font_fun.led_7seg_text_show(ON,TEXT_YES);
				}

			} else {
				__NOP();
			}

		default:
			__NOP();

	}
}

void page_ad (void)
{

	switch(info.page_step) {

		case INIT:

			if (info.cc1200_timeout_cn >= CC1200_TIMEOUT_SEC)
				led_font_fun.rssi_show(OFF,0);
			else
				draw_Rssi();

			led_font_fun.led_7seg_text_show(ON,TEXT_AD);
			led_font_fun.unit_show(ON,info.windv_unit);
			ui_select.page_ad_select.sub_screen_index = ITEM_SELECT;

		break;

		case WORK:

			if (info.cc1200_timeout_cn >= CC1200_TIMEOUT_SEC)
				led_font_fun.rssi_show(OFF,0);
			else
				draw_Rssi();

			led_font_fun.unit_show(ON,info.windv_unit);

			if (ui_select.page_ad_select.sub_screen_index == ITEM_SELECT) {

				led_font_fun.led_n1_number(OFF,0);
				led_font_fun.led_n2_number(ON,ui_select.page_ad_select.ad / 10);
				led_font_fun.led_n3_number(ON,ui_select.page_ad_select.ad % 10);

			} else if (ui_select.page_ad_select.sub_screen_index == ITEM_CHECK) {

				if (ui_select.ui_pause_100ms_cnt >= UI_PAUSE_2_SEC) {

					info.page_step = INIT;

					cc1200_reset_setting(info.windv_ad);

				} else {

					led_font_fun.led_7seg_text_show(ON,TEXT_YES);
				}

			} else {
				__NOP();
			}

		default:
			__NOP();

	}
}

void page_thr (void)
{

	switch(info.page_step) {

		case INIT:

			if (info.cc1200_timeout_cn >= CC1200_TIMEOUT_SEC)
				led_font_fun.rssi_show(OFF,0);
			else
				draw_Rssi();

			led_font_fun.led_7seg_text_show(ON,TEXT_THR);
			led_font_fun.unit_show(ON,info.windv_unit);
			ui_select.page_thr_select.sub_screen_index = ITEM_SELECT;

		break;

		case WORK:

			if (info.cc1200_timeout_cn >= CC1200_TIMEOUT_SEC)
				led_font_fun.rssi_show(OFF,0);
			else
				draw_Rssi();

			led_font_fun.unit_show(ON,info.windv_unit);

			if (ui_select.page_thr_select.sub_screen_index == ITEM_SELECT) {



			} else if (ui_select.page_thr_select.sub_screen_index == ITEM_CHECK) {

				if (ui_select.ui_pause_100ms_cnt >= UI_PAUSE_2_SEC) {

					info.page_step = INIT;

				} else {

					led_font_fun.led_7seg_text_show(ON,TEXT_YES);
				}

			} else {
				__NOP();
			}

		default:
			__NOP();

	}
}

void page_snd (void)
{

	switch(info.page_step) {

		case INIT:

			if (info.cc1200_timeout_cn >= CC1200_TIMEOUT_SEC)
				led_font_fun.rssi_show(OFF,0);
			else
				draw_Rssi();

			led_font_fun.led_7seg_text_show(ON,TEXT_SND);
			led_font_fun.unit_show(ON,info.windv_unit);
			ui_select.page_snd_select.sub_screen_index = ITEM_SELECT;

		break;

		case WORK:

			if (info.cc1200_timeout_cn >= CC1200_TIMEOUT_SEC)
				led_font_fun.rssi_show(OFF,0);
			else
				draw_Rssi();

			led_font_fun.unit_show(ON,info.windv_unit);

			if (ui_select.page_snd_select.sub_screen_index == ITEM_SELECT) {



			} else if (ui_select.page_snd_select.sub_screen_index == ITEM_CHECK) {

				if (ui_select.ui_pause_100ms_cnt >= UI_PAUSE_2_SEC) {

					info.page_step = INIT;

				} else {

					led_font_fun.led_7seg_text_show(ON,TEXT_YES);
				}

			} else {
				__NOP();
			}


		default:
			__NOP();

	}
}

void page_dur (void)
{

	switch(info.page_step) {

		case INIT:

			if (info.cc1200_timeout_cn >= CC1200_TIMEOUT_SEC)
				led_font_fun.rssi_show(OFF,0);
			else
				draw_Rssi();

			led_font_fun.led_7seg_text_show(ON,TEXT_DUR);
			led_font_fun.unit_show(ON,info.windv_unit);
			ui_select.page_dur_select.sub_screen_index = ITEM_SELECT;

		break;

		case WORK:

			if (info.cc1200_timeout_cn >= CC1200_TIMEOUT_SEC)
				led_font_fun.rssi_show(OFF,0);
			else
				draw_Rssi();

			led_font_fun.unit_show(ON,info.windv_unit);

			if (ui_select.page_dur_select.sub_screen_index == ITEM_SELECT) {



			} else if (ui_select.page_dur_select.sub_screen_index == ITEM_CHECK) {

				if (ui_select.ui_pause_100ms_cnt >= UI_PAUSE_2_SEC) {

					info.page_step = INIT;

				} else {

					led_font_fun.led_7seg_text_show(ON,TEXT_YES);
				}

			} else {
				__NOP();
			}


		default:
			__NOP();

	}
}

void page_fla (void)
{

	switch(info.page_step) {

		case INIT:

			if (info.cc1200_timeout_cn >= CC1200_TIMEOUT_SEC)
				led_font_fun.rssi_show(OFF,0);
			else
				draw_Rssi();

			led_font_fun.led_7seg_text_show(ON,TEXT_FLA);
			led_font_fun.unit_show(ON,info.windv_unit);
			ui_select.page_fla_select.sub_screen_index = ITEM_SELECT;

		break;

		case WORK:

			if (info.cc1200_timeout_cn >= CC1200_TIMEOUT_SEC)
				led_font_fun.rssi_show(OFF,0);
			else
				draw_Rssi();

			led_font_fun.unit_show(ON,info.windv_unit);

			if (ui_select.page_fla_select.sub_screen_index == ITEM_SELECT) {



			} else if (ui_select.page_fla_select.sub_screen_index == ITEM_CHECK) {

				if (ui_select.ui_pause_100ms_cnt >= UI_PAUSE_2_SEC) {

					info.page_step = INIT;

				} else {

					led_font_fun.led_7seg_text_show(ON,TEXT_YES);
				}

			} else {
				__NOP();
			}


		default:
			__NOP();

	}
}

void page_bri (void)
{

	switch(info.page_step) {

		case INIT:

			if (info.cc1200_timeout_cn >= CC1200_TIMEOUT_SEC)
				led_font_fun.rssi_show(OFF,0);
			else
				draw_Rssi();

			led_font_fun.led_7seg_text_show(ON,TEXT_BRI);
			led_font_fun.unit_show(ON,info.windv_unit);
			ui_select.page_bri_select.sub_screen_index = ITEM_SELECT;
		break;

		case WORK:

			if (info.cc1200_timeout_cn >= CC1200_TIMEOUT_SEC)
				led_font_fun.rssi_show(OFF,0);
			else
				draw_Rssi();

			led_font_fun.unit_show(ON,info.windv_unit);

			if (ui_select.page_bri_select.sub_screen_index == ITEM_SELECT) {



			} else if (ui_select.page_bri_select.sub_screen_index == ITEM_CHECK) {

				if (ui_select.ui_pause_100ms_cnt >= UI_PAUSE_2_SEC) {

					info.page_step = INIT;

				} else {

					led_font_fun.led_7seg_text_show(ON,TEXT_YES);
				}

			} else {
				__NOP();
			}

		default:
			__NOP();

	}
}

void page_unt (void)
{

	switch(info.page_step) {

		case INIT:

			if (info.cc1200_timeout_cn >= CC1200_TIMEOUT_SEC)
				led_font_fun.rssi_show(OFF,0);
			else
				draw_Rssi();

			led_font_fun.led_7seg_text_show(ON,TEXT_UNT);
			led_font_fun.unit_show(ON,info.windv_unit);
			ui_select.page_unit_select.sub_screen_index = ITEM_SELECT;

		break;

		case WORK:

			if (info.cc1200_timeout_cn >= CC1200_TIMEOUT_SEC)
				led_font_fun.rssi_show(OFF,0);
			else
				draw_Rssi();


			if (ui_select.page_unit_select.sub_screen_index == ITEM_SELECT) {

				led_font_fun.led_n1_number(OFF,0);
				led_font_fun.led_n2_number(OFF,0);

				if (ui_select.page_unit_select.unit == UNIT_MPH)
					led_font_fun.led_n3_number(ON,1);
				else if (ui_select.page_unit_select.unit == UNIT_KM)
					led_font_fun.led_n3_number(ON,2);
				else if (ui_select.page_unit_select.unit == UNIT_MS)
					led_font_fun.led_n3_number(ON,3);
				else
					__NOP();

				led_font_fun.unit_show(ON,ui_select.page_unit_select.unit);

			} else if (ui_select.page_unit_select.sub_screen_index == ITEM_CHECK) {

				if (ui_select.ui_pause_100ms_cnt >= UI_PAUSE_2_SEC) {

					info.page_step = INIT;

				} else {

					led_font_fun.led_7seg_text_show(ON,TEXT_YES);
				}

			} else {
				__NOP();
			}

		default:
			__NOP();

	}
}

void page_nod (void)
{

	switch(info.page_step) {

		case INIT:

			if (info.cc1200_timeout_cn >= CC1200_TIMEOUT_SEC)
				led_font_fun.rssi_show(OFF,0);
			else
				draw_Rssi();

			led_font_fun.led_7seg_text_show(ON,TEXT_NOD);
			led_font_fun.unit_show(ON,info.windv_unit);
			ui_select.page_nod_select.sub_screen_index = ITEM_SELECT;

		break;

		case WORK:

			if (info.cc1200_timeout_cn >= CC1200_TIMEOUT_SEC)
				led_font_fun.rssi_show(OFF,0);
			else
				draw_Rssi();

			led_font_fun.unit_show(ON,info.windv_unit);

			if (ui_select.page_nod_select.sub_screen_index == ITEM_SELECT) {



			} else if (ui_select.page_nod_select.sub_screen_index == ITEM_CHECK) {

				if (ui_select.ui_pause_100ms_cnt >= UI_PAUSE_2_SEC) {

					info.page_step = INIT;

				} else {

					led_font_fun.led_7seg_text_show(ON,TEXT_YES);
				}

			} else {
				__NOP();
			}

		default:
			__NOP();

	}
}
