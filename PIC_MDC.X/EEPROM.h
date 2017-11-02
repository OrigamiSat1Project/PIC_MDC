#ifndef EEPROM_H
#define	EEPROM_H

#define eeprom_ADDR 0x50
#define EE_P0_0 0x00
#define EE_P0_1 0x01

int readEEPROM(char ee_p,char address1, char address2, char *val, int n);
int writeEEPROM(char ee_p,char address1, char address2, char *val, int n);

#endif	/* EEPROMI2C_H */
