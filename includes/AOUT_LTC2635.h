/*
 * AOUT_LTC2635.h
 *
 *  Created on: 01.11.2014
 *      Author: Johannes Strasser
 *
 *      Functions of the Analog out LTC2635 Chip.
 *     	On the home controller EL-100-010-001 only DAC_A and DAC_B are used.
 */

#ifndef AOUT_LTC2635_H_
#define AOUT_LTC2635_H_

extern int dacOUT1;
extern int dacOUT2;

typedef struct {
	int dacValueOut1;
	int dacValueOut2;
} AOUT;

void init_AOUT();

void AOUT_set_internal_reference();
// The LTC2635 is a xxx Bit DAC 0 V = 0 and 10V = 1024
void AOUT_set_value_DACn(int DACchl, int value);

int AOUT_get_value_DACn(unsigned int channel);

#endif /* AOUT_LTC2635_H_ */
