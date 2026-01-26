#include <stdio.h>
#include "NuMicro.h"
#include "24LC02.h"
#include "main.h"

/* 24LC02 adress 僅1byte */
typedef void (*I2C_FUNC)(uint32_t u32Status);
static I2C_FUNC I2C0HandlerFn = NULL;
volatile enum DATA_TYPE ee2402_data_type = UINT8;
volatile uint8_t eerom_buf[10] = {0};
volatile uint8_t eerom_DataLen = 0;
volatile uint8_t eerom_EndFlag = 0;
volatile uint8_t eerom_error = 0;

//------------------------------------------------------------------------------------------------------------------------//
//24LC02, I2C0 Interrupt
//------------------------------------------------------------------------------------------------------------------------//
void I2C0_IRQHandler(void)
{
	uint32_t u32Status = 0;

	/* clear interrupt flag */
//	I2C0->INTSTS |= I2C_INTSTS_INTSTS_Msk;
	
	u32Status = I2C_GET_STATUS(I2C0);

	if (I2C_GET_TIMEOUT_FLAG(I2C0)) {

		/* Clear I2C0 Timeout Flag */
		 I2C_ClearTimeoutFlag(I2C0);

	} else {
		if (I2C0HandlerFn != NULL)
			I2C0HandlerFn(u32Status);
	}

}


void I2C0_Reset(void)
{
	/* I2C_GET_STATUS = 0x00 I2C通訊異常發生 */
	if (I2C_GET_STATUS(I2C0) == 0x00) {

//		SYS->IPRST_CTL2 |= SYS_IPRST_CTL2_I2C0_RST_Msk;
//		__NOP();
//		__NOP();
//		SYS->IPRST_CTL2 &= ~SYS_IPRST_CTL2_I2C0_RST_Msk;
//		__NOP();
//		__NOP();

		/* Reset I2C後重新設定 */
		I2C_Open(I2C0, 100000);
		I2C_SetSlaveAddr(I2C0,0,0x15,I2C_GCMODE_DISABLE);
		I2C_SetSlaveAddr(I2C0,1,0x35,I2C_GCMODE_DISABLE);
		I2C_EnableInt(I2C0);
		NVIC_EnableIRQ(I2C0_IRQn);
	}

}


//------------------------------------------------------------------------------------------------------------------------//
//(24LC02)EEPROM read Status
//------------------------------------------------------------------------------------------------------------------------//
void eerom2402_r(uint32_t u32Status)
{
	switch (u32Status) {

	/* START has been transmitted and prepare SLA+W */
	case(0x08):
		I2C_SET_DATA(I2C0,0xa0);
		I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
	break;


	/* SLA+W has been transmitted and ACK has been received */
	case(0x18):
		I2C_SET_DATA(I2C0, eerom_buf[eerom_DataLen]);
		eerom_DataLen++;
		I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
	break;


	/* SLA+W has been transmitted and NACK has been received */
	case(0x20):
		I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA | I2C_CTL_STO | I2C_CTL_SI);
	break;


	/* DATA has been transmitted and ACK has been received */
	case(0x28):
		I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA | I2C_CTL_SI);
	break;


	/* Repeat START has been transmitted and prepare SLA+R */
	case(0x10):
		I2C_SET_DATA(I2C0,0xa1);
		I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
	break;


	/* SLA+R has been transmitted and ACK has been received */
	case(0x40):
		I2C_SET_CONTROL_REG(I2C0,I2C_CTL_AA| I2C_CTL_SI);
	break;


	/* I2C Status Information: Master Data Address Receive ACK */
	case(0x50):

		eerom_buf[eerom_DataLen] = I2C_GET_DATA(I2C0);
		eerom_DataLen++;

		if (ee2402_data_type == UINT8) {

			I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);

		} else if (ee2402_data_type == UINT16) {

			if (eerom_DataLen <= 2) {
				I2C_SET_CONTROL_REG(I2C0, I2C_CTL_AA | I2C_CTL_SI);
			} else {
				I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
			}

		} else if (ee2402_data_type == UINT32 || ee2402_data_type == FLOAT) {

			if (eerom_DataLen <= 4) {
				I2C_SET_CONTROL_REG(I2C0, I2C_CTL_AA | I2C_CTL_SI);
			} else {
				I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
			}
		}

	break;


	/* DATA has been received and NACK has been returned */
	case(0x58):
		I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STO | I2C_CTL_SI);
		eerom_EndFlag = 1;
	break;
	}
}



