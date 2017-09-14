/* 
 * File:   I2cR.h
 * Author: ティンダル
 *
 * Created on 2016/11/30, 22:30
 */

#ifndef I2CR_H
#define	I2CR_H

#ifndef _XTAL_FREQ
 
 #define _XTAL_FREQ 16000000       // 使用するPIC等により動作周波数値を設定する
#endif

// Ｉ２Ｃのアドレス
#define AD5252_ADRES 0x2C       // AD5252のアドレス>>1
// レジスタのアドレス
#define RDAC1         0x21        //wiper setting
#define RDAC3         0x23        //wiper setting

int changeR();

#endif	/* I2CR_H */

