#include <xc.h>
#include "ADtest.h"

void AD_init(){
    ANCON0 = 0x17; //AN2pin_ON
    ANCON1 = 0x07; //AN10pin_ON
    ADCON1 = 0x00; //外部電圧参照設定
    ADCON2 = 0x2D;
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA3 = 1;
    TRISAbits.TRISA5 = 1;
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB4 = 1;
}

int AD_read(unsigned char *data){
    
    //AD読み取り
    AN0; //ADpin_con AN10
    //ADCON1 = 0x10; //外部電圧参照設定
    //ADCON2 = 0x2D; //
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);
    data[0] = ADRESH;
    
    //AD変換クリア
    AN4;
    //ADCON1 = 0x10;
    //ADCON2 = 0x2D;
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);
    
    //AD読み取り
    AN1; //ADpin_con AN10
    //ADCON1 = 0x10; //外部電圧参照設定
    //ADCON2 = 0x2D; //
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);
    data[1] = ADRESH;
    
    //AD変換クリア
    AN4;
    //ADCON1 = 0x10;
    //ADCON2 = 0x2D;
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);
    
    //AD読み取り
    AN2; //ADpin_con AN10
    //ADCON1 = 0x10; //外部電圧参照設定
    //ADCON2 = 0x2D; //
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);
    data[2] = ADRESH;
    
    //AD変換クリア
    AN4;
    //ADCON1 = 0x10;
    //ADCON2 = 0x2D;
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);
    
    //AD読み取り
    AN8; //ADpin_con AN10
    //ADCON1 = 0x10; //外部電圧参照設定
    //ADCON2 = 0x2D; //
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);
    data[3] = ADRESH;
    
    //AD変換クリア
    AN4;
    //ADCON1 = 0x10;
    //ADCON2 = 0x2D;
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);
    
    //AD読み取り
    AN9; //ADpin_con AN10
    //ADCON1 = 0x10; //外部電圧参照設定
    //ADCON2 = 0x2D; //
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);
    data[4] = ADRESH;
    
    //AD変換クリア
    AN4;
    //ADCON1 = 0x10;
    //ADCON2 = 0x2D;
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);
    
    //AD読み取り
    AN10; //ADpin_con AN10
    //ADCON1 = 0x10; //外部電圧参照設定
    //ADCON2 = 0x2D; //
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);
    data[5] = ADRESH;
    
    return 0;
    
}
