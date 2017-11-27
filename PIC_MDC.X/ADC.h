#include "CommonDefine.h"
#include "OrigamiTypeDefine.h"

#ifndef ADC_H
#define	ADC_H


void initAD(void);
void readAD0(UBYTE *, int);
void readAD1(UBYTE *, int);
void readAD2(UBYTE *, int);
void readAD8(UBYTE *, int);
void readAD9(UBYTE *, int);
void readAD10(UBYTE *, int);
void readAD(UBYTE *);

void waitADCIdle();

#endif	/* ADC_H */
