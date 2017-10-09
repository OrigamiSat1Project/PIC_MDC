/*
 * File:   init.h
 * Author: ƒeƒBƒ“ƒ_ƒ‹
 *
 * Created on 2016/10/25, 2:52
 */
#include "OrigamiTypeDefine.h"
#include "CommonDefine.h"

#ifndef INIT_H
#define	INIT_H

//  TODO    :   avoid hardcoding
#define LED_ON PORTBbits.RB7 = DIGITAL_HIGH
#define LED_OFF PORTBbits.RB7 = DIGITAL_LOW
#define SW_ON PORTCbits.RC0 = DIGITAL_HIGH
#define SW_OFF PORTCbits.RC0 = DIGITAL_LOW

void wait1ms(UINT);
void wait1us(UINT);
void initAll(void);

#endif	/* INIT_H */
