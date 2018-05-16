#include <xc.h>
#include "OrigamiTypeDefine.h"
#include "CommonDefine.h"
#include "adxl345.h"
#include "I2Clib.h"
#include "EEPROM.h"
#include "init.h"
#include "CAN.h"

const UBYTE ADXL345_ADDR    = 0x1D;
const UBYTE DEVID           = 0x00;
const UBYTE DEVID_VALUE     = 0xE5;
const UBYTE BW_RATE         = 0x2C;
const UBYTE DATA_FORMAT     = 0x31;
const UBYTE FIFO_CTL        = 0x38;
const UBYTE POWER_CTL       = 0x2D;
const UBYTE ADXL_DATA       = 0x32;


int readAddr(char address)
{
    int ans;
    ans = startI2C{ADXL345_ADDR,RW_0};
    if (ans == 0){
        sendI2CDat(address);
        restartI2C(ADXL345_ADDR,RW_1);
        ans = readI2CData(NOACK);
    }else ans = -1;
    stopI2C();
    return ans;
}

int writeAddr(char address, char val)
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

int initADXL()
{
    int ans;
    __delay_us(2000);
    ans = readAddr(DEVID);
    if(ans == DEVID_VALUE){
        writeAddr(BW_RATE,0x0B);        // rate = 200Hz
        writeAddr(DATA_FORMAT,0x00);    // proto=I2C,res=10bit,range=2g
        writeAddr(FIFO_CTL,0x00);       // FIFO=bypass
        writeAddr(POWER_CTL,0x08);      // autosleep=off,mode=measure
        __delay_us(2000);
    }else ans = -1;
    return ans;
}

int readADXL(UBYTE *data, int offset)
{
    int ans , i , ack;

    while(ans != 0x80){
        ans = readAddr(INT_SOURCE);
        ans = ans & 0x80;
    }

    ans = startI2C(ADXL345_ADDR,RW_0);
    if(ans == 0){
        sendI2CData(ADXL_DATA);
        restartI2C(ADXL345_ADDR,RW_1);
        ack = ACK;
        for(i=0;i<5;i++){
            data[offset+i] = readI2CData(ack);
        }
    }else ans = -1;
    stopI2C();
    return ans;
}