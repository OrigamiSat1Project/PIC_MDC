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

void readIMUsequence_ICM(UBYTE ee_p, UBYTE EEPROMH, UBYTE EEPROML, UINT measuring_time){
    
//    if(EEPROML % 0x08 != 0) return;
    
   UBYTE zeros[10] = {};
   UBYTE IMUdata[16] = {};
   UBYTE selEEP = ee_p;
   UBYTE initEEPROMH = EEPROMH;
   UBYTE initEEPROML = EEPROML;
   
   for(int i=0;i<10;i++) zeros[i] = 0xFF;
   
   
   writeEEPROM(selEEP, EEPROMH, EEPROML, &globalClock,6);
   delay_us(5000);
   EEPROML += 0x06;
   writeEEPROM(selEEP, EEPROMH, EEPROML, zeros,10);
   delay_us(5000);
   EEPROML += 0x0A;
   
   sampling_counter = 0x0000;
   sampling_counterH = 0x00;
   sampling_counterL = 0x00;
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
        delay_us(20);

        writeEEPROM(selEEP, EEPROMH, EEPROML, IMUdata, 16);
        delay_us(3000);
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
    writeEEPROM(selEEP, EEPROMH, EEPROML, &globalClock,6);
    __delay_us(5000);
    EEPROML += 0x06;
    writeEEPROM(selEEP, EEPROMH, EEPROML, zeros,10);
    __delay_us(5000);
    EEPROML += 0x0A;
    
    return;
}

void readIMUsequence_adxl_ITG(UBYTE ee_p, UBYTE EEPROMH, UBYTE EEPROML, UINT measuring_time){
    
   if(EEPROML % 0x08 != 0) return;
   
   UBYTE zeros[12] = {};
   UBYTE IMUdata[16] = {};
   UBYTE selEEP = ee_p;
   
   for(int i=0;i<12;i++) zeros[i] = 0xFF;
   
   writeEEPROM(selEEP, EEPROMH, EEPROML, &globalClock,6);
   __delay_us(5000);
   EEPROML += 0x06;
   writeEEPROM(selEEP, EEPROMH, EEPROML, zeros,10);
   __delay_us(5000);
   EEPROML += 0x0A;
   
   sampling_counter = 0x0000;
   sampling_counterH = 0x00;
   sampling_counterL = 0x00;
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
        if((EEPROMH == 0xFF) && (EEPROML == 0xF0)){
            selEEP += 1;
            EEPROML = 0;
            EEPROMH = 0;
            if(selEEP == 4){
                break;  //EEPROM full
            }
        }
    }
        
        
        
    // ending
    __delay_us(3000);
    writeEEPROM(selEEP, EEPROMH, EEPROML, &globalClock,6);
    __delay_us(5000);
    EEPROML += 0x06;
    writeEEPROM(selEEP, EEPROMH, EEPROML, zeros,10);
    __delay_us(5000);
    EEPROML += 0x0A;
    
    return;
}

void readIMUsequence_adxl_ITG_50Hz(UBYTE ee_p, UBYTE EEPROMH, UBYTE EEPROML, UINT measuring_time){
    
   if(EEPROML % 0x08 != 0) return;
   
   UBYTE zeros[12] = {};
   UBYTE IMUdata[16] = {};
   UBYTE selEEP = ee_p;
   
   for(int i=0;i<12;i++) zeros[i] = 0xFF;
   
   writeEEPROM(selEEP, EEPROMH, EEPROML, &globalClock,6);
   __delay_us(5000);
   EEPROML += 0x06;
   writeEEPROM(selEEP, EEPROMH, EEPROML, zeros,10);
   __delay_us(5000);
   EEPROML += 0x0A;
   
   sampling_counter = 0x0000;
   sampling_counterH = 0x00;
   sampling_counterL = 0x00;
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
        if((EEPROMH == 0xFF) && (EEPROML == 0xF0)){
            selEEP += 1;
            EEPROML = 0;
            EEPROMH = 0;
            if(selEEP == 4){
                break;  //EEPROM full
            }
        }
        __delay_ms(13);
    }
        
        
        
    // ending
    __delay_us(3000);
    writeEEPROM(selEEP, EEPROMH, EEPROML, &globalClock,6);
    __delay_us(5000);
    EEPROML += 0x06;
    writeEEPROM(selEEP, EEPROMH, EEPROML, zeros,10);
    __delay_us(5000);
    EEPROML += 0x0A;
    
    return;
}
