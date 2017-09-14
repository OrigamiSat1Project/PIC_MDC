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

#define PSITG_ADRES  0x68
#define WHO          0x00
#define WHO_VALUE    0x68
#define SAMPLE_RATE  0x15
#define DLPF         0x16
#define IN_CONFIG    0x17
#define POWER_MANAGE 0x3E
#define DATA_XG      0x1B
#define IN_STAT      0x1A

int gyro_Init();
int gyro_Read(unsigned char *data, int n);

#endif	/* PSITG_H */

