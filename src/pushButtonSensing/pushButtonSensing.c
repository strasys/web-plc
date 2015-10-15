/*
 * pushButtonSensing.c
 *
 *  Created on: 14.10.2015
 *      Author: Johannes Strasser
 *      www.strasys.at
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "GPIO.h"

int getboolRunStop(char charRunStop){
	int boolRunStop;
	switch (boolRunStop){
	case "stop":
		boolRunStop = 0;
		break;
	case "run":
		boolRunStop = 1;
		break;

	return boolRunStop;
}

char getcharRunStop(int boolRunStop){
		char charRunStop[5] = {};

		switch (boolRunStop){
		case 0:
			sprintf(charRunStop, "stop");
			break;
		case 1:
			sprintf(charRunStop, "run");
			break;

		return charRunStop;
	}

int getRunStopStatus() {
	FILE *f = NULL;
	char DIR_getRunStopStatus[255] = {};
	char charRunStop[5] = {};
	char fopenModus[2] = {};
	int flag = 0;

	sprintf(DIR_getRunStopStatus, "/tmp/pushButtonSensingRunStop.txt");

	if (access(DIR_getRunStopStatus, (R_OK | W_OK)) != -1) {
		sprintf(fopenModus, "r+");
		flag = 0;
	} else {
		sprintf(fopenModus, "w");
		flag = 1;
	}

	if (flag == 0){
		f = fopen(DIR_getRunStopStatus, fopenModus);
		fread(charRunStop,sizeof(charRunStop),f);
		fclose(f);
		return getboolRunStop(charRunStop);
	}
	else if(flag == 1){
		f = fopen(DIR_getRunStopStatus, fopenModus);
		sprintf(charRunStop, "stop");
		fwrite(charRunStop,5,f);
		fclose(f);
		return 0;
	}
}

void writeDigiInStatus(int boolDigiInStatus[][]) {
	FILE *f = NULL;
	char DIR_writeDigiInStatus[255] = {};
	char InStatus[7] = {};
	char fopenModus[2] = {};
	int i = 0;

	sprintf(DIR_writeDigiInStatus, "/tmp/pushButtonSensingDigiInStatus.txt");

	if (access(DIR_writeDigiInStatus, (R_OK | W_OK)) != -1){
		sprintf(fopenModus, "r+");
	} else {
		sprintf(fopenModus, "w");
	}

	f = fopen(DIR_writeDigiInStatus, fopenModus);
	for (i=0; i<4; i++){
		sprintf(InStatus,"IN%i:%i\n",boolDigiInStatus[i][1]);
		fprintf(f,"%s",InStatus);
	}
	fclose(f);

}

int main(int argc, char *argv[], char *env[]){
	int SensingInput[4] = {0,0,0,0};
	int i = 0;

/*
 * Get arguments what Inputs should be considered
 * for the pushButtonSensing.
 * 0 = sensing no
 * 1 = sensing yes
 */
	if (argv[1] && argv[2] && argv[3] && argv[4]!=0){
		for (i=1;i<5;i++){
		sscanf(argv[i],"%i",&SensingInput[i-1]);
		if (SensingInput[i-1] != (0 || 1)){
			fprintf(stderr, "Wrong argument value: %s\n", strerror( errno ));
			return EXIT_FAILURE;
			}
		}
	}
	else
	{
		fprintf(stderr, "To view arguments: %s\n", strerror( errno ));
		return EXIT_FAILURE;
	}

while()
	gpio_get_value(IN_OUT[i][0]);

usleep(50000);
}

