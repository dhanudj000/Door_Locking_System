/*
 ***********************************************************************
 * NAME         : KONIREDDY DHANUNJAYA REDDY                           *
 * DATE         : 16/11/2023                                           *
 * FILE         : EEprom.c                                             *
 * TITLE        : CAR_BLACK_BOX                                        *  
 * DESCRIPTION  : THIS FILE IS TO WRITE AND READ DATA FROM THE AT24C04 *
 * *********************************************************************
 */
#include "EEprom.h"
#include "i2c.h"

unsigned char eeprom_at24C04_read(unsigned char addr)   //FUNCTION TO READ FROM EEPROM USING I2C PROTOCOL
{
    unsigned char data;
    
    i2c_start();
    i2c_write(SLAVE_WRITE_EEPROM);
    i2c_write(addr);                    //START+ROM ADDRESS/WRITE + REGISTER ADDRESS + REP_START + ROM ADDRESS/READ
    i2c_rep_start();
    i2c_write(SLAVE_READ_EEPROM);
    data = i2c_read(0);                 //READ DATA AND STOP
    i2c_stop();
    
    return data;                        //RETURN THE READ DATA
    
}

void eeprom_at24C04_byte_write(unsigned char addr, char data)
{
    i2c_start();                //FUNCTION TO WRITE TO ROM
    i2c_write(SLAVE_WRITE_EEPROM);
    i2c_write(addr);            //START + ROM ADDRESS/WRITE + REGISTER ADDRESS + DATA TO WRITE +STOP
    i2c_write(data);
    i2c_stop();
}

void eeprom_at24C04_str_write(unsigned char addr, unsigned char *str)
{
    unsigned char i = 0;            //FUNCTION TO WRITE A STRING TO ROM
    while(str[i] != '\0')
    {
      eeprom_at24C04_byte_write(addr+i, str[i]);
      i++;                          //WRITE EACH BYTE TO MEMORY USING WRITE FUNCTION UNTIL THE END OF STRING
    }
}
