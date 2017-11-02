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
void I2C_IdleCheck(char mask)
{
     while (( I2C_SSPCON2 & 0x1F ) | (I2C_SSPSTAT & mask)) ;
}
/*
 *  interrupt for I2C. clear AckCheck, MSSP interrupt flag, bus collision.
 *	arg      :   void
 *	return   :   void
 */
void InterI2C(void)
{
     if (I2C_SSPIF == UINT_TRUE) {
          if (AckCheck == UINT_TRUE) {
              AckCheck = UINT_FALSE;
          }
          I2C_SSPIF = UINT_FALSE;
     }
     if (I2C_BCLIF == UINT_TRUE) {
          CollisionCheck = UINT_TRUE;
          I2C_BCLIF = UINT_FALSE;
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
    I2C_SSPCON1= 0x28 ;         //  use RC3, RC4 as I2Cline(SDA, SCL), clock :FOSC/((SSPADD + 1)*4)
    TRISCbits.TRISC4 = UINT_TRUE;       //  SDA : in
    TRISCbits.TRISC3 = UINT_TRUE;       //  SCL : in
    I2C_SSPSTAT= 0x00 ;
    if (speed_is_high == UINT_TRUE) {
        I2C_SSPADD = 0x09  ;     // SSPADD : 9 -> 400KHz
        I2C_SSPSTAT_SMP = UINT_FALSE ;    // disable slew rate control
    } else {
        I2C_SSPADD = 0x27  ;     // SSPADD : 39 -> 100KHz
        I2C_SSPSTAT_SMP = UINT_TRUE ;    // enable slew rate control
    }
    I2C_SSPIE       = UINT_TRUE ;               // enable MSSP interrupt
    I2C_BCLIE       = UINT_TRUE ;               // enable bus collision interrupt
    INTCONbits.PEIE = UINT_TRUE ;               // enable around device interrupt
    INTCONbits.GIE  = UINT_TRUE ;               // enable global interrupt
    I2C_SSPIF       = UINT_FALSE ;               // clear MSSP interrupt flag
    I2C_BCLIF       = UINT_FALSE ;               // clear bus collision flag
}
/*
 *  send start condition to slace
 *	arg      :   slave_address, rw (Read : 1 / Write : 0).
 *	return   :   acknowledge from slave.
                 0 -> succeed to receive from slave
                 1 -> failed to receive from slave
                -1 -> bus collision occured with other master
 */
int I2C_Start(int slave_address,int rw)
{
     CollisionCheck = UINT_FALSE ;
     I2C_IdleCheck(0x5) ;
     I2C_SSPCON2_SEN = UINT_TRUE ;
     I2C_IdleCheck(0x5) ;
     if (CollisionCheck == UINT_TRUE) return -1 ;
     AckCheck = UINT_TRUE ;
     I2C_SSPBUF = (char)((slave_address<<1)+rw);
     while (AckCheck);
     if (CollisionCheck == UINT_TRUE) return -1 ;
     return I2C_SSPCON2_ACKSTAT ;
}
/*
 *  send repeat start condition to slace
 *	arg      :   slave_address, rw (Read : 1 / Write : 0).
 *	return   :   acknowledge from slave.
                 0 -> succeed to receive from slave
                 1 -> failed to receive from slave
                -1 -> bus collision occured with other master
 */
int I2C_rStart(int slave_address,int rw)
{
     CollisionCheck = UINT_FALSE ;
     I2C_IdleCheck(0x5) ;
     I2C_SSPCON2_RSEN = UINT_TRUE ;
     I2C_IdleCheck(0x5) ;
     if (CollisionCheck == UINT_TRUE) return -1 ;
     AckCheck = UINT_TRUE ;
     I2C_SSPBUF = (char)((slave_address<<1)+rw);
     while (AckCheck);
     if (CollisionCheck == UINT_TRUE) return -1;
     return I2C_SSPCON2_ACKSTAT;
}
/*
 *  send stop condition to slace
 *	arg      :
 *	return   :   acknowledge from slave.
                 0 -> succeed to receive from slave
                -1 -> bus collision occured with other master
 */
int I2C_Stop()
{
     CollisionCheck = UINT_FALSE ;
     I2C_IdleCheck(0x5) ;
     I2C_SSPCON2_PEN = UINT_TRUE ;
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
int I2C_Send(char data_to_send)
{
     CollisionCheck = UINT_FALSE ;
     I2C_IdleCheck(0x5) ;
     if (CollisionCheck == UINT_TRUE) return -1;
     AckCheck = UINT_TRUE;
     I2C_SSPBUF = data_to_send;
     while (AckCheck);
     if (CollisionCheck == UINT_TRUE) return -1;
     return I2C_SSPCON2_ACKSTAT;
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
int I2C_Receive(int ack_to_slave)
{
     int data_from_slave ;

     CollisionCheck = UINT_FALSE ;
     I2C_IdleCheck(0x5) ;
     I2C_SSPCON2_RCEN = UINT_TRUE;      //  enable receive from slave
     I2C_IdleCheck(0x4) ;
     if (CollisionCheck == UINT_TRUE) return -1 ;
     data_from_slave = I2C_SSPBUF;
     I2C_IdleCheck(0x5) ;
     if (CollisionCheck == UINT_TRUE) return -1 ;
     I2C_SSPCON2_ACKDT = ack_to_slave;
     I2C_SSPCON2_ACKEN = UINT_TRUE;
     return data_from_slave;
}
