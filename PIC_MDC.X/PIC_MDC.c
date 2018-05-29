#include <xc.h>
#include <stdlib.h>
#include <math.h>
#include "I2Clib.h"
#include "CAN.h"
#include "ADC.h"
#include "init.h"
#include "EEPROM.h"
#include "adxl345.h"
#include "ITG3701.h"
#include "ICM20601.h"
#include "Timer.h"
#include "Solar.h"
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

void main()
{
    UINT time ; // unsigned int time
    UBYTE bufOBC[16];

    initAll();
    //  initialize buffer for communicate with OBC
    for(unsigned int i=0;i<16;i++){
        bufOBC[i]=0x00;
    }
    

    /*
    readCanData(bufOBC);
    wait1ms(1000);
    //  FIXME : check command of OBC is correct format or not
    //  echoback to OBC
    sendCanData(bufOBC);
    //  FIXME : change case syntax for command format
    switch (bufOBC[0]){
        case 0x01:
            readIMUSequence(0x00);
            break;
        case 0x02:
            readSolarSequence();
            break;
        case 0x03:
            if(bufOBC[1] == 0x00){
                break;
            }
            LED_SW_ON;
            //  FIXME : wait time is need to be got by command format
            wait1ms((int)bufOBC[1] * 1000);
            LED_SW_OFF;
            break;
        case 0x04:
            if(bufOBC[1] == 0x00){
                break;
            }
            HRM_SW_ON;
            //  FIXME : wait time, and date time is need to be got by command format
            wait1ms((int)bufOBC[1] * 1000);
            HRM_SW_OFF;
            break;
        case 0x05:
            break;

    }
    */

    //function test code

    UBYTE zero_data[24] = {};
    //UBYTE ADXL_data[8] = {};
    UBYTE *ADXL_data;
    UBYTE ITG_data[8] = {};
    UBYTE ICM_data[16] = {};
    UBYTE dummy_data[8] = {};
    UBYTE ADXL_ROM_data[8] = {};
    UBYTE ITG_ROM_data[8] = {};
    UBYTE ICM_ROM_data[16] = {};
    UBYTE dummy_ROM_data[8] = {};
    readCanData(bufOBC);
    wait1ms(1000);
    sendCanData(bufOBC);
    __delay_us(3000);
    switch (bufOBC[0]){
        case 0x01:
            writeEEPROM(EE_P0_0,0x00,0x00,zero_data,24);
            __delay_us(3000);
            writeEEPROM(EE_P0_1,0x00,0x00,zero_data,24);
            __delay_us(3000);
            writeEEPROM(EE_P0_2,0x00,0x00,zero_data,24);
            __delay_us(3000);
            writeEEPROM(EE_P0_3,0x00,0x00,zero_data,24);
            __delay_us(3000);
            break;
        case 0x02:
            readADXL(ADXL_data,0);
            sendCanData(ADXL_data[0]);     //6byte : x-axis m, x-axis l, y-axis m, y-axis l, z-axis m, z-axis l
            //writeEEPROM(EE_P0_0,0x00,0x00,ADXL_data,8);
            break;
        case 0x03:
            readITG(ITG_data,0);
            __delay_us(3000);
            sendCanData(ITG_data);     //8byte : temp m, temp l, gyro-x m, gyro-x l, gyro-y m, gyro-y l, gyro-z m, gyro-z l
            __delay_us(3000);
            writeEEPROM(EE_P0_1,0x00,0x00,ITG_data,8);
            __delay_us(3000);
            break;
        case 0x04:
            readICM(ICM_data,0);
            __delay_us(3000);
            sendCanData(ICM_data[0]);
            __delay_us(3000);
            sendCanData(ICM_data[8]);  //14byte : ax-H, ax-L, ay-H, ay-L, az-H, az-L, temp-H, temp-L, gyrox-H, gyrox-L, gyroy-H, gyroy-L, gyroz-H, gyroz-L
            __delay_us(3000);
            writeEEPROM(EE_P0_2,0x00,0x00,ICM_data,16);
            __delay_us(3000);
            break;
        case 0x05:
            dummy_data[0] = 0x99;
            dummy_data[1] = 0xAA;
            dummy_data[2] = 0xBB;
            dummy_data[3] = 0xCC;
            dummy_data[4] = 0xDD;
            dummy_data[5] = 0xEE;
            dummy_data[6] = 0x88;
            dummy_data[7] = 0x77;
            __delay_us(3000);
            sendCanData(dummy_data);
            __delay_us(3000);
            writeEEPROM(EE_P0_3,0x00,0x00,dummy_data,8);
            __delay_us(3000);
            break;
        case 0x06:
            readEEPROM(EE_P0_0,0x00,0x00,ADXL_ROM_data,8);
            __delay_us(3000);
            sendCanData(ADXL_ROM_data);
            __delay_us(3000);
            readEEPROM(EE_P0_1,0x00,0x00,ITG_ROM_data,8);
            __delay_us(3000);
            sendCanData(ITG_ROM_data);
            __delay_us(3000);
            readEEPROM(EE_P0_2,0x00,0x00,ICM_ROM_data,16);
            __delay_us(3000);
            sendCanData(ICM_ROM_data);
            __delay_us(3000);
            sendCanData(ICM_ROM_data[8]);
            __delay_us(3000);
            readEEPROM(EE_P0_3,0x00,0x00,dummy_ROM_data,8);
            __delay_us(3000);
            sendCanData(dummy_ROM_data);
            __delay_us(3000);
            break;
    }
}
