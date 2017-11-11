#include <xc.h>
#include "I2Clib.h"
#include "CommonDefine.h"
#include "OrigamiTypeDefine.h"

/// Global data
int AckCheck ;
int CollisionCheck ;

/*
 *  wait Idle mode on I2C
 *	arg      :   mask
 *	return   :   void
 */
void waitI2CIdle(char mask)
{
     while (( SSPCON2 & 0x1F ) | (SSPSTAT & mask)) ;
}
/*
 *  interrupt for I2C. clear AckCheck, MSSP interrupt flag, bus collision.
 *	arg      :   void
 *	return   :   void
 */
void interruptI2C(void)
{
     if (PIR1bits.SSPIF == UINT_TRUE) {
          if (AckCheck == UINT_TRUE) {
              AckCheck = UINT_FALSE;
          }
          PIR1bits.SSPIF = UINT_FALSE;
     }
     if (PIR2bits.BCLIF == UINT_TRUE) {
          CollisionCheck = UINT_TRUE;
          PIR2bits.BCLIF = UINT_FALSE;
     }
}
/*
 *  change MSSP Mode for read SMA antenna dBm
 *	arg      :   spped_is_high. high : 400kHz, low : 100kHz
 *	return   :   void
 *	XXX      :   400kHz, but actually speed of limit is 250Hz
 */
void changeMSSPModeToI2C(int speed_is_high)
{
    SSPCON1= 0x28 ;         //  use RC3, RC4 as I2Cline(SDA, SCL), clock :FOSC/((SSPADD + 1)*4)
    SSPSTAT= 0x00 ;
    if (speed_is_high == UINT_TRUE) {
        SSPADD = 0x09  ;     // SSPADD : 9 -> 400KHz
        SSPSTATbits.SMP = UINT_FALSE ;    // disable slew rate control
    } else {
        SSPADD = 0x27  ;     // SSPADD : 39 -> 100KHz
        SSPSTATbits.SMP = UINT_TRUE ;    // enable slew rate control
    }
    PIE1bits.SSPIE       = UINT_TRUE ;               // enable MSSP interrupt
    PIE2bits.BCLIE       = UINT_TRUE ;               // enable bus collision interrupt
    INTCONbits.PEIE = UINT_TRUE ;               // enable around device interrupt
    INTCONbits.GIE  = UINT_TRUE ;               // enable global interrupt
    PIR1bits.SSPIF       = UINT_FALSE ;               // clear MSSP interrupt flag
    PIR2bits.BCLIF       = UINT_FALSE ;               // clear bus collision flag
}

/*
 *  send start condition to slace
 *	arg      :   slave_address, rw (Read : 1 / Write : 0).
 *	return   :   acknowledge from slave.
                 0 -> succeed to receive from slave
                 1 -> failed to receive from slave
                -1 -> bus collision occured with other master
 */
int startI2C(int slave_address,int rw)
{
     CollisionCheck = UINT_FALSE ;
     waitI2CIdle(0x5) ;
     SSPCON2bits.SEN = UINT_TRUE ;
     waitI2CIdle(0x5) ;
     if (CollisionCheck == UINT_TRUE) return -1 ;
     AckCheck = UINT_TRUE ;
     SSPBUF = (char)((slave_address<<1)+rw);
     while (AckCheck);
     if (CollisionCheck == UINT_TRUE) return -1 ;
     return SSPCON2bits.ACKSTAT;
}
/*
 *  send repeat start condition to slace
 *	arg      :   slave_address, rw (Read : 1 / Write : 0).
 *	return   :   acknowledge from slave.
                 0 -> succeed to receive from slave
                 1 -> failed to receive from slave
                -1 -> bus collision occured with other master
 */
int restartI2C(int slave_address,int rw)
{
     CollisionCheck = UINT_FALSE ;
     waitI2CIdle(0x5) ;
     SSPCON2bits.RSEN = UINT_TRUE ;
     waitI2CIdle(0x5) ;
     if (CollisionCheck == UINT_TRUE) return -1 ;
     AckCheck = UINT_TRUE ;
     SSPBUF = (char)((slave_address<<1)+rw);
     while (AckCheck);
     if (CollisionCheck == UINT_TRUE) return -1;
     return SSPCON2bits.ACKSTAT;
}
/*
 *  send stop condition to slace
 *	arg      :
 *	return   :   acknowledge from slave.
                 0 -> succeed to receive from slave
                -1 -> bus collision occured with other master
 */
int stopI2C()
{
     CollisionCheck = UINT_FALSE ;
     waitI2CIdle(0x5) ;
     SSPCON2bits.PEN = UINT_TRUE ;
     if (CollisionCheck == UINT_TRUE) return -1 ;
     else                     return  UINT_FALSE ;
}
/*
 *  send data to slave
 *	arg      :   data to send.
 *	return   :   acknowledge from slave.
                 0 -> succeed to receive from slave
                 1 -> failed to receive from slave
                -1 -> bus collision occured with other master
 */
int sendI2CData(char data_to_send)
{
     CollisionCheck = UINT_FALSE ;
     waitI2CIdle(0x5) ;
     if (CollisionCheck == UINT_TRUE) return -1;
     AckCheck = UINT_TRUE;
     SSPBUF = data_to_send;
     while (AckCheck);
     if (CollisionCheck == UINT_TRUE) return -1;
     return SSPCON2bits.ACKSTAT;
}
/*
 *  receive data from slave
 *	arg      :   ack to send to slave
                 0 -> return ack to slave
                 1 -> return noack to slave
 *	return   :   acknowledge from slave.
                 0 -> succeed to receive from slave
                 1 -> failed to receive from slave
                -1 -> bus collision occured with other master
 */
int readI2CData(int ack_to_slave)
{
     int data_from_slave ;

     CollisionCheck = UINT_FALSE ;
     waitI2CIdle(0x5) ;
     SSPCON2bits.RCEN = UINT_TRUE;      //  enable receive from slave
     waitI2CIdle(0x4) ;
     if (CollisionCheck == UINT_TRUE) return -1 ;
     data_from_slave = SSPBUF;
     waitI2CIdle(0x5) ;
     if (CollisionCheck == UINT_TRUE) return -1 ;
     SSPCON2bits.ACKDT = ack_to_slave;
     SSPCON2bits.ACKEN = UINT_TRUE;
     return data_from_slave;
}
