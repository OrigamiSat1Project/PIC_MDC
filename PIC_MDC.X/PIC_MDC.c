#include <xc.h>
#include <stdlib.h>
#include <math.h>
#include <pic18f25k80.h>
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
#include "IMU.h"
#include "SMA.h"


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
    UBYTE bufOBC[8]={};
    UBYTE OBCClock[6] = {0x1D,0x05,0x0F,0x09,0x06,0x12};
    UBYTE ADXL_data[8] = {};
    UBYTE ITG_data[8] = {};
    UBYTE ICM_data[16] = {};
    UBYTE SMA_data[16] = {};
    UBYTE sEEPROMH = 0x00;
    UBYTE sEEPROML = 0x00;
    UBYTE eEEPROMH = 0x00;
    UBYTE eEEPROML = 0x00;
    UWORD eEEPROM = 0x0000;
    UBYTE selEEP;
    UBYTE data_length[8] = {};
    UBYTE LEDstatus[8] = {};
    UBYTE solar1[8] = {};
    UBYTE solar2[8] = {};
    UBYTE EEPROMwritetest[8];
    UBYTE EEPROMreadtest[8];
    UBYTE testboarder[8] = {0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA};
    int measuring_time;
    
    initAll();
    syncWithOBC(OBCClock);
    
    while(1){
    readCanData(bufOBC);
    wait1ms(1000);
    switch (bufOBC[0]){
        case 0x01:
            initAll();
            break;
        case 0x10:   //LED
            switch(bufOBC[1]){
                case 0x11:
                    LED_SW_ON;
                    LEDstatus[0] = LED_Status;
                    sendCanData(LEDstatus);
                    break;
                case 0x12:
                    LED_SW_OFF;
                    LEDstatus[0] = LED_Status;
                    sendCanData(LEDstatus);
                    break;
                case 0x13:
                    LED_SW_ON;
                    wait1ms(bufOBC[2]*1000);
                    LEDstatus[0] = LED_Status;
                    sendCanData(LEDstatus);
                    LED_SW_OFF;
                    break;
                default:
                    break;
            }
            break;
        case 0x20:   //HRM
            switch(bufOBC[1]){
                case 0x21:
                    HRM_SW_ON;
                    wait1ms(1);
                    HRM_SW_OFF;
                    break;
                case 0x22:
                    HRM_SW_ON;
                    wait1ms(bufOBC[2]*1000);
                    HRM_SW_OFF;
                    break;
                case 0x23:
                    HRM_SW_ON;
                    while(MSW == 0);
                    HRM_SW_OFF;
                    break;
                default:
                    break;
            }
            break;
        case 0x30:
            switch(bufOBC[1]){
                case 0x31:
                    measuring_time = bufOBC[2] * 62;
                    selEEP   = bufOBC[3];
                    sEEPROMH = bufOBC[4];
                    sEEPROML = bufOBC[5];

                    readIMUsequence_ICM(selEEP,sEEPROMH,sEEPROML,measuring_time);
                    
                    data_length[6] = (sampling_counterL + sampling_counterH * 256 + 2) / 16;
                    data_length[7] = ((sampling_counterL + sampling_counterH * 256 + 2) % 16) * 0x10;
                    writeEEPROM(selEEP,sEEPROMH,sEEPROML+0x06,&data_length[6],2);
                    __delay_us(5000);

                    break;
                case 0x32:
                    measuring_time = bufOBC[2] * 62;
                    selEEP = bufOBC[3];
                    sEEPROMH = bufOBC[4];
                    sEEPROML = bufOBC[5];

                    readIMUsequence_adxl_ITG(selEEP,sEEPROMH,sEEPROML,measuring_time);
                    
                    data_length[6] = (sampling_counterL + sampling_counterH * 256 + 2) / 16;
                    data_length[7] = ((sampling_counterL + sampling_counterH * 256 + 2) % 16) * 0x10;
                    writeEEPROM(selEEP,sEEPROMH,sEEPROML+0x06,&data_length[6],2);
                    __delay_us(5000);

                    break;
                default:
                    break;
            }
        case 0x40:
            switch(bufOBC[1]){
                case 0x41:
                    readSolar1(solar1);
                    wait1ms(1000);
                    sendCanData(solar1);
                    break;
                case 0x42:
                    readSolar2(solar2);
                    wait1ms(1000);
                    sendCanData(solar2);
                    break;
                default:
                    break;
            }
            break;
        case 0x50:
            selEEP = bufOBC[1];
            sEEPROMH = bufOBC[2];
            sEEPROML = bufOBC[3];
            
//            data_length[6] = (sampling_counterL + sampling_counterH * 256 + 2) / 16;
//            data_length[7] = ((sampling_counterL + sampling_counterH * 256 + 2) % 16) * 0x10;
//            writeEEPROM(selEEP,sEEPROMH,sEEPROML,&data_length,8);
//            __delay_us(5000);
            readEEPROM(selEEP,sEEPROMH,sEEPROML,&data_length,8);
            __delay_us(5000);
//            data_length[6] = (sampling_counterL + sampling_counterH * 256 + 2) / 16;
//            data_length[7] = ((sampling_counterL + sampling_counterH * 256 + 2) % 16) * 0x10;
            sendCanData(&data_length);
            __delay_us(3000);
            break;
            
        case 0xE0:
            selEEP = bufOBC[1];
            sEEPROMH = bufOBC[2];
            sEEPROML = bufOBC[3];
            data_length[1] = bufOBC[4];
            data_length[0] = bufOBC[5];
            eEEPROM = sEEPROML + (sEEPROMH << 8) + (data_length[1] << 8) + data_length[0];
            eEEPROMH = eEEPROM >> 8;
            eEEPROML = eEEPROM;
            
            if((eEEPROML % 8) != 0){
                eEEPROML = data_length[0] + 8 * (1 - data_length[0]);
            }
            
            sendEEPROMdata(selEEP,sEEPROMH,sEEPROML,eEEPROMH,eEEPROML);
            break;
        case 0x60:
                globalClock.year = bufOBC[1];
                globalClock.month = bufOBC[2];
                globalClock.day = bufOBC[3];
                globalClock.hour = bufOBC[4];
                globalClock.minute = bufOBC[5];
                globalClock.second = bufOBC[6];
                break;
            
        //function test
        case 0x80:
            sendCanData(bufOBC);
            __delay_us(3000);
            break;
        case 0x81:
            readADXL(ADXL_data,0);
            __delay_us(20);
            sendCanData(ADXL_data);
            __delay_us(3000);
            break;
        case 0x82:
            readITG(ITG_data,0);
            __delay_us(20);
            sendCanData(ITG_data);
            __delay_us(3000);
            break;
        case 0x83:
            readICM(ICM_data,0);
            __delay_us(20);
            sendCanData(ICM_data);
            __delay_us(3000);
            sendCanData(ICM_data[8]);
            __delay_us(3000);
            break;
            
        case 0x91:
            for(int i=0;i<8;i++) EEPROMwritetest[i] = 0x11;
            writeEEPROM(EE_P0_0,0x00,0x00,EEPROMwritetest,8);
            __delay_us(5000);
            readEEPROM(EE_P0_0,0x00,0x00,EEPROMreadtest,8);
            __delay_us(5000);
            sendCanData(EEPROMreadtest);
            __delay_us(3000);
            break;
        case 0x92:
            for(int i=0;i<8;i++) EEPROMwritetest[i] = 0x22;
            writeEEPROM(EE_P0_1,0x00,0x00,EEPROMwritetest,8);
            __delay_us(5000);
            readEEPROM(EE_P0_1,0x00,0x00,EEPROMreadtest,8);
            __delay_us(5000);
            sendCanData(EEPROMreadtest);
            __delay_us(3000);
            break;
        case 0x93:
            for(int i=0;i<8;i++) EEPROMwritetest[i] = 0x33;
            writeEEPROM(EE_P0_2,0x00,0x00,EEPROMwritetest,8);
            __delay_us(5000);
            readEEPROM(EE_P0_2,0x00,0x00,EEPROMreadtest,8);
            __delay_us(5000);
            sendCanData(EEPROMreadtest);
            __delay_us(3000);
            break;
        case 0x94:
            for(int i=0;i<8;i++) EEPROMwritetest[i] = 0x44;
            writeEEPROM(EE_P0_3,0x00,0x00,EEPROMwritetest,8);
            __delay_us(5000);
            readEEPROM(EE_P0_3,0x00,0x00,EEPROMreadtest,8);
            __delay_us(5000);
            sendCanData(EEPROMreadtest);
            __delay_us(3000);
            break;
            
        case 0xA1:
            readSolar1(solar1);
            __delay_us(3000);   //tekitou
            sendCanData(solar1);
            __delay_us(3000);
            break;
        case 0xA2:
            readSolar2(solar2);
            __delay_us(3000);   //tekitou
            sendCanData(solar2);
            __delay_us(3000);
            break;
            
        case 0xB1:
            sendCanData(&globalClock);
            wait1ms(3000);
            sendCanData(&globalClock);
            __delay_us(3000);
            break;
        case 0xC1:
            sendCanData(bufOBC);
            __delay_us(3000);
            readADXL(ADXL_data,0);
            __delay_us(20);
            sendCanData(ADXL_data);
            __delay_us(3000);
            sendCanData(testboarder);
            __delay_us(3000);
            readITG(ITG_data,0);
            __delay_us(20);
            sendCanData(ITG_data);
            __delay_us(3000);
            sendCanData(testboarder);
            __delay_us(3000);
//            readICM(ICM_data,0);
//            __delay_us(20);
//            sendCanData(ICM_data);
//            __delay_us(3000);
//            sendCanData(ICM_data[8]);
//            __delay_us(3000);
//            sendCanData(testboarder);
//            __delay_us(3000);
            for(int i=0;i<8;i++) EEPROMwritetest[i] = 0x11;
            writeEEPROM(EE_P0_0,0x00,0x00,EEPROMwritetest,8);
            __delay_us(5000);
            readEEPROM(EE_P0_0,0x00,0x00,EEPROMreadtest,8);
            __delay_us(5000);
            sendCanData(EEPROMreadtest);
            __delay_us(3000);
            sendCanData(testboarder);
            __delay_us(3000);
            for(int i=0;i<8;i++) EEPROMwritetest[i] = 0x22;
            writeEEPROM(EE_P0_1,0x00,0x00,EEPROMwritetest,8);
            __delay_us(5000);
            readEEPROM(EE_P0_1,0x00,0x00,EEPROMreadtest,8);
            __delay_us(5000);
            sendCanData(EEPROMreadtest);
            __delay_us(3000);
            sendCanData(testboarder);
            __delay_us(3000);
            for(int i=0;i<8;i++) EEPROMwritetest[i] = 0x33;
            writeEEPROM(EE_P0_2,0x00,0x00,EEPROMwritetest,8);
            __delay_us(5000);
            readEEPROM(EE_P0_2,0x00,0x00,EEPROMreadtest,8);
            __delay_us(5000);
            sendCanData(EEPROMreadtest);
            __delay_us(3000);
            sendCanData(testboarder);
            __delay_us(3000);
            for(int i=0;i<8;i++) EEPROMwritetest[i] = 0x44;
            writeEEPROM(EE_P0_3,0x00,0x00,EEPROMwritetest,8);
            __delay_us(5000);
            readEEPROM(EE_P0_3,0x00,0x00,EEPROMreadtest,8);
            __delay_us(5000);
            sendCanData(EEPROMreadtest);
            __delay_us(3000);
            sendCanData(testboarder);
            __delay_us(3000);
            readSolar1(solar1);
            __delay_us(3000);   //tekitou
            sendCanData(solar1);
            __delay_us(3000);
            sendCanData(testboarder);
            __delay_us(3000);
            readSolar2(solar2);
            __delay_us(3000);   //tekitou
            sendCanData(solar2);
            __delay_us(3000);
            sendCanData(testboarder);
            __delay_us(3000);
            sendCanData(&globalClock);
            wait1ms(3000);
            sendCanData(&globalClock);
            __delay_us(3000);
            break;
        default:
            break;
          
    }
    }
}


void interrupt timer(void){
    if(INTCONbits.TMR0IF){
        INTCONbits.TMR0IF = 0;
        TMR0L = 0x00;
        timer_counter++;
        constant_timer_counter++;
    }
    if(timer_counter >= 62){
        //  past 1 second
        increment_globalClock();
        timer_counter = 0;
        //sendCanData(&globalClock);
    }
    interruptI2C();
}
