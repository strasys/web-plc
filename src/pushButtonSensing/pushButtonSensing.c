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

int getboolRunStop(char *charRunStop){
	int boolRunStop;
	char charStop[4], charRun[3];
	//char RunStop[5];
	//printf("Übergabe an getboolRunStop = %s\n",charRunStop);
	strcpy(charStop,"stop");
	strcpy(charRun, "run");
	//printf("%s\n",charRunStop);
	//printf("%s\n",charStop);
	//printf("%s\n",charRun);

	if (strcmp(charRunStop,charStop) == 0)
	{
		boolRunStop = 0;
	}
	else if (strcmp(charRunStop,charRun) == 0)
	{
		boolRunStop = 1;
	}
	else
	{
		fprintf(stderr, "String comparison does not match: %s\n", strerror( errno ));
		return EXIT_FAILURE;
	}
	//printf("boolRunStop = %i\n", boolRunStop);
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
	}
		return *charRunStop;
}

int getRunStopStatus() {
	FILE *f = NULL;
	char DIR_getRunStopStatus[255] = {};
	char charRunStop[5] = {};
	char fopenModus[2] = {};
	int flag = 0, RunStopStatus;

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
		fread(charRunStop,sizeof(charRunStop),sizeof(charRunStop),f);
		sprintf(charRunStop,"%s%s",charRunStop,"\0");
		//printf("Info direkt nach fread: %s\n",charRunStop);
		fclose(f);

		RunStopStatus = getboolRunStop(charRunStop);
	}
	else if(flag == 1){
		f = fopen(DIR_getRunStopStatus, fopenModus);
		sprintf(charRunStop, "stop");
		fwrite(charRunStop,5,5,f);
		fclose(f);
		RunStopStatus = 0;
	}
	return RunStopStatus;
}

void writeDigiInStatus(char *DigiInStatus) {
	FILE *f = NULL;
	char DIR_writeDigiInStatus[255] = {};
	char InStatus[7] = {};
	char fopenModus[2] = {};
	char buffer1[4] = {}; //buffer2[5]={};
	int i = 0;
	printf("writeDigiInStatus erreicht\n");

	sprintf(DIR_writeDigiInStatus, "/tmp/pushButtonSensingDigiInStatus.txt");

	if (access(DIR_writeDigiInStatus, (R_OK | W_OK)) != -1){
		sprintf(fopenModus, "r+");
	} else {
		sprintf(fopenModus, "w");
	}

	sprintf(buffer1,"%s",DigiInStatus);
	printf("buffer1 = %s\n", buffer1);
	f = fopen(DIR_writeDigiInStatus, fopenModus);
	for (i=0; i<4; i++){
		sprintf(InStatus,"IN%i:%c\n",i,buffer1[i]);
		fprintf(f,"%s",InStatus);
	}
	fclose(f);

}

int main(int argc, char *argv[], char *env[]){
	char SensingInput[3] = {};
	char InputStatusNew[4] = {'1','1','1','1'};
	char InputStatusOld[4]={'1','1','1','1'};
	char InputStatus[4]={'1','1','1','1'};
	int i = 0, runstop = 1, InNumber, flagWriteDigiInStatus=0, sensingCycleTime;

/*
 * Get arguments what Inputs should be considered
 * for the pushButtonSensing.
 * 0 = sensing no
 * 1 = sensing yes
 */
	if ((argv[1] && argv[2] && argv[3] && argv[4])!=0){
		for (i=1;i<5;i++)
		{
			sscanf(argv[i],"%c",&SensingInput[i-1]);
			printf("Wert SensingInput = %c\n",SensingInput[i-1]);

			if (((SensingInput[i-1]) != '0')&&(SensingInput[i-1] != '1'))
			{
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

	if (argv[5]!=0)
	{
		sensingCycleTime = atoi(argv[5])*1000; //sensing in xx ms
	}
	else
	{
		sensingCycleTime = 80000; //standard sensing time if nothing is set
	}

	while(runstop == 1)
	{

		/*
		 * get status of input channel
		 * 1 = no high signal / 0 = high signal on input
		 * N = Is the marker that this channel is not considered for sensing.
		 */
		for (i=0;i<sizeof(SensingInput)+1;i++)
		{
			if (SensingInput[i] == '1')
			{
				InNumber = i + 8; //8 is the offset to read only IN channels.

				InputStatusNew[i] =	gpio_get_value(IN_OUT[InNumber][0])+'0';

			}
			else
			{
				//Mark an Input which is not considered for pushButtonSensing.
				InputStatus[i] = 'N';
			}
			//It is only interresting to sens the 0 value.
			if ((InputStatusNew[i] == '0') && (InputStatusOld[i] == '1') && (InputStatus[i] != 'N'))
			{
				//change IN switch Status
				if (InputStatus[i] == '1')
					{InputStatus[i] = '0';}
				else if (InputStatus[i] == '0')
					{InputStatus[i] = '1';}

				//set write flag
				flagWriteDigiInStatus = -1;
			}
			//remember status to sense status change
				InputStatusOld[i] = InputStatusNew[i];
		}
		printf("InputStatus = %c\n",InputStatus[0]);
		printf("InputStatus = %c\n",InputStatus[1]);
		printf("InputStatusNew = %c\n",InputStatusNew[0]);
		printf("InputStatusNew = %c\n",InputStatusNew[1]);

		if (flagWriteDigiInStatus == -1)
		{
			writeDigiInStatus(InputStatus);
		}
		usleep(sensingCycleTime);
		//Wihout the getRunStopSatus() it is not possible to control the pushButtonSensing function.
		runstop = getRunStopStatus();
		//set variables to initial status
		flagWriteDigiInStatus = 0;
	}

	return 0;
}

