/// Prolougue

//  interrupt file for PIC.
//  Author      :   reo kashiyama

/// Include files
#include "OrigamiTypeDefine.h"
#include "CommonDefine.h"

#ifndef INTERRUPT_H
#define	INTERRUPT_H

//  XXX     :   this is not good timer declation is here
UDWORD globalCount;

void initInterrupt(void);
void interrupt incrementTimer(void);

#endif	/* INTERRUPT_H */
