/// Prolougue
/// read IV-charactics of solar film

//  Control EEPROM
//  Author      :   reo kashiyama

#include <xc.h>
#include "ADC.h"
#include "Solar.h"
#include "CommonDefine.h"
#include "OrigamiTypeDefine.h"



/// Method
/*
*  read Solar1 current, voltage, temperature
*	arg      :
*	return   :   buffer size
*	TODO     :  use pointer, separate for each method
*	FIXME    :
*	XXX      :
*/
UINT readSolar1(UBYTE *buf){
    //  MEASURE_CURRENT
    MEASURE_CURRENT_SOLAR1;
    __delay_ms(10);
    //  readAN0
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
    //  readAN1
    ADCON0bits.CHS4 = UINT_FALSE;
    ADCON0bits.CHS3 = UINT_FALSE;
    ADCON0bits.CHS2 = UINT_FALSE;
    ADCON0bits.CHS1 = UINT_FALSE;
    ADCON0bits.CHS0 = UINT_TRUE;
    __delay_us(5);
    ADCON0bits.GO = UINT_TRUE;
    waitADCIdle();
    buf[2] = ADRESL;
    buf[3] = ADRESH;
    //  MEASURE_VOLTAGE
    MEASURE_VOLTAGE_SOLAR1;
    __delay_ms(10);
    //  read AN0
    ADCON0bits.CHS4 = UINT_FALSE;
    ADCON0bits.CHS3 = UINT_FALSE;
    ADCON0bits.CHS2 = UINT_FALSE;
    ADCON0bits.CHS1 = UINT_FALSE;
    ADCON0bits.CHS0 = UINT_FALSE;
    __delay_us(5);
    ADCON0bits.GO = UINT_TRUE;
    waitADCIdle();
    buf[4] = ADRESL;
    buf[5] = ADRESH;
    //  read AN1
    ADCON0bits.CHS4 = UINT_FALSE;
    ADCON0bits.CHS3 = UINT_FALSE;
    ADCON0bits.CHS2 = UINT_FALSE;
    ADCON0bits.CHS1 = UINT_FALSE;
    ADCON0bits.CHS0 = UINT_TRUE;
    __delay_us(5);
    ADCON0bits.GO = UINT_TRUE;
    waitADCIdle();
    buf[6] = ADRESL;
    buf[7] = ADRESH;
    //  MEASURE_TEMPERATURE
    //  read AN2
    ADCON0bits.CHS4 = UINT_FALSE;
    ADCON0bits.CHS3 = UINT_FALSE;
    ADCON0bits.CHS2 = UINT_FALSE;
    ADCON0bits.CHS1 = UINT_TRUE;
    ADCON0bits.CHS0 = UINT_FALSE;
    __delay_us(5);
    ADCON0bits.GO = UINT_TRUE;
    waitADCIdle();
    buf[8] = ADRESL;
    buf[9] = ADRESH;
    return 10;
}
