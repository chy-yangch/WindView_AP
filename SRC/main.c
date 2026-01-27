/**************************************************************************//**
 * @file     main.c
 * @version  V0.10
 * @brief    A project template for M251 MCU.
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
 ****************************************************************************/

#include <stdio.h>
#include "NuMicro.h"
#include "main.h"
#include "24LC02.h"
#include "ui.h"
#include "key_scan.h"
#include "cc1200.h"

void io_config(void);
void io_init(void);
void LXT_Enable(void);
void function_init(void);
void mcu_idle(void);

__IO uint8_t cc1200_get_flag = 0;
struct RX_INFO info;

void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable Internal RC 12MHz clock */
    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);

    /* Waiting for Internal RC clock ready */
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

    /* Switch HCLK clock source to Internal RC and HCLK source divide 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV0_HCLK(6));

    LXT_Enable();

	/* Enable UART clock */
	CLK_EnableModuleClock(UART0_MODULE);
	/* Enable RTC peripheral clock */
	CLK_EnableModuleClock(RTC_MODULE);
	/* Enable module clock */
	CLK_EnableModuleClock(UART0_MODULE);
	/* Enable I2C0 clock */
	CLK_EnableModuleClock(I2C0_MODULE);
	/* Enable TIMER 0 module clock */
	CLK_EnableModuleClock(TMR0_MODULE);
	/* Enable TIMER 1 module clock */
	CLK_EnableModuleClock(TMR1_MODULE);
	/* Enable TIMER 2 module clock */
	CLK_EnableModuleClock(TMR2_MODULE);
	/* Enable TIMER 3 module clock */
	CLK_EnableModuleClock(TMR3_MODULE);
	/* Enable SPI0 clock */
	CLK_EnableModuleClock(SPI0_MODULE);


	CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_LXT, 0);
	CLK_SetModuleClock(TMR1_MODULE, CLK_CLKSEL1_TMR1SEL_LXT, 0);
	CLK_SetModuleClock(TMR2_MODULE, CLK_CLKSEL1_TMR2SEL_LXT, 0);
	CLK_SetModuleClock(TMR3_MODULE, CLK_CLKSEL1_TMR3SEL_LXT, 0);
	CLK_SetModuleClock(WDT_MODULE, CLK_CLKSEL1_WDTSEL_LIRC, 0);

    /* Select UART clock source from HIRC */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    //Uart0DefaultMPF();

	io_init();
	io_config();

    /* Lock protected registers */
    SYS_LockReg();

    	/* Open I2C0 and set clock to 100k */
	I2C_Open(I2C0, 100000);
	I2C_SetSlaveAddr(I2C0,0,0x15,I2C_GCMODE_DISABLE);
	I2C_SetSlaveAddr(I2C0,1,0x35,I2C_GCMODE_DISABLE);
	I2C_EnableInt(I2C0);
	NVIC_EnableIRQ(I2C0_IRQn);

	/* Init SPI */
	/* Select PCLK0 as the clock source of SPI0 */
	CLK_SetModuleClock(SPI0_MODULE, CLK_CLKSEL2_SPI0SEL_PCLK1, MODULE_NoMsk);
	/* Enable SPI0 peripheral clock */
	CLK_EnableModuleClock(SPI0_MODULE);
	/* Configure SPI_FLASH_PORT as a master, MSB first, 8-bit transaction, SPI Mode-0 timing, clock is 20MHz */
	SPI_Open(SPI0, SPI_MASTER, SPI_MODE_0, 8, 2000000);
	/* Disable auto SS function, control SS signal manually. */
	SPI_DisableAutoSS(SPI0);


	TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 10);
	//TIMER_Open(TIMER1, TIMER_PERIODIC_MODE, 1);
	//TIMER_Open(TIMER2, TIMER_PERIODIC_MODE, 1);
	//TIMER_Open(TIMER3, TIMER_PERIODIC_MODE, 10);

	/* Enable timer wake up system */
	TIMER_EnableWakeup(TIMER0);
	//TIMER_EnableWakeup(TIMER1);
	//TIMER_EnableWakeup(TIMER3);

	/* Enable Timer0 interrupt */
	TIMER_EnableInt(TIMER0);
	//TIMER_EnableInt(TIMER1);
	//TIMER_EnableInt(TIMER2);
	//TIMER_EnableInt(TIMER3);

	/* Enable Timer0 ~ Timer3 NVIC */
	NVIC_EnableIRQ(TMR0_IRQn);
	//NVIC_EnableIRQ(TMR1_IRQn);
	//NVIC_EnableIRQ(TMR2_IRQn);
	//NVIC_EnableIRQ(TMR3_IRQn);

	/* Start Timer0 ~ Timer3 counting */
	TIMER_Start(TIMER0);
	//TIMER_Start(TIMER1);
	//TIMER_Start(TIMER2);
	//TIMER_Start(TIMER3);

	/* Configure PA.5 as Input mode and enable interrupt by rising edge trigger */
	GPIO_SetMode(PA, BIT5, GPIO_MODE_INPUT);
	GPIO_EnableInt(PA, 5, GPIO_INT_RISING);
	NVIC_EnableIRQ(GPA_IRQn);

}


