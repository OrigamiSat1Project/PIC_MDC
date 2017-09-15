/* 
 * File:   ADC.h
 * Author: Tesla
 *
 * Created on 2017/09/15, 15:26
 */

#ifndef ADC_H
#define	ADC_H

#define AN0  ADCON0 = 0b00000001
#define AN1  ADCON0 = 0b00000101
#define AN2  ADCON0 = 0b00001001
#define AN4  ADCON0 = 0b00010001
#define AN8  ADCON0 = 0b00100001
#define AN9  ADCON0 = 0b00100101
#define AN10 ADCON0 = 0b00101001

void AD_init();
int AD_read(unsigned char *data);

#endif	/* ADC_H */

