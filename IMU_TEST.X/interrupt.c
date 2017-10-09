/// Prolougue

//  interrupt file for PIC.
//  Author      :   reo kashiyama

/// Include files
#include <xc.h>
#include "interrupt.h"
#include "I2Clib.h"
#include "OrigamiTypeDefine.h"
#include "CommonDefine.h"

/// Method
/*
 *  initialise PIC interrupt setting
 *	arg      :   void
 *	return   :   void
 *	TODO     :   enhance comment
 *	FIXME    :   not yet
 *	XXX      :   avoid hardcoding
 */
void initInterrupt(void){
    INTCON = 0xE0;
    T0CON = 0xC7;   //0xc7
    TMR0H = 0x00;
    TMR0L = 0x00;
}
/*
 *  TIMER0 modole method
 *	arg      :   void
 *	return   :   void
 *	TODO     :   not yet
 *	FIXME    :   not yet
 *	XXX      :   not yet
 */
void interrupt incrementTimer(void){
    if(INTCONbits.TMR0IF){
        INTCONbits.TMR0IF = 0;
        TMR0L = 0x00;
        globalCount++;
    }
    InterI2C();
}
