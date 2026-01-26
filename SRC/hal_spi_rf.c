#include <stdint.h>
#include "hal_spi_rf.h"
#include "NuMicro.h"
//#include "cc1200_reg_config.h"
//#include "spi.h"

__IO uint8_t view[100] = {0};
/*******************************************************************************
 * @fn          trxSpiCmdStrobe
 *
 * @brief       Send command strobe to the radio. Returns status byte read
 *              during transfer of command strobe. Validation of provided
 *              is not done. Function assumes chip is ready.
 *
 * input parameters
 *
 * @param       cmd - command strobe
 *
 * output parameters
 *
 * @return      status byte
 */
//rfStatus_t trx0SpiCmdStrobe(uint8_t cmd)
rfStatus_t trxSpiCmdStrobe(SPI_T *spi, uint8_t cmd)
{
	uint8_t rc;

	SPI_SET_SS_LOW(spi);
	SPI_WRITE_TX(spi, cmd);
//	SPI_TRIGGER(spi);
//	SPI_ENABLE(spi);
	while(SPI_IS_BUSY(spi));

	rc=SPI_READ_RX(spi);
	SPI_SET_SS_HIGH(spi);
	return(rc);
}

/*******************************************************************************
 * @fn          trx8BitRegAccess
 *
 * @brief       This function performs a read or write from/to a 8bit register
 *              address space. The function handles burst and single read/write
 *              as specfied in addrByte. Function assumes that chip is ready.
 *
 * input parameters
 *
 * @param       accessType - Specifies if this is a read or write and if it's
 *                           a single or burst access. Bitmask made up of
 *                           RADIO_BURST_ACCESS/RADIO_SINGLE_ACCESS/
 *                           RADIO_WRITE_ACCESS/RADIO_READ_ACCESS.
 * @param       addrByte - address byte of register.  0~2e
 * @param       pData    - data array
 * @param       len      - Length of array to be read(TX)/written(RX)
 *
 * output parameters
 *
 * @return      chip status
 */
rfStatus_t trx8BitRegAccess(SPI_T *spi, uint8_t accessType, uint8_t addrByte, uint8_t *pData, uint16_t len)
{
  uint8_t readValue;
	uint16_t i;

  /* Pull CS_N low  */
  SPI_SET_SS_LOW(spi);
  /* send register address byte */
  SPI_WRITE_TX(spi, accessType|addrByte);
//  SPI_TRIGGER(spi);
//SPI_ENABLE(spi);
	while(SPI_IS_BUSY(spi));	//¥d¦í

	readValue=SPI_READ_RX(spi);   //cc1200 status
	
	if(accessType & RADIO_READ_ACCESS)
	{
		if( accessType & RADIO_BURST_ACCESS)
		{
			for(i=0; i<len; i++){
//				SPI_TRIGGER(spi);
				//SPI_ENABLE(spi);
				SPI_WRITE_TX(spi,0);
	  		while(SPI_IS_BUSY(spi));
				view[i]=*pData=SPI_READ_RX(spi);
				pData++;
			}
		}else{
//			SPI_TRIGGER(spi);
				//SPI_ENABLE(spi);
			SPI_WRITE_TX(spi,0);
			while(SPI_IS_BUSY(spi));
			*pData=SPI_READ_RX(spi);
		}
	}else{
		if( accessType & RADIO_BURST_ACCESS)
		{
			for(i=0; i<len; i++){
				SPI_WRITE_TX(spi, *pData);
//				SPI_TRIGGER(spi);
				//SPI_ENABLE(spi);
				while(SPI_IS_BUSY(spi));
				__NOP();
        pData++;
			}
		}else{
			SPI_WRITE_TX(spi, *pData);
//			SPI_TRIGGER(spi);
//			SPI_ENABLE(spi);
			while(SPI_IS_BUSY(spi));
		}
	}
	SPI_SET_SS_HIGH(spi);
  /* return the status byte value */
  return(readValue);
}

/******************************************************************************
 * @fn          trx16BitRegAccess
 *
 * @brief       This function performs a read or write in the extended adress
 *              space of CC112X.
 *
 * input parameters
 *
 * @param       accessType - Specifies if this is a read or write and if it's
 *                           a single or burst access. Bitmask made up of
 *                           RADIO_BURST_ACCESS/RADIO_SINGLE_ACCESS/
 *                           RADIO_WRITE_ACCESS/RADIO_READ_ACCESS.
 * @param       extAddr - Extended register space address = 0x2F.
 * @param       regAddr - Register address in the extended address space.
 * @param       *pData  - Pointer to data array for communication
 * @param       len     - Length of bytes to be read/written from/to radio
 *
 * output parameters
 *
 * @return      rfStatus_t
 */
rfStatus_t trx16BitRegAccess(SPI_T *spi, uint8_t accessType, uint8_t extAddr, uint8_t regAddr, uint8_t *pData, uint8_t len)
{
	uint8_t readValue;
	uint16_t i;

  /* Pull CS_N low  */
  SPI_SET_SS_LOW(spi);
  /* send register address byte */
  SPI_WRITE_TX(spi, accessType|extAddr);
//  SPI_TRIGGER(spi);
//	SPI_ENABLE(spi);
	while(SPI_IS_BUSY(spi));
	readValue=SPI_READ_RX(spi);   //cc1200 status

  SPI_WRITE_TX(spi, regAddr);
//				while(SPI_IS_BUSY(spi));
//				*pData=SPI_READ_RX(spi);	
//  SPI_TRIGGER(spi);
//	SPI_ENABLE(spi);
	while(SPI_IS_BUSY(spi));

	if(accessType & RADIO_READ_ACCESS)
	{
		if( accessType & RADIO_BURST_ACCESS)
		{
			for(i=0; i<len; i++){
//				SPI_TRIGGER(spi);
//				SPI_ENABLE(spi);
				SPI_WRITE_TX(spi,0);
				while(SPI_IS_BUSY(spi));
				*pData=SPI_READ_RX(spi);
				pData++;
			}
		}else{
//			SPI_TRIGGER(spi);
//			SPI_ENABLE(spi);
			SPI_WRITE_TX(spi,0);
			while(SPI_IS_BUSY(spi));
			*pData=SPI_READ_RX(spi);
		}
	}else{
		if( accessType & RADIO_BURST_ACCESS)
		{
			for(i=0; i<len; i++){
				SPI_WRITE_TX(spi, *pData);
//				SPI_TRIGGER(spi);
//				SPI_ENABLE(spi);
				while(SPI_IS_BUSY(spi));
				__NOP();
         pData++;
			}
		}else{
			SPI_WRITE_TX(spi, *pData);
//			SPI_TRIGGER(spi);
//			SPI_ENABLE(spi);
			while(SPI_IS_BUSY(spi));
		}
	}
	SPI_SET_SS_HIGH(spi);
  /* return the status byte value */
  return(readValue);
}
