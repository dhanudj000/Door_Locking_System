/* 
 * File:   main.h
 * Author: konir
 *
 * Created on December 21, 2023, 11:00 AM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
#include "EEprom.h"
#include "clcd.h"
#include "i2c.h"
#include "matrix_keypad.h"
#include "timers.h"
#include <string.h>

#define RESET_SCREEN 0x0A
#define RESET_NOTHING 0x0B
#define SET_PASS 0x00
#define LOGIN_SCREEN 0x01
#define OPEN_DOOR 0x02

void set_pass(unsigned char key , unsigned char *reset);
void login_screen(unsigned char key , unsigned char *reset);
void unlock_door(unsigned char key , unsigned char * reset);
#endif	/* MAIN_H */

