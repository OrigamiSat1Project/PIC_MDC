#include <xc.h>
#include "OrigamiTypeDefine.h"
#include "CommonDefine.h"
#include "MPU9250.h"
#include "I2Clib.h"
#include "EEPROM.h"
#include "init.h"
#include "CAN.h"

const UBYTE MPU9250_ADDR    = 0x68;
const UBYTE WHO             = 0x75;
const UBYTE WHO_VALUE       = 0x71;
const UBYTE SMPLRT_DIV      = 0x19;   // Sample rate divider
const UBYTE CONFIG          = 0x1A;
const UBYTE GYRO_CONFIG     = 0x1B;
const UBYTE ACCEL_CONFIG    = 0x1B;
const UBYTE ACCEL_CONFIG2   = 0x1C;
const UBYTE FIFO_EN         = 0x23;
const UBYTE INT_PIN_CONFIG  = 0x37;
const UBYTE INT_STATUS      = 0x3A;
const UBYTE IMU_DATA        = 0x3B;
const UBYTE ACCEL_DATA      = 0x3B;
const UBYTE TEMP_DATA       = 0x41;
const UBYTE GYRO_DATA       = 0x43;
const UBYTE PWR_MGMT_1      = 0x6B;

/// Method

/*
 *  read register buffer of MPU9250
 *	arg      :   address of register
 *	return   :   int. result
 *	TODO     :   nothing
 *	FIXME    :   not yet
 *	XXX      :
 */
int readAddr(char address)
{
     int ans ;
     ans = startI2C(MPU9250_ADDR,RW_0);
     if (ans == 0) {
          sendI2CData(address);
          restartI2C(MPU9250_ADDR,RW_1);
          ans = readI2CData(NOACK);
     } else ans = -1;
     stopI2C();
     return ans;
}

/*
 *  write register buffer of MPU9250
 *	arg      :   address of register, buffer to write
 *	return   :   int. result
 *	TODO     :   nothing
 *	FIXME    :   not yet
 *	XXX      :
 */
int writeAddr(char address, char val)
{
     int ans ;
     ans = startI2C(MPU9250_ADDR,RW_0);
     if (ans == 0) {
          sendI2CData(address) ;
          sendI2CData(val) ;
     } else ans = -1 ;
     stopI2C() ;
     return ans ;
}

/*
 *  initialize MPU9250
 *	arg      :   address of register
 *	return   :   int. result
 *	TODO     :   nothing
 *	FIXME    :   not yet
 *	XXX      :
 */
int initIMU()
{
    int ans ;
     __delay_us(2000) ;
     ans = readAddr(WHO) ;
     if (ans == WHO_VALUE) {
          writeAddr(PWR_MGMT_1,0x00);    //wake up sensor
          writeAddr(INT_PIN_CONFIG,0x02);//BYPASS:enabled, FSYNC:disabled
          writeAddr(SMPLRT_DIV,0xFF);    //divider:256, sample rate:30kHz
          writeAddr(CONFIG,0x07);        //FIFO, FSYNC:disabled, DLPF:7
          writeAddr(GYRO_CONFIG,0x18);   //range:±2000dps, bandwidth:8800Hz
          writeAddr(ACCEL_CONFIG,0x07);  //range:±16g
          writeAddr(ACCEL_CONFIG2,0x35); //bandwidth:1130Hz
          writeAddr(FIFO_EN,0x00);       //FIFO:all disabled
          __delay_us(2000);
     } else ans = -1 ;
     return ans ;
}

/*
 *  read IMU data from MPU9250
 *	arg      :   address of register
 *	return   :   int. result
 *	TODO     :   nothing
 *	FIXME    :
 *	XXX      :
 */
int readIMU(UBYTE *data, int offset)
{
     int ans , i , ack ;

     while(ans != 0x01){
         ans = readAddr(INT_STATUS) ;
         ans = ans & 0x01;
     }

     ans = startI2C(MPU9250_ADDR,RW_0);
     if (ans == 0) {
          sendI2CData(IMU_DATA) ;
          restartI2C(MPU9250_ADDR,RW_1) ;
          ack = ACK ;
          for (i=0 ; i<14 ; i++) {
               if (i==13) ack = NOACK ;
               data[offset+i] = readI2CData(ack);
          }
     } else ans = -1 ;
     stopI2C() ;
     return ans ;
}

/*
 *  read IMU sequence
 *	arg      :   IMUstarttime, timespan (second)
 *	return   :   nothing
 *	TODO     :   nothing
 *	FIXME    :   timer loop, dateStruct
 *	XXX      :   wait time for eeprom memorize
 */
void readIMUSequence(/*struct dateStruct IMUstarttime, */UBYTE timespan){
    int checkFlag = 0;
    UINT bufIMU[16];
    char EEPROMH = 0x00;
    char EEPROML = 0x00;
    //  FIXME : max value = 65536. if sampling count > 65536, this may cause error without reproducibility
    UINT IMUSamplingCounter = 0;
    for(unsigned int i=0;i<16;i++){
        bufIMU[i]=0x00;
    }
    while(1) {
        EEPROMH = 0x00;
        EEPROML = 0x00;
        checkFlag = 0;
        for(unsigned int i=0;i<16;i++){
            bufIMU[i]=0x00;
        }
        //244count -> 1
        IMUSamplingCounter = 0;
        //  FIXME : it must be timer loop not const loop
        //while(1/*globalCount-time <= 310*/){
        for (UINT j = 0; j < 200; j++) {
            checkFlag = readIMU(bufIMU,0);
            //  XXX : 20ms is need to be more smaller
            __delay_us(20);
            checkFlag = writeEEPROM(EE_P0_0, EEPROMH, EEPROML, bufIMU, 16);
            IMUSamplingCounter ++;
            //  XXX : 3000ms is need to be more smaller
            __delay_us(3000);
            EEPROML +=  0x10;
            if(EEPROML == 0xF0){
                EEPROMH += 0x01;
                EEPROML = 0x00;
            }
            if(EEPROMH == 0xFF && EEPROML == 0xF0){
                //  EEPROM is full. break.
                break;
            }
        }

        for(unsigned int i=0;i<16;i++){
            bufIMU[i]=0x00;
        }
        wait1ms(500);
        EEPROMH = 0x00;
        EEPROML = 0x00;
        // Gyro data send
        for(unsigned int k=0;k<=IMUSamplingCounter;k++){
            checkFlag = 0;
            checkFlag = readEEPROM(EE_P0_0, EEPROMH ,EEPROML ,bufIMU ,8);
            //  XXX : 3000ms is need to be more smaller
            __delay_us(3000);
            sendCanData(bufIMU);
            EEPROML += 0x10;
            if(EEPROML==0xF0){
                EEPROMH += 0x01;      //EEPROMH = EEPROMH+1;
                EEPROML = 0x00;
            }
        }

        EEPROMH = 0x00;
        EEPROML = 0x08;
        //  Accel data send
        for(unsigned int k=0;k<=IMUSamplingCounter;k++){
            readEEPROM(EE_P0_0, EEPROMH ,EEPROML ,bufIMU ,8);
            //  XXX : 3000ms is need to be more smaller
            __delay_us(3000);
            sendCanData(bufIMU);
            EEPROML += 0x10;   //(char)(16))
            if(EEPROML==0xF8){
                EEPROMH += 0x01;      //EEPROMH = EEPROMH+1;
                EEPROML = 0x00;
            }
        }
        wait1ms(3000);
    }
}
