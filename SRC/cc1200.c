#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "cc120x_reg_config.h"
#include "cc120x_spi.h"
#include "cc1200.h"
#include "main.h"

//#define CE
//#define FCC
//#define RCM

#ifdef CE
	#define Main_Frequency 86500000
#endif

#ifdef FCC
	#define Main_Frequency 90200000
#endif

#ifdef RCM
	#define Main_Frequency 91500000
#endif

#ifdef TELEC
	#define Main_Frequency 92070000
#endif

//#define MF_920_7
////#define MF_920_6

//#define Main_Frequency 92070000

////#define ISR_ACTION_REQUIRED     1
//#define PKTLEN                  64//64
//#define ISR_IDLE                0
//#define WL_LEN_BYTE		16
//#define RESET_N_PIN            PE2

volatile uint8_t packetSemaphore;
volatile uint8_t rssi_value;
volatile uint8_t cc1200_work_ch = 0;// = 0x0E; // = 14;// = 0;//
volatile uint32_t freq_offset = Main_Frequency;
__IO uint8_t cc1200_wait_rx_flag = 0;

volatile double fxosc_40M_real;

__IO uint8_t rxBuffer[PKTLEN+4] = {0}; // size+4 for length byte, address field(first 2 bytes); RSSI, CRC+LQI(last 2 bytes)
__IO uint8_t txBuffer[PKTLEN+1] = {0}; // size+1 for length byte

__IO uint8_t cc1200_power_on = OFF;
__IO uint8_t cc1200_re_setting = OFF;
void cc1200_power_off(void);

void runRX_ota(SPI_T * spi_ota);
void runRX_none(SPI_T * spi_none);

void cc1200_power_down(void);

typedef struct
{
  uint16_t  addr;
  uint8_t   data;
}registerSetting_t;

//***************************************************************************************
// Packet length mode = Variable
// Device address = 0
// Bit rate = 100
// Modulation format = 2-GFSK
// Whitening = false
// RX filter BW = 208.333333
// Address config = No address check
// Packet bit length = 0
// Symbol rate = 100
// Deviation = 49.896240
//
// Manchester enable = false
// Packet length = 255

