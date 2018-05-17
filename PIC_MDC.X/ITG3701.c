#include <xc.h>
#include "OrigamiTypeDefine.h"
#include "CommonDefine.h"
#include "ITG3701.h"
#include "I2Clib.h"
#include "EEPROM.h"
#include "init.h"
#include "CAN.h"

const UBYTE ITG_ADDR        = 0x69;
const UBYTE WHO_AM_I        = 0x75;
const UBYTE WHO_VALUE       = 0x68;
const UBYTE SMPLRT_DIV      = 0x19;
const UBYTE CONFIG          = 0x1A;
const UBYTE GYRO_CONFIG     = 0x1B;
const UBYTE FIFO_EN         = 0x1C;
const UBYTE INT_PIN_CFG     = 0x37;
const UBYTE INT_ENABLE      = 0x38;
const UBYTE INT_STATUS      = 0x3A;
const UBYTE ITG_DATA        = 0x41;
const UBYTE PWR_MGMT_1      = 0x6B;
const UBYTE PWR_MGMT_2      = 0x6C;

int readAddr(char address)
{
    int ans;
    ans = startI2C(ITG_ADDR,RW_0);
    if(ans == 0){
        sendI2CData(address);
        restartI2C(ITG_ADDR,RW_1);
        ans = readI2CData(NOACK);
    }else ans = -1;
    stopI2C();
    return ans;
}

int writeAddr(char address, char val)
{
    int ans;
    ans = startI2C(ITG_ADDR,RW_0);
    if(ans == 0){
        sendI2CData(address);
        sendI2CData(val);
    }else ans = -1;
    stopI2C();
    return ans;
}

int initITG()
{
    __delay_us(2000);
    ans = readAddr(WHO_AM_I);
    if(ans == WHO_VALUE){
        writeAddr(FIFO_EN,0x00);        //FIFO disabled
        writeAdde(CONFIG,0x00);         //FIFO disabled , DLPF 250Hz
        writeAddr(GYRO_CONFIG,0x18);    //FS:4000deg/sec
        writeAddr(INT_PIN_CFG,0x08);    //FSYNC:activ low
        writeAddr(INT_ENABLE,0x01);     //DARA Ready Interupt : Enable
        writeAddr(PWR_MGMT_1,0x01);     //oscirator : PLL
        __delay_us(2000);
    }else ans = -1;
    return ans;
}
//survey address for initializing

int readITG(UBYTE *data, int offset)
{
    int ans , i , ack ;

    while(ans != 0xE7){
        ans = readAddr(INT_STATUS);
        ans = ans & 0xE7;               //Data Ready Interupt generated -> break
    }

    ans = startI2C(ITG_ADDR,RW_0);
    if(ans == 0){
        sendI2CData(ITG_DATA);
        restartI2C(ITG_ADDR,RW_1);
        ack = ACK;
        for(i=0;i<8;i++){
            if(i == 7) ack = NOACK;
            dara[offset+i] = readI2CData(ack);
        }
    }else ans = -1;
    stopI2C();
    return ans;
}