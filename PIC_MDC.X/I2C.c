#include <xc.h>
//#include "UART.h"
//#include "Type_define.h"

#define _XTAL_FREQ 10000000
unsigned char EEPROMData[32];

void Init_I2C_M(const unsigned long c){
  SSPCON1 = 0b00101000;
  SSPCON2 = 0;
  SSPADD = (_XTAL_FREQ/(4*c))-1;
  SSPSTAT = 0;
}

void I2C_Master_Wait(){
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Master_Start(){
  I2C_Master_Wait();
  SEN = 1;
}

void I2C_Master_RepeatedStart(){
  I2C_Master_Wait();
  RSEN = 1;
}

void I2C_Master_Stop(){
  I2C_Master_Wait();
  PEN = 1;
}

void I2C_Master_Write(unsigned d){
  I2C_Master_Wait();
  SSPBUF = d;
}

unsigned char I2C_Master_Read(unsigned char a){
  unsigned char temp;
  I2C_Master_Wait();
  RCEN = 1;
  I2C_Master_Wait();
  temp = SSPBUF;
  I2C_Master_Wait();
  ACKDT = (a)?0:1;
  ACKEN = 1;
  return temp;
}

void EEPROM_Write(unsigned char EEPROM_address,unsigned char high_address,unsigned char low_address,unsigned char *data){
    unsigned char Address = EEPROM_address << 1;
    //unsigned int Datasize = sizeof(data);
    /**/
    I2C_Master_Start();         //Start condition
    I2C_Master_Write(Address);     //7 bit address + Write
    I2C_Master_Write(high_address);    //Adress High Byte
    I2C_Master_Write(low_address);    //Adress Low Byte
    while(*data){
        I2C_Master_Write(*data);    //Data
        ++data;
    }
    I2C_Master_Stop();          //Stop condition
    __delay_ms(200);
}

unsigned char *EEPROM_Read(unsigned char EEPROM_address,unsigned char high_address,unsigned char low_address, unsigned int DataSize){
    unsigned char Address = EEPROM_address << 1;
    unsigned char ReadAddress = Address | 0x01;
    
    
    //unsigned int Datasize = sizeof(data);
    I2C_Master_Start();         //Start condition
    I2C_Master_Write(Address);     //7 bit address + Write
    I2C_Master_Write(high_address);    //Adress High Byte
    I2C_Master_Write(low_address);    //Adress Low Byte
    I2C_Master_RepeatedStart();         //Restart condition
    
    
    I2C_Master_Write(ReadAddress);     //7 bit address + Read
    for(unsigned int i = 0; i < DataSize-1; i++){
        EEPROMData[i] = I2C_Master_Read(1); //Read + Acknowledge
    }
    EEPROMData[DataSize-1] = I2C_Master_Read(0);
    I2C_Master_Stop();          //Stop condition
    /*
    for(unsigned int j = 0; j < DataSize; j++){
        putch(EEPROMData[j]);
    }*/
    return EEPROMData;
    __delay_ms(200);
}