//TX modulate
static const registerSetting_t preferredSettings[]=
{

#ifdef CE

  {CC120X_IOCFG3,            0x06},
  {CC120X_IOCFG2,            0x06},
  {CC120X_SYNC_CFG1,         0xA8},
  {CC120X_SYNC_CFG0,         0x13},
  {CC120X_DEVIATION_M,       0x68},
  {CC120X_MODCFG_DEV_E,      0x0B},
  {CC120X_DCFILT_CFG,        0x26},
  {CC120X_PREAMBLE_CFG0,     0x8A},
  {CC120X_IQIC,              0x80},
  {CC120X_CHAN_BW,           0x0F},

  {CC120X_MDMCFG1,           0x40},
  {CC120X_MDMCFG0,           0x05},
  {CC120X_SYMBOL_RATE2,      0x96},
  {CC120X_SYMBOL_RATE1,      0x87},
  {CC120X_SYMBOL_RATE0,      0x2B},
  {CC120X_AGC_REF,           0x27},
  {CC120X_AGC_CS_THR,        0x01},
  {CC120X_AGC_CFG1,          0x16},
  {CC120X_AGC_CFG0,          0x84},
  {CC120X_FIFO_CFG,          0x00},
  {CC120X_FS_CFG,            0x12},
  {CC120X_PKT_CFG2,          0x00},
  {CC120X_PKT_CFG0,          0x20},

//	//POWER 8
//  {CC120X_PA_CFG1,           0x71},
//  {CC120X_PA_CFG0,           0x50},

	//POWER 10
  {CC120X_PA_CFG1,           0x76},
  {CC120X_PA_CFG0,           0x50},

	//POWER 14
//  {CC120X_PA_CFG1,           0x7F},
//  {CC120X_PA_CFG0,           0x50},

  {CC120X_PKT_LEN,           0xFF},
  {CC120X_IF_MIX_CFG,        0x18},
  {CC120X_FREQOFF_CFG,       0x22},
  {CC120X_TOC_CFG,           0x03},
  {CC120X_MDMCFG2,           0x00},

//	Carrier frequency = 865	MHZ
  {CC120X_FREQ2,             0x56},
  {CC120X_FREQ1,             0x80},
  {CC120X_FREQ0,             0x00},

//// Carrier frequency = 866.5	MHZ
//	{CC120X_FREQ2,             0x56},
//  {CC120X_FREQ1,             0xA6},
//  {CC120X_FREQ0,             0x66},

//	Carrier frequency = 868	MHZ
//  {CC120X_FREQ2,             0x56},
//  {CC120X_FREQ1,             0xCC},
//  {CC120X_FREQ0,             0xCC},

////	Carrier frequency = 865.045	MHZ
//  {CC120X_FREQ2,             0x56},
//  {CC120X_FREQ1,             0x81},
//  {CC120X_FREQ0,             0x26},

  {CC120X_IF_ADC1,           0xEE},
  {CC120X_IF_ADC0,           0x10},
  {CC120X_FS_DIG1,           0x07},
  {CC120X_FS_DIG0,           0xA5},
  {CC120X_FS_CAL1,           0x40},
  {CC120X_FS_CAL0,           0x0E},
  {CC120X_FS_DIVTWO,         0x03},
  {CC120X_FS_DSM0,           0x33},
  {CC120X_FS_DVC0,           0x17},
  {CC120X_FS_PFD,            0x00},
  {CC120X_FS_PRE,            0x6E},
  {CC120X_FS_REG_DIV_CML,    0x1C},
  {CC120X_FS_SPARE,          0xAC},
  {CC120X_FS_VCO0,           0xB5},
  {CC120X_IFAMP,             0x0D},
  {CC120X_XOSC5,             0x0E},
  {CC120X_XOSC1,             0x03},
  {CC120X_PARTNUMBER,        0x20},
  {CC120X_PARTVERSION,       0x11},
  {CC120X_MODEM_STATUS1,     0x10},

#endif


#ifdef FCC

  {CC120X_IOCFG3,            0x06},
  {CC120X_IOCFG2,            0x06},
  {CC120X_SYNC_CFG1,         0xA8},
  {CC120X_SYNC_CFG0,         0x13},
  {CC120X_DEVIATION_M,       0x37},
  {CC120X_MODCFG_DEV_E,      0x0E},
  {CC120X_DCFILT_CFG,        0x26},
  {CC120X_PREAMBLE_CFG0,     0x8A},
  {CC120X_IQIC,              0x00},
  {CC120X_CHAN_BW,           0x41},

  {CC120X_MDMCFG1,           0x40},
  {CC120X_MDMCFG0,           0x05},
  {CC120X_SYMBOL_RATE2,      0x96},
  {CC120X_SYMBOL_RATE1,      0x87},
  {CC120X_SYMBOL_RATE0,      0x2B},
  {CC120X_AGC_REF,           0x42},
  {CC120X_AGC_CS_THR,        0x01},
  {CC120X_AGC_CFG1,          0x16},
  {CC120X_AGC_CFG0,          0x84},
  {CC120X_FIFO_CFG,          0x00},
  {CC120X_FS_CFG,            0x12},
  {CC120X_PKT_CFG2,          0x00},
  {CC120X_PKT_CFG0,          0x20},

//	//POWER 8
//  {CC120X_PA_CFG1,           0x71},
//  {CC120X_PA_CFG0,           0x50},

	//POWER 10
  {CC120X_PA_CFG1,           0x76},
  {CC120X_PA_CFG0,           0x50},

	//POWER 14
//  {CC120X_PA_CFG1,           0x7F},
//  {CC120X_PA_CFG0,           0x50},

  {CC120X_PKT_LEN,           0xFF},
  {CC120X_IF_MIX_CFG,        0x18},
  {CC120X_FREQOFF_CFG,       0x22},
  {CC120X_TOC_CFG,           0x03},
  {CC120X_MDMCFG2,           0x00},

// Carrier frequency = 902 MHZ
  {CC120X_FREQ2,             0x5A},
  {CC120X_FREQ1,             0x33},
  {CC120X_FREQ0,             0x33},


  {CC120X_IF_ADC1,           0xEE},
  {CC120X_IF_ADC0,           0x10},
  {CC120X_FS_DIG1,           0x07},
  //{CC120X_FS_DIG0,           0xA5},
  {CC120X_FS_DIG0,           0xAB},
  {CC120X_FS_CAL1,           0x40},
  {CC120X_FS_CAL0,           0x0E},
  {CC120X_FS_DIVTWO,         0x03},
  {CC120X_FS_DSM0,           0x33},
  {CC120X_FS_DVC0,           0x17},
  {CC120X_FS_PFD,            0x00},
  {CC120X_FS_PRE,            0x6E},
  {CC120X_FS_REG_DIV_CML,    0x1C},
  {CC120X_FS_SPARE,          0xAC},
  {CC120X_FS_VCO0,           0xB5},
  {CC120X_IFAMP,             0x0D},
  {CC120X_XOSC5,             0x0E},
  {CC120X_XOSC1,             0x03},
  {CC120X_PARTNUMBER,        0x20},
  {CC120X_PARTVERSION,       0x11},
  {CC120X_MODEM_STATUS1,     0x10},

#endif


#ifdef RCM

  {CC120X_IOCFG3,            0x06},
  {CC120X_IOCFG2,            0x06},
  {CC120X_SYNC_CFG1,         0xA8},
  {CC120X_SYNC_CFG0,         0x13},
  {CC120X_DEVIATION_M,       0x37},
  {CC120X_MODCFG_DEV_E,      0x0E},
  {CC120X_DCFILT_CFG,        0x26},
  {CC120X_PREAMBLE_CFG0,     0x8A},
  {CC120X_IQIC,              0x00},
  {CC120X_CHAN_BW,           0x41},

  {CC120X_MDMCFG1,           0x40},
  {CC120X_MDMCFG0,           0x05},
  {CC120X_SYMBOL_RATE2,      0x96},
  {CC120X_SYMBOL_RATE1,      0x87},
  {CC120X_SYMBOL_RATE0,      0x2B},
  {CC120X_AGC_REF,           0x42},
  {CC120X_AGC_CS_THR,        0x01},
  {CC120X_AGC_CFG1,          0x16},
  {CC120X_AGC_CFG0,          0x84},
  {CC120X_FIFO_CFG,          0x00},
  {CC120X_FS_CFG,            0x12},
  {CC120X_PKT_CFG2,          0x00},
  {CC120X_PKT_CFG0,          0x20},

//	//POWER 8
//  {CC120X_PA_CFG1,           0x71},
//  {CC120X_PA_CFG0,           0x50},

	//POWER 10
  {CC120X_PA_CFG1,           0x76},
  {CC120X_PA_CFG0,           0x50},

	//POWER 14
//  {CC120X_PA_CFG1,           0x7F},
//  {CC120X_PA_CFG0,           0x50},

  {CC120X_PKT_LEN,           0xFF},
  {CC120X_IF_MIX_CFG,        0x18},
  {CC120X_FREQOFF_CFG,       0x22},
  {CC120X_TOC_CFG,           0x03},
  {CC120X_MDMCFG2,           0x00},

//	Carrier frequency = 915	MHZ
  {CC120X_FREQ2,             0x5B},
  {CC120X_FREQ1,             0x80},
  {CC120X_FREQ0,             0x00},

//// Carrier frequency = 866.5	MHZ
//	{CC120X_FREQ2,             0x56},
//  {CC120X_FREQ1,             0xA6},
//  {CC120X_FREQ0,             0x66},

//	Carrier frequency = 868	MHZ
//  {CC120X_FREQ2,             0x56},
//  {CC120X_FREQ1,             0xCC},
//  {CC120X_FREQ0,             0xCC},

////	Carrier frequency = 865.045	MHZ
//  {CC120X_FREQ2,             0x56},
//  {CC120X_FREQ1,             0x81},
//  {CC120X_FREQ0,             0x26},

  {CC120X_IF_ADC1,           0xEE},
  {CC120X_IF_ADC0,           0x10},
  {CC120X_FS_DIG1,           0x07},
  {CC120X_FS_DIG0,           0xAB},
  {CC120X_FS_CAL1,           0x40},
  {CC120X_FS_CAL0,           0x0E},
  {CC120X_FS_DIVTWO,         0x03},
  {CC120X_FS_DSM0,           0x33},
  {CC120X_FS_DVC0,           0x17},
  {CC120X_FS_PFD,            0x00},
  {CC120X_FS_PRE,            0x6E},
  {CC120X_FS_REG_DIV_CML,    0x1C},
  {CC120X_FS_SPARE,          0xAC},
  {CC120X_FS_VCO0,           0xB5},
  {CC120X_IFAMP,             0x0D},
  {CC120X_XOSC5,             0x0E},
  {CC120X_XOSC1,             0x03},
  {CC120X_PARTNUMBER,        0x20},
  {CC120X_PARTVERSION,       0x11},
  {CC120X_MODEM_STATUS1,     0x10},

#endif

#ifdef TELEC

	{CC120X_IOCFG3,            0x06},
	{CC120X_IOCFG2, 0x06},
	{CC120X_SYNC_CFG1, 0xA8},
	{CC120X_SYNC_CFG0, 0x13},
	{CC120X_DEVIATION_M, 0xEB},
	{CC120X_MODCFG_DEV_E, 0x0C},
	{CC120X_DCFILT_CFG, 0x26},
	{CC120X_PREAMBLE_CFG0, 0x8A},
	{CC120X_IQIC, 0x80},
	{CC120X_CHAN_BW, 0x05},
	{CC120X_MDMCFG1, 0x40},
	{CC120X_MDMCFG0, 0x05},
	{CC120X_SYMBOL_RATE2, 0xA4},
	{CC120X_SYMBOL_RATE1, 0x7A},
	{CC120X_SYMBOL_RATE0, 0xE1},
	{CC120X_AGC_REF, 0x3E},
	{CC120X_AGC_CS_THR, 0x01},
	{CC120X_AGC_CFG1, 0x16},
	{CC120X_AGC_CFG0, 0x84},
	{CC120X_FIFO_CFG, 0x00},
	{CC120X_FS_CFG, 0x12},
	{CC120X_PKT_CFG2, 0x00},
	{CC120X_PKT_CFG0, 0x20},

	{CC120X_PA_CFG1,           0x76},//10 dBm
	//{CC120X_PA_CFG1,           0x71},//8 dBm
	//{CC120X_PA_CFG1,           0x6C},//6 dBm

	{CC120X_PA_CFG0, 0x52},
	{CC120X_PKT_LEN, 0xFF},
	{CC120X_IF_MIX_CFG, 0x18},
	{CC120X_FREQOFF_CFG, 0x22},
	{CC120X_TOC_CFG, 0x03},
	{CC120X_MDMCFG2, 0x00},

	//920.7
	{CC120X_FREQ2,             0x5C},
	{CC120X_FREQ1,             0x12},
	{CC120X_FREQ0,             0x64},

	{CC120X_IF_ADC1, 0xEE},
	{CC120X_IF_ADC0, 0x10},
	{CC120X_FS_DIG1, 0x07},
	{CC120X_FS_DIG0, 0xAB},
	{CC120X_FS_CAL1, 0x40},
	{CC120X_FS_CAL0, 0x0E},
	{CC120X_FS_DIVTWO, 0x03},
	{CC120X_FS_DSM0, 0x33},
	{CC120X_FS_DVC0, 0x17},
	{CC120X_FS_PFD, 0x00},
	{CC120X_FS_PRE, 0x6E},
	{CC120X_FS_REG_DIV_CML, 0x1C},
	{CC120X_FS_SPARE, 0xAC},
	{CC120X_FS_VCO0, 0xB5},
	{CC120X_IFAMP, 0x0D},
	{CC120X_XOSC5, 0x0E},
	{CC120X_XOSC1, 0x03},
	{CC120X_PARTNUMBER, 0x20},
	{CC120X_PARTVERSION, 0x11},
	{CC120X_MODEM_STATUS1, 0x10},
#endif

};


