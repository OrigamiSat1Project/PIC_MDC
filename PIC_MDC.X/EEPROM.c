/// Prolougue

//  Control EEPROM
//  Author      :   reo kashiyama

#include <xc.h>
#include "EEPROM.h"
#include "I2Clib.h"
#include "CommonDefine.h"
#include "OrigamiTypeDefine.h"
#include "CAN.h"


/// Method
/*
 *  read data from EEPROM
 *	arg      :   ee_p, higher address, lower address, buffer, number of buffer
 *	return   :   void
 *	TODO     :   nothing
 *	FIXME    :   not yet
 *	XXX      :   avoid hardcoding
 */
int readEEPROM(char ee_p, char address1, char address2, char *val, int n){
    int ans;
    int ack;
    int i;

    ans = startI2C(eeprom_ADDR | ee_p,RW_0);
    if (ans == 0) {
        sendI2CData(address1) ;
        sendI2CData(address2) ;
        restartI2C(eeprom_ADDR | ee_p,RW_1);
        ack = ACK ;
        for(unsigned int i=0 ; i<n ; i++) {
            if (i==n-1) ack = NOACK ;
            val[i] = readI2CData(ack);
        }
    } else ans = -1 ;
    stopI2C() ;
    return ans ;
}

/*
 *  write data to EEPROM
 *	arg      :   ee_p, higher address, lower address, buffer, number of buffer
 *	return   :   void
 *	TODO     :   nothing
 *	FIXME    :   not yet
 *	XXX      :   avoid hardcoding
 */
int writeEEPROM(char ee_p, char address1,  char address2, char *val, int n){
    int ans;
    int i;

    ans = startI2C(eeprom_ADDR | ee_p,RW_0);
    if (ans == 0) {
        sendI2CData(address1) ;
        sendI2CData(address2) ;
        for(i=0;i<n;i++){
            sendI2CData(val[i]) ;
        }
     } else ans = -1 ;
     stopI2C() ;
     return ans ;
}


void sendEEPROMdata(char ee_p, char address1, char address2, char address3, char address4){
    while(((address1 << 8 ) + address2) != ((address3 << 8) + address4)){
        UBYTE val[8] = {};
        readEEPROM(ee_p,address1,address2,val,8);
        __delay_us(5000);
        sendCanData(val);
        __delay_us(3000);
        address2 += 0x08;
        if(address2 == 0xF0){
            address1 += 0x01;
            address2 = 0x00; 
        }
        if(address1 == 0xF0){
            break;
        }
    }
    return;
}
