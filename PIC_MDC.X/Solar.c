/// Prolougue
/// read IV-charactics of solar film

//  Control EEPROM
//  Author      :   reo kashiyama

#include <xc.h>
#include "Solar.h"
#include "CommonDefine.h"
#include "OrigamiTypeDefine.h"



/// Method
/*
*  read Solar1 voltage
*	arg      :
*	return   :   void
*	TODO     :
*	FIXME    :
*	XXX      :
*/
UBYTE readSolar1Voltage(void){
    Solar1SW = DIGITAL_HIGH;
    __delay_ms(10);
    //  AN0, AN1 -> solar, AN 2 -> thermister
    UBYTE a;
    return a;
}
/*
*  read Solar1 current
*	arg      :
*	return   :   void
*	TODO     :
*	FIXME    :
*	XXX      :
*/
UBYTE readSolar1Current(void){
    Solar1SW = DIGITAL_LOW;
    __delay_ms(10);
    //  AN0, AN1 -> solar, AN 2 -> thermister
    UBYTE a;
    return a;
}
/*
*  read Solar1 temperature
*	arg      :
*	return   :   void
*	TODO     :
*	FIXME    :
*	XXX      :
*/
UBYTE readSolar1Thermistor(void){
    //  AN0, AN1 -> solar, AN 2 -> thermister
    UBYTE a;
    return a;
}

/*
*  read Solar2 voltage
*	arg      :
*	return   :   void
*	TODO     :
*	FIXME    :
*	XXX      :
*/
UBYTE readSolar2Voltage(void){
    Solar2SW = DIGITAL_HIGH;
    __delay_ms(10);
    //  AN0, AN1 -> solar, AN 2 -> thermister
    UBYTE a;
    return a;
}

/*
*  read Solar2 current
*	arg      :
*	return   :   void
*	TODO     :
*	FIXME    :
*	XXX      :
*/
UBYTE readSolar2Current(void){
    Solar2SW = DIGITAL_LOW;
    __delay_ms(10);
    //  AN0, AN1 -> solar, AN 2 -> thermister
    UBYTE a;
    return a;
}
/*
*  read Solar2 temperature
*	arg      :
*	return   :   void
*	TODO     :
*	FIXME    :
*	XXX      :
*/
UBYTE readSolar2Thermistor(void){
    //  AN0, AN1 -> solar, AN 2 -> thermister
    UBYTE a;
    return a;
}
/*
*  read Solar1, 2 data
*	arg      :
*	return   :   I(current), V(voltage), T(temperature)
*	TODO     :
*	FIXME    :
*	XXX      :
*/
void readSolarData(UBYTE *IVTs){
    IVTs[0] = readSolar1Voltage();
    IVTs[1] = readSolar1Current();
    IVTs[2] = readSolar1Thermistor();
    IVTs[3] = readSolar2Voltage();
    IVTs[4] = readSolar2Current();
    IVTs[5] = readSolar2Thermistor();
    return;
}