/*
 * This is a template project for M251 series MCU. Users could based on this project to create their
 * own application without worry about the IAR/Keil project settings.
 *
 * This template application uses external crystal as HCLK source and configures UART0 to print out
 * "Hello World", users may need to do extra system configuration based on their system design.
 */
int main()
{
	SYS_Init();
	function_init();
	page_logo();

	while (1){

		runRX(SPI0);
		key_case_array[info.current_page]();
		ui_fun_array[info.current_page]();
		mcu_idle();
	}
}

void io_config(void)
{

    //SYS->GPA_MFPH = 0x00000000;
    //SYS->GPA_MFPL = 0x00004444;
    //SYS->GPB_MFPH = 0x00000000;
    //SYS->GPB_MFPL = 0x00000000;
    //SYS->GPC_MFPH = 0x00000000;
    //SYS->GPC_MFPL = 0x00000099;
    //SYS->GPD_MFPH = 0x00000000;
    //SYS->GPD_MFPL = 0x00000000;
    //SYS->GPF_MFPL = 0x00AA33EE;

    //If the defines do not exist in your project, please refer to the corresponding sys.h in the Header folder appended to the tool package.
    SYS->GPA_MFPH = 0x00000000;
    SYS->GPA_MFPL = SYS_GPA_MFPL_PA3MFP_SPI0_SS | SYS_GPA_MFPL_PA2MFP_SPI0_CLK | SYS_GPA_MFPL_PA1MFP_SPI0_MISO | SYS_GPA_MFPL_PA0MFP_SPI0_MOSI;
    SYS->GPB_MFPH = 0x00000000;
    SYS->GPB_MFPL = 0x00000000;
    SYS->GPC_MFPH = 0x00000000;
    SYS->GPC_MFPL = SYS_GPC_MFPL_PC1MFP_I2C0_SCL | SYS_GPC_MFPL_PC0MFP_I2C0_SDA;
    SYS->GPD_MFPH = 0x00000000;
    SYS->GPD_MFPL = 0x00000000;
    SYS->GPF_MFPL = SYS_GPF_MFPL_PF5MFP_X32_IN | SYS_GPF_MFPL_PF4MFP_X32_OUT | SYS_GPF_MFPL_PF3MFP_UART0_TXD | SYS_GPF_MFPL_PF2MFP_UART0_RXD | SYS_GPF_MFPL_PF1MFP_ICE_CLK | SYS_GPF_MFPL_PF0MFP_ICE_DAT;

}

