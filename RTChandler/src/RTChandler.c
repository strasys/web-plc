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


int main(int argc, char *argv[], char *env[]){
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
			RTC_set_day(atoi(argv[3]));
			RTC_set_month(atoi(argv[4]));
			RTC_set_year(atoi(argv[5]));
		}

//	if ((setget == 'g')) {
	if (timedate == 'f') {
		// formate for date -u
		printf("%2.2d%2.2d%2.2d%2.2d%4.4d", RTC_get_month(),RTC_get_day()
				                          , RTC_get_hours(),RTC_get_minutes()
										  , RTC_get_year());
	} else {
	printf("%2.2d\n", RTC_get_day());
	printf("%2.2d\n", RTC_get_month());
	printf("%4.4d\n", RTC_get_year());
	printf("%2.2d\n", RTC_get_hours());
	printf("%2.2d\n", RTC_get_minutes());
	printf("%2.2d\n", RTC_get_seconds());
	}
	return 0;
}

