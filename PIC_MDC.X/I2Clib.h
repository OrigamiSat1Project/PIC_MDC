/*
 * File:   I2Clib.h
 * Author: ティンダル
 *
 * Created on 2016/10/24, 13:54
 */

#ifndef I2CLIB_H
#define	I2CLIB_H

// 定数の定義
#define ACK   0
#define NOACK 1
#define RW_0  0
#define RW_1  1

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

void InterI2C( void ) ;
void changeMSSPModeToI2C(int) ;
int  I2C_Start(int ,int ) ;
int  I2C_rStart(int ,int ) ;
int  I2C_Stop( void ) ;
int  I2C_Send(char ) ;
int  I2C_Receive(int ) ;

#endif	/* I2CLIB_H */