void io_init(void)
{
	// PA15	N2_B_PIN		IO/O
	// PA14	N2_F_PIN		IO/O
	// PA13 	N2_A_PIN		IO/O
	// PA12	N3_A_PIN		IO/O
	// PA11 	LED_H_SW		IO/O
	// PA10	LED_M_SW		IO/O
	// PA9 	LED_L_SW		IO/O
	// PA8 	N1_D_PIN		IO/O
	// PA7 	N1_A_PIN		IO/O
	// PA6 	N1_G_PIN		IO/O
	// PA5 	W1_GPIO2_INT	IO/I (INT)
	// PA4 	GPIO0_W1		IO/I
	// PA3 	SPI0_SS			FUN/O
	// PA2 	SPI0_CLK		FUN/O
	// PA1 	SPI0_MISO		FUN/I
	// PA0 	SPI0_MOSI		FUN/O

	PA->MODE 		=	0x55555051;
	PA->DINOFF 		=	0x00000000;
	PA->DOUT 		=	0x00000000;
	PA->DATMSK 	=	0x00000000;		//Data Output Write Mask
	PA->SLEWCTL 	=	0x00000000; 		//High Slew Rate Control Register
	PA->PUSEL 		=	0x00000000;

	// PB15 	N3_B_PIN		IO/O
	// PB14 	N3_G_PIN		IO/O
	// PB13 	N2_G_PIN		IO/O
	// PB12 	N2_C_PIN		IO/O
	// PB11 	N2_E_PIN		IO/O
	// PB10 	N3_E_PIN		IO/O
	// PB9 	N3_C_PIN		IO/O
	// PB8 	DOT_PIN			IO/O
	// PB7 	N2_D_PIN		IO/O
	// PB6 	N3_D_PIN		IO/O
	// PB5 	PWM0_BEEPER_SW	IO/O
	// PB4 	MP_PIN			IO/O
	// PB3 	KM_PIN			IO/O
	// PB2 	MS_PIN			IO/O
	// PB1 	N1_B_PIN		IO/O
	// PB0	N1_C_PIN		IO/O

	PB->MODE 		=	0x55555555;
	PB->DINOFF 		=	0x00000000;
	PB->DOUT 		=	0x00000000;
	PB->DATMSK 	=	0x00000000;		//Data Output Write Mask
	PB->SLEWCTL 	=	0x00000000;		//High Slew Rate Control Register
	PB->PUSEL 		=	0x00000000;

	// PC15	X				IO/I - only Input
	// PC14 	N3_F_PIN		IO/O
	// PC13 	X				IO/I - only Input
	// PC12 	X				IO/O
	// PC11 	X				IO/O
	// PC10 	X				IO/O
	// PC9 	X				IO/O
	// PC8 	X				IO/O
	// PC7 	N1_E_PIN		IO/O
	// PC6 	N1_F_PIN		IO/O
	// PC5 	CANCEL_KEY	IO/I
	// PC4 	UP_KEY			IO/I
	// PC3 	DOWN_KEY		IO/I
	// PC2 	POW_KEY		IO/I
	// PC1 	SCL_0			FUN/O
	// PC0	SDA_0			FUN/IO

	PC->MODE 		=	0x11555004;
	PC->DINOFF 		=	0x00000000;
	PC->DOUT 		=	0x00005FFF;
	PC->DATMSK 	=	0x00000000;		//Data Output Write Mask
	PC->SLEWCTL 	=	0x00000000;		//High Slew Rate Control Register
	PC->PUSEL 		=	0x00000040;

	// PD15 	W1_RESET		IO/O
	// PD14 	X				IO/O - only Input
	// PD13 	X				IO/O
	// PD12 	X				IO/O
	// PD11 	X				IO/O
	// PD10 	X				IO/O
	// PD9 	X				IO/O
	// PD8 	X				IO/O
	// PD7 	X				IO/O
	// PD6 	X				IO/O
	// PD5 	X				IO/O
	// PD4 	X				IO/O
	// PD3 	RSSI_4_PIN		IO/O
	// PD2 	RSSI_3_PIN		IO/O
	// PD1 	RSSI_2_PIN		IO/O
	// PD0	RSSI_1_PIN		IO/O

	PD->MODE 		=	0x45555555;
	PD->DINOFF 		=	0x00000000;
	PD->DOUT 		=	0x00000000;
	PD->DATMSK 	=	0x00000000;		//Data Output Write Mask
	PD->SLEWCTL 	=	0x00000000;		//High Slew Rate Control Register
	PD->PUSEL 		=	0x00000001;

	// PE15	X				IO/O
	// PE14 	X				IO/O
	// PE13 	X				IO/O
	// PE12 	X				IO/O
	// PE11 	X				IO/O
	// PE10 	X				IO/O
	// PE9 	X				IO/O
	// PE8 	X				IO/O
	// PE7 	X				IO/O
	// PE6 	X				IO/O
	// PE5 	X				IO/O
	// PE4 	X				IO/O
	// PE3 	X				IO/O
	// PE2 	X				IO/O
	// PE1 	X				IO/O
	// PE0	X				IO/O

	PE->MODE 		=	0x55555555;
	PE->DINOFF 		=	0x00000000;
	PE->DOUT 		=	0x00000000;
	PE->DATMSK 	=	0x00000000;		//Data Output Write Mask
	PE->SLEWCTL 	=	0x00000000;   		//High Slew Rate Control Register
	PE->PUSEL 		=	0x00000000;

	// PF15 	X				IO/O
	// PF14 	X				IO/O
	// PF13 	X				IO/O
	// PF12 	X				IO/O
	// PF11 	X				IO/O
	// PF10 	X				IO/O
	// PF9 	X				IO/O
	// PF8 	X				IO/O
	// PF7 	X				IO/O
	// PF6 	CONFIRM_KEY	IO/I
	// PF5 	X_IN			FUN-X32_IN
	// PF4 	X_OUT			FUN-X32_OUT
	// PF3 	UART0_TXD		FUN/O
	// PF2 	UART0_RXD		FUN/I
	// PF1 	CLK				CLK
	// PF0	DAT				DAT

	PF->DOUT 		=	0x00004044;
	PF->MODE 		=	0x00004041;
	PF->DINOFF 		=	0x00000000;
	PF->DATMSK 		=	0x00000000;		//Data Output Write Mask
	PF->SLEWCTL 	=	0x00000000;		//High Slew Rate Control Register
	PF->PUSEL 		=	0x00000000;

}

