/*
 * SMAN5 7Segment LCD
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "led_font.h"
#include "main.h"

//===================================================
//	NO 1
//===================================================
void led_n1_number(uint8_t no)
{
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


	}
}

void led_n1_text(uint8_t text)
{
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

	}
}

//===================================================
//	NO 2
//===================================================
void led_n2_number(uint8_t no)
{
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


	}
}

void led_n2_text(uint8_t text)
{
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

	}
}
//===================================================
//	NO 3
//===================================================
void led_n3_number(uint8_t no)
{
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


	}
}

void led_n3_text(uint8_t text)
{
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

	}
}

//===================================================