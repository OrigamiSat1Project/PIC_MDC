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
#include "ITG3701.h"
#include "adxl345.h"
#include "ICM20601.h"
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
     OSCCONbits.IRCF0 = UINT_TRUE;
     OSCCONbits.IRCF1 = UINT_TRUE;
     OSCCONbits.IRCF2 = UINT_TRUE;

     // A/D setting
     ANCON0bits.ANSEL0 = ANSEL_ANALOG;
     ANCON0bits.ANSEL1 = ANSEL_ANALOG;
     ANCON0bits.ANSEL2 = ANSEL_ANALOG;
     ANCON0bits.ANSEL3 = ANSEL_DIGITAL;
     ANCON0bits.ANSEL4 = ANSEL_DIGITAL;

     ANCON1bits.ANSEL8 = ANSEL_ANALOG;
     ANCON1bits.ANSEL9 = ANSEL_ANALOG;
     ANCON1bits.ANSEL10= ANSEL_ANALOG;

     // I/O setting
     TRISAbits.TRISA0 = TRIS_IN;
     TRISAbits.TRISA1 = TRIS_IN;
     TRISAbits.TRISA2 = TRIS_IN;
     TRISAbits.TRISA3 = TRIS_IN;
     TRISAbits.TRISA5 = TRIS_OUT;
     TRISAbits.TRISA6 = TRIS_OUT;
     TRISAbits.TRISA7 = TRIS_IN;

     TRISBbits.TRISB0 = TRIS_IN;
     TRISBbits.TRISB1 = TRIS_IN;
     TRISBbits.TRISB2 = TRIS_OUT;
     TRISBbits.TRISB3 = TRIS_OUT;
     TRISBbits.TRISB4 = TRIS_IN;
     TRISBbits.TRISB5 = TRIS_OUT;
     TRISBbits.TRISB6 = TRIS_OUT;
     TRISBbits.TRISB7 = TRIS_IN;

     TRISCbits.TRISC0 = TRIS_OUT;
     TRISCbits.TRISC1 = TRIS_OUT;
     TRISCbits.TRISC2 = TRIS_OUT;
     TRISCbits.TRISC3 = TRIS_IN;
     TRISCbits.TRISC4 = TRIS_IN;
     TRISCbits.TRISC5 = TRIS_OUT;
     TRISCbits.TRISC6 = TRIS_OUT;
     TRISCbits.TRISC7 = TRIS_IN;
     // H/L setting. set all low.
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
    //initIMU();
    initITG();
    initADXL();
    initIMU();
    initAD();
    initPWM();
}