void LXT_Enable(void)
{
    /* Set X32_OUT(PF.4) and X32_IN(PF.5) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE4_Msk | GPIO_MODE_MODE5_Msk);

    /* Enable external 32768Hz XTAL */
    CLK_EnableXtalRC(CLK_PWRCTL_LXTEN_Msk);

    /* Waiting for clock ready */
    CLK_WaitClockReady(CLK_STATUS_LXTSTB_Msk);

    /* Disable digital input path of analog pin X32_OUT to prevent leakage */
    GPIO_DISABLE_DIGITAL_PATH(PF, (1ul << 4));

    /* Disable digital input path of analog pin XT32_IN to prevent leakage */
    GPIO_DISABLE_DIGITAL_PATH(PF, (1ul << 5));
}

void TMR0_IRQHandler(void)
{
	/* 每秒10次 */

	/* Clean Timer0 Interrupt Flag */
	TIMER_ClearIntFlag(TIMER0);
	/* Clean TIMER0 Wake up Flag */
	TIMER_ClearWakeupFlag(TIMER0);

	Key_Scan();

}

void TMR1_IRQHandler(void)
{
	/* 每秒10次 */

	/* Clean Timer1 Interrupt Flag */
	TIMER_ClearIntFlag(TIMER1);
	/* Clean TIMER0 Wake up Flag */
	TIMER_ClearWakeupFlag(TIMER1);

}

void function_init(void)
{
	ui_init();
	key_case_init();
	led_font_init();
}

void windview_eeprom_read(void)
{
	uint8_t i = 0;
	int32_t reg_int32 = 0;

	CLK_SysTickDelay(5000);

	info.windv_type			=	eep2402_r_uint8(EEP_WINDV_TYPE);
	info.windv_ad				=	eep2402_r_uint8(EEP_WINDV_AD);
	info.windv_unit			=	eep2402_r_uint8(EEP_WINDV_UNIT);
	info.windv_thr				=	eep2402_r_uint8(EEP_WINDV_THR);
	info.windv_sound_sw 		=	eep2402_r_uint8(EEP_WINDV_SOUND_SW);
	info.windv_sound_reset_time 	=	eep2402_r_uint8(EEP_WINDV_SOUND_RESET_TIME);
	info.windv_light_level 		=	eep2402_r_uint8(EEP_WINDV_LIGHT_LEVEL);
	info.windv_mode			=	eep2402_r_uint8(EEP_WINDV_MODE);

	CLK_SysTickDelay(5000);
}

void GPA_IRQHandler(void)
{
    /* To check if PA.5 interrupt occurred */
    if (GPIO_GET_INT_FLAG(PA, BIT5))
    {
        GPIO_CLR_INT_FLAG(PA, BIT5);

	packetSemaphore = ISR_ACTION_REQUIRED;

	/* 提早10ms,其中5ms對CC1200設定
	 * 移到中斷處計算,才不會因為CC1200 Timeout
	 * 因執行主程式造成時間計算上的誤差
	 */

	 TIMER2->CMP = 327680;

	// TIMER1->CMP = 65012; //free run 提早16ms - timeout :720
	//TIMER1->CMP = 64848; //debug 提早16ms    - timeout :1000
	TIMER1->CMP = 64881; //327 - ok free run 模式需使用此參數,提早ms
	TIMER3->CMP = 64881 + 654; //比TIMER1 + 20ms
	//TIMER3->CMP = 64881 + 490; //比TIMER1 + 15ms
	 //TIMER3->CMP = 64881 + 392; //比TIMER1 + 12ms
	//TIMER1->CMP = 64440;   //327 - 因debug模式下會比較慢故需用此參數

    }
    else
    {
        /* Un-expected interrupt. Just clear all PC interrupts */
        PA->INTSRC = PA->INTSRC;
    }
}

void mcu_idle(void)
{
	info.exit_sleep_flag = 0;

	while(!info.exit_sleep_flag) {	
		CLK_Idle();
	}
}