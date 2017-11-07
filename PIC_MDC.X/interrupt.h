/// Prolougue

//  interrupt file for PIC.
//  Author      :   reo kashiyama

/// Include files
#include "OrigamiTypeDefine.h"
#include "CommonDefine.h"

#ifndef INTERRUPT_H
#define	INTERRUPT_H
int timer_counter = 0;

//  XXX     :   this is not good timer declation is here
//UDWORD globalCount;
struct dateStruct{
    UBYTE year;
    UBYTE month;
    UBYTE day;
    UBYTE hour;
    UBYTE minute;
    UBYTE second;
};
struct dateStruct globalClock;

void initInterrupt(void);
void interrupt incrementTimer(void);

#endif	/* INTERRUPT_H */
