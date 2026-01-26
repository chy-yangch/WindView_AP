#include <stdint.h>
#include "NuMicro.h"

/******************************************************************************
 * TYPEDEFS
 */

/*typedef struct
{
  uint16_t  addr;
  uint8_t   data;
}registerSetting_t;*/

typedef uint8_t rfStatus_t;

rfStatus_t trx8BitRegAccess(SPI_T *spi, uint8_t accessType, uint8_t addrByte, uint8_t *pData, uint16_t len);
rfStatus_t trxSpiCmdStrobe(SPI_T *spi, uint8_t cmd);

/* CC112X specific prototype function */
rfStatus_t trx16BitRegAccess(SPI_T *spi, uint8_t accessType, uint8_t extAddr, uint8_t regAddr, uint8_t *pData, uint8_t len);

/******************************************************************************
 * CONSTANTS
 */

#define RADIO_BURST_ACCESS   0x40
#define RADIO_SINGLE_ACCESS  0x00
#define RADIO_READ_ACCESS    0x80
#define RADIO_WRITE_ACCESS   0x00


/* Bit fields in the chip status byte */
#define STATUS_CHIP_RDYn_BM             0x80
#define STATUS_STATE_BM                 0x70
#define STATUS_FIFO_BYTES_AVAILABLE_BM  0x0F
