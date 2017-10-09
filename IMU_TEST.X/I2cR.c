#include <xc.h>
#include "I2cR.h"
#include "I2Clib.h"

int ADregister_read(char address)
{
     int ans ;

     ans = I2C_Start(AD5252_ADRES,RW_0);    // スタートコンディションを発行する
     if (ans == 0) {
          I2C_Send(address) ;                // レジスタアドレスの送信
          I2C_rStart(AD5252_ADRES,RW_1) ;   // リピート・スタートコンディションを発行する
          ans = I2C_Receive(NOACK);          // データ内容を受信する
     } else ans = -1 ;
     I2C_Stop() ;                            // ストップコンディションを発行する
     return ans ;
}

int ADregister_write(char address, char val)
{
     int ans ;

     ans = I2C_Start(AD5252_ADRES,RW_0);    // スタートコンディションを発行する
     if (ans == 0) {
          I2C_Send(address) ;                // レジスタアドレスの送信
          I2C_Send(val) ;                    // データ内容の送信
     } else ans = -1 ;
     I2C_Stop() ;                            // ストップコンディションを発行する
     return ans ;
}

int changeR(){
    
    int ans;
        
    ans = ADregister_write(RDAC1,0xFF);
    
    return ans ;
    
}