static const registerSetting_t preferredSettings_ota[]=
{

#ifdef CE

//  {CC120X_IOCFG3,            0x06},
  {CC120X_IOCFG2,            0x06},
  {CC120X_SYNC_CFG1,         0xA8},
  {CC120X_SYNC_CFG0,         0x13},
  {CC120X_DEVIATION_M,       0x68},
  {CC120X_MODCFG_DEV_E,      0x0B},
  {CC120X_DCFILT_CFG,        0x26},
  {CC120X_PREAMBLE_CFG0,     0x8A},
  {CC120X_IQIC,              0x80},
  {CC120X_CHAN_BW,           0x0F},

  {CC120X_MDMCFG1,           0x40},
  {CC120X_MDMCFG0,           0x05},
  {CC120X_SYMBOL_RATE2,      0x96},
  {CC120X_SYMBOL_RATE1,      0x87},
  {CC120X_SYMBOL_RATE0,      0x2B},
  {CC120X_AGC_REF,           0x27},
  {CC120X_AGC_CS_THR,        0x01},
  {CC120X_AGC_CFG1,          0x16},
  {CC120X_AGC_CFG0,          0x84},
  {CC120X_FIFO_CFG,          0x00},
  {CC120X_FS_CFG,            0x12},
  {CC120X_PKT_CFG2,          0x00},
  {CC120X_PKT_CFG0,          0x20},

//	//POWER 8
//  {CC120X_PA_CFG1,           0x71},
//  {CC120X_PA_CFG0,           0x50},

	//POWER 10
  {CC120X_PA_CFG1,           0x76},
  {CC120X_PA_CFG0,           0x50},

	//POWER 14
//  {CC120X_PA_CFG1,           0x7F},
//  {CC120X_PA_CFG0,           0x50},

  {CC120X_PKT_LEN,           0xFF},
  {CC120X_IF_MIX_CFG,        0x18},
  {CC120X_FREQOFF_CFG,       0x22},
  {CC120X_TOC_CFG,           0x03},
  {CC120X_MDMCFG2,           0x00},

//	Carrier frequency = 865	MHZ
  {CC120X_FREQ2,             0x56},
  {CC120X_FREQ1,             0x80},
  {CC120X_FREQ0,             0x00},

//// Carrier frequency = 866.5	MHZ
//	{CC120X_FREQ2,             0x56},
//  {CC120X_FREQ1,             0xA6},
//  {CC120X_FREQ0,             0x66},

//	Carrier frequency = 868	MHZ
//  {CC120X_FREQ2,             0x56},
//  {CC120X_FREQ1,             0xCC},
//  {CC120X_FREQ0,             0xCC},

////	Carrier frequency = 865.045	MHZ
//  {CC120X_FREQ2,             0x56},
//  {CC120X_FREQ1,             0x81},
//  {CC120X_FREQ0,             0x26},

  {CC120X_IF_ADC1,           0xEE},
  {CC120X_IF_ADC0,           0x10},
  {CC120X_FS_DIG1,           0x07},
  {CC120X_FS_DIG0,           0xA5},
  {CC120X_FS_CAL1,           0x40},
  {CC120X_FS_CAL0,           0x0E},
  {CC120X_FS_DIVTWO,         0x03},
  {CC120X_FS_DSM0,           0x33},
  {CC120X_FS_DVC0,           0x17},
  {CC120X_FS_PFD,            0x00},
  {CC120X_FS_PRE,            0x6E},
  {CC120X_FS_REG_DIV_CML,    0x1C},
  {CC120X_FS_SPARE,          0xAC},
  {CC120X_FS_VCO0,           0xB5},
  {CC120X_IFAMP,             0x0D},
  {CC120X_XOSC5,             0x0E},
  {CC120X_XOSC1,             0x03},
  {CC120X_PARTNUMBER,        0x20},
  {CC120X_PARTVERSION,       0x11},
  {CC120X_MODEM_STATUS1,     0x10},

#endif


#ifdef FCC

  //{CC120X_IOCFG3,            0x06},
  {CC120X_IOCFG2,            0x06},
  {CC120X_SYNC_CFG1,         0xA8},
  {CC120X_SYNC_CFG0,         0x13},
  {CC120X_DEVIATION_M,       0x37},
  {CC120X_MODCFG_DEV_E,      0x0E},
  {CC120X_DCFILT_CFG,        0x26},
  {CC120X_PREAMBLE_CFG0,     0x8A},
  {CC120X_IQIC,              0x00},
  {CC120X_CHAN_BW,           0x41},

  {CC120X_MDMCFG1,           0x40},
  {CC120X_MDMCFG0,           0x05},
  {CC120X_SYMBOL_RATE2,      0x96},
  {CC120X_SYMBOL_RATE1,      0x87},
  {CC120X_SYMBOL_RATE0,      0x2B},
  {CC120X_AGC_REF,           0x42},
  {CC120X_AGC_CS_THR,        0x01},
  {CC120X_AGC_CFG1,          0x16},
  {CC120X_AGC_CFG0,          0x84},
  {CC120X_FIFO_CFG,          0x00},
  {CC120X_FS_CFG,            0x12},
  {CC120X_PKT_CFG2,          0x00},
  {CC120X_PKT_CFG0,          0x20},

//	//POWER 8
//  {CC120X_PA_CFG1,           0x71},
//  {CC120X_PA_CFG0,           0x50},

	//POWER 10
  {CC120X_PA_CFG1,           0x76},
  {CC120X_PA_CFG0,           0x50},

	//POWER 14
//  {CC120X_PA_CFG1,           0x7F},
//  {CC120X_PA_CFG0,           0x50},

  {CC120X_PKT_LEN,           0xFF},
  {CC120X_IF_MIX_CFG,        0x18},
  {CC120X_FREQOFF_CFG,       0x22},
  {CC120X_TOC_CFG,           0x03},
  {CC120X_MDMCFG2,           0x00},

// Carrier frequency = 902 MHZ
  {CC120X_FREQ2,             0x5A},
  {CC120X_FREQ1,             0x33},
  {CC120X_FREQ0,             0x33},

//// Carrier frequency = 866.5	MHZ
//	{CC120X_FREQ2,             0x56},
//  {CC120X_FREQ1,             0xA6},
//  {CC120X_FREQ0,             0x66},

//	Carrier frequency = 868	MHZ
//  {CC120X_FREQ2,             0x56},
//  {CC120X_FREQ1,             0xCC},
//  {CC120X_FREQ0,             0xCC},

////	Carrier frequency = 865.045	MHZ
//  {CC120X_FREQ2,             0x56},
//  {CC120X_FREQ1,             0x81},
//  {CC120X_FREQ0,             0x26},

  {CC120X_IF_ADC1,           0xEE},
  {CC120X_IF_ADC0,           0x10},
  {CC120X_FS_DIG1,           0x07},
//  {CC120X_FS_DIG0,           0xA5},
  {CC120X_FS_DIG0,           0xAB},
  {CC120X_FS_CAL1,           0x40},
  {CC120X_FS_CAL0,           0x0E},
  {CC120X_FS_DIVTWO,         0x03},
  {CC120X_FS_DSM0,           0x33},
  {CC120X_FS_DVC0,           0x17},
  {CC120X_FS_PFD,            0x00},
  {CC120X_FS_PRE,            0x6E},
  {CC120X_FS_REG_DIV_CML,    0x1C},
  {CC120X_FS_SPARE,          0xAC},
  {CC120X_FS_VCO0,           0xB5},
  {CC120X_IFAMP,             0x0D},
  {CC120X_XOSC5,             0x0E},
  {CC120X_XOSC1,             0x03},
  {CC120X_PARTNUMBER,        0x20},
  {CC120X_PARTVERSION,       0x11},
  {CC120X_MODEM_STATUS1,     0x10},

#endif


#ifdef RCM

  //{CC120X_IOCFG3,            0x06},
   {CC120X_IOCFG2,            0x06},
  {CC120X_SYNC_CFG1,         0xA8},
  {CC120X_SYNC_CFG0,         0x13},
  {CC120X_DEVIATION_M,       0x37},
  {CC120X_MODCFG_DEV_E,      0x0E},
  {CC120X_DCFILT_CFG,        0x26},
  {CC120X_PREAMBLE_CFG0,     0x8A},
  {CC120X_IQIC,              0x00},
  {CC120X_CHAN_BW,           0x41},

  {CC120X_MDMCFG1,           0x40},
  {CC120X_MDMCFG0,           0x05},
  {CC120X_SYMBOL_RATE2,      0x96},
  {CC120X_SYMBOL_RATE1,      0x87},
  {CC120X_SYMBOL_RATE0,      0x2B},
  {CC120X_AGC_REF,           0x42},
  {CC120X_AGC_CS_THR,        0x01},
  {CC120X_AGC_CFG1,          0x16},
  {CC120X_AGC_CFG0,          0x84},
  {CC120X_FIFO_CFG,          0x00},
  {CC120X_FS_CFG,            0x12},
  {CC120X_PKT_CFG2,          0x00},
  {CC120X_PKT_CFG0,          0x20},

//	//POWER 8
//  {CC120X_PA_CFG1,           0x71},
//  {CC120X_PA_CFG0,           0x50},

	//POWER 10
  {CC120X_PA_CFG1,           0x76},
  {CC120X_PA_CFG0,           0x50},

	//POWER 14
//  {CC120X_PA_CFG1,           0x7F},
//  {CC120X_PA_CFG0,           0x50},

  {CC120X_PKT_LEN,           0xFF},
  {CC120X_IF_MIX_CFG,        0x18},
  {CC120X_FREQOFF_CFG,       0x22},
  {CC120X_TOC_CFG,           0x03},
  {CC120X_MDMCFG2,           0x00},

//	Carrier frequency = 915	MHZ
  {CC120X_FREQ2,             0x5B},
  {CC120X_FREQ1,             0x80},
  {CC120X_FREQ0,             0x00},

//// Carrier frequency = 866.5	MHZ
//	{CC120X_FREQ2,             0x56},
//  {CC120X_FREQ1,             0xA6},
//  {CC120X_FREQ0,             0x66},

//	Carrier frequency = 868	MHZ
//  {CC120X_FREQ2,             0x56},
//  {CC120X_FREQ1,             0xCC},
//  {CC120X_FREQ0,             0xCC},

////	Carrier frequency = 865.045	MHZ
//  {CC120X_FREQ2,             0x56},
//  {CC120X_FREQ1,             0x81},
//  {CC120X_FREQ0,             0x26},

  {CC120X_IF_ADC1,           0xEE},
  {CC120X_IF_ADC0,           0x10},
  {CC120X_FS_DIG1,           0x07},
  {CC120X_FS_DIG0,           0xAB},
  {CC120X_FS_CAL1,           0x40},
  {CC120X_FS_CAL0,           0x0E},
  {CC120X_FS_DIVTWO,         0x03},
  {CC120X_FS_DSM0,           0x33},
  {CC120X_FS_DVC0,           0x17},
  {CC120X_FS_PFD,            0x00},
  {CC120X_FS_PRE,            0x6E},
  {CC120X_FS_REG_DIV_CML,    0x1C},
  {CC120X_FS_SPARE,          0xAC},
  {CC120X_FS_VCO0,           0xB5},
  {CC120X_IFAMP,             0x0D},
  {CC120X_XOSC5,             0x0E},
  {CC120X_XOSC1,             0x03},
  {CC120X_PARTNUMBER,        0x20},
  {CC120X_PARTVERSION,       0x11},
  {CC120X_MODEM_STATUS1,     0x10},

#endif

#ifdef TELEC

	//{CC120X_IOCFG3,            0x06},
	{CC120X_IOCFG2, 0x06},
	{CC120X_SYNC_CFG1, 0xA8},
	{CC120X_SYNC_CFG0, 0x13},
	{CC120X_DEVIATION_M, 0xEB},
	{CC120X_MODCFG_DEV_E, 0x0C},
	{CC120X_DCFILT_CFG, 0x26},
	{CC120X_PREAMBLE_CFG0, 0x8A},
	{CC120X_IQIC, 0x80},
	{CC120X_CHAN_BW, 0x05},
	{CC120X_MDMCFG1, 0x40},
	{CC120X_MDMCFG0, 0x05},
	{CC120X_SYMBOL_RATE2, 0xA4},
	{CC120X_SYMBOL_RATE1, 0x7A},
	{CC120X_SYMBOL_RATE0, 0xE1},
	{CC120X_AGC_REF, 0x3E},
	{CC120X_AGC_CS_THR, 0x01},
	{CC120X_AGC_CFG1, 0x16},
	{CC120X_AGC_CFG0, 0x84},
	{CC120X_FIFO_CFG, 0x00},
	{CC120X_FS_CFG, 0x12},
	{CC120X_PKT_CFG2, 0x00},
	{CC120X_PKT_CFG0, 0x20},

	{CC120X_PA_CFG1,           0x76},//10 dBm
	//{CC120X_PA_CFG1,           0x71},//8 dBm
	//{CC120X_PA_CFG1,           0x6C},//6 dBm

	{CC120X_PA_CFG0, 0x52},
	{CC120X_PKT_LEN, 0xFF},
	{CC120X_IF_MIX_CFG, 0x18},
	{CC120X_FREQOFF_CFG, 0x22},
	{CC120X_TOC_CFG, 0x03},
	{CC120X_MDMCFG2, 0x00},

	//920.7
	{CC120X_FREQ2,             0x5C},
	{CC120X_FREQ1,             0x12},
	{CC120X_FREQ0,             0x64},

	{CC120X_IF_ADC1, 0xEE},
	{CC120X_IF_ADC0, 0x10},
	{CC120X_FS_DIG1, 0x07},
	{CC120X_FS_DIG0, 0xAB},
	{CC120X_FS_CAL1, 0x40},
	{CC120X_FS_CAL0, 0x0E},
	{CC120X_FS_DIVTWO, 0x03},
	{CC120X_FS_DSM0, 0x33},
	{CC120X_FS_DVC0, 0x17},
	{CC120X_FS_PFD, 0x00},
	{CC120X_FS_PRE, 0x6E},
	{CC120X_FS_REG_DIV_CML, 0x1C},
	{CC120X_FS_SPARE, 0xAC},
	{CC120X_FS_VCO0, 0xB5},
	{CC120X_IFAMP, 0x0D},
	{CC120X_XOSC5, 0x0E},
	{CC120X_XOSC1, 0x03},
	{CC120X_PARTNUMBER, 0x20},
	{CC120X_PARTVERSION, 0x11},
	{CC120X_MODEM_STATUS1, 0x10},

#endif

};


