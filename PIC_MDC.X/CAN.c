/// Prolougue

//  CAN setting initialise, read Can data from OBC, send Can data to OBC
//  Author      :   reo kashiyama

/// Include files
#include <xc.h>
#include "CAN.h"
#include "CommonDefine.h"
#include "OrigamiTypeDefine.h"

/// Global data
const UBYTE CAN_ID_L   = 0xEB;
const UBYTE CAN_ID_H   = 0xFF;
const UBYTE CAN_EID_L  = 0xFF;
const UBYTE CAN_EID_H  = 0xFF;
/// Method
/*
 *  initialise PIC CAN setting
 *	arg      :   void
 *	return   :   void
 *	TODO     :   nothing
 *	FIXME    :   not yet
 *	XXX      :   avoid hardcoding
 */
void initCan(){
    //TRISCbits.TRISC6 = 0;  //Can設定　RC6=0、RC7=1
    //TRISCbits.TRISC7 = 1;
    CANCON = 0x80; //configモードON
    CANSTAT = 0x80;
    //
    ECANCON = 0x00;
    BRGCON1 = 0x09; //T_Q = 2/Fosc, Sync_seg = 1 * T_Q
    BRGCON2 = 0x91; //Phase_seg1 = 3 * T_Q, Prop_seg = 2 * T_Q;
    BRGCON3 = 0x01; //Phase_seg2 = 2 * T_Q
    /***************************************************************************
     * Nominal bit time = T_Q * (Sync_seg + Prop_seg + Phase_seg1 + Phase_seg2)
     **************************************************************************/
    RXB0CON = 0x40;
    RXB1CON = 0x40;
    //
    TXB0D0 = 0x00;
    TXB0D1 = 0x00;
    TXB0D2 = 0x00;
    TXB0D3 = 0x00;
    TXB0D4 = 0x00;
    TXB0D5 = 0x00;
    TXB0D6 = 0x00;
    TXB0D7 = 0x00;
    TXB0SIDL = 0x00;
    TXB0SIDH = 0x00;
    TXB0DLC = 0x00;
    TXB0CON = 0x00;
    //
    RXB0D0 = 0x00;
    RXB0D1 = 0x00;
    RXB0D2 = 0x00;
    RXB0D3 = 0x00;
    RXB0D4 = 0x00;
    RXB0D5 = 0x00;
    RXB0D6 = 0x00;
    RXB0D7 = 0x00;
    //
    CANSTAT =0x00;
    CANCON = 0x00;
    return;
}


/*
 *  read received Can buffer
 *	arg      :   address of char array (size:8)
 *	return   :   void
 *	TODO     :   nothing
 *	FIXME    :   not yet
 *	XXX      :   wait for RXFUL forever. need received interrupt
*/
void readCanData(char *read_data){
    RXF0SIDH = CAN_ID_H;
    RXF0SIDL = CAN_ID_L;
    RXF0EIDH = CAN_EID_H;
    RXF0EIDL = CAN_EID_L;

    while(RXB0CONbits.RXFUL==0){}
    read_data[0] = RXB0D0;
    read_data[1] = RXB0D1;
    read_data[2] = RXB0D2;
    read_data[3] = RXB0D3;
    read_data[4] = RXB0D4;
    read_data[5] = RXB0D5;
    read_data[6] = RXB0D6;
    read_data[7] = RXB0D7;
    RXB0CONbits.RXFUL = 0;
    return;
}

/*
 *  send Can buffer
 *	arg      :   address of char array (size:8)
 *	return   :   void
 *	TODO     :   nothing
 *	FIXME    :   not yet
 *	XXX      :   wait for RXFUL forever. need received interrupt
 */
void sendCanData(char *send_data){
    //  set data to buffer for sending
    TXB0D0 = send_data[0];
    TXB0D1 = send_data[1];
    TXB0D2 = send_data[2];
    TXB0D3 = send_data[3];
    TXB0D4 = send_data[4];
    TXB0D5 = send_data[5];
    TXB0D6 = send_data[6];
    TXB0D7 = send_data[7];
    //  set buffer for standarf identifier registers
    TXB0SIDL = CAN_ID_L;
    TXB0SIDH = CAN_ID_H;
    TXB0EIDL = CAN_EID_L;
    TXB0EIDH = CAN_EID_H;
    TXB0DLC = 0x08;     //  DataLength = 8 bytes
    TXB0CON = 0x0B;     //  set TXREQ, set priority level
    while(TXB0CONbits.TXREQ){}  //  TXREQ cleared when message is successfully sent
    return;
}