//------------------------------------------------------------------------------------------------------------------------//
//(24LC02)EEPROM read (int8)
//------------------------------------------------------------------------------------------------------------------------//
uint8_t eep2402_r_uint8(uint8_t addr)
{
	uint16_t r_int8_wait_cn = 0;
	uint8_t data = 0;
	uint8_t r_int8_wait = 1;

	ee2402_data_type = UINT8;

	I2C0_Reset();

	eerom_EndFlag = 0;
	eerom_DataLen = 0;
	eerom_error = 0;

	eerom_buf[0] = addr;

	I2C0HandlerFn = (I2C_FUNC)eerom2402_r;
	I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA);

	r_int8_wait_cn = 0;

	while(r_int8_wait) {

		if(eerom_EndFlag == 1)
			r_int8_wait = 0;

		if (r_int8_wait_cn >= 1000) {
			eerom_error = 1;
			r_int8_wait = 0;
		}

		CLK_SysTickDelay(500);
		r_int8_wait_cn++;
	}

	data = eerom_buf[1];

	/* I2C連續讀取時byte與byte需delay */
	CLK_SysTickDelay(100);


	return data;
}


//------------------------------------------------------------------------------------------------------------------------//
//(24LC02)EEPROM read (int16)
//------------------------------------------------------------------------------------------------------------------------//
int16_t eep2402_r_int16(uint8_t addr)
{
	uint16_t r_int16_wait_cn = 0;
	uint16_t data16 = 0;
	uint8_t r_int16_wait = 1;

	ee2402_data_type = UINT16;

	I2C0_Reset();

	eerom_EndFlag = 0;
	eerom_DataLen = 0;
	eerom_error = 0;

	eerom_buf[0] = addr * 2;

	I2C0HandlerFn = (I2C_FUNC)eerom2402_r;
	I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA);

	r_int16_wait_cn = 0;

	while(r_int16_wait) {

		if(eerom_EndFlag == 1)
			r_int16_wait = 0;

		if (r_int16_wait_cn >= 1000) {
			eerom_error = 1;
			r_int16_wait = 0;
		}

		CLK_SysTickDelay(500);
		r_int16_wait_cn++;
	}

	data16 = eerom_buf[2] << 8;
	data16 |= eerom_buf[1];

	/* I2C連續讀取時byte與byte需delay */
	CLK_SysTickDelay(100);

	return data16;
}


//------------------------------------------------------------------------------------------------------------------------//
//(24LC02)EEPROM read (int32)
//------------------------------------------------------------------------------------------------------------------------//
int32_t eep2402_r_int32(uint8_t addr)
{
	uint16_t r_int32_wait_cn = 0;
	uint32_t data32 = 0;
	uint8_t r_int32_wait = 1;

	ee2402_data_type = UINT32;

	I2C0_Reset();

	eerom_EndFlag = 0;
	eerom_DataLen = 0;
	eerom_error = 0;

	eerom_buf[0] = addr * 4;

	I2C0HandlerFn = (I2C_FUNC)eerom2402_r;
	I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA);

	r_int32_wait_cn = 0;
	while(r_int32_wait) {

		if(eerom_EndFlag == 1)
			r_int32_wait = 0;

		if (r_int32_wait_cn >= 1000) {
			eerom_error = 1;
			r_int32_wait = 0;
		}

		CLK_SysTickDelay(500);
		r_int32_wait_cn++;
	}

	data32 = eerom_buf[4]  << 24;
	data32 |= eerom_buf[3] << 16;
	data32 |= eerom_buf[2] << 8;
	data32 |= eerom_buf[1];

	/* I2C連續讀取時byte與byte需delay */
	CLK_SysTickDelay(100);

	return data32;
}


