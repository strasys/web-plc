/*
 * AOUT_LTC2635.c
 *
 *  Created on: 01.11.2014
 *      Author: Johannes Strasser
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "I2C-handler.h"
#include "AOUT_LTC2635.h"

AOUT aout;

int dacOUT1addr = 0b00000000;	//The last 4 bits describe the address codes
int dacOUT2addr = 0b00000001;
int dacALLaddr = 0b00001111;

int dacOUT1 = 1;
int dacOUT2 = 2;

void AOUT_set_internal_reference() {
	int file, numByte;
	unsigned char buf[3];
	buf[0] = 0b01101111; //The first 4 bit in byte 1 are relevant to set to internal reference.
	buf[1] = 0;
	buf[2] = 0;
	file = i2c_open(I2C2_path, addr_AOUT_LTC2635);
	numByte = i2c_write(file, buf, 3);
	printf("AOUT Number of bytes written: %d", numByte);
	i2c_close(file);
}

// DACchannel is DAC_A or DAC_B
/*
 void AOUT_set_value_DACn(int DACchl, int value){
 int file, numByte;
 unsigned char buf[3];
 buf[0] = 0b00110000; //The first 4 bits COMMAND = Write to and Update (Power Up) DAC Register n.
 buf[1] = 0;
 buf[2] = 0;

 file = i2c_open(I2C2_path, addr_AOUT_LTC2635);

 i2c_close(file);

 }
 */

