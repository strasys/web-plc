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

#define AOUT_DIR "/usr/lib/cgi-bin/AOUTlastsetvalue.txt"

void init_AOUT();

void AOUT_set_internal_reference();
// The LTC2635 is a xxx Bit DAC 0 V = 0 and 10V = 1024
void AOUT_set_value_DACn(int DACchl, int value);

//Function to write set value in a txt file to read back!
void AOUT_write_value_DACn(int channel, int value);

int AOUT_get_value_DACn(unsigned int channel);

#endif /* AOUT_LTC2635_H_ */
