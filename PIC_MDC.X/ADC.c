/// Prolougue

//  AD setting initialise, read Analog voltage for get SMA antenna dBm
//  Author      :   reo kashiyama

/// Include files
#include <xc.h>
#include "CommonDefine.h"
#include "ADC.h"
#include "OrigamiTypeDefine.h"

/// Global data


/// Method
/*
 *  initialise PIC AD setting
 *	arg      :   void
 *	return   :   void
 *	TODO     :   nothing
 *	FIXME    :   not yet
 *	XXX      :
 */
void initAD(void){
    //  enable ADC, GO : not in progress, CHS : AN0
    ADCON0 = 0x01;
    //  TRIGSEL : ECCP1, VCFG : AVdd, VNCFG : AVss, CHSN (Analog negative channel) : AN6
    ADCON1 = 0x00;
    //  ADFM (A/D Result Format Select bit) : Left, ACQT (A/D Acquisition Time Select bits) : 12Tad, ADCS (A/D Conversion Clock Select bits) : Fosc/16
    ADCON2 = 0x2D;
}

/*
 * wait ADC has completed
 *	arg      :
 *	return   :   void
 *	TODO     :
 *	FIXME    :
 *	XXX      :
 */
void waitADCIdle(){
    while(ADCON0bits.GO);
}

/*
 *  read AN0 channel
 *	arg      :   store buffer
 *	return   :   void
 *	TODO     :
 *	FIXME    :   not yet
 *	XXX      :
 */
void readAN0(UBYTE * buf){
    //  CHS : 00000 (AN0)
    ADCON0bits.CHS4 = UINT_FALSE;
    ADCON0bits.CHS3 = UINT_FALSE;
    ADCON0bits.CHS2 = UINT_FALSE;
    ADCON0bits.CHS1 = UINT_FALSE;
    ADCON0bits.CHS0 = UINT_FALSE;
    __delay_us(5);
    ADCON0bits.GO = UINT_TRUE;
    waitADCIdle();
    buf[0] = ADRESL;
    buf[1] = ADRESH;
    return;
}
/*
 *  read AN1 channel
 *	arg      :   store buffer
 *	return   :   void
 *	TODO     :
 *	FIXME    :   not yet
 *	XXX      :
 */
void readAN1(UBYTE * buf){
    //  CHS : 00001 (AN1)
    ADCON0bits.CHS4 = UINT_FALSE;
    ADCON0bits.CHS3 = UINT_FALSE;
    ADCON0bits.CHS2 = UINT_FALSE;
    ADCON0bits.CHS1 = UINT_FALSE;
    ADCON0bits.CHS0 = UINT_TRUE;
    __delay_us(5);
    ADCON0bits.GO = UINT_TRUE;
    waitADCIdle();
    buf[0] = ADRESL;
    buf[1] = ADRESH;
    return;
}
/*
 *  read AN2 channel
 *	arg      :   store buffer
 *	return   :   void
 *	TODO     :
 *	FIXME    :   not yet
 *	XXX      :
 */
void readAN2(UBYTE * buf){
    //  CHS : 00010 (AN2)
    ADCON0bits.CHS4 = UINT_FALSE;
    ADCON0bits.CHS3 = UINT_FALSE;
    ADCON0bits.CHS2 = UINT_FALSE;
    ADCON0bits.CHS1 = UINT_TRUE;
    ADCON0bits.CHS0 = UINT_FALSE;
    __delay_us(5);
    ADCON0bits.GO = UINT_TRUE;
    waitADCIdle();
    buf[0] = ADRESL;
    buf[1] = ADRESH;
    return;
}
/*
 *  read AN8 channel
 *	arg      :   store buffer
 *	return   :   void
 *	TODO     :
 *	FIXME    :   not yet
 *	XXX      :
 */
void readAN8(UBYTE * buf){
    //  CHS : 01000 (AN8)
    ADCON0bits.CHS4 = UINT_FALSE;
    ADCON0bits.CHS3 = UINT_TRUE;
    ADCON0bits.CHS2 = UINT_FALSE;
    ADCON0bits.CHS1 = UINT_FALSE;
    ADCON0bits.CHS0 = UINT_FALSE;
    __delay_us(5);
    ADCON0bits.GO = UINT_TRUE;
    waitADCIdle();
    buf[0] = ADRESL;
    buf[1] = ADRESH;
    return;
}
/*
 *  read AN9 channel
 *	arg      :   store buffer
 *	return   :   void
 *	TODO     :
 *	FIXME    :   not yet
 *	XXX      :
 */
