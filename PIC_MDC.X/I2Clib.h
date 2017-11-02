/*
 * File:   I2Clib.h
 * Author: ƒeƒBƒ“ƒ_ƒ‹
 *
 * Created on 2016/10/24, 13:54
 */

#ifndef I2CLIB_H
#define	I2CLIB_H

void InterI2C( void ) ;
void changeMSSPModeToI2C(int) ;
int  I2C_Start(int ,int ) ;
int  I2C_rStart(int ,int ) ;
int  I2C_Stop( void ) ;
int  I2C_Send(char ) ;
int  I2C_Receive(int ) ;

#endif	/* I2CLIB_H */
