/* 
 * File:   init.h
 * Author: ティンダル
 *
 * Created on 2016/10/25, 2:52
 */

#ifndef INIT_H
#define	INIT_H

#ifndef _XTAL_FREQ
 #define _XTAL_FREQ 16000000       // 使用するPIC等により動作周波数値を設定する
#endif

#define LED_ON PORTBbits.RB7 = 1
#define LED_OFF PORTBbits.RB7 = 0 
#define SW_ON PORTCbits.RC0 = 1
#define SW_OFF PORTCbits.RC0 = 0

void Wait_1ms(int num);
void Wait_1us(int num);
void all_init();

#endif	/* INIT_H */

