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
#include "GPIO.h"

int main(int argc, char *argv[], char *env[]){
	int i = 0;
	int Num = 0, Value = 0;
	int GPIOstatval[12];
	char setget;
	char InOut;


	if (argv[1] != 0){
	sscanf(argv[1], "%c", &setget);
	}


	if ((setget == 's')){
		Num = atoi(argv[2]);
		Value = atoi(argv[3]);

		//Num = GPIOnum;
		//Value = GPIOvalue;
		printf("Num=%d Value=%d\n",Num, Value);
		printf("Value=%d\n", Value);
		gpio_set_value(IN_OUT[Num][0], Value);
		for (i = 0; i < 8; i++){
				GPIOstatval[i] = gpio_get_value(IN_OUT[i][0]);
				printf("%d\n", GPIOstatval[i]);
				}
	}

	if ((setget == 'g')){
		sscanf(argv[2], "%c", &InOut);

		if ((InOut == 'O')){
			for (i = 0; i < 8; i++){
			GPIOstatval[i] = gpio_get_value(IN_OUT[i][0]);
			printf("%d\n", GPIOstatval[i]);
			}
		}

		else if ((InOut == 'I')){
			for (i = 8; i < 12; i++){
			GPIOstatval[i] = gpio_get_value(IN_OUT[i][0]);
			printf("%d\n", GPIOstatval[i]);
			}
		}
	}

	return 0;
}
