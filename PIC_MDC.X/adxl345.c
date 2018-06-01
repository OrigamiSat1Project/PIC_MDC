#include <xc.h>
#include "OrigamiTypeDefine.h"
#include "CommonDefine.h"
#include "adxl345.h"
#include "I2Clib.h"
#include "EEPROM.h"
#include "init.h"
#include "CAN.h"

const UBYTE ADXL345_ADDR            = 0x1D;
const UBYTE ADXL345_DEVID           = 0x00;
const UBYTE ADXL345_DEVID_VALUE     = 0xE5;
const UBYTE ADXL345_BW_RATE         = 0x2C;
const UBYTE ADXL345_DATA_FORMAT     = 0x31;
const UBYTE ADXL345_FIFO_CTL        = 0x38;
const UBYTE ADXL345_POWER_CTL       = 0x2D;
const UBYTE ADXL345_DATA            = 0x32;
const UBYTE ADXL345_INT_SOURCE      = 0x30;
const UBYTE ADXL345_INT_ENABLE      = 0x2E;


int readADXLAddr(char address)
{
    int ans;
    ans = startI2C(ADXL345_ADDR,RW_0);
    if(ans == 0){
        sendI2CData(address);
        restartI2C(ADXL345_ADDR,RW_1);
        ans = readI2CData(NOACK);
    }else ans = -1;
    stopI2C();
    return ans;
}

int writeADXLAddr(char address, char val)
{
    int ans;
    ans = startI2C(ADXL345_ADDR,RW_0);
    if(ans == 0){
        sendI2CData(address);
        sendI2CData(val);
    }else ans = -1;
    stopI2C();
    return ans;
}

int initADXL()
{
    int ans;
    UBYTE test[8] = {};
    __delay_us(2000);
    ans = readADXLAddr(ADXL345_DEVID);
    if(ans == ADXL345_DEVID_VALUE){
        writeADXLAddr(ADXL345_POWER_CTL,0x08);      // autosleep=off,mode=measure
        writeADXLAddr(ADXL345_INT_ENABLE,0x81);     // interupe enable
        writeADXLAddr(ADXL345_BW_RATE,0x0B);        // rate = 200Hz
        writeADXLAddr(ADXL345_DATA_FORMAT,0x00);    // proto=I2C,full resolution mode,range=16g
        writeADXLAddr(ADXL345_FIFO_CTL,0x00);       // FIFO=bypass
        __delay_us(2000);
        test[0] = readADXLAddr(ADXL345_POWER_CTL);      // autosleep=off,mode=measure
        test[1] = readADXLAddr(ADXL345_BW_RATE);        // rate = 200Hz
        test[2] = readADXLAddr(ADXL345_DATA_FORMAT);    // proto=I2C,full resolution mode,range=16g
        test[3] = readADXLAddr(ADXL345_FIFO_CTL);       // FIFO=bypass
        test[4] = readADXLAddr(ADXL345_INT_ENABLE);     // interupe enable
        __delay_us(2000);
        sendCanData(test);
        __delay_us(3000);
    }else ans = -1;
    return ans;
}

int readADXL(UBYTE *data, int offset)
{
    int ans , i , ack;
    ans = 0x00;
    //UBYTE who[8] = {};

    while(ans != 0x81){
        ans = readADXLAddr(ADXL345_INT_SOURCE);
        ans = ans & 0x81;
    }

    //who[0] = readADXLAddr(ADXL345_DEVID);
    //sendCanData(who);
    //__delay_us(3000);
    
    ans = startI2C(ADXL345_ADDR,RW_0);
    if(ans == 0){
        sendI2CData(ADXL345_DATA);
        restartI2C(ADXL345_ADDR,RW_1);
        ack = ACK;
        for(i=0;i<6;i++){
            if(i=5) ack = NOACK;
            data[offset+i] = readI2CData(ack);
        }
    }else ans = -1;
    stopI2C();
    return ans;
}