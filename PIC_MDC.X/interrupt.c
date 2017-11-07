/// Prolougue

//  interrupt file for PIC.
//  Author      :   reo kashiyama

/// Include files
#include <xc.h>
#include "interrupt.h"
#include "I2Clib.h"
#include "OrigamiTypeDefine.h"
#include "CommonDefine.h"
/// Global data


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
    globalClock.year = 0x00;
    globalClock.month = 0x00;
    globalClock.day = 0x00;
    globalClock.hour = 0x00;
    globalClock.minute = 0x00;
    globalClock.second = 0x00;
    INTCON = 0xE0;
    T0CON = 0xC7;
    TMR0H = 0x00;
    TMR0L = 0x00;
}

/*
 *  increment global count
 *	arg      :   void
 *	return   :   void
 *	TODO     :   not yet
 *	FIXME    :   can not 29days month,,,
 *	XXX      :   not yet
 */
void increment_globalClock(void){
    globalClock.second += 0x01;
    if(globalClock.second == 0x60){
        globalClock.second = 0x00;
        globalClock.minute += 0x01;
        if(globalClock.minute == 0x60){
            globalClock.minute = 0x00;
            globalClock.hour += 0x01;
            if(globalClock.hour == 0x24){
                globalClock.hour = 0x00;
                globalClock.day += 0x01;
                if(globalClock.day == 31){
                    globalClock.day = 0x00;
                    globalClock.month += 0x01;
                    if(globalClock.month == 0x13){
                        globalClock.month = 0x00;
                        globalClock.year += 0x01;
                    }
                }
            }
        }
    }
    return;
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
        timer_counter++;
    }
    if(timer_counter >= 62){
        //  past 1 second
        increment_globalClock();
        timer_counter = 0;
    }
    interruptI2C();
}
