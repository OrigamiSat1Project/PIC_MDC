#include <xc.h>
#include "OrigamiTypeDefine.h"
#include "CommonDefine.h"
#include "MPU9250.h"
#include "I2Clib.h"

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

int readAddr(char address)
{
     int ans ;

     ans = I2C_Start(MPU9250_ADDR,RW_0);    // スタートコンディションを発行する
     if (ans == 0) {
          I2C_Send(address) ;                // レジスタアドレスの送信
          I2C_rStart(MPU9250_ADDR,RW_1) ;   // リピート・スタートコンディションを発行する
          ans = I2C_Receive(NOACK);          // データ内容を受信する
     } else ans = -1 ;
     I2C_Stop() ;                            // ストップコンディションを発行する
     return ans ;
}

int writeAddr(char address, char val)
{
     int ans ;

     ans = I2C_Start(MPU9250_ADDR,RW_0);    // スタートコンディションを発行する
     if (ans == 0) {
          I2C_Send(address) ;                // レジスタアドレスの送信
          I2C_Send(val) ;                    // データ内容の送信
     } else ans = -1 ;
     I2C_Stop() ;                            // ストップコンディションを発行する
     return ans ;
}

int initIMU()
{
    int ans ;

     __delay_us(2000) ;                      // 立ち上がりを待つ
     ans = readAddr(WHO) ;            // 接続ＯＫかＩＤを読みだして見る
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

int readIMU(unsigned char *data, int offset)
{
     int ans , i , ack ;

     while(ans != 0x01){
         ans = readAddr(INT_STATUS) ;
         ans = ans & 0x01;
     }

     ans = I2C_Start(MPU9250_ADDR,RW_0);    // スタートコンディションを発行する
     if (ans == 0) {
          I2C_Send(IMU_DATA) ;                // レジスタアドレスの送信
          I2C_rStart(MPU9250_ADDR,RW_1) ;   // リピート・スタートコンディションを発行する
          ack = ACK ;
          for (i=0 ; i<14 ; i++) {
               if (i==13) ack = NOACK ;
               data[offset+i] = I2C_Receive(ack);
          }
     } else ans = -1 ;
     I2C_Stop() ;                            // ストップコンディションを発行する

     return ans ;
}
