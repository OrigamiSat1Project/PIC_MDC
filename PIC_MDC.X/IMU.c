#include <xc.h>
#include "OrigamiTypeDefine.h"
#include "CommonDefine.h"
#include "I2Clib.h"
#include "EEPROM.h"
#include "init.h"
#include "CAN.h"
#include "adxl345.h"
#include "ITG3701.h"
#include "ICM20601.h"
#include "Timer.h"
#include "IMU.h"

void readIMUsequence_ICM(UBYTE ee_p, UBYTE EEPROMH, UBYTE EEPROML, int measuring_time){
    
    if(EEPROML % 0x08 != 0) break;
   
   UBYTE zeros[10] = {};
   UBYTE IMUdata[16] = {};
   UBYTE selEEP = ee_p;
   UBYTE initEEPROMH = EEPROMH;
   UBYTE initEEPROML = EEPROML;
   
   for(int i=0;i<10;i++) zeros[i] = 0xAA;
   
   
   writeEEPROM(selEEP, EEPROMH, EEPROML, &globalClock,6);
   __delay_us(5000);
   EEPROML += 0x06;
   writeEEPROM(selEEP, EEPROMH, EEPROML, zeros,10);
   __delay_us(5000);
   EEPROML += 0x0A;
   
   sampling_counter = 0;
   sampling_counterH = 0;
   sampling_counterL = 0;
   constant_timer_counter = 0;

    while(constant_timer_counter <= measuring_time){
    //while(sampling_counter[0] <= 100){
        if(sampling_counterL == 0xFF){
            sampling_counterL = 0x00;
            sampling_counterH += 0x01;
        }else{
            sampling_counterL += 0x01;
        }
        
        IMUdata[0] = sampling_counterH;
        IMUdata[1] = sampling_counterL;
        readICM(IMUdata,2);
        __delay_us(20);

        writeEEPROM(selEEP, EEPROMH, EEPROML, IMUdata, 16);
        __delay_us(3000);
        if(EEPROML == 0xF0){
            EEPROMH = EEPROMH + 0x01;
            EEPROML = 0x00;
        }else{
            EEPROML += 0x10;
        }
        if(EEPROMH >= 0xF0){
            selEEP += 1;
            EEPROML = 0;
            EEPROMH = 0;
            if(selEEP == 4){
                break;  //EEPROM full
            }
        }
    }
        
        
        
    // ending
    IMUdata[0] = sampling_counterH;
    IMUdata[1] = sampling_counterL;
    writeEEPROM(selEEP,initEEPROMH,initEEPROML+0x06,IMUdata,2);
    __delay_us(5000);
    writeEEPROM(selEEP, EEPROMH, EEPROML, &globalClock,6);
    __delay_us(5000);
    EEPROML += 0x06;
    writeEEPROM(selEEP, EEPROMH, EEPROML, zeros,10);
    __delay_us(5000);
    EEPROML += 0x0A;
    
    return;
}

void readIMUsequence_adxl_ITG(UBYTE ee_p, UBYTE EEPROMH, UBYTE EEPROML, int measuring_time){
    
    if(EEPROML % 0x08 != 0) break;
   
   UBYTE zeros[10] = {};
   UBYTE IMUdata[16] = {};
   UBYTE selEEP = ee_p;
   UBYTE initEEPROMH = EEPROMH;
   UBYTE initEEPROML = EEPROML;
   
   for(int i=0;i<10;i++) zeros[i] = 0xAA;
   
   
   writeEEPROM(selEEP, EEPROMH, EEPROML, &globalClock,6);
   __delay_us(5000);
   EEPROML += 0x06;
   writeEEPROM(selEEP, EEPROMH, EEPROML, zeros,10);
   __delay_us(5000);
   EEPROML += 0x0A;
   
   sampling_counter = 0;
   sampling_counterH = 0;
   sampling_counterL = 0;
   constant_timer_counter = 0;

    while(constant_timer_counter <= measuring_time){
    //while(sampling_counter[0] <= 100){
        if(sampling_counterL == 0xFF){
            sampling_counterL = 0x00;
            sampling_counterH += 0x01;
        }else{
            sampling_counterL += 0x01;
        }
        
        IMUdata[0] = sampling_counterH;
        IMUdata[1] = sampling_counterL;
        readADXL(IMUdata,2);
        __delay_us(20);
        readITG(IMUdata,8);
        __delay_us(20);

        writeEEPROM(selEEP, EEPROMH, EEPROML, IMUdata, 16);
        __delay_us(3000);
        if(EEPROML == 0xF0){
            EEPROMH = EEPROMH + 0x01;
            EEPROML = 0x00;
        }else{
            EEPROML += 0x10;
        }
        if(EEPROMH >= 0xF0){
            selEEP += 1;
            EEPROML = 0;
            EEPROMH = 0;
            if(selEEP == 4){
                break;  //EEPROM full
            }
        }
    }
        
        
        
    // ending
    IMUdata[0] = sampling_counterH;
    IMUdata[1] = sampling_counterL;
    writeEEPROM(selEEP,initEEPROMH,initEEPROML+0x06,IMUdata,2);
    __delay_us(5000);
    writeEEPROM(selEEP, EEPROMH, EEPROML, &globalClock,6);
    __delay_us(5000);
    EEPROML += 0x06;
    writeEEPROM(selEEP, EEPROMH, EEPROML, zeros,10);
    __delay_us(5000);
    EEPROML += 0x0A;
    
    return;
}


