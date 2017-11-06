/// Prolougue

//  Control EEPROM
//  Author      :   reo kashiyama

#include <xc.h>
#include "I2Clib.h"
#include "CommonDefine.h"
#include "OrigamiTypeDefine.h"

#define I2C_SSPCON1         SSPCON1
#define I2C_SSPCON2         SSPCON2
#define I2C_SSPSTAT         SSPSTAT
#define I2C_SSPADD          SSPADD
#define I2C_SSPBUF          SSPBUF
#define I2C_SSPIF           PIR1bits.SSPIF
#define I2C_SSPIE           PIE1bits.SSPIE
#define I2C_BCLIF           PIR2bits.BCLIF
#define I2C_BCLIE           PIE2bits.BCLIE
#define I2C_SSPSTAT_SMP     SSPSTATbits.SMP
#define I2C_SSPCON2_SEN     SSPCON2bits.SEN
#define I2C_SSPCON2_RSEN    SSPCON2bits.RSEN
#define I2C_SSPCON2_PEN     SSPCON2bits.PEN
#define I2C_SSPCON2_RCEN    SSPCON2bits.RCEN
#define I2C_SSPCON2_ACKSTAT SSPCON2bits.ACKSTAT
#define I2C_SSPCON2_ACKDT   SSPCON2bits.ACKDT
#define I2C_SSPCON2_ACKEN   SSPCON2bits.ACKEN

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