void readAN9(UBYTE * buf){
    //  CHS : 01001 (AN9)
    ADCON0bits.CHS4 = UINT_FALSE;
    ADCON0bits.CHS3 = UINT_TRUE;
    ADCON0bits.CHS2 = UINT_FALSE;
    ADCON0bits.CHS1 = UINT_FALSE;
    ADCON0bits.CHS0 = UINT_TRUE;
    __delay_us(5);
    ADCON0bits.GO = UINT_TRUE;
    waitADCIdle();
    buf[0] = ADRESL;
    buf[1] = ADRESH;
    return;
}
/*
 *  read AN8 channel
 *	arg      :   store buffer
 *	return   :   void
 *	TODO     :
 *	FIXME    :   not yet
 *	XXX      :
 */
void readAN10(UBYTE * buf){
    //  CHS : 01010 (AN10)
    ADCON0bits.CHS4 = UINT_FALSE;
    ADCON0bits.CHS3 = UINT_TRUE;
    ADCON0bits.CHS2 = UINT_FALSE;
    ADCON0bits.CHS1 = UINT_TRUE;
    ADCON0bits.CHS0 = UINT_FALSE;
    __delay_us(5);
    ADCON0bits.GO = UINT_TRUE;
    waitADCIdle();
    buf[0] = ADRESL;
    buf[1] = ADRESH;
    return;
}
/*
 *  AD Read Me
 *	arg      :   store buffer
 *	return   :   void
 *	TODO     :
 *	FIXME    :   not yet
 *	XXX      :   avoid hardcoding
                 avoid AN0,AN1,,,,
 */
 void readAD(UBYTE *_data){
     //
     ADCON0 = 0x01;
     //ADCON1 = 0x10;
     //ADCON2 = 0x2D; //
     ADCON0bits.GO = UINT_TRUE;
     while(ADCON0bits.GO);
     _data[0] = ADRESH;

     ADCON0 = 0x11;
     //ADCON1 = 0x10;
     //ADCON2 = 0x2D;
     ADCON0bits.GO = UINT_TRUE;
     while(ADCON0bits.GO);

     ADCON0 = 0x05;
     //ADCON1 = 0x10;
     //ADCON2 = 0x2D; //
     ADCON0bits.GO = UINT_TRUE;
     while(ADCON0bits.GO);
     _data[1] = ADRESH;

     ADCON0 = 0x11;
     //ADCON1 = 0x10;
     //ADCON2 = 0x2D;
     ADCON0bits.GO = UINT_TRUE;
     while(ADCON0bits.GO);

     ADCON0 = 0x05;
     //ADCON1 = 0x10;
     //ADCON2 = 0x2D; //
     ADCON0bits.GO = UINT_TRUE;
     while(ADCON0bits.GO);
     _data[2] = ADRESH;

     ADCON0 = 0x11;
     //ADCON1 = 0x10;
     //ADCON2 = 0x2D;
     ADCON0bits.GO = UINT_TRUE;
     while(ADCON0bits.GO);

     ADCON0 = 0x21;
     //ADCON1 = 0x10;
     //ADCON2 = 0x2D; //
     ADCON0bits.GO = UINT_TRUE;
     while(ADCON0bits.GO);
     _data[3] = ADRESH;

     ADCON0 = 0x11;
     //ADCON1 = 0x10;
     //ADCON2 = 0x2D;
     ADCON0bits.GO = UINT_TRUE;
     while(ADCON0bits.GO);

     ADCON0 = 0x25;
     //ADCON1 = 0x10;
     //ADCON2 = 0x2D; //
     ADCON0bits.GO = UINT_TRUE;
     while(ADCON0bits.GO);
     _data[4] = ADRESH;

     ADCON0 = 0x11;
     //ADCON1 = 0x10;
     //ADCON2 = 0x2D;
     ADCON0bits.GO = UINT_TRUE;
     while(ADCON0bits.GO);

     ADCON0 = 0x25;
     //ADCON1 = 0x10;
     //ADCON2 = 0x2D; //
     ADCON0bits.GO = UINT_TRUE;
     while(ADCON0bits.GO);
     _data[5] = ADRESH;

     return;
 }
