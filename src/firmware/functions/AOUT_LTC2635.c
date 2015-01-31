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

void init_AOUT() {
	AOUT_set_internal_reference();
	AOUT_set_value_DACn(dacOUT1, 0);
	AOUT_set_value_DACn(dacOUT2, 0);
}
//This set's the internal reference of the Digital
//to Analog converter.
//For that chip the internal ref. is 2,5 V

void AOUT_set_internal_reference() {
	int file;
	unsigned char buf[3];
	buf[0] = 0b01101111; //The first 4 bit in byte 1 are relevant to set to internal reference.
	buf[1] = 0;
	buf[2] = 0;
	file = i2c_open(I2C2_path, addr_AOUT_LTC2635);
	i2c_write(file, buf, 3);
	//printf("AOUT Number of bytes written: %d\n", numByte);
	i2c_close(file);
}

// DACchannel is DAC_A or DAC_B

void AOUT_set_value_DACn(int DACchl, int value) {
	int file;
	unsigned char buf[3];
	buf[0] = 0b00110000; //The first 4 bits COMMAND = Write to and Update (Power Up) DAC Register n.
	buf[1] = 0;
	buf[2] = 0;

	if (DACchl == 1) {
		buf[0] = buf[0] | dacOUT1addr;
		aout.dacValueOut1 = value;
	}
	if (DACchl == 2) {
		buf[0] = buf[0] | dacOUT2addr;
		aout.dacValueOut2 = value;
	}

	if ((value < 0) | (value > 1024)) {
		printf("Error: DAC value < 0 or > 1023\n");
	} else {
		buf[1] = (value >> 2) & 0xFF;
		//printf("buf 1 %x\n",buf[1]);
		buf[2] = (value << 6) & 0xFF;
		//printf("buf 2 %x\n",buf[2]);
	}

	file = i2c_open(I2C2_path, addr_AOUT_LTC2635);
	i2c_write(file, buf, 3);
	//printf("AOUT Number of bytes written: %d\n", numByte);
	i2c_close(file);
}

int AOUT_get_value_DACn(unsigned int channel) {
	int AOUTn;

	if ((channel == 1) | (channel == 2)) {
		if (channel == 1) {
			AOUTn = aout.dacValueOut1;
		}
		if (channel == 2) {
			AOUTn = aout.dacValueOut2;
		}
	} else {
		printf("Error in Function \"AOUT_get_value_DACn\"! channel = %d",
				channel);
		AOUTn = -1;
	}
	return (AOUTn);
}