void delay_cycles(uint32_t x)
{
	uint32_t j;

	for(j=0; j<=x; j++) {
		__NOP();
	}
}

// Simple Round Function
double into45(double a)
{
	double c;
	uint32_t b;

	b = (uint32_t)a;   // get integer part
	c = a - (double)b; // get 0.xxx

	if(c >= 0.5)       // round
		b = b + 1;

	return (double)b;
}


void cc1200_rx(void)
{
	//SPI_SET_SS0_HIGH(SPI0);
	SPI_SET_SS_HIGH(SPI0);
	trxSpiCmdStrobe(SPI0, CC120X_SIDLE);
	trxSpiCmdStrobe(SPI0, CC120X_SFRX);
	trxSpiCmdStrobe(SPI0, CC120X_SRX);
}


void cc1200_channel_init(uint32_t frf_920p6_m)
{
	//uint32_t frf_920p6_m = 92058780;
	uint8_t  frf_FREQ2, frf_FREQ1, frf_FREQ0;

	//902.6MHz : FREQ2=0x5C, FREQ1=0x0F, FREQ0=0x5C

#ifdef CE
	// Carrier frequency = 865 MHZ
	frf_FREQ2=0x56;
	frf_FREQ1=0x80;
	frf_FREQ0=0x00;

	fxosc_40M_real=((double)frf_920p6_m*4.0)/((double)frf_FREQ2+(double)frf_FREQ1/256.0+(double)frf_FREQ0/65536.0);

#endif


#ifdef FCC

	// Carrier frequency = 902 MHZ
	frf_FREQ2=0x5A;
	frf_FREQ1=0x33;
	frf_FREQ0=0x33;

	fxosc_40M_real=((double)frf_920p6_m*4.0)/((double)frf_FREQ2+(double)frf_FREQ1/256.0+(double)frf_FREQ0/65536.0);

#endif


#ifdef RCM

	// Carrier frequency = 915 MHZ
	frf_FREQ2=0x5B;
	frf_FREQ1=0x80;
	frf_FREQ0=0x00;

	fxosc_40M_real=((double)frf_920p6_m*4.0)/((double)frf_FREQ2+(double)frf_FREQ1/256.0+(double)frf_FREQ0/65536.0);

#endif

#ifdef TELEC

	// Carrier frequency = 920.7 MHZ
	frf_FREQ2=0x5C;
	frf_FREQ1=0x12;
	frf_FREQ0=0x64;

	fxosc_40M_real=((double)frf_920p6_m*4.0)/((double)frf_FREQ2+(double)frf_FREQ1/256.0+(double)frf_FREQ0/65536.0);

#endif

	//fxosc_40M_real = 4000000;
}
void cc1200_channel(uint8_t frf_channel)
{
	uint8_t  writeByte[4];
	uint8_t  frf_FREQ2 = 0, frf_FREQ1 = 0, frf_FREQ0 = 0, frf_FREQOFF0 = 0;
	double   FREQ2 = 0, FREQ1 = 0, FREQ0 = 0, FREQOFF0 = 0;
	uint32_t frf_ch_freq = 0;

#ifdef CE
	frf_ch_freq = Main_Frequency + frf_channel * 3500;

	FREQ2=(double)(frf_ch_freq*4.0/fxosc_40M_real);
	frf_FREQ2 = (uint8_t)FREQ2;
	writeByte[3] = frf_FREQ2;
	FREQ1=(double)(FREQ2-(double)frf_FREQ2)*256.0;
	frf_FREQ1 = (uint8_t)FREQ1;
	writeByte[2] = frf_FREQ1;
	FREQ0=(double)(FREQ1-(double)frf_FREQ1)*256.0;
	frf_FREQ0=(uint8_t)into45(FREQ0);
	writeByte[1] = frf_FREQ0;
	FREQOFF0=(double)(FREQ0-(double)frf_FREQ0)*4.0;
	//frf_FREQOFF0=(uint8_t)into45(FREQOFF0);
	frf_FREQOFF0 = (uint8_t)FREQOFF0;
	writeByte[0] = frf_FREQOFF0;
#endif


#ifdef FCC

	if (frf_channel == 0)
		frf_ch_freq = Main_Frequency;
	else
		frf_ch_freq = Main_Frequency + (frf_channel * 30000) + 60000;

	FREQ2=(double)(frf_ch_freq*4.0/fxosc_40M_real);
	frf_FREQ2 = (uint8_t)FREQ2;
	writeByte[3] = frf_FREQ2;
	FREQ1=(double)(FREQ2-(double)frf_FREQ2)*256.0;
	frf_FREQ1 = (uint8_t)FREQ1;
	writeByte[2] = frf_FREQ1;
	FREQ0=(double)(FREQ1-(double)frf_FREQ1)*256.0;
	frf_FREQ0=(uint8_t)into45(FREQ0);
	writeByte[1] = frf_FREQ0;
	FREQOFF0=(double)(FREQ0-(double)frf_FREQ0)*4.0;
	//frf_FREQOFF0=(uint8_t)into45(FREQOFF0);
	frf_FREQOFF0 = (uint8_t)FREQOFF0;
	writeByte[0] = frf_FREQOFF0;

#endif


#ifdef RCM

	if (frf_channel == 0)
		frf_ch_freq = Main_Frequency;
	else
		frf_ch_freq = Main_Frequency + (frf_channel * 12000) + 84000;

	FREQ2=(double)(frf_ch_freq*4.0/fxosc_40M_real);
	frf_FREQ2 = (uint8_t)FREQ2;
	writeByte[3] = frf_FREQ2;
	FREQ1=(double)(FREQ2-(double)frf_FREQ2)*256.0;
	frf_FREQ1 = (uint8_t)FREQ1;
	writeByte[2] = frf_FREQ1;
	FREQ0=(double)(FREQ1-(double)frf_FREQ1)*256.0;
	frf_FREQ0=(uint8_t)into45(FREQ0);
	writeByte[1] = frf_FREQ0;
	FREQOFF0=(double)(FREQ0-(double)frf_FREQ0)*4.0;
	//frf_FREQOFF0=(uint8_t)into45(FREQOFF0);
	frf_FREQOFF0 = (uint8_t)FREQOFF0;
	writeByte[0] = frf_FREQOFF0;

#endif

#ifdef TELEC

	if (frf_channel == 0)
		frf_ch_freq = Main_Frequency;
	else
		frf_ch_freq = Main_Frequency + (frf_channel * 20000) + 20000;
	//printf("f=%d\r\n",frf_ch_freq);
	FREQ2=(double)(frf_ch_freq*4.0/fxosc_40M_real);
	frf_FREQ2 = (uint8_t)FREQ2;
	writeByte[3] = frf_FREQ2;
	FREQ1=(double)(FREQ2-(double)frf_FREQ2)*256.0;
	frf_FREQ1 = (uint8_t)FREQ1;
	writeByte[2] = frf_FREQ1;
	FREQ0=(double)(FREQ1-(double)frf_FREQ1)*256.0;
	frf_FREQ0=(uint8_t)into45(FREQ0);
	writeByte[1] = frf_FREQ0;
	FREQOFF0=(double)(FREQ0-(double)frf_FREQ0)*4.0;
	//frf_FREQOFF0=(uint8_t)into45(FREQOFF0);
	frf_FREQOFF0 = (uint8_t)FREQOFF0;
	writeByte[0] = frf_FREQOFF0;

#endif

	cc120xSpiWriteReg(SPI0, CC120X_FREQ2, &writeByte[3], 1);
	cc120xSpiWriteReg(SPI0, CC120X_FREQ1, &writeByte[2], 1);
	cc120xSpiWriteReg(SPI0, CC120X_FREQ0, &writeByte[1], 1);
	cc120xSpiWriteReg(SPI0, CC120X_FREQOFF0, &writeByte[0], 1);
}

