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

void ui_init(void)
{
	ui_fun_array[0] = page_logo;
	ui_fun_array[1] = page_main;
	ui_fun_array[2] = page_dev;

	info.current_page = PAGE_LOGO;
	info.page_step = INIT;
}


void page_logo (void)
{
	uint8_t i = 0;

	switch(info.page_step) {

		case INIT:

			info.page_step = WORK;

		case WORK:

			led_font_fun.led_7seg_pic_show(ON,PIC_ALL_ON,0);

			windview_eeprom_read();

			W1_RESET = 0;
			CLK_SysTickDelay(200000);
			W1_RESET = 1;

			cc1200_work_ch = info.wireless_ch_status;

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
			}

			info.current_page = PAGE_MAIN;
			info.page_step = INIT;

		default:
			__NOP();

	}
}

void page_main (void)
{

	switch(info.page_step) {

		case INIT:


		case WORK:


		default:
			__NOP();

	}
}

void page_dev (void)
{

	switch(info.page_step) {

		case INIT:


		case WORK:


		default:
			__NOP();

	}
}



