//
/******************************************************************************/
/* Filename:EEPROM_24LC02.h                                                   */
/* 24LC02 Register Definitions                                                */
/******************************************************************************/
#include "NuMicro.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum DATA_TYPE {
	UINT8 = 0,
	UINT16,
	UINT32,
	FLOAT,
};

extern volatile uint8_t eerom_buf[10];

/* LC2402 Read function */
extern uint8_t eep2402_r_unt8(uint8_t addr);
extern int16_t eep2402_r_int16(uint8_t addr);
extern int32_t eep2402_r_int32(uint8_t addr);
extern float eep2402_r_float(uint8_t addr);

/* LC2402 Write function */
extern void eerom2402_w_unt8(uint8_t addr,uint8_t data);
extern void eerom2402_w_int16(uint8_t addr,int16_t data);
extern void eerom2402_w_int32(uint8_t addr,int32_t data);
extern void eerom2402_w_float(uint8_t addr,float data);

enum windv_eeprom_addr {

	EEP_WINDV_TYPE ,
	EEP_WINDV_AD ,
	EEP_WINDV_UNIT,
	EEP_WINDV_THR,
	EEP_WINDV_SOUND_SW,
	EEP_WINDV_SOUND_RESET_TIME,
	EEP_WINDV_LIGHT_LEVEL,
	EEP_WINDV_MODE,
	EEP_WINDV_FLA_SW,

};