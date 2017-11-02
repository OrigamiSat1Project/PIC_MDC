#define UINT_TRUE       1
#define UINT_FALSE      0
#define TRIS_IN         1
#define TRIS_OUT        0
#define ANSEL_ANALOG    1
#define ANSEL_DIGITAL   0
#define DIGITAL_HIGH    1
#define DIGITAL_LOW     0
#define ACK   0
#define NOACK 1
#define RW_0  0
#define RW_1  1

#define LED_ON PORTBbits.RB7 = DIGITAL_HIGH
#define LED_OFF PORTBbits.RB7 = DIGITAL_LOW
#define SW_ON PORTCbits.RC0 = DIGITAL_HIGH
#define SW_OFF PORTCbits.RC0 = DIGITAL_LOW

#define _XTAL_FREQ    16000000
