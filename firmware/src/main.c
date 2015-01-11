/*
 * main.c
 *
 *  Created on: 27.09.2014
 *      Author: Johannes Strasser
 *      Author:
 */


#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include "I2C-handler.h"
#include "RTC_MCP7940N.h"
#include "GPIO.h"
#include "AOUT_LTC2635.h"

void init(void){

	init_RTC();
	init_GPIO();
	init_AOUT();
}

void getFormatForDate(char * pDateTime) {
	// formats for date -u
	// date --universal $(/www/pages/cgi-bin/RTChandler g f)
	sprintf(pDateTime, "%2.2d%2.2d%2.2d%2.2d%4.4d", RTC_get_month(),
			RTC_get_day(), RTC_get_hours(), RTC_get_minutes(), RTC_get_year());
}


int main(int argc, char *argv[], char *env[])
{

		init();

		//set time on beaglebone according to RTC time
		// at start up.
			char command[128];
			char dateTime[13];
			getFormatForDate(dateTime);
					sprintf(command,"date -u %s",dateTime);
					system(command);

	return (0);
}

