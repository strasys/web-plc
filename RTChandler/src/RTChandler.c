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
#include "/home/johannes/git/firmware/src/functions/I2C-handler.h"
#include "/home/johannes/git/firmware/src/functions/RTC_MCP7940N.h"



void init(){

	init_RTC();

	//init_GPIO();
	//RTC_print_status();

}


int main(int argc, char *argv[], char *env[]){
	init();
	char setget, timedate;

	if (argv[1] != 0){
	sscanf(argv[1], "%c", &setget);
	sscanf(argv[2], "%c", &timedate);
	}

	if ((setget == 's')&&(timedate == 't')){
		RTC_set_hours(atoi(argv[3]));
		RTC_set_minutes(atoi(argv[4]));
		RTC_set_seconds(atoi(argv[5]));
	}

	if	((setget == 's')&&(timedate == 'd')){
			RTC_set_dayOfWeek(atoi(argv[3]));
			RTC_set_day(atoi(argv[4]));
			RTC_set_month(atoi(argv[5]));
			RTC_set_year(atoi(argv[6]));
		}

	printf("%d\n", RTC_get_dayOfWeek());
	printf("%d\n", RTC_get_day());
	printf("%d\n", RTC_get_month());
	printf("%d\n", RTC_get_year());
	printf("%d\n", RTC_get_hours());
	printf("%d\n", RTC_get_minutes());
	printf("%d\n", RTC_get_seconds());

	return 0;
}


