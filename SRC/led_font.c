/*
 *	LED Font
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "led_font.h"
#include "main.h"



struct LED_Font led_font_fun;

//===================================================
//	NO 1
//===================================================
uint8_t led_n1_number(uint8_t on_off,uint8_t no)
{
	if (on_off == OFF) {

		N1_A_PIN = 0;
		N1_B_PIN = 0;
		N1_C_PIN = 0;
		N1_D_PIN = 0;
		N1_E_PIN = 0;
		N1_F_PIN = 0;
		N1_G_PIN = 0;

	} else {

		switch(no) {

			case 0:

				N1_A_PIN = 1;
				N1_B_PIN = 1;
				N1_C_PIN = 1;
				N1_D_PIN = 1;
				N1_E_PIN = 1;
				N1_F_PIN = 1;
				N1_G_PIN = 0;

				break;

			case 1:

				N1_A_PIN = 0;
				N1_B_PIN = 1;
				N1_C_PIN = 1;
				N1_D_PIN = 0;
				N1_E_PIN = 0;
				N1_F_PIN = 0;
				N1_G_PIN = 0;

				break;

			case 2:

				N1_A_PIN = 1;
				N1_B_PIN = 1;
				N1_C_PIN = 0;
				N1_D_PIN = 1;
				N1_E_PIN = 1;
				N1_F_PIN = 0;
				N1_G_PIN = 1;

				break;

			case 3:

				N1_A_PIN = 1;
				N1_B_PIN = 1;
				N1_C_PIN = 1;
				N1_D_PIN = 1;
				N1_E_PIN = 0;
				N1_F_PIN = 0;
				N1_G_PIN = 1;

				break;

			case 4:

				N1_A_PIN = 0;
				N1_B_PIN = 1;
				N1_C_PIN = 1;
				N1_D_PIN = 0;
				N1_E_PIN = 0;
				N1_F_PIN = 1;
				N1_G_PIN = 1;

				break;

			case 5:

				N1_A_PIN = 1;
				N1_B_PIN = 0;
				N1_C_PIN = 1;
				N1_D_PIN = 1;
				N1_E_PIN = 0;
				N1_F_PIN = 1;
				N1_G_PIN = 1;

				break;

			case 6:

				N1_A_PIN = 1;
				N1_B_PIN = 0;
				N1_C_PIN = 1;
				N1_D_PIN = 1;
				N1_E_PIN = 1;
				N1_F_PIN = 1;
				N1_G_PIN = 1;

				break;

			case 7:

				N1_A_PIN = 1;
				N1_B_PIN = 1;
				N1_C_PIN = 1;
				N1_D_PIN = 0;
				N1_E_PIN = 0;
				N1_F_PIN = 0;
				N1_G_PIN = 0;

				break;

			case 8:

				N1_A_PIN = 1;
				N1_B_PIN = 1;
				N1_C_PIN = 1;
				N1_D_PIN = 1;
				N1_E_PIN = 1;
				N1_F_PIN = 1;
				N1_G_PIN = 1;

				break;

			case 9:

				N1_A_PIN = 1;
				N1_B_PIN = 1;
				N1_C_PIN = 1;
				N1_D_PIN = 1;
				N1_E_PIN = 0;
				N1_F_PIN = 1;
				N1_G_PIN = 1;

				break;

			default :

				N1_A_PIN = 0;
				N1_B_PIN = 0;
				N1_C_PIN = 0;
				N1_D_PIN = 0;
				N1_E_PIN = 0;
				N1_F_PIN = 0;
				N1_G_PIN = 0;

				break;
		}
	}

	return 0;
}

uint8_t led_n1_text(uint8_t on_off,uint8_t text)
{
	if (on_off == OFF) {

		N1_A_PIN = 0;
		N1_B_PIN = 0;
		N1_C_PIN = 0;
		N1_D_PIN = 0;
		N1_E_PIN = 0;
		N1_F_PIN = 0;
		N1_G_PIN = 0;

	} else {

		switch(text- 0x41) {

			case TEXT_A:

				N1_A_PIN = 1;
				N1_B_PIN = 1;
				N1_C_PIN = 1;
				N1_D_PIN = 0;
				N1_E_PIN = 1;
				N1_F_PIN = 1;
				N1_G_PIN = 1;

				break;

			case TEXT_B:

				N1_A_PIN = 0;
				N1_B_PIN = 0;
				N1_C_PIN = 1;
				N1_D_PIN = 1;
				N1_E_PIN = 1;
				N1_F_PIN = 1;
				N1_G_PIN = 1;

				break;

			case TEXT_C:

				N1_A_PIN = 1;
				N1_B_PIN = 0;
				N1_C_PIN = 0;
				N1_D_PIN = 1;
				N1_E_PIN = 1;
				N1_F_PIN = 1;
				N1_G_PIN = 0;

				break;

			case TEXT_D:

				N1_A_PIN = 0;
				N1_B_PIN = 1;
				N1_C_PIN = 1;
				N1_D_PIN = 1;
				N1_E_PIN = 1;
				N1_F_PIN = 0;
				N1_G_PIN = 1;

				break;

			case TEXT_E:

				N1_A_PIN = 1;
				N1_B_PIN = 0;
				N1_C_PIN = 0;
				N1_D_PIN = 1;
				N1_E_PIN = 1;
				N1_F_PIN = 1;
				N1_G_PIN = 1;

				break;

			case TEXT_F:

				N1_A_PIN = 1;
				N1_B_PIN = 0;
				N1_C_PIN = 0;
				N1_D_PIN = 0;
				N1_E_PIN = 1;
				N1_F_PIN = 1;
				N1_G_PIN = 1;

				break;

			case TEXT_G:

				N1_A_PIN = 1;
				N1_B_PIN = 0;
				N1_C_PIN = 1;
				N1_D_PIN = 1;
				N1_E_PIN = 1;
				N1_F_PIN = 1;
				N1_G_PIN = 0;

				break;

			case TEXT_H:

				N1_A_PIN = 0;
				N1_B_PIN = 1;
				N1_C_PIN = 1;
				N1_D_PIN = 0;
				N1_E_PIN = 1;
				N1_F_PIN = 1;
				N1_G_PIN = 1;

				break;

			case TEXT_I:

				N1_A_PIN = 0;
				N1_B_PIN = 1;
				N1_C_PIN = 1;
				N1_D_PIN = 0;
				N1_E_PIN = 0;
				N1_F_PIN = 0;
				N1_G_PIN = 0;

				break;

			case TEXT_J:

				N1_A_PIN = 0;
				N1_B_PIN = 1;
				N1_C_PIN = 1;
				N1_D_PIN = 1;
				N1_E_PIN = 0;
				N1_F_PIN = 0;
				N1_G_PIN = 0;

				break;

			case TEXT_K:		//X

				N1_A_PIN = 0;
				N1_B_PIN = 0;
				N1_C_PIN = 0;
				N1_D_PIN = 0;
				N1_E_PIN = 0;
				N1_F_PIN = 0;
				N1_G_PIN = 0;

				break;

			case TEXT_L:

				N1_A_PIN = 0;
				N1_B_PIN = 0;
				N1_C_PIN = 0;
				N1_D_PIN = 1;
				N1_E_PIN = 1;
				N1_F_PIN = 1;
				N1_G_PIN = 0;

				break;

			case TEXT_M:		//X

				N1_A_PIN = 0;
				N1_B_PIN = 0;
				N1_C_PIN = 0;
				N1_D_PIN = 0;
				N1_E_PIN = 0;
				N1_F_PIN = 0;
				N1_G_PIN = 0;

				break;

			case TEXT_N:

				N1_A_PIN = 0;
				N1_B_PIN = 0;
				N1_C_PIN = 1;
				N1_D_PIN = 0;
				N1_E_PIN = 1;
				N1_F_PIN = 0;
				N1_G_PIN = 1;

				break;

			case TEXT_O:

				N1_A_PIN = 1;
				N1_B_PIN = 1;
				N1_C_PIN = 1;
				N1_D_PIN = 1;
				N1_E_PIN = 1;
				N1_F_PIN = 1;
				N1_G_PIN = 0;

				break;

			case TEXT_P:

				N1_A_PIN = 1;
				N1_B_PIN = 1;
				N1_C_PIN = 0;
				N1_D_PIN = 0;
				N1_E_PIN = 1;
				N1_F_PIN = 1;
				N1_G_PIN = 1;

				break;

			case TEXT_Q:

				N1_A_PIN = 1;
				N1_B_PIN = 1;
				N1_C_PIN = 1;
				N1_D_PIN = 0;
				N1_E_PIN = 0;
				N1_F_PIN = 1;
				N1_G_PIN = 1;

				break;

			case TEXT_R:

				N1_A_PIN = 0;
				N1_B_PIN = 0;
				N1_C_PIN = 0;
				N1_D_PIN = 0;
				N1_E_PIN = 1;
				N1_F_PIN = 0;
				N1_G_PIN = 1;

				break;

			case TEXT_S:

				N1_A_PIN = 1;
				N1_B_PIN = 0;
				N1_C_PIN = 1;
				N1_D_PIN = 1;
				N1_E_PIN = 0;
				N1_F_PIN = 1;
				N1_G_PIN = 1;

				break;

			case TEXT_T:

				N1_A_PIN = 0;
				N1_B_PIN = 0;
				N1_C_PIN = 0;
				N1_D_PIN = 1;
				N1_E_PIN = 1;
				N1_F_PIN = 1;
				N1_G_PIN = 1;

				break;

			case TEXT_U:

				N1_A_PIN = 0;
				N1_B_PIN = 1;
				N1_C_PIN = 1;
				N1_D_PIN = 1;
				N1_E_PIN = 1;
				N1_F_PIN = 1;
				N1_G_PIN = 0;

				break;

			case TEXT_V:

				N1_A_PIN = 0;
				N1_B_PIN = 1;
				N1_C_PIN = 1;
				N1_D_PIN = 1;
				N1_E_PIN = 1;
				N1_F_PIN = 1;
				N1_G_PIN = 0;

				break;

			case TEXT_W:		//X

				N1_A_PIN = 0;
				N1_B_PIN = 0;
				N1_C_PIN = 0;
				N1_D_PIN = 0;
				N1_E_PIN = 0;
				N1_F_PIN = 0;
				N1_G_PIN = 0;

				break;

			case TEXT_X:		//X

				N1_A_PIN = 0;
				N1_B_PIN = 0;
				N1_C_PIN = 0;
				N1_D_PIN = 0;
				N1_E_PIN = 0;
				N1_F_PIN = 0;
				N1_G_PIN = 0;

				break;

			case TEXT_Y:

				N1_A_PIN = 0;
				N1_B_PIN = 1;
				N1_C_PIN = 1;
				N1_D_PIN = 0;
				N1_E_PIN = 0;
				N1_F_PIN = 1;
				N1_G_PIN = 1;

				break;

			case TEXT_Z:

				N1_A_PIN = 1;
				N1_B_PIN = 1;
				N1_C_PIN = 0;
				N1_D_PIN = 1;
				N1_E_PIN = 1;
				N1_F_PIN = 0;
				N1_G_PIN = 1;

				break;

			default :

				N1_A_PIN = 0;
				N1_B_PIN = 0;
				N1_C_PIN = 0;
				N1_D_PIN = 0;
				N1_E_PIN = 0;
				N1_F_PIN = 0;
				N1_G_PIN = 0;

				break;
		}
	}

	return 0;
}

//===================================================
//	NO 2
//===================================================
uint8_t led_n2_number(uint8_t on_off,uint8_t no)
{
	if (on_off == OFF) {

		N2_A_PIN = 0;
		N2_B_PIN = 0;
		N2_C_PIN = 0;
		N2_D_PIN = 0;
		N2_E_PIN = 0;
		N2_F_PIN = 0;
		N2_G_PIN = 0;

	} else {

		switch(no) {

			case 0:

				N2_A_PIN = 1;
				N2_B_PIN = 1;
				N2_C_PIN = 1;
				N2_D_PIN = 1;
				N2_E_PIN = 1;
				N2_F_PIN = 1;
				N2_G_PIN = 0;

				break;

			case 1:

				N2_A_PIN = 0;
				N2_B_PIN = 1;
				N2_C_PIN = 1;
				N2_D_PIN = 0;
				N2_E_PIN = 0;
				N2_F_PIN = 0;
				N2_G_PIN = 0;

				break;

			case 2:

				N2_A_PIN = 1;
				N2_B_PIN = 1;
				N2_C_PIN = 0;
				N2_D_PIN = 1;
				N2_E_PIN = 1;
				N2_F_PIN = 0;
				N2_G_PIN = 1;

				break;

			case 3:

				N2_A_PIN = 1;
				N2_B_PIN = 1;
				N2_C_PIN = 1;
				N2_D_PIN = 1;
				N2_E_PIN = 0;
				N2_F_PIN = 0;
				N2_G_PIN = 1;

				break;

			case 4:

				N2_A_PIN = 0;
				N2_B_PIN = 1;
				N2_C_PIN = 1;
				N2_D_PIN = 0;
				N2_E_PIN = 0;
				N2_F_PIN = 1;
				N2_G_PIN = 1;

				break;

			case 5:

				N2_A_PIN = 1;
				N2_B_PIN = 0;
				N2_C_PIN = 1;
				N2_D_PIN = 1;
				N2_E_PIN = 0;
				N2_F_PIN = 1;
				N2_G_PIN = 1;

				break;

			case 6:

				N2_A_PIN = 1;
				N2_B_PIN = 0;
				N2_C_PIN = 1;
				N2_D_PIN = 1;
				N2_E_PIN = 1;
				N2_F_PIN = 1;
				N2_G_PIN = 1;

				break;

			case 7:

				N2_A_PIN = 1;
				N2_B_PIN = 1;
				N2_C_PIN = 1;
				N2_D_PIN = 0;
				N2_E_PIN = 0;
				N2_F_PIN = 0;
				N2_G_PIN = 0;

				break;

			case 8:

				N2_A_PIN = 1;
				N2_B_PIN = 1;
				N2_C_PIN = 1;
				N2_D_PIN = 1;
				N2_E_PIN = 1;
				N2_F_PIN = 1;
				N2_G_PIN = 1;

				break;

			case 9:

				N2_A_PIN = 1;
				N2_B_PIN = 1;
				N2_C_PIN = 1;
				N2_D_PIN = 1;
				N2_E_PIN = 0;
				N2_F_PIN = 1;
				N2_G_PIN = 1;

				break;

			default :

				N2_A_PIN = 0;
				N2_B_PIN = 0;
				N2_C_PIN = 0;
				N2_D_PIN = 0;
				N2_E_PIN = 0;
				N2_F_PIN = 0;
				N2_G_PIN = 0;

				break;
		}
	}

	return 0;
}

uint8_t led_n2_text(uint8_t on_off,uint8_t text)
{
	if (on_off == OFF) {

		N2_A_PIN = 0;
		N2_B_PIN = 0;
		N2_C_PIN = 0;
		N2_D_PIN = 0;
		N2_E_PIN = 0;
		N2_F_PIN = 0;
		N2_G_PIN = 0;

	} else {

		switch(text- 0x41) {

			case TEXT_A:

				N2_A_PIN = 1;
				N2_B_PIN = 1;
				N2_C_PIN = 1;
				N2_D_PIN = 0;
				N2_E_PIN = 1;
				N2_F_PIN = 1;
				N2_G_PIN = 1;

				break;

			case TEXT_B:

				N2_A_PIN = 0;
				N2_B_PIN = 0;
				N2_C_PIN = 1;
				N2_D_PIN = 1;
				N2_E_PIN = 1;
				N2_F_PIN = 1;
				N2_G_PIN = 1;

				break;

			case TEXT_C:

				N2_A_PIN = 1;
				N2_B_PIN = 0;
				N2_C_PIN = 0;
				N2_D_PIN = 1;
				N2_E_PIN = 1;
				N2_F_PIN = 1;
				N2_G_PIN = 0;

				break;

			case TEXT_D:

				N2_A_PIN = 0;
				N2_B_PIN = 1;
				N2_C_PIN = 1;
				N2_D_PIN = 1;
				N2_E_PIN = 1;
				N2_F_PIN = 0;
				N2_G_PIN = 1;

				break;

			case TEXT_E:

				N2_A_PIN = 1;
				N2_B_PIN = 0;
				N2_C_PIN = 0;
				N2_D_PIN = 1;
				N2_E_PIN = 1;
				N2_F_PIN = 1;
				N2_G_PIN = 1;

				break;

			case TEXT_F:

				N2_A_PIN = 1;
				N2_B_PIN = 0;
				N2_C_PIN = 0;
				N2_D_PIN = 0;
				N2_E_PIN = 1;
				N2_F_PIN = 1;
				N2_G_PIN = 1;

				break;

			case TEXT_G:

				N2_A_PIN = 1;
				N2_B_PIN = 0;
				N2_C_PIN = 1;
				N2_D_PIN = 1;
				N2_E_PIN = 1;
				N2_F_PIN = 1;
				N2_G_PIN = 0;

				break;

			case TEXT_H:

				N2_A_PIN = 0;
				N2_B_PIN = 1;
				N2_C_PIN = 1;
				N2_D_PIN = 0;
				N2_E_PIN = 1;
				N2_F_PIN = 1;
				N2_G_PIN = 1;

				break;

			case TEXT_I:

				N2_A_PIN = 0;
				N2_B_PIN = 1;
				N2_C_PIN = 1;
				N2_D_PIN = 0;
				N2_E_PIN = 0;
				N2_F_PIN = 0;
				N2_G_PIN = 0;

				break;

			case TEXT_J:

				N2_A_PIN = 0;
				N2_B_PIN = 1;
				N2_C_PIN = 1;
				N2_D_PIN = 1;
				N2_E_PIN = 0;
				N2_F_PIN = 0;
				N2_G_PIN = 0;

				break;

			case TEXT_K:		//X

				N2_A_PIN = 0;
				N2_B_PIN = 0;
				N2_C_PIN = 0;
				N2_D_PIN = 0;
				N2_E_PIN = 0;
				N2_F_PIN = 0;
				N2_G_PIN = 0;

				break;

			case TEXT_L:

				N2_A_PIN = 0;
				N2_B_PIN = 0;
				N2_C_PIN = 0;
				N2_D_PIN = 1;
				N2_E_PIN = 1;
				N2_F_PIN = 1;
				N2_G_PIN = 0;

				break;

			case TEXT_M:		//X

				N2_A_PIN = 0;
				N2_B_PIN = 0;
				N2_C_PIN = 0;
				N2_D_PIN = 0;
				N2_E_PIN = 0;
				N2_F_PIN = 0;
				N2_G_PIN = 0;

				break;

			case TEXT_N:

				N2_A_PIN = 0;
				N2_B_PIN = 0;
				N2_C_PIN = 1;
				N2_D_PIN = 0;
				N2_E_PIN = 1;
				N2_F_PIN = 0;
				N2_G_PIN = 1;

				break;

			case TEXT_O:

				N2_A_PIN = 1;
				N2_B_PIN = 1;
				N2_C_PIN = 1;
				N2_D_PIN = 1;
				N2_E_PIN = 1;
				N2_F_PIN = 1;
				N2_G_PIN = 0;

				break;

			case TEXT_P:

				N2_A_PIN = 1;
				N2_B_PIN = 1;
				N2_C_PIN = 0;
				N2_D_PIN = 0;
				N2_E_PIN = 1;
				N2_F_PIN = 1;
				N2_G_PIN = 1;

				break;

			case TEXT_Q:

				N2_A_PIN = 1;
				N2_B_PIN = 1;
				N2_C_PIN = 1;
				N2_D_PIN = 0;
				N2_E_PIN = 0;
				N2_F_PIN = 1;
				N2_G_PIN = 1;

				break;

			case TEXT_R:

				N2_A_PIN = 0;
				N2_B_PIN = 0;
				N2_C_PIN = 0;
				N2_D_PIN = 0;
				N2_E_PIN = 1;
				N2_F_PIN = 0;
				N2_G_PIN = 1;

				break;

			case TEXT_S:

				N2_A_PIN = 1;
				N2_B_PIN = 0;
				N2_C_PIN = 1;
				N2_D_PIN = 1;
				N2_E_PIN = 0;
				N2_F_PIN = 1;
				N2_G_PIN = 1;

				break;

			case TEXT_T:

				N2_A_PIN = 0;
				N2_B_PIN = 0;
				N2_C_PIN = 0;
				N2_D_PIN = 1;
				N2_E_PIN = 1;
				N2_F_PIN = 1;
				N2_G_PIN = 1;

				break;

			case TEXT_U:

				N2_A_PIN = 0;
				N2_B_PIN = 1;
				N2_C_PIN = 1;
				N2_D_PIN = 1;
				N2_E_PIN = 1;
				N2_F_PIN = 1;
				N2_G_PIN = 0;

				break;

			case TEXT_V:

				N2_A_PIN = 0;
				N2_B_PIN = 1;
				N2_C_PIN = 1;
				N2_D_PIN = 1;
				N2_E_PIN = 1;
				N2_F_PIN = 1;
				N2_G_PIN = 0;

				break;

			case TEXT_W:		//X

				N2_A_PIN = 0;
				N2_B_PIN = 0;
				N2_C_PIN = 0;
				N2_D_PIN = 0;
				N2_E_PIN = 0;
				N2_F_PIN = 0;
				N2_G_PIN = 0;

				break;

			case TEXT_X:		//X

				N2_A_PIN = 0;
				N2_B_PIN = 0;
				N2_C_PIN = 0;
				N2_D_PIN = 0;
				N2_E_PIN = 0;
				N2_F_PIN = 0;
				N2_G_PIN = 0;

				break;

			case TEXT_Y:

				N2_A_PIN = 0;
				N2_B_PIN = 1;
				N2_C_PIN = 1;
				N2_D_PIN = 0;
				N2_E_PIN = 0;
				N2_F_PIN = 1;
				N2_G_PIN = 1;

				break;

			case TEXT_Z:

				N2_A_PIN = 1;
				N2_B_PIN = 1;
				N2_C_PIN = 0;
				N2_D_PIN = 1;
				N2_E_PIN = 1;
				N2_F_PIN = 0;
				N2_G_PIN = 1;

				break;

			default :

				N2_A_PIN = 0;
				N2_B_PIN = 0;
				N2_C_PIN = 0;
				N2_D_PIN = 0;
				N2_E_PIN = 0;
				N2_F_PIN = 0;
				N2_G_PIN = 0;

				break;
		}
	}

	return 0;
}

//===================================================
//	NO 3
//===================================================
uint8_t led_n3_number(uint8_t on_off,uint8_t no)
{
	if (on_off == OFF) {

		N3_A_PIN = 0;
		N3_B_PIN = 0;
		N3_C_PIN = 0;
		N3_D_PIN = 0;
		N3_E_PIN = 0;
		N3_F_PIN = 0;
		N3_G_PIN = 0;

	} else {

		switch(no) {

			case 0:

				N3_A_PIN = 1;
				N3_B_PIN = 1;
				N3_C_PIN = 1;
				N3_D_PIN = 1;
				N3_E_PIN = 1;
				N3_F_PIN = 1;
				N3_G_PIN = 0;

				break;

			case 1:

				N3_A_PIN = 0;
				N3_B_PIN = 1;
				N3_C_PIN = 1;
				N3_D_PIN = 0;
				N3_E_PIN = 0;
				N3_F_PIN = 0;
				N3_G_PIN = 0;

				break;

			case 2:

				N3_A_PIN = 1;
				N3_B_PIN = 1;
				N3_C_PIN = 0;
				N3_D_PIN = 1;
				N3_E_PIN = 1;
				N3_F_PIN = 0;
				N3_G_PIN = 1;

				break;

			case 3:

				N3_A_PIN = 1;
				N3_B_PIN = 1;
				N3_C_PIN = 1;
				N3_D_PIN = 1;
				N3_E_PIN = 0;
				N3_F_PIN = 0;
				N3_G_PIN = 1;

				break;

			case 4:

				N3_A_PIN = 0;
				N3_B_PIN = 1;
				N3_C_PIN = 1;
				N3_D_PIN = 0;
				N3_E_PIN = 0;
				N3_F_PIN = 1;
				N3_G_PIN = 1;

				break;

			case 5:

				N3_A_PIN = 1;
				N3_B_PIN = 0;
				N3_C_PIN = 1;
				N3_D_PIN = 1;
				N3_E_PIN = 0;
				N3_F_PIN = 1;
				N3_G_PIN = 1;

				break;

			case 6:

				N3_A_PIN = 1;
				N3_B_PIN = 0;
				N3_C_PIN = 1;
				N3_D_PIN = 1;
				N3_E_PIN = 1;
				N3_F_PIN = 1;
				N3_G_PIN = 1;

				break;

			case 7:

				N3_A_PIN = 1;
				N3_B_PIN = 1;
				N3_C_PIN = 1;
				N3_D_PIN = 0;
				N3_E_PIN = 0;
				N3_F_PIN = 0;
				N3_G_PIN = 0;

				break;

			case 8:

				N3_A_PIN = 1;
				N3_B_PIN = 1;
				N3_C_PIN = 1;
				N3_D_PIN = 1;
				N3_E_PIN = 1;
				N3_F_PIN = 1;
				N3_G_PIN = 1;

				break;

			case 9:

				N3_A_PIN = 1;
				N3_B_PIN = 1;
				N3_C_PIN = 1;
				N3_D_PIN = 1;
				N3_E_PIN = 0;
				N3_F_PIN = 1;
				N3_G_PIN = 1;

				break;

			default :

				N3_A_PIN = 0;
				N3_B_PIN = 0;
				N3_C_PIN = 0;
				N3_D_PIN = 0;
				N3_E_PIN = 0;
				N3_F_PIN = 0;
				N3_G_PIN = 0;

				break;
		}
	}

	return 0;
}

uint8_t led_n3_text(uint8_t on_off,uint8_t text)
{
	if (on_off == OFF) {

		N3_A_PIN = 0;
		N3_B_PIN = 0;
		N3_C_PIN = 0;
		N3_D_PIN = 0;
		N3_E_PIN = 0;
		N3_F_PIN = 0;
		N3_G_PIN = 0;

	} else {

		switch(text- 0x41) {

			case TEXT_A:

				N3_A_PIN = 1;
				N3_B_PIN = 1;
				N3_C_PIN = 1;
				N3_D_PIN = 0;
				N3_E_PIN = 1;
				N3_F_PIN = 1;
				N3_G_PIN = 1;

				break;

			case TEXT_B:

				N3_A_PIN = 0;
				N3_B_PIN = 0;
				N3_C_PIN = 1;
				N3_D_PIN = 1;
				N3_E_PIN = 1;
				N3_F_PIN = 1;
				N3_G_PIN = 1;

				break;

			case TEXT_C:

				N3_A_PIN = 1;
				N3_B_PIN = 0;
				N3_C_PIN = 0;
				N3_D_PIN = 1;
				N3_E_PIN = 1;
				N3_F_PIN = 1;
				N3_G_PIN = 0;

				break;

			case TEXT_D:

				N3_A_PIN = 0;
				N3_B_PIN = 1;
				N3_C_PIN = 1;
				N3_D_PIN = 1;
				N3_E_PIN = 1;
				N3_F_PIN = 0;
				N3_G_PIN = 1;

				break;

			case TEXT_E:

				N3_A_PIN = 1;
				N3_B_PIN = 0;
				N3_C_PIN = 0;
				N3_D_PIN = 1;
				N3_E_PIN = 1;
				N3_F_PIN = 1;
				N3_G_PIN = 1;

				break;

			case TEXT_F:

				N3_A_PIN = 1;
				N3_B_PIN = 0;
				N3_C_PIN = 0;
				N3_D_PIN = 0;
				N3_E_PIN = 1;
				N3_F_PIN = 1;
				N3_G_PIN = 1;

				break;

			case TEXT_G:

				N3_A_PIN = 1;
				N3_B_PIN = 0;
				N3_C_PIN = 1;
				N3_D_PIN = 1;
				N3_E_PIN = 1;
				N3_F_PIN = 1;
				N3_G_PIN = 0;

				break;

			case TEXT_H:

				N3_A_PIN = 0;
				N3_B_PIN = 1;
				N3_C_PIN = 1;
				N3_D_PIN = 0;
				N3_E_PIN = 1;
				N3_F_PIN = 1;
				N3_G_PIN = 1;

				break;

			case TEXT_I:

				N3_A_PIN = 0;
				N3_B_PIN = 1;
				N3_C_PIN = 1;
				N3_D_PIN = 0;
				N3_E_PIN = 0;
				N3_F_PIN = 0;
				N3_G_PIN = 0;

				break;

			case TEXT_J:

				N3_A_PIN = 0;
				N3_B_PIN = 1;
				N3_C_PIN = 1;
				N3_D_PIN = 1;
				N3_E_PIN = 0;
				N3_F_PIN = 0;
				N3_G_PIN = 0;

				break;

			case TEXT_K:		//X

				N3_A_PIN = 0;
				N3_B_PIN = 0;
				N3_C_PIN = 0;
				N3_D_PIN = 0;
				N3_E_PIN = 0;
				N3_F_PIN = 0;
				N3_G_PIN = 0;

				break;

			case TEXT_L:

				N3_A_PIN = 0;
				N3_B_PIN = 0;
				N3_C_PIN = 0;
				N3_D_PIN = 1;
				N3_E_PIN = 1;
				N3_F_PIN = 1;
				N3_G_PIN = 0;

				break;

			case TEXT_M:		//X

				N3_A_PIN = 0;
				N3_B_PIN = 0;
				N3_C_PIN = 0;
				N3_D_PIN = 0;
				N3_E_PIN = 0;
				N3_F_PIN = 0;
				N3_G_PIN = 0;

				break;

			case TEXT_N:

				N3_A_PIN = 0;
				N3_B_PIN = 0;
				N3_C_PIN = 1;
				N3_D_PIN = 0;
				N3_E_PIN = 1;
				N3_F_PIN = 0;
				N3_G_PIN = 1;

				break;

			case TEXT_O:

				N3_A_PIN = 1;
				N3_B_PIN = 1;
				N3_C_PIN = 1;
				N3_D_PIN = 1;
				N3_E_PIN = 1;
				N3_F_PIN = 1;
				N3_G_PIN = 0;

				break;

			case TEXT_P:

				N3_A_PIN = 1;
				N3_B_PIN = 1;
				N3_C_PIN = 0;
				N3_D_PIN = 0;
				N3_E_PIN = 1;
				N3_F_PIN = 1;
				N3_G_PIN = 1;

				break;

			case TEXT_Q:

				N3_A_PIN = 1;
				N3_B_PIN = 1;
				N3_C_PIN = 1;
				N3_D_PIN = 0;
				N3_E_PIN = 0;
				N3_F_PIN = 1;
				N3_G_PIN = 1;

				break;

			case TEXT_R:

				N3_A_PIN = 0;
				N3_B_PIN = 0;
				N3_C_PIN = 0;
				N3_D_PIN = 0;
				N3_E_PIN = 1;
				N3_F_PIN = 0;
				N3_G_PIN = 1;

				break;

			case TEXT_S:

				N3_A_PIN = 1;
				N3_B_PIN = 0;
				N3_C_PIN = 1;
				N3_D_PIN = 1;
				N3_E_PIN = 0;
				N3_F_PIN = 1;
				N3_G_PIN = 1;

				break;

			case TEXT_T:

				N3_A_PIN = 0;
				N3_B_PIN = 0;
				N3_C_PIN = 0;
				N3_D_PIN = 1;
				N3_E_PIN = 1;
				N3_F_PIN = 1;
				N3_G_PIN = 1;

				break;

			case TEXT_U:

				N3_A_PIN = 0;
				N3_B_PIN = 1;
				N3_C_PIN = 1;
				N3_D_PIN = 1;
				N3_E_PIN = 1;
				N3_F_PIN = 1;
				N3_G_PIN = 0;

				break;

			case TEXT_V:

				N3_A_PIN = 0;
				N3_B_PIN = 1;
				N3_C_PIN = 1;
				N3_D_PIN = 1;
				N3_E_PIN = 1;
				N3_F_PIN = 1;
				N3_G_PIN = 0;

				break;

			case TEXT_W:		//X

				N3_A_PIN = 0;
				N3_B_PIN = 0;
				N3_C_PIN = 0;
				N3_D_PIN = 0;
				N3_E_PIN = 0;
				N3_F_PIN = 0;
				N3_G_PIN = 0;

				break;

			case TEXT_X:		//X

				N3_A_PIN = 0;
				N3_B_PIN = 0;
				N3_C_PIN = 0;
				N3_D_PIN = 0;
				N3_E_PIN = 0;
				N3_F_PIN = 0;
				N3_G_PIN = 0;

				break;

			case TEXT_Y:

				N3_A_PIN = 0;
				N3_B_PIN = 1;
				N3_C_PIN = 1;
				N3_D_PIN = 0;
				N3_E_PIN = 0;
				N3_F_PIN = 1;
				N3_G_PIN = 1;

				break;

			case TEXT_Z:

				N3_A_PIN = 1;
				N3_B_PIN = 1;
				N3_C_PIN = 0;
				N3_D_PIN = 1;
				N3_E_PIN = 1;
				N3_F_PIN = 0;
				N3_G_PIN = 1;

				break;

			default :

				N3_A_PIN = 0;
				N3_B_PIN = 0;
				N3_C_PIN = 0;
				N3_D_PIN = 0;
				N3_E_PIN = 0;
				N3_F_PIN = 0;
				N3_G_PIN = 0;

				break;
		}
	}

	return 0;
}

//===================================================

uint8_t unit_show(uint8_t on_off,uint8_t unit_type)
{
	if (on_off == OFF) {

		MP_PIN = 0;
		KM_PIN = 0;
		MS_PIN = 0;

	} else if (unit_type == UNIT_MS) {

		MP_PIN = 0;
		KM_PIN = 0;
		MS_PIN = 1;

	} else if (unit_type == UNIT_KM) {

		MP_PIN = 0;
		KM_PIN = 1;
		MS_PIN = 0;

	} else if (unit_type == UNIT_MPH) {

		MP_PIN = 1;
		KM_PIN = 0;
		MS_PIN = 0;

	} else {

		MP_PIN = 0;
		KM_PIN = 0;
		MS_PIN = 0;
	}

	return 0;
}

uint8_t rssi_show(uint8_t on_off,uint8_t rss_level)
{
	if (on_off == OFF) {

		RSSI_1_PIN = 0;
		RSSI_2_PIN = 0;
		RSSI_3_PIN = 0;
		RSSI_4_PIN = 0;

	} else if (rss_level ==RSSI_LV0) {

		RSSI_1_PIN = 0;
		RSSI_2_PIN = 0;
		RSSI_3_PIN = 0;
		RSSI_4_PIN = 0;

	} else if (rss_level ==RSSI_LV1) {

		RSSI_1_PIN = 1;
		RSSI_2_PIN = 0;
		RSSI_3_PIN = 0;
		RSSI_4_PIN = 0;

	} else if (rss_level ==RSSI_LV2) {

		RSSI_1_PIN = 1;
		RSSI_2_PIN = 1;
		RSSI_3_PIN = 0;
		RSSI_4_PIN = 0;

	} else if (rss_level ==RSSI_LV3) {

		RSSI_1_PIN = 1;
		RSSI_2_PIN = 1;
		RSSI_3_PIN = 1;
		RSSI_4_PIN = 0;

	} else if (rss_level ==RSSI_LV4) {

		RSSI_1_PIN = 1;
		RSSI_2_PIN = 1;
		RSSI_3_PIN = 1;
		RSSI_4_PIN = 1;

	} else {

		RSSI_1_PIN = 0;
		RSSI_2_PIN = 0;
		RSSI_3_PIN = 0;
		RSSI_4_PIN = 0;
	}

	return 0;
}

uint8_t led_7seg_number_show(uint8_t on_off,uint16_t value)
{
	uint8_t num = 0;

	if (on_off == OFF) {

		DOT_PIN = 0;
		led_n1_number(OFF,0xff);
		led_n2_number(OFF,0xff);
		led_n3_number(OFF,0xff);

	} else {

		//數值小於1000需有小數點,大於1000則除10無小數點
		//無前導零

		if (value < 1000) {

			DOT_PIN = 1;

			if (value >= 100) {

				num = (value % 1000) / 100;
				led_n1_number(ON,num);

				num = (value % 100) / 10;
				led_n2_number(ON,num);

				num = (value % 10);
				led_n3_number(ON,num);

			} else if (value >= 10) {

				led_n1_number(OFF,0);

				num = (value % 100) / 10;
				led_n2_number(ON,num);

				num = (value % 10);
				led_n3_number(ON,num);

			} else {

				led_n1_number(OFF,0);

				num = (value % 100) / 10;
				led_n2_number(ON,num);

				num = (value % 10);
				led_n3_number(ON,num);
			}

		} else {

			// value >= 1000

			DOT_PIN = 0;

			value = value / 10;

			num = (value % 1000) / 100;
			led_n1_number(ON,num);

			num = (value % 100) / 10;
			led_n2_number(ON,num);

			num = (value % 10);
			led_n3_number(ON,num);

		}
	}

	return 0;
}



uint8_t led_7seg_text_show(uint8_t on_off,uint8_t word)
{

	if (on_off == OFF) {

		DOT_PIN = 0;
		led_n1_number(OFF,0xff);
		led_n2_number(OFF,0xff);
		led_n3_number(OFF,0xff);

	} else {

		DOT_PIN = 0;
		led_n1_number(OFF,0xff);
		led_n2_number(OFF,0xff);
		led_n3_number(OFF,0xff);

		switch (word) {

			case TEXT_DEV:

				led_n1_text(ON,'D');
				led_n2_text(ON,'E');
				led_n3_text(ON,'V');

				break;

			case TEXT_AD:

				led_n1_text(OFF,' ');
				led_n2_text(ON,'A');
				led_n3_text(ON,'D');

				break;

			case TEXT_THR:

				led_n1_text(ON,'T');
				led_n2_text(ON,'H');
				led_n3_text(ON,'R');

				break;

			case TEXT_SND:

				led_n1_text(ON,'S');
				led_n2_text(ON,'N');
				led_n3_text(ON,'D');

				break;

			case TEXT_DUR:

				led_n1_text(ON,'D');
				led_n2_text(ON,'U');
				led_n3_text(ON,'R');

				break;

			case TEXT_FLA:

				led_n1_text(ON,'F');
				led_n2_text(ON,'L');
				led_n3_text(ON,'A');

				break;

			case TEXT_BRI:

				led_n1_text(ON,'B');
				led_n2_text(ON,'R');
				led_n3_text(ON,'I');

				break;

			case TEXT_UNT:

				led_n1_text(ON,'U');
				led_n2_text(ON,'N');
				led_n3_text(ON,'T');

				break;

			case TEXT_NOD:

				led_n1_text(ON,'N');
				led_n2_text(ON,'O');
				led_n3_text(ON,'D');

				break;

			case TEXT_YES:

				led_n1_text(ON,'Y');
				led_n2_text(ON,'E');
				led_n3_text(ON,'S');

				break;

			default:

				DOT_PIN = 0;
				led_n1_number(OFF,0xff);
				led_n2_number(OFF,0xff);
				led_n3_number(OFF,0xff);

			break;

		}
	}

	return 0;
}


uint8_t led_7seg_pic_show(uint8_t on_off,uint8_t pic_item,uint8_t item_index)
{

	if (on_off == OFF) {

		// All OFF
		DOT_PIN = 0;

		led_n1_number(OFF,0xff);
		led_n2_number(OFF,0xff);
		led_n3_number(OFF,0xff);

		RSSI_1_PIN = 0;
		RSSI_2_PIN = 0;
		RSSI_3_PIN = 0;
		RSSI_4_PIN = 0;

		MP_PIN = 0;
		KM_PIN = 0;
		MS_PIN = 0;

	} else {

		switch (pic_item) {

			case PIC_ALL_ON:

				// All ON
				DOT_PIN = 1;

				led_n1_number(ON,8);
				led_n2_number(ON,8);
				led_n3_number(ON,8);

				RSSI_1_PIN = 1;
				RSSI_2_PIN = 1;
				RSSI_3_PIN = 1;
				RSSI_4_PIN = 1;

				MP_PIN = 1;
				KM_PIN = 1;
				MS_PIN = 1;

				break;

			case PIC_TURN_ON_MOVE:	// 開機全顯後右移

				if (item_index == 0) {

					N1_A_PIN = 1;
					N1_B_PIN = 0;
					N1_C_PIN = 0;
					N1_D_PIN = 1;
					N1_E_PIN = 0;
					N1_F_PIN = 0;
					N1_G_PIN = 1;

					N2_A_PIN = 0;
					N2_B_PIN = 0;
					N2_C_PIN = 0;
					N2_D_PIN = 0;
					N2_E_PIN = 0;
					N2_F_PIN = 0;
					N2_G_PIN = 0;

					N3_A_PIN = 0;
					N3_B_PIN = 0;
					N3_C_PIN = 0;
					N3_D_PIN = 0;
					N3_E_PIN = 0;
					N3_F_PIN = 0;
					N3_G_PIN = 0;

				} else if (item_index == 1) {

					N1_A_PIN = 0;
					N1_B_PIN = 0;
					N1_C_PIN = 0;
					N1_D_PIN = 0;
					N1_E_PIN = 0;
					N1_F_PIN = 0;
					N1_G_PIN = 0;

					N2_A_PIN = 1;
					N2_B_PIN = 0;
					N2_C_PIN = 0;
					N2_D_PIN = 1;
					N2_E_PIN = 0;
					N2_F_PIN = 0;
					N2_G_PIN = 1;

					N3_A_PIN = 0;
					N3_B_PIN = 0;
					N3_C_PIN = 0;
					N3_D_PIN = 0;
					N3_E_PIN = 0;
					N3_F_PIN = 0;
					N3_G_PIN = 0;

				} else if (item_index == 2) {

					N1_A_PIN = 0;
					N1_B_PIN = 0;
					N1_C_PIN = 0;
					N1_D_PIN = 0;
					N1_E_PIN = 0;
					N1_F_PIN = 0;
					N1_G_PIN = 0;

					N2_A_PIN = 0;
					N2_B_PIN = 0;
					N2_C_PIN = 0;
					N2_D_PIN = 0;
					N2_E_PIN = 0;
					N2_F_PIN = 0;
					N2_G_PIN = 0;

					N3_A_PIN = 1;
					N3_B_PIN = 0;
					N3_C_PIN = 0;
					N3_D_PIN = 1;
					N3_E_PIN = 0;
					N3_F_PIN = 0;
					N3_G_PIN = 1;

				} else {
					__NOP();
				}

				break;

			case PIC_NO_LINK:

				DOT_PIN = 0;

				N1_A_PIN = 0;
				N1_B_PIN = 0;
				N1_C_PIN = 0;
				N1_D_PIN = 0;
				N1_E_PIN = 0;
				N1_F_PIN = 0;
				N1_G_PIN = 1;

				led_n2_number(OFF,0xFF);

				N3_A_PIN = 0;
				N3_B_PIN = 0;
				N3_C_PIN = 0;
				N3_D_PIN = 0;
				N3_E_PIN = 0;
				N3_F_PIN = 0;
				N3_G_PIN = 1;

				RSSI_1_PIN = 0;
				RSSI_2_PIN = 0;
				RSSI_3_PIN = 0;
				RSSI_4_PIN = 0;

				MP_PIN = 0;
				KM_PIN = 0;
				MS_PIN = 0;

				break;

			case PIC_RESET_ROLL:

				DOT_PIN = 0;
				MP_PIN = 0;
				KM_PIN = 0;
				MS_PIN = 0;

				if (item_index == 0) {

					N1_A_PIN = 1;
					N1_B_PIN = 0;
					N1_C_PIN = 0;
					N1_D_PIN = 0;
					N1_E_PIN = 0;
					N1_F_PIN = 0;
					N1_G_PIN = 0;

					led_n2_number(OFF,0xFF);
					led_n3_number(OFF,0xFF);

				} else if (item_index == 1) {

					led_n1_number(OFF,0xFF);

					N2_A_PIN = 1;
					N2_B_PIN = 0;
					N2_C_PIN = 0;
					N2_D_PIN = 0;
					N2_E_PIN = 0;
					N2_F_PIN = 0;
					N2_G_PIN = 0;

					led_n3_number(OFF,0xFF);

				} else if (item_index == 2) {

					led_n1_number(OFF,0xFF);
					led_n2_number(OFF,0xFF);

					N3_A_PIN = 1;
					N3_B_PIN = 0;
					N3_C_PIN = 0;
					N3_D_PIN = 0;
					N3_E_PIN = 0;
					N3_F_PIN = 0;
					N3_G_PIN = 0;

				} else if (item_index == 3) {

					led_n1_number(OFF,0xFF);
					led_n2_number(OFF,0xFF);

					N3_A_PIN = 0;
					N3_B_PIN = 1;
					N3_C_PIN = 0;
					N3_D_PIN = 0;
					N3_E_PIN = 0;
					N3_F_PIN = 0;
					N3_G_PIN = 0;

				} else if (item_index == 4) {

					led_n1_number(OFF,0xFF);
					led_n2_number(OFF,0xFF);

					N3_A_PIN = 0;
					N3_B_PIN = 0;
					N3_C_PIN = 1;
					N3_D_PIN = 0;
					N3_E_PIN = 0;
					N3_F_PIN = 0;
					N3_G_PIN = 0;

				} else if (item_index == 5) {

					led_n1_number(OFF,0xFF);
					led_n2_number(OFF,0xFF);

					N3_A_PIN = 0;
					N3_B_PIN = 0;
					N3_C_PIN = 0;
					N3_D_PIN = 1;
					N3_E_PIN = 0;
					N3_F_PIN = 0;
					N3_G_PIN = 0;

				} else if (item_index == 6) {

					led_n1_number(OFF,0xFF);

					N2_A_PIN = 0;
					N2_B_PIN = 0;
					N2_C_PIN = 0;
					N2_D_PIN = 1;
					N2_E_PIN = 0;
					N2_F_PIN = 0;
					N2_G_PIN = 0;

					led_n3_number(OFF,0xFF);

				} else if (item_index == 7) {

					N1_A_PIN = 0;
					N1_B_PIN = 0;
					N1_C_PIN = 0;
					N1_D_PIN = 1;
					N1_E_PIN = 0;
					N1_F_PIN = 0;
					N1_G_PIN = 0;

					led_n2_number(OFF,0xFF);
					led_n3_number(OFF,0xFF);

				} else if (item_index == 8) {

					N1_A_PIN = 0;
					N1_B_PIN = 0;
					N1_C_PIN = 0;
					N1_D_PIN = 0;
					N1_E_PIN = 1;
					N1_F_PIN = 0;
					N1_G_PIN = 0;

					led_n2_number(OFF,0xFF);
					led_n3_number(OFF,0xFF);

				} else if (item_index == 9) {

					N1_A_PIN = 0;
					N1_B_PIN = 0;
					N1_C_PIN = 0;
					N1_D_PIN = 0;
					N1_E_PIN = 0;
					N1_F_PIN = 1;
					N1_G_PIN = 0;

					led_n2_number(OFF,0xFF);
					led_n3_number(OFF,0xFF);

				} else {
					__NOP();
				}

				break;

			default:

			break;
		}
	}

	return 0;
}

void led_font_init(void)
{
	led_font_fun.rssi_show = rssi_show;
	led_font_fun.unit_show = unit_show;
	led_font_fun.led_7seg_number_show = led_7seg_number_show;
	led_font_fun.led_7seg_text_show = led_7seg_text_show;
	led_font_fun.led_7seg_pic_show = led_7seg_pic_show;
	led_font_fun.led_n1_text = led_n1_text;
	led_font_fun.led_n2_text = led_n2_text;
	led_font_fun.led_n3_text = led_n3_text;
}
