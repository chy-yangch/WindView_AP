#include <stdint.h>
#include "hal_spi_rf.h"
#include "cc120x_spi.h"
#include "NuMicro.h"

/******************************************************************************
 * @fn          cc120xSpiReadReg
 *
 * @brief       Read value(s) from config/status/extended radio register(s).
 *              If len  = 1: Reads a single register
 *              if len != 1: Reads len register values in burst mode 
 *
 * input parameters
 *
 * @param       addr   - address of first register to read
 * @param       *pData - pointer to data array where read bytes are saved
 * @param       len   - number of bytes to read
 *
 * output parameters
 *
 * @return      rfStatus_t
 */
rfStatus_t cc120xSpiReadReg(SPI_T *spi, uint16_t addr, uint8_t *pData, uint8_t len)
{
  uint8_t tempExt  = (uint8_t)(addr>>8);
  uint8_t tempAddr = (uint8_t)(addr & 0x00FF);
  uint8_t rc;
  
  /* Checking if this is a FIFO access -> returns chip not ready  */
//  if((CC120X_SINGLE_TXFIFO<=tempAddr)&&(tempExt==0)) return STATUS_CHIP_RDYn_BM;
  
  /* Decide what register space is accessed */
  if(!tempExt)
  {
    rc = trx8BitRegAccess( spi,(RADIO_BURST_ACCESS|RADIO_READ_ACCESS),tempAddr,pData,len);
  }
  else if (tempExt == 0x2F)
  {
    rc = trx16BitRegAccess( spi, (RADIO_SINGLE_ACCESS|RADIO_READ_ACCESS),tempExt,tempAddr,pData,1);
  }
  return (rc);
}

/******************************************************************************
 * @fn          cc120xSpiWriteReg
 *
 * @brief       Write value(s) to config/status/extended radio register(s).
 *              If len  = 1: Writes a single register
 *              if len  > 1: Writes len register values in burst mode 
 *
 * input parameters
 *
 * @param       addr   - address of first register to write
 * @param       *pData - pointer to data array that holds bytes to be written
 * @param       len    - number of bytes to write
 *
 * output parameters
 *
 * @return      rfStatus_t
 */
rfStatus_t cc120xSpiWriteReg(SPI_T * spi, uint16_t addr, uint8_t *pData, uint8_t len)
{
  uint8_t tempExt  = (uint8_t)(addr>>8);
  uint8_t tempAddr = (uint8_t)(addr & 0x00FF);
  uint8_t rc;
  
  /* Checking if this is a FIFO access - returns chip not ready */
  if((CC120X_SINGLE_TXFIFO<=tempAddr)&&(tempExt==0)) return STATUS_CHIP_RDYn_BM;
  	
  /* Decide what register space is accessed */  
  if(!tempExt)
  {
    rc = trx8BitRegAccess( spi,(RADIO_BURST_ACCESS|RADIO_WRITE_ACCESS),tempAddr,pData,len);
  }  else if (tempExt == 0x2F)  {
    rc = trx16BitRegAccess( spi, (RADIO_BURST_ACCESS|RADIO_WRITE_ACCESS),tempExt,tempAddr,pData,len);
  }
  return (rc);
}

/*******************************************************************************
 * @fn          cc120xSpiWriteTxFifo
 *
 * @brief       Write pData to radio transmit FIFO.
 *
 * input parameters
 *
 * @param       *pData - pointer to data array that is written to TX FIFO
 * @param       len    - Length of data array to be written
 *
 * output parameters
 *
 * @return      rfStatus_t
 */
rfStatus_t cc120xSpiWriteTxFifo(SPI_T * spi, uint8_t *pData, uint8_t len)
{
  uint8_t rc;
  rc = trx8BitRegAccess(  spi, RADIO_WRITE_ACCESS|RADIO_BURST_ACCESS, CC120X_BURST_TXFIFO, pData, len);
  return (rc);
}

/*******************************************************************************
 * @fn          cc120xSpiReadRxFifo
 *
 * @brief       Reads RX FIFO values to pData array
 *
 * input parameters
 *
 * @param       *pData - pointer to data array where RX FIFO bytes are saved
 * @param       len    - number of bytes to read from the RX FIFO
 *
 * output parameters
 *
 * @return      rfStatus_t
 */
rfStatus_t cc120xSpiReadRxFifo(SPI_T * spi, uint8_t * pData, uint8_t len)
{
  uint8_t rc;
//  rc = trx8BitRegAccess(spi, 0x80,CC120X_BURST_RXFIFO, pData, len);
  rc = trx8BitRegAccess(spi, RADIO_READ_ACCESS|RADIO_BURST_ACCESS ,CC120X_BURST_RXFIFO, pData, len);
  return (rc);
}

/******************************************************************************
 * @fn      cc120xGetTxStatus(void)
 *          
 * @brief   This function transmits a No Operation Strobe (SNOP) to get the 
 *          status of the radio and the number of free bytes in the TX FIFO.
 *          
 *          Status byte:
 *          
 *          ---------------------------------------------------------------------------
 *          |          |            |                                                 |
 *          | CHIP_RDY | STATE[2:0] | FIFO_BYTES_AVAILABLE (free bytes in the TX FIFO |
 *          |          |            |                                                 |
 *          ---------------------------------------------------------------------------
 *
 *
 * input parameters
 *
 * @param   none
 *
 * output parameters
 *         
 * @return  rfStatus_t 
 *
 */
rfStatus_t cc120xGetTxStatus(SPI_T * spi)
{
    return(trxSpiCmdStrobe(spi, CC120X_SNOP));
}

/******************************************************************************
 *
 *  @fn       cc120xGetRxStatus(void)
 *
 *  @brief   
 *            This function transmits a No Operation Strobe (SNOP) with the 
 *            read bit set to get the status of the radio and the number of 
 *            available bytes in the RXFIFO.
 *            
 *            Status byte:
 *            
 *            --------------------------------------------------------------------------------
 *            |          |            |                                                      |
 *            | CHIP_RDY | STATE[2:0] | FIFO_BYTES_AVAILABLE (available bytes in the RX FIFO |
 *            |          |            |                                                      |
 *            --------------------------------------------------------------------------------
 *
 *
 * input parameters
 *
 * @param     none
 *
 * output parameters
 *         
 * @return    rfStatus_t 
 *
 */
rfStatus_t cc120xGetRxStatus(SPI_T * spi)
{
    return(trxSpiCmdStrobe(spi, CC120X_SNOP | RADIO_READ_ACCESS));
}

/*******************************************************************************
 * @fn          perCC120xRead8BitRssi
 *    
 * @brief       Reads MSB RSSI value from register, converts the dBm value to
 *              decimal and adjusts it according to RSSI offset
 *
 * input parameters
 *
 * @param       none
 *
 * output parameters
 *
 * @return      decimal RSSI value corrected for RSSI offset
 */ 
int8_t perCC120xRead8BitRssi(SPI_T *spi)
{
  uint8_t rssi2compl,rssiValid;
  int16_t rssiConverted;
  
  cc120xSpiReadReg(spi, CC120X_RSSI0, &rssiValid,1);
  if(rssiValid & 0x01)
  {
    /* Read RSSI from MSB register */
    cc120xSpiReadReg(spi, CC120X_RSSI1, &rssi2compl,1);
    rssiConverted = (int16_t)((int8_t)rssi2compl);
  }
  return rssiConverted;
}
