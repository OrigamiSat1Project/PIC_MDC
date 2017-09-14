/* 
 * File:   eepromI2C.h
 * Author: ティンダル
 *
 * Created on 2016/10/25, 3:10
 */

#ifndef EEPROMI2C_H
#define	EEPROMI2C_H

#define eeprom_ADRES 0x50 //デバイスアドレス>>1
#define EE_P0_0 0x00
#define EE_P0_1 0x01

int eep_read(char ee_p,char address1, char address2, char *val, int n);
int eep_send(char ee_p,char address1, char address2, char *val, int n);

#endif	/* EEPROMI2C_H */