//------------------------------------------------------------------------------------------------------------------------//
//(24LC02)EEPROM read (float)
//------------------------------------------------------------------------------------------------------------------------//
float eep2402_r_float(uint8_t addr)
{
	uint16_t r_float_wait_cn = 0;
	uint32_t data32 = 0;
	float *dfptr = NULL;
	uint8_t r_float_wait = 1;

	ee2402_data_type = FLOAT;
	I2C0_Reset();

	eerom_EndFlag = 0;
	eerom_DataLen = 0;
	eerom_error = 0;

	eerom_buf[0] = addr * 4;

	I2C0HandlerFn = (I2C_FUNC)eerom2402_r;
	I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA);

	r_float_wait_cn = 0;
	while(r_float_wait) {

		if(eerom_EndFlag == 1)
			r_float_wait = 0;

		if (r_float_wait_cn >= 1000) {
			eerom_error = 1;
			r_float_wait = 0;
		}

		CLK_SysTickDelay(500);
		r_float_wait_cn++;
	}

	data32 = (uint32_t)eerom_buf[4]  << 24;
	data32 |= (uint32_t)eerom_buf[3] << 16;
	data32 |= (uint32_t)eerom_buf[2] << 8;
	data32 |= (uint32_t)eerom_buf[1];

	dfptr = (float *)&data32;

	/* I2C連續讀取時byte與byte需delay */
	CLK_SysTickDelay(100);


	return *dfptr;
}



//------------------------------------------------------------------------------------------------------------------------//
//(24LC02)EEPROM wirt Status
//------------------------------------------------------------------------------------------------------------------------//
void eerom2402_w(uint32_t u32Status)
{
	switch(u32Status) {

	/* START has been transmitted */
	case(0x08):

		/* Write SLA+W to Register I2CDAT */
		I2C_SET_DATA(I2C0,0xa0);
		I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
	break;

	/* SLA+W has been transmitted and ACK has been received */
	case(0x18):

		I2C_SET_DATA(I2C0, eerom_buf[eerom_DataLen]);
		eerom_DataLen++;
		I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
	break;

	 /* SLA+W has been transmitted and NACK has been received */
	case(0x20):

		I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA | I2C_CTL_STO | I2C_CTL_SI);
	break;

	 /* DATA has been transmitted and ACK has been received */
	case(0x28):

		if (ee2402_data_type == UINT8 ) {

			if (eerom_DataLen <= 1) {
				I2C_SET_DATA(I2C0, eerom_buf[eerom_DataLen]);
				I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
				eerom_DataLen++;
			} else {
				I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STO | I2C_CTL_SI);
				eerom_EndFlag = 1;
			}

		} else if (ee2402_data_type == UINT16 ) {

			if (eerom_DataLen <= 2) {
				I2C_SET_DATA(I2C0, eerom_buf[eerom_DataLen]);
				I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
				eerom_DataLen++;
			} else {
				I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STO | I2C_CTL_SI);
				eerom_EndFlag = 1;
			}

		} else if (ee2402_data_type == UINT32 || ee2402_data_type == FLOAT) {

			if (eerom_DataLen <= 4) {
				I2C_SET_DATA(I2C0, eerom_buf[eerom_DataLen]);
				I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
				eerom_DataLen++;
			} else {
				I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STO | I2C_CTL_SI);
				eerom_EndFlag = 1;
			}

		}

	break;
	}
}


//------------------------------------------------------------------------------------------------------------------------//
//(24LC02)EEPROM write byte (int8)
//------------------------------------------------------------------------------------------------------------------------//
void eerom2402_w_uint8(uint8_t addr,uint8_t data)
{
	uint16_t w_int8_wait_cn = 0;
	uint8_t w_int8_wait = 1;

	I2C0_Reset();

	ee2402_data_type = UINT8;

	eerom_EndFlag = 0;
	eerom_DataLen = 0;
	eerom_error = 0;

	eerom_buf[0] = addr;
	eerom_buf[1] = data;

	I2C0HandlerFn = (I2C_FUNC)eerom2402_w;
	I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA);

	while (w_int8_wait) {

		if (eerom_EndFlag == 1)
			w_int8_wait = 0;

		if (w_int8_wait_cn >= 1000) {
			eerom_error = 1;
			w_int8_wait = 0;
		}

		CLK_SysTickDelay(500);
		w_int8_wait_cn++;
	}

	/* I2C連續寫入時byte與byte需delay */
	//CLK_SysTickDelay(10000);


}


