/*
 * File:   PWM_LED.h
 * Author: ティンダル
 *
 * Created on 2016/12/05, 14:36
 */

#ifndef PWM_LED_H
#define	PWM_LED_H

#ifndef _XTAL_FREQ
 #define _XTAL_FREQ 16000000       // 使用するPIC等により動作周波数値を設定する
#endif

int initPWM(void);
int pwmLED_ON(int, int);
void rLED_ON(void);
void rLED_OFF(void);

#endif	/* PWM_LED_H */
