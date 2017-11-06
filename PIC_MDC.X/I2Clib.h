#ifndef I2CLIB_H
#define	I2CLIB_H

void interruptI2C( void ) ;
void changeMSSPModeToI2C(int) ;
int  startI2C(int ,int ) ;
int  restartI2C(int ,int ) ;
int  stopI2C( void ) ;
int  sendI2CData(char ) ;
int  readI2CData(int ) ;

#endif	/* I2CLIB_H */
