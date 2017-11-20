#ifndef CAN_H
#define	CAN_H

#include "CommonDefine.h"
#include "OrigamiTypeDefine.h"

#ifndef _XTAL_FREQ
 #define _XTAL_FREQ 16000000       // 使用するPIC等により動作周波数値を設定する
#endif

//#define CAN_ID_L  0xEB
//#define CAN_ID_H  0xFF
//#define CAN_EID_L  0xFF
//#define CAN_EID_H  0xFF

void initCan();
void readCanData(UBYTE *read_data);
void sendCanData(UBYTE *send_data);

#endif	/* CAN_H */