//------------------------------------------------------------------------------------------------------------------------//
//(24LC02)EEPROM write byte (int16)
//------------------------------------------------------------------------------------------------------------------------//
void eerom2402_w_int16(uint8_t addr,int16_t data)
{
	uint16_t w_int16_wait_cn = 0;
	uint8_t w_int16_wait = 1;
	uint16_t data16_reg = 0;

	I2C0_Reset();

	ee2402_data_type = UINT16;

	eerom_EndFlag = 0;
	eerom_DataLen = 0;
	eerom_error = 0;

	eerom_buf[0] = addr * 2;

	data16_reg = data & 0x00ff;
	eerom_buf[1]= data16_reg;
	data16_reg =  data >> 8;
	eerom_buf[2]= data16_reg;

	I2C0HandlerFn = (I2C_FUNC)eerom2402_w;
	I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA);

	while (w_int16_wait) {

		if (eerom_EndFlag == 1)
			w_int16_wait = 0;

		if (w_int16_wait_cn >= 1000) {

			eerom_error = 1;
			w_int16_wait = 0;
		}

		//CLK_SysTickDelay(500);
		w_int16_wait_cn++;
	}

	/* I2C連續寫入時byte與byte需delay */
	//CLK_SysTickDelay(10000);


}


//------------------------------------------------------------------------------------------------------------------------//
//(24LC02)EEPROM write byte (int32)
//------------------------------------------------------------------------------------------------------------------------//
void eerom2402_w_int32(uint8_t addr,int32_t data)
{
	uint16_t w_int32_wait_cn = 0;
	uint8_t w_int32_wait = 1;
	uint16_t data32_reg = 0;

	I2C0_Reset();

	ee2402_data_type = UINT32;

	eerom_EndFlag = 0;
	eerom_DataLen = 0;
	eerom_error = 0;

	eerom_buf[0] = addr * 4;

	data32_reg = data & 0x00ff;
	eerom_buf[1]= data32_reg;
	data32_reg =  data >> 8;
	eerom_buf[2]= data32_reg;
	data32_reg =  data >> 16;
	eerom_buf[3]= data32_reg;
	data32_reg =  data >> 24;
	eerom_buf[4]= data32_reg;

	I2C0HandlerFn = (I2C_FUNC)eerom2402_w;
	I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA);

	while (w_int32_wait) {

		if (eerom_EndFlag == 1)
			w_int32_wait = 0;

		if (w_int32_wait_cn >= 1000) {

			eerom_error = 1;
			w_int32_wait = 0;
		}

		//CLK_SysTickDelay(500);
		w_int32_wait_cn++;
	}

	/* I2C連續寫入時byte與byte需delay */
	//CLK_SysTickDelay(10000);


}


//------------------------------------------------------------------------------------------------------------------------//
//(24LC02)EEPROM write byte (float)
//------------------------------------------------------------------------------------------------------------------------//
void eerom2402_w_float(uint8_t addr,float data)
{
	uint16_t w_float_wait_cn = 0;
	uint8_t w_float_wait = 1;
	uint8_t *ptr = NULL;

	I2C0_Reset();

	ee2402_data_type = UINT32;

	eerom_EndFlag = 0;
	eerom_DataLen = 0;
	eerom_error = 0;

	eerom_buf[0] = addr * 4;

	ptr = (uint8_t *)&data;
	eerom_buf[1] = *ptr;
	eerom_buf[2] = *(ptr + 1);
	eerom_buf[3] = *(ptr + 2);
	eerom_buf[4] = *(ptr + 3);


	I2C0HandlerFn = (I2C_FUNC)eerom2402_w;
	I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA);

	while (w_float_wait) {

		if (eerom_EndFlag == 1)
			w_float_wait = 0;


		if (w_float_wait_cn >= 1000) {
			eerom_error = 1;
			w_float_wait = 0;
		}

		//CLK_SysTickDelay(500);
		w_float_wait_cn++;
	}

	/* I2C連續寫入時byte與byte需delay */
	//CLK_SysTickDelay(10000);

}

