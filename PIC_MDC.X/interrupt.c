#include <xc.h>
#include "interrupt.h"
#include "I2Clib.h"

void interrupt_int(void){
    INTCON = 0xE0;
    T0CON = 0xC7;   //0xc7
    TMR0H = 0x00;
    TMR0L = 0x00;
}

int interrupt InterFunction(void){
    if(INTCONbits.TMR0IF){
        INTCONbits.TMR0IF = 0;
        TMR0L = 0x00;
        cnt++;
    }
    InterI2C();
}