/*******************************************************************************
*   @fn         registerConfig
*
*   @brief      Write register settings as given by SmartRF Studio found in
*               cc120x_easy_link_reg_config.h
*
*   @param      none
*
*   @return     none
*/
void registerConfig(void)
{

	uint8_t writeByte;
	uint8_t rf_ver = 0;
	uint16_t i;

	// Reset RF Module
	W1_RESET = 0;
	//delay_cycles(3);
	CLK_SysTickDelay(1000);
	W1_RESET = 1;
	//delay_cycles(3000);
	CLK_SysTickDelay(1000);

	// Reset radio
	trxSpiCmdStrobe(SPI0, CC120X_SRES);

	// Write registers to radio
	if (cc1200_work_ch == 0) {

		for(i = 0; i < (sizeof(preferredSettings_ota)/sizeof(registerSetting_t)); i++) {
		//	printf("i=%d\r\n",i);
			writeByte = preferredSettings_ota[i].data;
			cc120xSpiWriteReg(SPI0, preferredSettings_ota[i].addr, &writeByte, 1);
		}

	} else {
		for(i = 0; i < (sizeof(preferredSettings)/sizeof(registerSetting_t)); i++) {
		//	printf("i=%d\r\n",i);
			writeByte = preferredSettings[i].data;
			cc120xSpiWriteReg(SPI0, preferredSettings[i].addr, &writeByte, 1);
		}
	}

//	if (info.wr3ptx_info.tx_frequency_cal_mode == ON)  {

//		writeByte = 0x03;
//		cc120xSpiWriteReg(SPI0, CC120X_MDMCFG2, &writeByte, 1);
//	} else {

//		writeByte = 0x02;
//		cc120xSpiWriteReg(SPI0, CC120X_MDMCFG2, &writeByte, 1);
//	}

		writeByte = 0x02;
		cc120xSpiWriteReg(SPI0, CC120X_MDMCFG2, &writeByte, 1);

	// CS Init Config
	// Carrier Sense Threshold(dB)
	// 0xAB = -85; 0xAE = -82; 0xAD = -83; 0xB0 = -80
	//writeByte = 0xAE;
	writeByte = 0xBD;
	cc120xSpiWriteReg(SPI0, CC120X_AGC_CS_THR, &writeByte, 1);
	// AGC_CFG0[3:2] = RSSI_VALID_CNT, No. of samples in moving average filter
	// 0x00: 1, 0x04: 2, 0x08: 5, 0x0C: 9
	writeByte = 0x80;
	cc120xSpiWriteReg(SPI0, CC120X_AGC_CFG0, &writeByte, 1);
	// RSSI Offset = 0(0x9D), -99(0x00), -80(0xB0)
	writeByte = 0xB0;
	cc120xSpiWriteReg(SPI0, CC120X_AGC_GAIN_ADJUST, &writeByte, 1);

	cc1200_channel_init(freq_offset);
	cc1200_channel(cc1200_work_ch);

	cc120xSpiReadReg(SPI0, CC120X_PARTNUMBER, &rf_ver, 1);

	cc1200_rx();

	writeByte = 0x76;
	cc120xSpiWriteReg(SPI0, CC120X_PA_CFG1, &writeByte, 1);

	 while (!SPI_GET_RX_FIFO_EMPTY_FLAG(SPI0))
		 SPI_READ_RX(SPI0);

	SPI_ClearIntFlag(SPI0,SPI_FIFO_RXOV_INT_MASK);

	cc1200_power_on = ON;
}

