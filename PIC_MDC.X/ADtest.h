/* 
 * File:   ADtest.h
 * Author: ティンダル
 *
 * Created on 2016/11/30, 21:52
 */

#ifndef ADTEST_H
#define	ADTEST_H

#ifndef _XTAL_FREQ
 #define _XTAL_FREQ 16000000       // 使用するPIC等により動作周波数値を設定する
#endif

#define AN0  ADCON0 = 0b00000001
#define AN1  ADCON0 = 0b00000101
#define AN2  ADCON0 = 0b00001001
#define AN4  ADCON0 = 0b00010001
#define AN8  ADCON0 = 0b00100001
#define AN9  ADCON0 = 0b00100101
#define AN10 ADCON0 = 0b00101001

void AD_init();
int AD_read(unsigned char *data);

#endif	/* ADTEST_H */

