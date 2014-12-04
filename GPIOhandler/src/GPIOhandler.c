/*
 * RTChandler.c
 *
 *  Created on: 08.11.2014
 *      Author: Johannes Strasser
 *
 *This program is supposed to be called from the server
 *to set and read the on board RTC.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "/home/johannes/git/firmware/src/functions/GPIO.h"

int main(int argc, char *argv[], char *env[]){
	int i = 0;
	int Num, Value;
	int GPIOstatval[8];
	char setget, GPIOvalue, GPIOnum;

	if (argv[1] != 0){
	sscanf(argv[1], "%c", &setget);
	}


	if ((setget == 's')){
		sscanf(argv[2], "%c", &GPIOnum);
		sscanf(argv[3], "%c", &GPIOvalue);
		Num = atoi(&GPIOnum);
		Value = atoi(&GPIOvalue);
		gpio_set_value(IN_OUT[Num][0], Value);
		for (i = 0; i < 8; i++){
				GPIOstatval[i] = gpio_get_value(IN_OUT[i][0]);
				printf("%d\n", GPIOstatval[i]);
				}
	}

	if ((setget == 'g')){
		for (i = 0; i < 8; i++){
		GPIOstatval[i] = gpio_get_value(IN_OUT[i][0]);
		printf("%d\n", GPIOstatval[i]);
		}
	}

	return 0;
}