// void readIMUsequence_ICM(UBYTE ee_p, UBYTE EEPROMH, UBYTE EEPROML, int measuring_time){
    
   
//    UBYTE zeros[10] = {};
//    UBYTE IMUdata[16] = {};
//    UBYTE IMUdatas[128] = {};
//    UBYTE delay_time = ee_p && 0x3F;
//    UBYTE selEEP = (ee_p && 0xC0) >> 6;
//    UBYTE initEEPROMH = EEPROMH;
//    UBYTE initEEPROML = EEPROML;
   
//    for(int i=0;i<10;i++) zeros[i] = 0xAA;
   
//    //syncWithOBC(OBCClock);
//    //sendCanData(&globalClock);
//    /**/
//    writeEEPROM(selEEP, EEPROMH, EEPROML, &globalClock,6);
//    __delay_us(5000);
//    EEPROML += 0x06;
//    writeEEPROM(selEEP, EEPROMH, EEPROML, zeros,10);
//    __delay_us(5000);
//    EEPROML += 0x0A;
   
//    sampling_counter[0] = 0;
//    sampling_counter[1] = 0;
   
//    constant_timer_counter = 0;
//     while(constant_timer_counter <= measuring_time){
//     //while(sampling_counter[0] <= 100){    
//         while(EEPROML != 0x00){
//             sampling_counter[0] += 1;
//             IMUdata[0] = sampling_counter[1];
//             IMUdata[1] = sampling_counter[0];
//             readICM(IMUdata,2);
//             __delay_us(20);

//             writeEEPROM(selEEP, EEPROMH, EEPROML, IMUdata, 16);
//             __delay_us(3000);
//             if(EEPROML == 0xF0){
//                 EEPROMH = EEPROMH + 0x01;
//                 EEPROML = 0x00;
//             }else{
//                 EEPROML += 0x10;
//             }
//             if(EEPROMH >= 0xF0){
//                 selEEP += 1;
//                 EEPROML = 0;
//                 EEPROMH = 0;
//                 if(selEEP == 4){
//                     break;  //EEPROM full
//                 }
//             }
//            //wait1ms(delay_time);
//         }
        
        
//         for(int k=0;k<2;k++){
//             for(int i=0;i<8;i++){
//                 if(sampling_counter[0] == 0xFF){
//                     sampling_counter[0] = 0x00;
//                     sampling_counter[1] += 0x01;
//                 }else{
//                     sampling_counter[0] += 1;
//                 }
//                 IMUdatas[16*i] = sampling_counter[1];
//                 IMUdatas[1+16*i] = sampling_counter[0];
//                 readICM(IMUdatas,2+16*i);
//                 __delay_us(20);
//                 //wait1ms(delay_time);
//             }
        
//             writeEEPROM(selEEP, EEPROMH, EEPROML, IMUdatas, 128);
//             __delay_us(3000);
//             if(EEPROML == 0x80){
//                 EEPROMH += 0x01;
//                 EEPROML = 0x00;
//             }else{
//                 EEPROML = 0x80;
//             }
//             if(EEPROMH >= 0xF0){
//                 selEEP += 1;
//                 EEPROML = 0;
//                 EEPROMH = 0;
//                 if(selEEP == 4){
//                     break;  //EEPROM full
//                 }
//             }
//         }
        
