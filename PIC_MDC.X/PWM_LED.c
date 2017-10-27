/// Prolougue

//  control infrated LED, debugger LED
//  Author      :   reo kashiyama

#include "PWM_LED.h"
#include "init.h"
#include <xc.h>

/// Global data
/// Method

/*
 *  initialise PWM setting for PWM LED
 *	arg      :   void
 *	return   :   void
 *	TODO     :   understanding
 *	FIXME    :   not yet
 *	XXX      :   avoid hardcoding
 */
int initPWM(void){
    int ans = 1;
    PMD0bits.CCP5MD = 0;  // enable CCP5 module
    CCP5CON = 0b00111100; // set PWM mode
    /*
    // PWM period is set to 819
    CCPR5L = 0b11001100;   // Upper 8bits
    //CCPR2H = 0b11001100;   // Duty cycle buffer register
    // Timer select register
    CCPTMRSbits.C5TSEL = 0; //CCP5 is based on TMR1orTMR2
    */
    // TMR2 setting
    T2CON = 0x00;          // Timer2 reset
    T2CONbits.TMR2ON = 1;  // Time 2 ON
    T2CONbits.T2CKPS1 = 0; // Prescale is set as 1:1
    T2CONbits.T2CKPS0 = 0; // Prescale is set as 1:1
    /*
    PWM Period = [(PR2) + 1] • 4 • TOSC • (TMR2 Prescale Value)
    PWM Duty Cycle = (CCPR4L:CCP4CON<5:4>) • TOSC • (TMR2 Prescale Value)
    */
    PR2 = 0b00011000; // PWM period Duty:80%
    return ans;
}


/*
 *  on LED by PEM
 *	arg      :   lux, on seconds
 *	return   :   void
 *	TODO     :   understanding
 *	FIXME    :   not yet
 *	XXX      :   avoid hardcoding
 */
int pwmLED_ON(int lux, int on_seconds){
    CCP5CON = 0b00111100; // set PWM mode
    if(lux==10){CCPR5L = 0b00000010;}//10%
    if(lux==40){CCPR5L = 0b00010011;}//10%
    if(lux==80){CCPR5L = 0b00011000;}//10%
    if(lux==100){CCPR5L = 0b00011000;}//10%
    //CCP5CON = 0b00111100; // set PWM mode
    Wait_1ms(on_seconds * 1000);
    CCP5CON = 0x00;
}

void rLED_ON(void){
    PORTBbits.RB5 = 1;
}
void rLED_OFF(void){
    PORTBbits.RB5 = 0;
}
