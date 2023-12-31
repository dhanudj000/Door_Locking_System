/*
 * FILE : EEprom.h
 */

#ifndef EEPROM_H
#define	EEPROM_H

#define SLAVE_WRITE_EEPROM             0b10100000   //0xA0
#define SLAVE_READ_EEPROM              0b10100001   //0xA1

//FUNCTION TO READ FROM ROM
unsigned char eeprom_at24C04_read(unsigned char addr);
//FUNCTION TO WRITE CHARACTER INTO ROM
void eeprom_at24C04_byte_write(unsigned char addr, char data);
//FUNCTION TO WRITE STRING INTO ROM
void eeprom_at24C04_str_write(unsigned char addr, unsigned char *str);

#endif	/* EEPROM_H */