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

void AOUT_set_value_DACn(int DACchl, int value);

#endif /* AOUT_LTC2635_H_ */
