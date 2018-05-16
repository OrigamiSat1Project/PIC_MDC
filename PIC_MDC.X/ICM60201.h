#ifndef ICM_H
#define	ICM_H

#ifndef _XTAL_FREQ
 // Unless already defined assume 8MHz system frequency
 // This definition is required to calibrate __delay_us() and __delay_ms()
 #define _XTAL_FREQ 16000000       // Žg—p‚·‚éPIC“™‚É‚æ‚è“®ìŽü”g”’l‚ðÝ’è‚·‚é
#endif

int initICM();
int readICM(unsigned char *, int);

#endif	/* ICM_H */