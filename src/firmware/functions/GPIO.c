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
unsigned int IN_OUT_1[][2] = { { 66, 1 }, //P8_07 "out" OUT 1  value 1 = ON; 0 = OFF (= Naming on EL-100-010-001)
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

/*
 * Variable naming is based on the add on board design
 * comments are based on the beaglebone naming.
 * Definition for: EL-100-020-001 (DIN-Rail-controller)
 * applicable device tree: strasys-EL100020001.dts
 */
//definition: 1 = "out"; 0 = "in"
//def.matrix: 0 = PortNumber; 1 = Input =0/Output=1; 2 = Initial value of Output pin
unsigned int IN_OUT_2[][3] = {
		{ 66, 1, 0},	// P8_07 66 OUTPUT "OUT4"
		{ 67, 1, 0},	// P8_08 67 OUTPUT "OUT3"
		{ 69, 1, 0},	// P8_09 69 OUTPUT "OUT2"
		{ 68, 1, 0},	// P8_10 68 OUTPUT "OUT1"
		{ 45, 1, 0},	// P8_11 45 OUTPUT "OUT8"
		{ 44, 1, 0},	// P8_12 44 OUTPUT "OUT7"
		{ 23, 1, 0},	// P8_13 23 OUTPUT "OUT6"
		{ 26, 1, 0},	// P8_14 26 OUTPUT "OUT5"
		{ 47, 0,  },	// P8_15 47 INPUT "IN4"
		{ 46, 0,  },	// P8_16 46 INPUT "IN3"
		{ 27, 0,  },	// P8_17 27 INPUT "IN2"
		{ 65, 0,  },	// P8_18 65 INPUT "IN1"
		{ 86, 1, 0},	// P8_27 86 OUTPUT "OUT9"
		{ 88, 1, 0},	// P8_28 88 OUTPUT "OUT10"
		{ 87, 1, 0},	// P8_29 87 OUTPUT "OUT11"
		{ 89, 1, 0},	// P8_30 89 OUTPUT "OUT12"
		{ 76, 0,  },	// P8_39 76 INPUT "IN5"
		{ 77, 0,  },	// P8_40 77 INPUT "IN6"
		{ 74, 0,  },	// P8_41 74 INPUT "IN7"
		{ 75, 0,  },	// P8_42 75 INPUT "IN8"
		{ 72, 0,  },	// P8_43 72 INPUT "IN9"
		{ 73, 0,  },	// P8_44 73 INPUT "IN10"
		{ 70, 0,  },	// P8_45 70 INPUT "IN11"
		{ 71, 0,  },	// P8_46 71 INPUT "IN12"
		{ 50, 1, 0},	// P9_14 50 OUTPUT "HEARTBEAT"
		{ 48, 1, 0},	// P9_15 48 OUTPUT "ERROR"
		{ 0, 0, 0}
};

//GPIO gpio;
/*
 * devicetype:
 * EL-100-020-001 = 2
 * EL-100-010-001 = 1
 */
void init_GPIO(int devicetype) {
	int i;
	switch(devicetype) {
	case 1:
			//The following for loop sets all OUT_x defined pins
				//as defined

				for (i = 0; !IN_OUT_1 == 0; ++i) {
					gpio_export(IN_OUT_1[i][0]);
					gpio_set_direction(IN_OUT_1[i][0], IN_OUT_1[i][1]);
				}

				gpio_set_value_byte(initStatusOut);

				//set output pins values if values set in one byte
				// gpio_set_out_pin_value_byte(initStatusOut);

				gpio_export(RESET_4D[0]);
				gpio_set_direction(RESET_4D[0], RESET_4D[1]);

				gpio_export(TX_434MHz[0]);
				gpio_set_direction(TX_434MHz[0], TX_434MHz[1]);
				gpio_set_value(TX_434MHz[0], 0);
		break;
	case 2:
			for (i = 0; !IN_OUT_2[i][0] == 0; ++i) {
				gpio_export(IN_OUT_2[i][0]);
				gpio_set_direction(IN_OUT_2[i][0], IN_OUT_2[i][1]);
				//set value if the pin is an output pin.
				if (IN_OUT_2[i][1] == 1){
					gpio_set_value(IN_OUT_2[i][0], IN_OUT_2[i][2]);
				}
			}
			break;
	default: printf("Error init GPIO\n"); break;
	}


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
		gpio_set_value(IN_OUT_1[i][0], tmp);
		statusOut >>= 1;
	}
}