void runRX(SPI_T * spi) {

	runRX_none(SPI0);

}

__IO uint8_t get_cn = 0;
void runRX_none(SPI_T * spi_none) {

	uint8_t  pkt_len = 0,rssi = 0;
	int32_t  crc_Checksum = 0;
	uint8_t  RECEIVED_CRC_L = 0, RECEIVED_CRC_H = 0;
	uint32_t RECEIVED_CRC = 0;
	uint8_t  rf_rx_flag = 0;
	uint8_t cn = 1,i;
	uint8_t checksum = 0;
	int32_t ms_count1,ms_count2 = 0;
	uint32_t u32_reg;
	uint8_t crc_check_ok = 0,ch_check = 0;
	uint16_t degrees_reg = 0;
	uint8_t reg_u8[6] = {0};
	uint8_t sn_check_ok = 0;
	uint32_t timer3_cn = 0;

	#ifndef POWER_SAVING
		cc1200_wait_rx_flag = 1;
	#endif
	if (cc1200_wait_rx_flag) {

		#ifdef POWER_SAVING
		//ms_count1 = TIMER1->CNT;
		ms_count1 = TIMER2->CNT;
		while(packetSemaphore == ISR_IDLE) {

			//ms_count2 = TIMER1->CNT;
			ms_count2 = TIMER2->CNT;
			ms_count2 = abs(ms_count2-ms_count1);

			//if (ms_count2 >= 656) {
			//if (ms_count2 >= 984) { //OK
			//if (ms_count2 >= 490) {
			if (ms_count2 >= 327) {
			//if (ms_count2 >= 192) {
			//if (ms_count2 >= 720) {		//65012 - //free run 提早16ms - timeout :720
			//if (ms_count2 >= 1000) {		//64848; //debug 提早16ms    - timeout :1000
				__NOP();
				packetSemaphore = 2;	//超過20ms沒收到資料
//				info.cc1200_timeout_cn = 5;
			}
		}
		#endif

		//cc1200_get_flag = OFF;

		// Wait for packet received interrupt
		if(packetSemaphore == ISR_ACTION_REQUIRED) {

//			/* 提早10ms,其中5ms對CC1200設定 */
//			//TIMER1->CMP = 65195;	//o
//			TIMER1->CMP = 64881;

			memset((void*)rxBuffer, 0, sizeof(rxBuffer));
			get_cn++;
			/*CC1200產生中斷後立即進行SPI讀取會出錯,需Delay後再讀取*/
			CLK_SysTickDelay(5000);
//			for (i = 0;i < 255; i++)
//				__NOP();

//			for (i = 0;i < 255; i++)
//				__NOP();

			cc120xSpiReadRxFifo(spi_none,(uint8_t *)rxBuffer,17);

			// Reset packet semaphore
			packetSemaphore = ISR_IDLE;

			// Clear RX Buffer
			cc1200_rx();

//			#ifdef POWER_SAVING
//			if (info.backlight_cn < LCM_BACKLIGHT_SEC) {
//				__NOP();
//			} else {
//				cc1200_power_off();
//				//printf("1\r\n");
//			}
//			#endif

//			rxBuffer[0] = 0x0D;
//			rxBuffer[1] = 0x02;
//			rxBuffer[2] = 0x41;
//			rxBuffer[3] = 0xA0;
//			rxBuffer[4] = 0x09;
//			rxBuffer[5] = 0x3F;
//			rxBuffer[6] = 0x80;
//			rxBuffer[7] = 0x00;
//			rxBuffer[8] = 0x40;
//			rxBuffer[9] = 0xF1;
//			rxBuffer[10] = 0x4B;
//			rxBuffer[11] = 0x9C;
//			rxBuffer[12] = 0x00;
//			rxBuffer[13] = 0xD0;


			/* 先解析封包資料,再進行風速MAX&AVG及溫度AVG */
			for (i = 0; i <= 12; i++)
				checksum += rxBuffer[i];

			if (rxBuffer[0] == 0) {

				__NOP();
				__NOP();
			}

			if (rxBuffer[15] & 0x80)
				crc_check_ok = 1;

			checksum = checksum + ((rxBuffer[13] & 0xC0) >> 6);
			checksum = checksum & 0x3F;

			cc1200_re_setting = OFF;

			if (info.tx_sn_binding_status) {

				/* 有綁定時,需對SN進行確認 */
				reg_u8[0] = (rxBuffer[1] >> 1) + 20;
				reg_u8[1] = ((rxBuffer[1] & 0x01) << 3) | ((rxBuffer[2] & 0xe0) >> 5) ;
				reg_u8[2] = (rxBuffer[2] & 0x1F) + 0x40;
				reg_u8[3] = ((rxBuffer[3] & 0xF8) >> 3 ) + 0x40;
				reg_u8[4] = ((rxBuffer[3] & 0x07) << 1) | ((rxBuffer[4] & 0x80) >> 7);
				reg_u8[5] = (rxBuffer[4] & 0x7F);

//				for (i = 0;i < 6;i++)
//					printf("reg_u8[%d] = %d\r\n",i,reg_u8[i]);

				if ((reg_u8[0] == info.rx_sn[0]) && (reg_u8[1] == info.rx_sn[1]) &&
					(reg_u8[2] == 'A') && (reg_u8[3] == 'T') &&
					(reg_u8[4] == info.rx_sn[4]) && (reg_u8[5] == info.rx_sn[5]))
					sn_check_ok = ON;
				else
					sn_check_ok = OFF;
			} else {

				reg_u8[0] = (rxBuffer[1] >> 1) + 20;
				reg_u8[1] = ((rxBuffer[1] & 0x01) << 3) | ((rxBuffer[2] & 0xe0) >> 5) ;
				reg_u8[2] = (rxBuffer[2] & 0x1F) + 0x40;
				reg_u8[3] = ((rxBuffer[3] & 0xF8) >> 3 ) + 0x40;
				reg_u8[4] = ((rxBuffer[3] & 0x07) << 1) | ((rxBuffer[4] & 0x80) >> 7);
				reg_u8[5] = (rxBuffer[4] & 0x7F);

				/* 沒有綁定時,如果不是相同頻道時放棄該筆資料 */
				ch_check = (rxBuffer[4] & 0x7F);

				if ((ch_check == info.wireless_ch_status) && (reg_u8[2] == 'A') && (reg_u8[3] == 'T'))
					sn_check_ok = ON;
				else
					sn_check_ok = OFF;
			}

			//if ((checksum == rxBuffer[13]) && (rxBuffer[0]!= 0)) {
			//if ((checksum == (rxBuffer[13] & 0x3F)) && (rxBuffer[0]!= 0) && (sn_check_ok == ON )) {
			if (((checksum == (rxBuffer[13] & 0x3F)) && (rxBuffer[0]!= 0) && (sn_check_ok == ON )) && (crc_check_ok == 1)) {
			//if ((checksum == (rxBuffer[13] & 0x3F)) && (rxBuffer[0]!= 0)) {
			//if (rxBuffer[0]!= 0) {

//				#ifdef POWER_SAVING
//				if (info.backlight_cn < LCM_BACKLIGHT_SEC) {
//					__NOP();
//				} else {
//					cc1200_power_off();
//					//printf("1\r\n");
//				}
//				#endif

				timer3_cn = TIMER2->CNT;
				//TIMER1->CMP = CC1200_WAKE_UP_TIME + timer3_cn; //ok
				//TIMER1->CMP = CC1200_WAKE_UP_TIME - timer3_cn; //x

				//printf("t1 = %d TO = %d\r\n",TIMER1->CMP,info.cc1200_timeout_cn);

				cc1200_get_flag = ON;

//				if(info.current_page == TEST_Page)
//					__NOP();
//				else
//					cc1200_power_off();

				memset((void*)info.origin_tx_data,0,sizeof(info.origin_tx_data));

				memcpy((void*)info.origin_tx_data,(uint8_t *)&rxBuffer[1],13);

				//info.wireless_get_cn++;
				info.cc1200_timeout_cn = 0;
				info.cc1200_sleep_mode = OFF;
				cc1200_wait_rx_flag = 0;
				info.wr3ptx_info.wr3ptx_info_get = ON;
				/* 取2補數加1 */
				//info.wr3ptx_info.rssi = (~rxBuffer[14]) + 1;
				//info.wr3ptx_info.rssi = rxBuffer[14];
				info.wr3ptx_info.rssi = (0xFF - rxBuffer[14]) + 1;

				info.wr3ptx_info.rssi = abs(info.wr3ptx_info.rssi);
				/* 分析封包 */
				//year
				info.wr3ptx_info.year = rxBuffer[1] >> 1;

				//month
				info.wr3ptx_info.month = ((rxBuffer[1] & 0x01) << 3) | ((rxBuffer[2] & 0xe0) >> 5) ;

				//sn
//				u32_reg = __IO uint8_t rx_sn[6];	//0:year 1:month 2~3:module name 4:No. 5:ch[2] << 16;
//				u32_reg |= rxBuffer[3] << 8;
//				u32_reg |= rxBuffer[4];
//				u32_reg &= 0x0000fffff;
//				info.wr3ptx_info.sn = u32_reg;

				/* TX SN */
				info.tx_sn[0] = (rxBuffer[1] >> 1) + 20;
				info.tx_sn[1] = ((rxBuffer[1] & 0x01) << 3) | ((rxBuffer[2] & 0xe0) >> 5) ;
				info.tx_sn[2] = (rxBuffer[2] & 0x1F) + 0x40;
				info.tx_sn[3] = ((rxBuffer[3] & 0xF8) >> 3 ) + 0x40;
				info.tx_sn[4] = ((rxBuffer[3] & 0x07) << 1) | ((rxBuffer[4] & 0x80) >> 7);
				info.tx_sn[5] = (rxBuffer[4] & 0x7F);

				//pressure / hpa
				u32_reg = rxBuffer[5] << 8;
				u32_reg |= rxBuffer[6];
				u32_reg = u32_reg >> 4;

				/* 壓力值異常 */
//				if (u32_reg > 2000)
//					__NOP();
//				else
				info.wr3ptx_info.pressure = u32_reg;


				//rh
				u32_reg = rxBuffer[6] << 8;
				u32_reg |= rxBuffer[7];
				u32_reg &= 0x0fff;
				u32_reg = u32_reg;;

				/* RH值異常 */
//				if (info.wr3ptx_info.rh > 1000)
//					__NOP();
//				else
				info.wr3ptx_info.rh = u32_reg;


				//temperature /deg F + 300
				u32_reg = rxBuffer[8] << 8;
				u32_reg |= rxBuffer[9];
				u32_reg = u32_reg >> 4;

				/* 溫度值異常 */
//				if (info.wr3ptx_info.temperature > 1880)
//					__NOP();
//				else
				info.wr3ptx_info.temperature = u32_reg;

				//info.wr3ptx_info.temperature = 150;		//test溫度負值

				//wind speed /km-h
				u32_reg = rxBuffer[9] << 8;
				u32_reg |= rxBuffer[10];
				u32_reg &= 0x0fff;

				/* 風速值異常 */
//				if (info.wr3ptx_info.wind_speed > 1800)
//					__NOP();
//				else
				info.wr3ptx_info.wind_speed = u32_reg;

				//low batt
				info.wr3ptx_info.low_batt = (rxBuffer[11] & 0xFE) >> 1;

				degrees_reg = (rxBuffer[11] & 0x01) << 8;
				degrees_reg |= rxBuffer[12];
				info.wr3ptx_info.degrees = degrees_reg;

				//degree
//				info.wr3ptx_info.degrees = rxBuffer[11] << 8;
//				info.wr3ptx_info.degrees |= rxBuffer[12];
//				info.wr3ptx_info.degrees &= 0x3fff;

				info.wr3ptx_info.tx_count = rxBuffer[13] >> 6;

				//printf("c = %d\r\n",info.wr3ptx_info.tx_count);



//				if (info.history_info.History_hour >= 1)
//					info.history_info.Had_Info[0] = ON;

				info.wr3ptx_info.wr3ptx_info_hour_between_get = ON;

				if (info.wr3ptx_info.wr3ptx_first_data_get == OFF) {

					info.wr3ptx_info.wr3ptx_first_data_get = ON;

					if (!info.wr3ptx_info.wr3ptx_first_data_get_had_beeper_flag) {

						info.wr3ptx_info.wr3ptx_first_data_get_had_beeper_flag = ON;

						PWM0_BEEPER_SW = ON;
						CLK_SysTickDelay(50000);
						PWM0_BEEPER_SW = OFF;

						CLK_SysTickDelay(100000);

						PWM0_BEEPER_SW = ON;
						CLK_SysTickDelay(50000);
						PWM0_BEEPER_SW = OFF;

//						//PWM_ConfigOutputChannel(PWM0, 1, 2900, 50);
//						BP_SW_PIN = 1;
//						BP_PIN = ON;
//						//PWM_Start(PWM0, PWM_CH_1_MASK);
//						//PWM_EnableOutput(PWM0, PWM_CH_1_MASK);
//						LED_G_PIN = ON;
//						CLK_SysTickDelay(50000);
//						LED_G_PIN = OFF;

//						//PWM_DisableOutput(PWM0, PWM_CH_1_MASK);
//						BP_PIN = OFF;
//						CLK_SysTickDelay(100000);

//						//PWM_EnableOutput(PWM0, PWM_CH_1_MASK);
//						BP_PIN = ON;
//						LED_G_PIN = ON;
//						CLK_SysTickDelay(50000);
//						LED_G_PIN = OFF;
//						//PWM_DisableOutput(PWM0, PWM_CH_1_MASK);
//						BP_PIN = OFF;
//						BP_SW_PIN = 0;
//						//PWM_Stop(PWM0, PWM_CH_1_MASK);
					}

				}

				/* 先清除存放RSSI空間 */
				info.origin_tx_data[12] = 0;

				if (info.wr3ptx_info.rssi <= 7)
					rssi = 0;
				else if (info.wr3ptx_info.rssi <= 15)
					rssi = 1;
				else if (info.wr3ptx_info.rssi <= 23)
					rssi = 2;
				else if (info.wr3ptx_info.rssi <= 31)
					rssi = 3;
				else if (info.wr3ptx_info.rssi <= 39)
					rssi = 4;
				else if (info.wr3ptx_info.rssi <= 47)
					rssi = 5;
				else if (info.wr3ptx_info.rssi <= 55)
					rssi = 6;
				else if (info.wr3ptx_info.rssi <= 63)
					rssi = 7;
				else if (info.wr3ptx_info.rssi <= 71)
					rssi = 8;
				else if (info.wr3ptx_info.rssi <= 79)
					rssi = 9;
				else if (info.wr3ptx_info.rssi <= 87)
					rssi = 10;
				else if (info.wr3ptx_info.rssi <= 95)
					rssi = 11;
				else if (info.wr3ptx_info.rssi <= 103)
					rssi = 12;
				else if (info.wr3ptx_info.rssi <= 111)
					rssi = 13;
				else if (info.wr3ptx_info.rssi <= 119)
					rssi = 14;
				else if (info.wr3ptx_info.rssi <= 127)
					rssi = 15;
				else
					rssi = 15;


				rssi = rssi & 0x0F;

				info.origin_tx_data[12] |= rssi;



//				info.history_info.Wind_Speed_AVG_Data_Array[0] = info.history_info.C_Wind_Speed_AVG_Value;
//				info.history_info.Wind_Speed_MAX_Data_Array[0] = info.history_info.C_Wind_Speed_MAX_Value;

//				info.history_info.Temperature_AVG_Data_Array[0] = info.history_info.C_Temperature_AVG_Value;


//				/* 表示已經過1小時,需進行資料移位*/
//				if ((info.history_info.TimeCount % HISTORY_UPDATE_SEC) == 0) {

//					info.history_info.TimeCount = 1;

//					for (i = 0;i < 11;i++) {

//						info.history_info.Wind_Speed_AVG_Data_Array[11 - i] = info.history_info.Wind_Speed_AVG_Data_Array[10 - i];
//						info.history_info.Wind_Speed_MAX_Data_Array[11 - i] = info.history_info.Wind_Speed_MAX_Data_Array[10 - i];

//						info.history_info.Temperature_AVG_Data_Array[11 - i] = info.history_info.Temperature_AVG_Data_Array[10 - i];
//					}

//					info.history_info.Wind_Speed_AVG_Data_Array[0] = info.history_info.C_Wind_Speed_AVG_Value;
//					info.history_info.Wind_Speed_MAX_Data_Array[0] = info.history_info.C_Wind_Speed_MAX_Value;

//					info.history_info.Temperature_AVG_Data_Array[0] = info.history_info.C_Temperature_AVG_Value;

//					info.history_info.AVG_DATA_Count = 1;
//					info.history_info.Wind_Speed_AVG_DATA_Total_Value = info.history_info.C_Wind_Speed_AVG_Value;
//					info.history_info.Temperature_AVG_DATA_Total_Value = info.history_info.C_Temperature_AVG_Value;

//				} else {
//					__NOP();
//		//			if (info.wind_speed_value >= info.history_info.C_Wind_Speed_MAX_Value)
//		//				info.history_info.C_Wind_Speed_MAX_Value = info.wind_speed_value;

//		//			info.history_info.Wind_Speed_AVG_DATA_Total_Value += info.wind_speed_value;
//		//			info.history_info.Temperature_AVG_DATA_Total_Value += info.temperature_value;
//		//
//		//			info.history_info.AVG_DATA_Count++;
//		//
//		//			info.history_info.C_Wind_Speed_AVG_Value = info.history_info.Wind_Speed_AVG_DATA_Total_Value / info.history_info.AVG_DATA_Count;
//		//			info.history_info.C_Temperature_AVG_Value = info.history_info.Temperature_AVG_DATA_Total_Value / info.history_info.AVG_DATA_Count;


//				}
			}
		} else {

//			if ((info.current_page == TEST_Page) || (info.cc1200_sleep_mode) || ((info.wr3ptx_info.wr3ptx_first_data_get == OFF) && (info.cc1200_timeout_cn <= 60))) {

//				__NOP();

//			} else {
//				cc1200_power_off();
//			}

			packetSemaphore = ISR_IDLE;
		}
	}
}



