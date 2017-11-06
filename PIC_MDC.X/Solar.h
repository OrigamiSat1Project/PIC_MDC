/*
 * File:   Solar.h
 * Author: Tesla
 *
 * Created on 2017/11/07, 0:31
 */

#include "CommonDefine.h"
#include "OrigamiTypeDefine.h"

#define Solar1SW PORTCbits.RC2
#define Solar2SW PORTCbits.RC1

#ifndef SOLAR_H
#define	SOLAR_H

void readSolarData(UBYTE *);

#endif	/* SOLAR_H */
