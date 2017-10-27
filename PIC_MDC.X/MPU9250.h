/*
 * File:   PSITG.h
 * Author: ティンダル
 *
 * Created on October 25, 2016, 5:02 AM
 */

#ifndef PSITG_H
#define	PSITG_H

#ifndef _XTAL_FREQ
 // Unless already defined assume 8MHz system frequency
 // This definition is required to calibrate __delay_us() and __delay_ms()
 #define _XTAL_FREQ 16000000       // 使用するPIC等により動作周波数値を設定する
#endif



int initIMU();
int readIMU(unsigned char *, int);

#endif	/* PSITG_H */
