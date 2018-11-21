/// Prolougue

//  interrupt file for PIC.
//  Author      :   reo kashiyama

/// Include files
#include <xc.h>
#include "Timer.h"
#include "I2Clib.h"
#include "OrigamiTypeDefine.h"
#include "CommonDefine.h"
/// Global data
const UBYTE UBYTE_13 = 0x0D;
const UBYTE UBYTE_24 = 0x18;
const UBYTE UBYTE_31 = 0x1F;
const UBYTE UBYTE_60 = 0x3C;

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
    T0CON = 0xC7;
    TMR0H = 0x00;
    TMR0L = 0x00;
}

void initTimer(void){
    globalClock.year = 0x00;
    globalClock.month = 0x00;
    globalClock.day = 0x00;
    globalClock.hour = 0x00;
    globalClock.minute = 0x00;
    globalClock.second = 0x00;
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
    if(globalClock.second == UBYTE_60){
        globalClock.second = 0x00;
        globalClock.minute += 0x01;
        if(globalClock.minute == UBYTE_60){
            globalClock.minute = 0x00;
            globalClock.hour += 0x01;
            if(globalClock.hour == UBYTE_24){
                globalClock.hour = 0x00;
                globalClock.day += 0x01;
                if(globalClock.day == UBYTE_31){
                    globalClock.day = 0x00;
                    globalClock.month += 0x01;
                    if(globalClock.month == UBYTE_13){
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
 *  sync with OBC
 *	arg      :   year, month, day, hour, minute, second
 *	return   :   void
 *	TODO     :   not yet
 *	FIXME    :   not yet
 *	XXX      :   not yet
 */
UINT syncWithOBC(UBYTE *OBCClock){
     if((OBCClock[4] >= 0x13) || (OBCClock[3] >= 0x32) || (OBCClock[2] >= 0x25) || (OBCClock[1] >= 0x60) || (OBCClock[0] >= 0x60)){
         return UINT_FALSE;
     }
     globalClock.year = OBCClock[5];
     globalClock.month = OBCClock[4];
     globalClock.day = OBCClock[3];
     globalClock.hour = OBCClock[2];
     globalClock.minute = OBCClock[1];
     globalClock.second = OBCClock[0];
     return UINT_TRUE;
 }

/*
 *  TIMER0 modole method
 *	arg      :   void
 *	return   :   void
 *	TODO     :   not yet
 *	FIXME    :   not yet
 *	XXX      :   not yet
 */

/*
void interrupt incrementTimer(void){
    if(INTCONbits.TMR0IF){
        INTCONbits.TMR0IF = 0;
        TMR0L = 0x00;
        timer_counter++;
    }
    if(timer_counter >= 31){
        //  past 1 second
        increment_globalClock();
        timer_counter = 0;
        sendCanData(&globalClock);
    }
    interruptI2C();
}
*/

void delay_us(USLONG time){
    for(USLONG i = 0; i < time ; i++){
        __delay_us(1);
    }
}

void delay_ms(USLONG time){
    for (USLONG i = 0 ; i < time ; i++){
        __delay_ms(1);
    }
}