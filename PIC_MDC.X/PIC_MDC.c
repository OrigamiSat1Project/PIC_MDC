#include <xc.h>
#include <stdlib.h>
#include <math.h>
#include "I2Clib.h"
#include "CAN.h"
#include "ADC.h"
#include "init.h"
#include "EEPROM.h"
#include "MPU9250.h"
#include "interrupt.h"
#include "PWM.h"
#include "OrigamiTypeDefine.h"
#include "CommonDefine.h"


#pragma config RETEN = OFF      // VREG Sleep Enable bit (Ultra low-power regulator is Disabled (Controlled by REGSLP bit))
#pragma config INTOSCSEL = HIGH // LF-INTOSC Low-power Enable bit (LF-INTOSC in High-power mode during Sleep)
#pragma config SOSCSEL = DIG    // SOSC Power Selection and mode Configuration bits (Digital (SCLKI) mode)
#pragma config XINST = OFF      // Extended Instruction Set (Disabled)

// CONFIG1H
#pragma config FOSC = INTIO2    // Oscillator (Internal RC oscillator)
#pragma config PLLCFG = OFF     // PLL x4 Enable bit (Disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor (Disabled)
#pragma config IESO = OFF       // Internal External Oscillator Switch Over Mode (Disabled)

// CONFIG2L
#pragma config PWRTEN = OFF     // Power Up Timer (Disabled)
#pragma config BOREN = SBORDIS  // Brown Out Detect (Enabled in hardware, SBOREN disabled)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (1.8V)
#pragma config BORPWR = ZPBORMV // BORMV Power level (ZPBORMV instead of BORMV is selected)

// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer (WDT disabled in hardware; SWDTEN bit disabled)
#pragma config WDTPS = 1048576  // Watchdog Postscaler (1:1048576)

// CONFIG3H
#pragma config CANMX = PORTC    // ECAN Mux bit (ECAN TX and RX pins are located on RC6 and RC7, respectively)
#pragma config MSSPMSK = MSK7   // MSSP address masking (7 Bit address masking mode)
#pragma config MCLRE = ON      // Master Clear Enable (MCLR Enabled, RE3 Disabled)
// CONFIG4L
#pragma config STVREN = OFF     // Stack Overflow Reset (Disabled)
#pragma config BBSIZ = BB2K     // Boot Block Size (2K word Boot Block size)
// CONFIG5L
#pragma config CP0 = OFF        // Code Protect 00800-01FFF (Disabled)
#pragma config CP1 = OFF        // Code Protect 02000-03FFF (Disabled)
#pragma config CP2 = OFF        // Code Protect 04000-05FFF (Disabled)
#pragma config CP3 = OFF        // Code Protect 06000-07FFF (Disabled)
// CONFIG5H
#pragma config CPB = OFF        // Code Protect Boot (Disabled)
#pragma config CPD = OFF        // Data EE Read Protect (Disabled)
// CONFIG6L
#pragma config WRT0 = OFF       // Table Write Protect 00800-01FFF (Disabled)
#pragma config WRT1 = OFF       // Table Write Protect 02000-03FFF (Disabled)
#pragma config WRT2 = OFF       // Table Write Protect 04000-05FFF (Disabled)
#pragma config WRT3 = OFF       // Table Write Protect 06000-07FFF (Disabled)

// CONFIG6H
#pragma config WRTC = OFF       // Config. Write Protect (Disabled)
#pragma config WRTB = OFF       // Table Write Protect Boot (Disabled)
#pragma config WRTD = OFF       // Data EE Write Protect (Disabled)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protect 00800-01FFF (Disabled)
#pragma config EBTR1 = OFF      // Table Read Protect 02000-03FFF (Disabled)
#pragma config EBTR2 = OFF      // Table Read Protect 04000-05FFF (Disabled)
#pragma config EBTR3 = OFF      // Table Read Protect 06000-07FFF (Disabled)
// CONFIG7H
#pragma config EBTRB = OFF      // Table Read Protect Boot (Disabled)
#define __delay_ms(x)    _delay((UDWORD)((x)*(_XTAL_FREQ/4000UL)))
#define __delay_us(x) _delay((UDWORD)((x)*(_XTAL_FREQ/4000000.0)))

