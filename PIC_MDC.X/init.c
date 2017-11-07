/// Prolougue

//  initialise PIC, other device
//  Author      :   reo kashiyama

/// Include files
#include <xc.h>
#include "init.h"
#include "I2Clib.h"
#include "CAN.h"
#include "EEPROM.h"
#include "MPU9250.h"
#include "Timer.h"
#include "ADC.h"
#include "PWM.h"
#include "OrigamiTypeDefine.h"
#include "CommonDefine.h"

/// Global data


/// Method
/*
 *  initialise PIC setting
 *	arg      :   void
 *	return   :   void
 *	TODO     :   avoid double declation
 *	FIXME    :   not yet
 *	XXX      :   avoid hardcoding
*/
void initPic(void){
     OSCCONbits.IRCF0 = 1;
     OSCCONbits.IRCF1 = 1;
     OSCCONbits.IRCF2 = 1;
     // A/D setting
     ANCON0 = 0x00;
     ANCON1 = 0x00;
     // I/O setting
     TRISA = 0x00;
     TRISB = 0x00;
     TRISC = 0x00;
     // H/L setting
     PORTA = 0x00;
     PORTB = 0x00;
     PORTC = 0x00;
}

/// Method
/*
 *  wait 1ms.
 *	arg      :   void
 *	return   :   void
 *	TODO     :   not yet
 *	FIXME    :   not yet
 *	XXX      :   not yet
*/
void wait1ms(UINT num) {
    do {
        __delay_ms(1);
    } while (--num > 0);
    return;
}

/// Method
/*
 *  wait 1us. not correct for few micro second.
 *	arg      :   void
 *	return   :   void
 *	TODO     :   not yet
 *	FIXME    :   not yet
 *	XXX      :   not yet
*/
void wait1us(UINT num){
    do {
        __delay_us(1);
    } while (--num > 0);
    return;
}

/// Method
/*
 *  initialise all device on MDC board
 *	arg      :   void
 *	return   :   void
 *	TODO     :   avoid double declation
 *	FIXME    :   not yet
 *	XXX      :   avoid hardcoding, reduce init method for here
*/
void initAll(void){
    initPic();
    changeMSSPModeToI2C(1) ;
    initCan();
    initInterrupt();
    initIMU();
    initAD();
    initPWM();
}
