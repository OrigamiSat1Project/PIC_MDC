/// Prolougue

//  Control EEPROM
//  Author      :   reo kashiyama

#include <xc.h>
#include "EEPROM.h"
#include "I2Clib.h"
#include "CommonDefine.h"
#include "OrigamiTypeDefine.h"


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

    ans = I2C_Start(eeprom_ADDR | ee_p,RW_0);
    if (ans == 0) {
        I2C_Send(address1) ;                // ���W�X�^�A�h���X�̑��M
        I2C_Send(address2) ;                // ���W�X�^�A�h���X�̑��M
        I2C_Start(eeprom_ADDR | ee_p,RW_1);
        ack = ACK ;
        for(unsigned int i=0 ; i<n ; i++) {
            if (i==n-1) ack = NOACK ;
            val[i] = I2C_Receive(ack);
        }
    } else ans = -1 ;
    I2C_Stop() ;                            // �X�g�b�v�R���f�B�V�����𔭍s����
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

    ans = I2C_Start(eeprom_ADDR | ee_p,RW_0);
    if (ans == 0) {
        I2C_Send(address1) ;                // ���W�X�^�A�h���X�̑��M
        I2C_Send(address2) ;                // ���W�X�^�A�h���X�̑��M
        for(i=0;i<n;i++){
            I2C_Send(val[i]) ;                    // �f�[�^���e�̑��M
        }
     } else ans = -1 ;
     I2C_Stop() ;                            // �X�g�b�v�R���f�B�V�����𔭍s����
     return ans ;
}