//  メインの処理
void main()
{
    UINT time ; // unsigned int time
    UINT SamplingCounter = 0; //max value = 65536. if sampling count > 65536, this may cause error without reproducibility
    int fail;
    //CAN送信データ
    UINT bufTx[16];
    //CAN受信データ
    UINT bufRx[16];
    char EEPROMH;
    char EEPROML;

    initAll();

    wait1ms(3000);           // ３秒後に開始

    //maybe this is not necesarry
    for(unsigned int i=0;i<16;i++){
        bufTx[i]=0x00;
        bufRx[i]=0x00;
    }

    /*fail = changeR();
    if(fail == -1){
        bufTx[1] = 0xFF;
    }*/

    while(1) {
       /* rLED_ON();
        Wait_1ms(1000);
        rLED_OFF();
        Wait_1ms(1000);*/

        for(unsigned int i=0;i<16;i++){
            bufTx[i]=0x00;
            bufRx[i]=0x00;
        }

        readCanData(bufRx);
        wait1ms(1000);
        sendCanData(bufRx);

        globalCount = 0;

        if(bufRx[0] == 0x01){
            readAD(*bufTx);
            sendCanData(bufTx);
        }

        if(bufRx[0] == 0x02){

            EEPROMH = 0x00;
            EEPROML = 0x00;
            fail = 0;
            for(unsigned int i=0;i<16;i++){
                bufRx[i]=0x00;
            }
            sendCanData(bufRx);
            //unsigned int clock = 0;
            //rLED_ON();
            //244count → 1s
            time = globalCount;
            rLED_ON();
            SamplingCounter = 0;
            while(globalCount-time <= 310){

                //while((cnt-time) > clock);
                //clock = cnt-time;
                /*fail = 0;
                for(i=0;i<16;i++){
                    bufRx[i]=0x00;
                }*/
                fail = readIMU(bufRx,0);
                __delay_us(10);
                fail = writeEEPROM(EE_P0_0, EEPROMH, EEPROML, bufRx, 16);
                SamplingCounter ++;
                __delay_us(1750);   //Wait_1ms(1);
                if(fail == -1){
                    bufTx[0] = 0xFF;
                    sendCanData(bufTx);
                }
                if(EEPROML == 0xF0){
                    EEPROMH +=  0x01;
                    EEPROML = 0x00;
                }
                if(EEPROMH == 0xFF && EEPROML == 0xF0){
                    break;
                }
                EEPROML +=  0x10;
            }
            rLED_OFF();
           // rLED_OFF();

            for(unsigned int i=0;i<16;i++){
                bufRx[i]=0x00;
            }
            wait1ms(500);
            sendCanData(bufRx);
            wait1ms(500);
            EEPROMH = 0x00;
            EEPROML = 0x00;
            // Gyro data send
            for(unsigned int k=0;k<=SamplingCounter;k++){
                fail = 0;
                fail = readEEPROM(EE_P0_0, EEPROMH ,EEPROML ,bufTx ,8);
                __delay_us(3000);
                /*for(unsigned int i=0;i<16;i++){
                    bufTx[i]=bufRx[i];
                }*/
                sendCanData(bufTx);
                /*if(fail == -1){
                    bufTx[0] = 0xFF;
                    sendCanData(bufTx);
                }*/
                if(EEPROML==0xF0){
                    EEPROMH +=  0x01;      //EEPROMH = EEPROMH+1;
                    //EEPROML = 0x00;
                }
                EEPROML += 0x10;
            }

            EEPROMH = 0x00;
            EEPROML = 0x08;
            //  Accel data send
            for(unsigned int k=0;k<=SamplingCounter;k++){
                readEEPROM(EE_P0_0, EEPROMH ,EEPROML ,bufTx ,8);
                __delay_us(3000);
                sendCanData(bufTx);
                /*if(fail == -1){
                    bufTx[0] = 0xFF;
                    sendCanData(bufTx);
                }*/
                if(EEPROML==0xF8){
                    EEPROMH +=  0x01;      //EEPROMH = EEPROMH+1;
                }
                EEPROML += 0x10;   //(char)(16))
            }
            for(unsigned int i=0;i<16;i++){
                bufRx[i]=0xFF;
            }
            for(unsigned int i=0;i<SamplingCounter;i++){
                sendCanData(bufRx);
            }
        }

        if(bufRx[0] == 0x03){
            rLED_ON();
            wait1ms(3000);
            rLED_OFF();
        }

        if(bufRx[0] == 0x04){
            SW_ON;
            wait1ms(3000);
            SW_OFF;
        }

        for(unsigned int i=0;i<16;i++){
            bufTx[i]=0xFF;
        }

        //sendCanData(bufTx);

        wait1ms(3000);

     }
}
