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

void readIMU(UBYTE *data, int i){
    data[0] = i;
    data[1] = 0;
    readADXL(data,2);
    readITG(data,8);
    readICM(data,16);
    data[30] = 0;
    data[31] = 0;
}

void readIMUsequence(UBYTE ee_p, UBYTE EEPROMH, UBYTE EEPROML, int measuring_time){

   int sampling_counter = 1;
   //UBYTE zeros[26] = {0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11};
   UBYTE zeros[26] = {};
   UBYTE IMUdata[32] = {};


   //syncWithOBC(OBCClock);
   
   writeEEPROM(ee_p, EEPROMH, EEPROML, &globalClock,6);
   __delay_us(5000);
   EEPROML += 0x06;
   writeEEPROM(ee_p, EEPROMH, EEPROML, zeros,26);
   __delay_us(5000);
   EEPROML += 0x1A;
   
    while(timer_counter <= measuring_time){
        
        


        IMUdata[0] = sampling_counter;
        IMUdata[1] = 0;
        readADXL(IMUdata,2);
        __delay_us(20);
        readITG(IMUdata,8);
        __delay_us(20);
        readICM(IMUdata,16);
        __delay_us(20);
        IMUdata[30] = 0;
        IMUdata[31] = 0;
        //__delay_us(3000);
        writeEEPROM(ee_p, EEPROMH, EEPROML, IMUdata, 32);
        __delay_us(5000);
        if(EEPROML == 0xE0){
            EEPROMH = EEPROMH + 0x01;
            EEPROML = 0x00;
        }else{
            EEPROML += 0x20;
        }
        
        if(EEPROMH >= 0xF0){
            break;  //EEPROM full
        }
        sampling_counter += 1;
    }
   // ending 
   __delay_us(3000);
   writeEEPROM(ee_p, EEPROMH, EEPROML, &globalClock,6);
   __delay_us(5000);
   EEPROML += 0x06;
   writeEEPROM(ee_p, EEPROMH, EEPROML, zeros,26);
   __delay_us(5000);
   EEPROML += 0x1A;

    return;
}