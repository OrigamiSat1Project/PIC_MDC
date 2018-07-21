#ifndef EEPROM_H
#define	EEPROM_H

#define eeprom_ADDR 0x50
#define EE_P0_0 0x00
#define EE_P0_1 0x01
#define EE_P0_2 0x02
#define EE_P0_3 0x03

int readEEPROM(unsigned char,unsigned char, unsigned char, unsigned char *, int);
int writeEEPROM(unsigned char,unsigned char, unsigned char, unsigned char *, int);
void sendEEPROMdata(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);

#endif	/* EEPROMI2C_H */
