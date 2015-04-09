/*
 * GPIO.c
 *
 *  Created on: 24.10.2014
 *      Author: Johannes Strasser
 *      www.strasys.at
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "GPIO.h"

/*
 * Variable naming is based on the add on board design
 * comments are based on the beaglebone naming.
 * Definition for: EL-100-010-001 (home control board)
 * applicable device tree: strasys-homenew.dts
 */
//definition: 1 = "out"; 0 = "in"
unsigned int IN_OUT[][2] = { { 66, 1 }, //P8_07 "out" OUT 1  value 1 = ON; 0 = OFF (= Naming on EL-100-010-001)
		{ 67, 1 }, //P8_08 "out" OUT 2
		{ 69, 1 }, //P8_09 "out" OUT 3
		{ 68, 1 }, //P8_10 "out" OUT 4
		{ 45, 1 }, //P8_11 "out" OUT 5
		{ 44, 1 }, //P8_12 "out" OUT 6
		{ 23, 1 }, //P8_13 "out" OUT 7
		{ 26, 1 }, //P8_14 "out" OUT 8
		{ 47, 0 }, //P8_15 "in"  IN 1  value 1 = low; 0 = high (= pull up circuit)
		{ 46, 0 }, //P8_16 "in"  IN 2
		{ 27, 0 }, //P8_17 "in"  IN 3
		{ 65, 0 }, //P8_18 "in"  IN 4
		{ 0, 0 } };

unsigned int RESET_4D[2] = { 61, 0 }; //P8_26 "in" Pin on Sub - connector for Reset, etc. purposes

unsigned int TX_434MHz[2] = { 60, 1 }; //P9_12 "out" Signal generator for 434 MHz Funkmodul

unsigned int initStatusOut = 0b00000000; // Defines the initial value set of the Output Pins

//GPIO gpio;

void init_GPIO() {
	int i;

	//The following for loop sets all OUT_x defined pins
	//as defined

	for (i = 0; !IN_OUT[i][0] == 0; ++i) {
		gpio_export(IN_OUT[i][0]);
		gpio_set_direction(IN_OUT[i][0], IN_OUT[i][1]);
	}

	gpio_set_value_byte(initStatusOut);

	//set output pins values if values set in one byte
	// gpio_set_out_pin_value_byte(initStatusOut);

	gpio_export(RESET_4D[0]);
	gpio_set_direction(RESET_4D[0], RESET_4D[1]);

	gpio_export(TX_434MHz[0]);
	gpio_set_direction(TX_434MHz[0], TX_434MHz[1]);
	gpio_set_value(TX_434MHz[0], 0);

}

// Export a PIN
// gpio - Number = gpio2[2] = 2*32+2 = 66
int gpio_export(int gpio) {
	FILE *f = NULL;
	f = fopen(GPIO_DIR "/export", "w");
	if (f != NULL) {
		fprintf(f, "%d", gpio);
		fclose(f);
		return 0;
	}
	perror(GPIO_DIR"/gpio/export");
	return 0;
}
// Set if pin is an Input = "in" or an Output = "out"
int gpio_set_direction(int gpio, int direction) {
	FILE *f = NULL;
	char file_dir[255];
	char *direction_str = NULL;

	if (direction == 1) {
		direction_str = "out";
	}
	if (direction == 0) {
		direction_str = "in";
	}

	printf("\"%s\"\n", direction_str);

	snprintf(file_dir, sizeof(file_dir), GPIO_DIR "/gpio%d/direction", gpio);
	f = fopen(file_dir, "w");
	if (f != NULL) {

		fprintf(f, "%s", direction_str);

		fclose(f);
		return 0;
	}
	perror(GPIO_DIR"/gpio/direction");
	return 0;
}

// Set value of the pin
// 1 = Signal "high", 0 = Signal "low"
int gpio_set_value(int gpio, int value) {
	FILE *f = NULL;
	char file_value[255];
	snprintf(file_value, sizeof(file_value), GPIO_DIR "/gpio%d/value", gpio);
	f = fopen(file_value, "w");
	if (f != NULL) {
		fprintf(f, "%d", value);
		fclose(f);
		return 0;

	}
	perror(file_value);
	return 0;
}

int gpio_get_value(int gpio) {
	FILE *f = NULL;
	char file_value[255];
	char value_buffer[255];
	snprintf(file_value, sizeof(file_value), GPIO_DIR "/gpio%d/value", gpio);
	f = fopen(file_value, "r");
	if (f != NULL) {
		int len;
		len = fread(value_buffer, sizeof(char), 255, f);
		fclose(f);
		if (len > 0) {
			value_buffer[len] = 0;
			return atoi(value_buffer);
		}
	}
	perror(GPIO_DIR "/gpio/value");
	return 0;
}

/*
 *	statusOut is one byte which contains the status of 8 Output Pins
 *	The pins are named in the header OUT_x which is essential for
 *	the sequenz to work!
 */

void gpio_set_value_byte(int statusOut) {
	int i = 0;

	for (i = 0; i < 8; i++) {
		int tmp = (statusOut & 1);
		gpio_set_value(IN_OUT[i][0], tmp);
		statusOut >>= 1;
	}
}