void runTX(SPI_T * spi) {

	int32_t crc_Checksum = 0;
	// Fill CRC in packet (to-do list)
//	crc_Checksum = CRC_CCITTPolyMode((uint32_t)txBuffer, txBuffer[WL_LEN_BYTE]-1); // CRC-1
//	txBuffer[txBuffer[WL_LEN_BYTE]-1] = (uint8_t)((crc_Checksum & 0x0000FF00) >> 8);
//	txBuffer[txBuffer[WL_LEN_BYTE]]   = (uint8_t)(crc_Checksum & 0x000000FF);

	txBuffer[0] = 5;
	txBuffer[1] = 1;
	txBuffer[2] = 2;
	txBuffer[3] = 3;
	txBuffer[4] = 4;
	txBuffer[5] = 5;
	txBuffer[6] = 6;
	SPI_SET_SS_HIGH(spi);
	trxSpiCmdStrobe(spi, CC120X_SIDLE);
	trxSpiCmdStrobe(spi, CC120X_SFTX); //flush TX

	// Write packet to TX FIFO
	//cc120xSpiWriteTxFifo(spi, txBuffer, (txBuffer[WL_LEN_BYTE]+1));//sizeof(txBuffer)); ERROR

	cc120xSpiWriteTxFifo(spi, (uint8_t *)txBuffer, (txBuffer[0]+1));//sizeof(txBuffer));
	// Strobe TX to send packet
	trxSpiCmdStrobe(spi, CC120X_STX);

	// Wait for interrupt that packet has been sent.
	// (Assumes the GPIO connected to the radioRxTxISR function is set to GPIOx_CFG = 0x06)



	// Clear semaphore flag
	packetSemaphore = ISR_IDLE;


//	cc1200_rx();


}

