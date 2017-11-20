#ifndef CAN_H
#define	CAN_H

#include "CommonDefine.h"
#include "OrigamiTypeDefine.h"

#ifndef _XTAL_FREQ
 #define _XTAL_FREQ 16000000       // g—p‚·‚éPIC“™‚É‚æ‚è“®ìü”g”’l‚ğİ’è‚·‚é
#endif

//#define CAN_ID_L  0xEB
//#define CAN_ID_H  0xFF
//#define CAN_EID_L  0xFF
//#define CAN_EID_H  0xFF

void initCan();
void readCanData(UBYTE *read_data);
void sendCanData(UBYTE *send_data);

#endif	/* CAN_H */
