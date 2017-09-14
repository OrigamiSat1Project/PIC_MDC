/* 
 * File:   HMC.h
 * Author: ティンダル
 *
 * Created on October 25, 2016, 4:13 AM
 */

#ifndef HMC_H
#define	HMC_H

#ifndef _XTAL_FREQ
 #define _XTAL_FREQ 16000000       // 使用するPIC等により動作周波数値を設定する
#endif

#define HMC_ADRES 0x1E
#define CONFIG_A  0x00
#define CONFIG_B  0x01
#define MODE_REG  0x02
#define DATA_XM   0x03
#define ID_REGA   0x10
#define ID_REGA_VALUE   0x48
#define ID_STAT 0x09

int magnet_Init();
int magnet_Read(unsigned char *data);

#endif	/* HMC_H */

