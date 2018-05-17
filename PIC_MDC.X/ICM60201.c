#include <xc.h>
#include "OrigamiTypeDefine.h"
#include "CommonDefine.h"
#include "ICM20601.h"
#include "I2Clib.h"
#include "EEPROM.h"
#include "init.h"
#include "CAN.h"

const UBYTE ICM_ADDR        = 0x68;
const UBYTE ICM_DATA        = 0x3B;
const UBYTE WHO_AM_I        = 0x75;
//const UBYTE SMPLRT_DIV      = 0x19;
const UBYTE CONFIG          = 0x1A;
const UBYTE GYRO_CONFIG     = 0x1B;
const UBYTE ACCEL_CONFIG    = 0x1C;
const UBYTE ACCEL_CONFIG2   = 0x1D;
const UBYTE FIFO_EN         = 0x23;
const UBYTE INT_PIN_CONFIG  = 0x37;
const UBYTE INT_ENABLE      = 0x38;
const UBYTE INT_STATUS      = 0x39;
const UBYTE PWR_MGMT_1      = 0x6B;
const UBYTE PWR_MGMT_2      = 0x6C;

int readAddr(char address)
{
    int ans;
    ans = startI2C(ICM_ADDR,RW_0);
    if(ans == 0){
        sendI2CData(address);
        restartI2C(ICM_ADDR,RW_1);
        ans = readI2CData(NOACK);
    }else ans = -1;
    stopI2C();
    return ans;
}

int writeAddr(char address , char val)
{
    int ans;
    ans = startI2C(ICM_ADDR,RW_0);
    if(ans == 0){
        sendI2CData(address);
        sendI2CData(val);
    }else ans = -1;
}

int initICM()
{
    int ans;
    ans = readAddr(WHO_AM_I);
    if(ans == 0){
            __delay_us(2000);
            writeAddr(PWR_MGMT_1,0x01);     //clock : PLL
            writeAddr(CONFIG,0x00);         //FSYNC:disabled
            writeAddr(GYRO_CONFIG,0x00);    //FS:500 deg/sec
            writeAdde(ACCEL_CONFIG,0x00);   //FS:4g
            writeAddr(ACCEL_CONFIG2,0x00);  //averaging 4 samples, DLPF : 218Hz
            __delay_us(2000);
    }else ans == -1;
    return ans;
}

int readICM(UBYTE *data, int offset)
{
    int ans , i , ack ;

    while(ans != 0xE5){
        ans = readAddr(INT_STATUS);
        ans = ans & 0xE5;
    }

    ans = startI2C(ICM_ADDR,RW_0);
    if(ans == 0){
        sendI2CData(ICM_DATA);
        restartI2C(ICM_ADDR,RW_1);
        ack = ACK;
        for(i=0;i<14;i++){
            if(i==13) ack = NOACK;
            data[offset+i] = readI2CData(ack);
        }else ans = -1;
        stopI2C();
        return ans;
    }
}