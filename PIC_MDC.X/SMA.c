/// Prolougue

//  Control EEPROM
//  Author      :   reo kashiyama

#include <xc.h>
#include "I2Clib.h"
#include "SMA.h"
#include "CommonDefine.h"
#include "OrigamiTypeDefine.h"

/// Method
/*
 *  change MSSP Mode for read SMA antenna dBm
 *	arg      :
 *	return   :   void
 *	TODO     :
 *	FIXME    :
 *	XXX      :
 */
 void changeMSSPModeToSPI(int speed_is_high){
     SSPCON1= 0x20 ;           // use RA5, RC3, 4, 5 as SPI lines (SS, SCK, SDI, SDO)
     TRISAbits.TRISA5 = UINT_FALSE;         //  SS  : out (only slave mode)
     SS = DIGITAL_HIGH;
     TRISCbits.TRISC3 = UINT_TRUE;         //  SCK : in
     TRISCbits.TRISC4 = UINT_TRUE;         //  SDI : in
     TRISCbits.TRISC5 = UINT_FALSE;         //  SDO : out
     SSPSTAT= 0xC0 ;     // sampled at the end of data, transition from active to idle
     if (speed_is_high == UINT_TRUE) {
         SSPCON1= 0x20 ;     // MSSP enable, SPI Master mode, clock : Fosc/4
     } else {
         SSPCON1= 0x22 ;     // MSSP enable, SPI Master mode, clock : Fosc/64
     }
     PIE1bits.SSPIE       = UINT_TRUE ;               // enable SPI interrupt
     PIE2bits.BCLIE       = UINT_TRUE ;               // enable bus collision
     INTCONbits.PEIE      = UINT_TRUE ;               // enbale around device interrupt
     INTCONbits.GIE       = UINT_TRUE ;               // enbale all interrupt
     PIR1bits.SSPIF       = UINT_FALSE ;               // clear SPI interrupt flag
     PIR2bits.BCLIF       = UINT_FALSE ;               // clear SPI bus collision flag
 }
 /*
  * wait complete receive (buffer full status bit is set)
  *	arg      :
  *	return   :   void
  *	TODO     :
  *	FIXME    :
  *	XXX      :
  */
  void waitSPIIdle(){
      while(!SSPSTATbits.BF);
  }
 /*
  * read SPI data
  *	arg      :  slave address
  *	return   :  SPI data
  *	TODO     :
  *	FIXME    :
  *	XXX      :
  */
  UBYTE readSPIData(UBYTE slave_address)
  {
       UBYTE data_from_slave;

       SS = DIGITAL_LOW;
       data_from_slave = SSPBUF;        //  dummy
       SSPBUF = slave_address;          //  send address data
       waitSPIIdle();
       data_from_slave = SSPBUF;        //  dummy
       SSPBUF = 0;                      //  send dummy data
       waitSPIIdle();
       SS = DIGITAL_HIGH;
       return SSPBUF;
  }
  /*
   * read SPI data
   *	arg      :  slave address, data for send
   *	return   :   void
   *	TODO     :
   *	FIXME    :
   *	XXX      :
   */
   void sendSPIData(UBYTE slave_address, UBYTE data)
   {
        UBYTE data_from_slave;

        SS = DIGITAL_LOW;
        data_from_slave = SSPBUF;        //  dummy
        SSPBUF = slave_address;          //  send address data
        waitSPIIdle();
        data_from_slave = SSPBUF;        //  dummy
        SSPBUF = data;                      //  send dummy data
        waitSPIIdle();
        data_from_slave = SSPBUF;
        SS = DIGITAL_HIGH;
        return ;
   }
 /*
  * read SMA antenna Gain (dBm)
  *	arg      :
  *	return   :   void
  *	TODO     :
  *	FIXME    :
  *	XXX      :
  */
 void readSMAAntennaGain(int SPIspeed, int I2Cspeed, UBYTE *gains, UINT offset){
     changeMSSPModeToSPI(SPIspeed);
     for (UINT i = 0; i < 16; i++) {
         UBYTE gain = readSPIData(0x00);
         gains[offset + i] = gain;
     }
     changeMSSPModeToI2C(I2Cspeed);
 }
