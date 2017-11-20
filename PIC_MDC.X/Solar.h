/*
 * File:   Solar.h
 * Author: Tesla
 *
 * Created on 2017/11/07, 0:31
 */

#include "CommonDefine.h"
#include "OrigamiTypeDefine.h"

#define Solar1SW PORTCbits.RC2  //  DIGITAL_HIGH -> Current value, DIGITAL_LOW => Voltage value
#define Solar2SW PORTCbits.RC1  //  DIGITAL_HIGH -> Current value, DIGITAL_LOW => Voltage value

#define MEASURE_CURRENT_SOLAR1 Solar1SW = DIGITAL_HIGH
#define MEASURE_CURRENT_SOLAR2 Solar2SW = DIGITAL_HIGH
#define MEASURE_VOLTAGE_SOLAR1 Solar1SW = DIGITAL_LOW
#define MEASURE_VOLTAGE_SOLAR2 Solar2SW = DIGITAL_LOW

#ifndef SOLAR_H
#define	SOLAR_H

UINT readSolar1(UBYTE *);
void readSolarSequence(void);

#endif	/* SOLAR_H */
