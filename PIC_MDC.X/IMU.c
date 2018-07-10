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
    /*
    OBCとの時間同期
    開始時間書き込み
    for�? or while�?�?measuring時間まで繰り返し
    {
        if�?{
            時間カウン�?
        }
        IMU計測
        EEPROM書き込み
        EEPROM書き込みアドレス更新
        計測番号�?+1
    }
    */
   int sampling_counter = 0;
   UBYTE zeros[10] = {0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11};

   //syncWithOBC(OBCClock);
   /*
   writeEEPROM(ee_p, EEPROMH, EEPROML, &globalClock,6);
   __delay_us(5000);
   writeEEPROM(ee_p, EEPROMH, EEPROML+0x06, zeros,10);
   __delay_us(5000);
   EEPROML += 0x10;
   */
    while(sampling_counter < measuring_time){
        
        UBYTE IMUdata[32] = {};

        /*
        if(INTCONbits.TMR0IF){
            INTCONbits.TMR0IF = 0;
            TMR0L = 0x00;
            sampling_counter += 1;
        }
        */
        
        if((EEPROML == 0xE0) || (EEPROML == 0xF0)){
            EEPROMH = EEPROMH + 0x01;
            EEPROML = 0x00;
        }
        if(EEPROMH >= 0xF0){
            break;
        }
        
        //readIMU(*IMUdata, sampling_counter);
        IMUdata[0] = sampling_counter;
        IMUdata[1] = 0;
        readADXL(IMUdata,2);
        readITG(IMUdata,8);
        readICM(IMUdata,16);
        IMUdata[30] = 0;
        IMUdata[31] = 0;
        //__delay_us(3000);
        writeEEPROM(ee_p, EEPROMH, EEPROML, IMUdata, 32);
        __delay_us(5000);
        EEPROML += 0x20;
        sampling_counter += 1;
    }
    
    return;
}