void runTX_ota(SPI_T * spi,uint8_t *ota_package) {
//void runTX_ota(SPI_T * spi) {
	uint8_t i=0;
	int32_t crc_Checksum = 0;



//	ota_package[0]= 0x3f; //always have 64 byte
//	ota_package[1]= 0;
//	ota_package[2]= 0;
//	ota_package[3]= 0;
//
//	ota_package[3]= 0xAF;

//	SYS_UnlockReg();
//	SYS->GPB_MFPH = SYS_GPB_MFPH_PB15MFP_SPI0_SS | SYS_GPB_MFPH_PB14MFP_SPI0_CLK |
//	SYS_GPB_MFPH_PB13MFP_SPI0_MISO | SYS_GPB_MFPH_PB12MFP_SPI0_MOSI;
//	SYS_LockReg();


	SPI_SET_SS_HIGH(spi);
	trxSpiCmdStrobe(spi, CC120X_SIDLE);
	trxSpiCmdStrobe(spi, CC120X_SFTX); //flush TX



	cc120xSpiWriteTxFifo(spi, (uint8_t *)ota_package, (ota_package[0]+1));
	// Strobe TX to send packet
	trxSpiCmdStrobe(spi, CC120X_STX);

	// Clear semaphore flag
	packetSemaphore = ISR_IDLE;

	CLK_SysTickDelay(6000);
	SPI0->STATUS |= SPI_STATUS_RXOVIF_Msk;
	SPI_ClearRxFIFO(SPI0);
	SPI_ClearTxFIFO(SPI0);
	CLK_SysTickDelay(6000);

	cc1200_rx();


}

void cc1200_power_off(void)
{
	cc1200_power_down();
}


void cc1200_power_down(void)
{
        SPI_SET_SS_HIGH(SPI0);
        trxSpiCmdStrobe(SPI0, CC120X_SIDLE);
        //trxSpiCmdStrobe(QSPI0, CC120X_SXOFF);
        trxSpiCmdStrobe(SPI0, CC120X_SPWD);
}


void cc1200_wake_up(void)
{
        SPI_SET_SS_HIGH(SPI0);
        __NOP();
	CLK_SysTickDelay(200);
        SPI_SET_SS_LOW(SPI0);
	CLK_SysTickDelay(1000);
        //delay_cycles(300);
       // trxSpiCmdStrobe(SPI0, CC120X_SIDLE);
        //trxSpiCmdStrobe(SPI0, CC120X_SFTX);
        //trxSpiCmdStrobe(SPI0, CC120X_SFRX);
}

