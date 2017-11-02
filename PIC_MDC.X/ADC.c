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
 *	XXX      :   avoid hardcoding
 */
void initAD(void){
    ANCON0 = 0x17; //AN2pin_ON
    ANCON1 = 0x07; //AN10pin_ON
    ADCON1 = 0x00;
    ADCON2 = 0x2D;
    TRISAbits.TRISA0 = TRIS_IN;
    TRISAbits.TRISA1 = TRIS_IN;
    TRISAbits.TRISA2 = TRIS_IN;
    TRISAbits.TRISA3 = TRIS_IN;
    TRISAbits.TRISA5 = TRIS_IN;
    TRISBbits.TRISB0 = TRIS_IN;
    TRISBbits.TRISB1 = TRIS_IN;
    TRISBbits.TRISB4 = TRIS_IN;
}

/*
 *  AD Read Me
 *	arg      :   store buffer
 *	return   :   void
 *	TODO     :   understand this method
 *	FIXME    :   not yet
 *	XXX      :   avoid hardcoding
                 avoid AN0,AN1,,,,
 */
 void readAD(UBYTE *_data){
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
