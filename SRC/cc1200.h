#include "NuMicro.h"
#ifdef __cplusplus
extern "C"
{
#endif

#define W1_GPIO2_INT		PA5
#define ISR_ACTION_REQUIRED     1

//#define MF_920_7
//#define MF_920_6

//#define Main_Frequency 92070000
//#define Main_Frequency 90200000
//#define Main_Frequency 86500000

//#define ISR_ACTION_REQUIRED     1
#define PKTLEN                  64//64
#define ISR_IDLE                0
#define WL_LEN_BYTE		16
#define W1_RESET			PD15

extern volatile uint8_t cc1200_work_ch;
extern volatile uint8_t packetSemaphore;
extern void registerConfig(void);
extern void runTX(SPI_T * spi);
extern void runTX_ota(SPI_T * spi,uint8_t *ota_package);
extern __IO uint8_t cc1200_wait_rx_flag;
extern __IO uint8_t cc1200_power_on;
extern __IO uint8_t cc1200_re_setting;
extern __IO uint8_t txBuffer[PKTLEN+1];

extern volatile uint32_t freq_offset;

