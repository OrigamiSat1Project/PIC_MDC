#ifndef ITG_H
#define	ITG_H


#ifndef _XTAL_FREQ
 // Unless already defined assume 8MHz system frequency
 // This definition is required to calibrate __delay_us() and __delay_ms()
 #define _XTAL_FREQ 16000000       // Žg—p‚·‚éPIC“™‚É�?�æ‚è“®ìŽü”g�?��?�l‚ðÝ�?�è‚·‚é
#endif

int initITG();
int readITG(unsigned char *, int);

#endif	/* ITG_H */
