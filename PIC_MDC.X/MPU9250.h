/*
 * File:   MPU9250.h
 * Author: reo kashiyama
 *
 * Created on October 25, 2016, 5:02 AM
 */

#ifndef PSITG_H
#define	PSITG_H

#ifndef _XTAL_FREQ
 // Unless already defined assume 8MHz system frequency
 // This definition is required to calibrate __delay_us() and __delay_ms()
 #define _XTAL_FREQ 16000000       // Žg—p‚·‚éPIC“™‚É‚æ‚è“®ìŽü”g”’l‚ðÝ’è‚·‚é
#endif

int initIMU();
int readIMU(unsigned char *, int);
void readIMUSequence(UBYTE);

#endif	/* PSITG_H */
