/*******************************************************************************
*  skADXL345I2C - ＡＤＸＬ３４５関数ライブラリ(I2Cバージョン)                  *
*             このライブラリは、ADXL345を使った3軸加速度センサモジュール用です *
*             現在このライブラリは各軸の値を読み込む機能のみ対応です。         *
*                                                                              *
*    acceler_Init - ADXL345の初期化を行う処理                                  *
*    acceler_Read - ADXL345の各軸の値を読み込む処理                            *
*                                                                              *
*    メモ：__delay_us() を使用しているので "skADXL345I2C.h" に                 *
*         "#define _XTAL_FREQ 8000000"が記述されています、                     *
*         8MHz以外のCPUクロックにする人は書き換えましょう。                    *
* ============================================================================ *
*  VERSION DATE        BY                    CHANGE/COMMENT                    *
* ---------------------------------------------------------------------------- *
*  1.00    2014-01-29  きむ茶工房(きむしげ)  Create                            *
*  1.01    2014-03-29  きむ茶工房(きむしげ)  ファイル名とacceler_Initの変更    *
*  1.10    2015-10-10  きむ茶工房(きむしげ)  MPLAB X・XC8 V1.32用に書換え      *
* ============================================================================ *
*  PIC 12F1822 16F1827 (このライブラリ自体は他のＰＩＣでもＯＫと思います)      *
*  MPLAB IDE(V8.84)  MPLAB X(v2.15)                                            *
*  MPLAB(R) XC8 C Compiler Version 1.00/1.32                                   *
*******************************************************************************/
#include <xc.h>
#include "I2Clib.h"
#include "skADXL345I2C.h"

// ADXL345のレジスターからデータを読み込む処理
// adress : 読み込むアドレスを指定
int register_read(char address)
{
     int ans ;

     ans = I2C_Start(ADXL345_ADRES,RW_0);    // スタートコンディションを発行する
     if (ans == 0) {
          I2C_Send(address) ;                // レジスタアドレスの送信
          I2C_rStart(ADXL345_ADRES,RW_1) ;   // リピート・スタートコンディションを発行する
          ans = I2C_Receive(NOACK);          // データ内容を受信する
     } else ans = -1 ;
     I2C_Stop() ;                            // ストップコンディションを発行する
     return ans ;
}
// ADXL345のレジスターにデータを書き込む処理
// adress : 書き込むアドレスを指定
// val    : 書き込むデータを指定
int register_write(char address, char val)
{
     int ans ;

     ans = I2C_Start(ADXL345_ADRES,RW_0);    // スタートコンディションを発行する
     if (ans == 0) {
          I2C_Send(address) ;                // レジスタアドレスの送信
          I2C_Send(val) ;                    // データ内容の送信
     } else ans = -1 ;
     I2C_Stop() ;                            // ストップコンディションを発行する
     return ans ;
}
/*******************************************************************************
*  ans = acceler_Init()                                                        *
*    ADXL345の初期化を行う処理                                                 *
*    ans = -1ならADXL345が応答していない                                       *
*******************************************************************************/
int acceler_Init()
{
    int ans ;

     __delay_us(2000) ;                      // 立ち上がりを待つ
     ans = register_read(DEVID) ;            // 接続ＯＫかＩＤを読みだして見る
     if (ans == DEVID_VALUE) {
          register_write(BW_RATE,0x0B) ;     // rate=200Hz
          register_write(DATA_FORMAT,0x00) ; // proto=I2C,res=10bit,range=±2g
          register_write(FIFO_CTL,0x00) ;    // FIFO=bypass
          register_write(POWER_CTL,0x08) ;   // autosleep=off,mode=measure
          __delay_us(2000) ;                 // wait for set config
     } else ans = -1 ;
     return ans ;
}
/*******************************************************************************
*  ans = acceler_Read(*X,*Y,*Z)                                                *
*    ADXL345の各軸の値を読み込む処理                                           *
*                                                                              *
*    *X  : X軸の値を読み込みこの変数にデータを設定                             *
*    *Y  : Y軸の値を読み込みこの変数にデータを設定                             *
*    *Z  : Z軸の値を読み込みこの変数にデータを設定                             *
*    ans : ０＝正常　－１＝読込み失敗(I2C異常)                                 *
*******************************************************************************/
int acceler_Read(unsigned char *data, int n)
{
     int ans , i , ack ;
     
     while(ans != 0x80){
         ans = register_read(INT_SOURCE) ;
         ans = ans & 0x80;
     }
    
     ans = I2C_Start(ADXL345_ADRES,RW_0);    // スタートコンディションを発行する
     if (ans == 0) {
          I2C_Send(DATA_X0) ;                // レジスタアドレスの送信
          I2C_rStart(ADXL345_ADRES,RW_1) ;   // リピート・スタートコンディションを発行する
          ack = ACK ;
          for (i=0 ; i<6 ; i++) {
               if (i==5) ack = NOACK ;
               data[n+i] = I2C_Receive(ack); // ＸＹＺの３軸データを読み出す
          }
     } else ans = -1 ;
     I2C_Stop() ;                            // ストップコンディションを発行する

     return ans ;
}
