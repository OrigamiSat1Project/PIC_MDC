#include <xc.h>
#include "HMC.h"
#include "I2Clib.h"

int Mregister_read(char address)
{
     int ans ;

     ans = I2C_Start(HMC_ADRES,RW_0);    // スタートコンディションを発行する
     if (ans == 0) {
          I2C_Send(address) ;                // レジスタアドレスの送信
          I2C_rStart(HMC_ADRES,RW_1) ;   // リピート・スタートコンディションを発行する
          ans = I2C_Receive(NOACK);          // データ内容を受信する
     } else ans = -1 ;
     I2C_Stop() ;                            // ストップコンディションを発行する
     return ans ;
}
// AHMC5883のレジスターにデータを書き込む処理
// adress : 書き込むアドレスを指定
// val    : 書き込むデータを指定
int Mregister_write(char address, char val)
{
     int ans ;

     ans = I2C_Start(HMC_ADRES,RW_0);    // スタートコンディションを発行する
     if (ans == 0) {
          I2C_Send(address) ;                // レジスタアドレスの送信
          I2C_Send(val) ;                    // データ内容の送信
     } else ans = -1 ;
     I2C_Stop() ;                            // ストップコンディションを発行する
     return ans ;
}

int magnet_Init()
{
    int ans ;

     __delay_us(2000) ;                      // 立ち上がりを待つ
     ans = Mregister_read(ID_REGA) ;            // 接続ＯＫかＩＤを読みだして見る
     if (ans == ID_REGA_VALUE) {
          Mregister_write(CONFIG_A,0x18) ;     // ノーマルモード・出力データレートは75Hz
          Mregister_write(CONFIG_B,0x20) ; // ゲイン設定　1090
          Mregister_write(MODE_REG,0x00) ;    // 連続測定モード
          __delay_us(2000) ;                 // 設定されるのを待つ
     } else ans = -1 ;
     return ans ;
}
/*
*    ans : ０＝正常　－１＝読込み失敗(I2C異常)                                 *
******************************************************************************/ 
int magnet_Read(unsigned char *data)
{
     int ans , i , ack ;
     
    while(ans != 0x01){
         ans = Mregister_read(ID_STAT) ;
         ans = ans & 0x02;
    }

     ans = I2C_Start(HMC_ADRES,RW_0);    // スタートコンディションを発行する
     if (ans == 0) {
          I2C_Send(DATA_XM) ;                // レジスタアドレスの送信
          I2C_rStart(HMC_ADRES,RW_1) ;   // リピート・スタートコンディションを発行する
          ack = ACK ;
          for (i=0 ; i<6 ; i++) {
               if (i==5) ack = NOACK ;
               data[i] = I2C_Receive(ack); // ＸＹＺの３軸データを読み出す
          }
     } else ans = -1 ;
     I2C_Stop() ;                            // ストップコンディションを発行する

     return ans ;
}
