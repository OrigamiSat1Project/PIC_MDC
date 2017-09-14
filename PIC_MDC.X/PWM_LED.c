#include "PWM_LED.h"
#include "init.h"
#include <xc.h>

int PWM_init(void){
    int ans;
    
    ans = 1;
    
    PMD0bits.CCP5MD = 0;  // CCP5 module is enabled
    /*
    //PWM setting    
    CCP5CON = 0b00111100;  // Lower 2bits are allocated in 5 and 4
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
    
    PR2 = 0b00011000; // PWM period Duty:80%  
    
    return ans;

}

int PWM_LED(int lux){
              
    if(lux==10){CCPR5L = 0b00000010;}//10%
    if(lux==40){CCPR5L = 0b00010011;}//10%
    if(lux==80){CCPR5L = 0b00011000;}//10%
    if(lux==100){CCPR5L = 0b00011000;}//10%
    
    CCP5CON = 0b00111100; // Lower 2bits are allocated in 5 and 4
    
    Wait_1ms(500);
    CCP5CON = 0x00;
}

void rLED_ON(void){
    //PORTCbits.RC2 = 1;
    PORTBbits.RB5 = 1;
}
void rLED_OFF(void){
    //PORTCbits.RC2 = 0;
    PORTBbits.RB5 = 0;
}

 

