#ifndef IMU_H
#define	IMU_H

#ifndef _XTAL_FREQ
 // Unless already defined assume 8MHz system frequency
 // This definition is required to calibrate __delay_us() and __delay_ms()
 #define _XTAL_FREQ 16000000       // Žg—p‚·‚éPIC“™‚É�??��æ‚è“®ìŽü”g�??��?��??��l‚ðÝ�??��è‚·‚é
#endif

UWORD sampling_counter = 0x0000;
UBYTE sampling_counterH = 0x00;
UBYTE sampling_counterL = 0x00;

void readIMUsequence_ICM(unsigned char, unsigned char, unsigned char, UINT);
void readIMUsequence_adxl_ITG(unsigned char, unsigned char, unsigned char, UINT);
void readIMUsequence_adxl_ITG_50Hz(unsigned char, unsigned char, unsigned char, UINT);

#endif	/* ADXL_H */