//     }
//     // ending 
//     /**/
//     __delay_us(3000);
//     IMUdata[0] = sampling_counter[1];
//     IMUdata[1] = sampling_counter[0];
//     writeEEPROM(selEEP,initEEPROMH,initEEPROML+0x06,IMUdata,2);
//     __delay_us(5000);
//     writeEEPROM(selEEP, EEPROMH, EEPROML, &globalClock,6);
//     __delay_us(5000);
//     EEPROML += 0x06;
//     writeEEPROM(selEEP, EEPROMH, EEPROML, zeros,10);
//     __delay_us(5000);
//     EEPROML += 0x0A;
    
//     return;
// }

// void readIMUsequence_adxl_ITG(UBYTE ee_p, UBYTE EEPROMH, UBYTE EEPROML, int measuring_time){
    
   
//    UBYTE zeros[10] = {};
//    UBYTE IMUdata[16] = {};
//    UBYTE IMUdatas[128] = {};
//    UBYTE delay_time = ee_p && 0x3F;
//    UBYTE selEEP = (ee_p && 0xC0) >> 6;
//    UBYTE initEEPROMH = EEPROMH;
//    UBYTE initEEPROML = EEPROML;
   
//    for(int i=0;i<10;i++) zeros[i] = 0xAA;
   
//    //syncWithOBC(OBCClock);
//    //sendCanData(&globalClock);
   
//    writeEEPROM(selEEP, EEPROMH, EEPROML, &globalClock,6);
//    __delay_us(5000);
//    EEPROML += 0x06;
//    writeEEPROM(selEEP, EEPROMH, EEPROML, zeros,10);
//    __delay_us(5000);
//    EEPROML += 0x0A;
   
//    sampling_counter[0] = 0;
//    sampling_counter[1] = 0;
   
//    constant_timer_counter = 0;
//     while(constant_timer_counter <= measuring_time){
//     //while(sampling_counter[0] <= 100){    
//         while(EEPROML != 0x00){
//             sampling_counter[0] += 1;
//             IMUdata[0] = sampling_counter[1];
//             IMUdata[1] = sampling_counter[0];
//             readADXL(IMUdata,2);
//             __delay_us(20);
//             readITG(IMUdata,8);
//             __delay_us(20);

//             writeEEPROM(selEEP, EEPROMH, EEPROML, IMUdata, 16);
//             __delay_us(3000);
//             if(EEPROML == 0xF0){
//                 EEPROMH = EEPROMH + 0x01;
//                 EEPROML = 0x00;
//             }else{
//                 EEPROML += 0x10;
//             }
//             if(EEPROMH >= 0xF0){
//                 selEEP += 1;
//                 EEPROML = 0;
//                 EEPROMH = 0;
//                 if(selEEP == 4){
//                     break;  //EEPROM full
//                 }
//             }
//            //wait1ms(delay_time);
//         }
        
        
//         for(int k=0;k<2;k++){
//             for(int i=0;i<8;i++){
//                 if(sampling_counter[0] == 0xFF){
//                     sampling_counter[0] = 0x00;
//                     sampling_counter[1] += 0x01;
//                 }else{
//                     sampling_counter[0] += 1;
//                 }
//                 IMUdatas[16*i] = sampling_counter[1];
//                 IMUdatas[1+16*i] = sampling_counter[0];
//                 readADXL(IMUdatas,2+16*i);
//                 __delay_us(20);
//                 readITG(IMUdatas,8+16*i);
//                 __delay_us(20);
//                 //wait1ms(delay_time);
//             }
        
//             writeEEPROM(selEEP, EEPROMH, EEPROML, IMUdatas, 128);
//             __delay_us(3000);
//             if(EEPROML == 0x80){
//                 EEPROMH += 0x01;
//                 EEPROML = 0x00;
//             }else{
//                 EEPROML = 0x80;
//             }
//             if(EEPROMH >= 0xF0){
//                 selEEP += 1;
//                 EEPROML = 0;
//                 EEPROMH = 0;
//                 if(selEEP == 4){
//                     break;  //EEPROM full
//                 }
//             }
//         }
        
//     }
//     // ending 
//    IMUdata[0] = sampling_counter[1];
//     IMUdata[1] = sampling_counter[0];
//     writeEEPROM(selEEP,initEEPROMH,initEEPROML+0x06,IMUdata,2);
//     __delay_us(5000);
//     __delay_us(3000);
//     writeEEPROM(selEEP, EEPROMH, EEPROML, &globalClock,6);
//     __delay_us(5000);
//     EEPROML += 0x06;
//     writeEEPROM(selEEP, EEPROMH, EEPROML, zeros,10);
//     __delay_us(5000);
//     EEPROML += 0x0A;
    
//     return;
// }


