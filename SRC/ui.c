#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "main.h"
#include "ui.h"
#include "cc1200.h"

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

	switch(info.page_step) {

		case INIT:


		case WORK:


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



