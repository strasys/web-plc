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
#include "GPIO.h"

void writeRunStop(int boolRunStop) {
	FILE *f = NULL;
	char DIR_writeRunStop[255] = {};
	char charRunStop[5] = {};
	char fopenModus[2] = {};

	sprintf(DIR_writeRunStop, "/tmp/pushButtonSensingRunStop.txt");

	if (access(DIR_writeRunStop, (R_OK | W_OK)) != -1) {
		sprintf(fopenModus, "r+");
	} else {
		sprintf(fopenModus, "w");
	}

	switch (boolRunStop){
	case 0:
		sprintf(charRunStop, "stop");
		break;
	case 1:
		sprintf(charRunStop, "run");
		break;
	}

	f = fopen(DIR_writeRunStop, fopenModus);
	fprintf(f,"%s",charRunStop);
	fclose(f);
}

void writeDigiInStatus(int channel, int boolDigiInStatus) {
	FILE *f = NULL;
	char DIR_writeRunStop[255] = {};
	char charRunStop[5] = {};
	char fopenModus[2] = {};


}

int main(int argc, char *argv[], char *env[]){


}

