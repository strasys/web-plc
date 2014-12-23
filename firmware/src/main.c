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
#include "functions/I2C-handler.h"
#include "functions/RTC_MCP7940N.h"
#include "functions/GPIO.h"
#include "functions/AOUT_LTC2635.h"

void init(void){

	init_RTC();
	init_GPIO();
	init_AOUT();
	//RTC_print_status();
}


int main(int argc, char *argv[], char *env[])
{
	int AOUTval1, AOUTchannel1;
	char setgetinit;

	if (argv[1] != 0){
	sscanf(argv[1], "%c", &setgetinit);
	}

	if (argv[2] != 0)
	AOUTchannel1 = atoi(argv[2]);

	if (argv[3] != 0)
	AOUTval1 = atoi(argv[3]);

	if (setgetinit == 's'){
	AOUT_set_value_DACn(AOUTchannel1, AOUTval1);
	}
	if (setgetinit == 'i'){
		init();
	}
	if (setgetinit == 'g'){
		printf("Channel: %d \n", AOUTchannel1);
		printf("value: %d \n", AOUT_get_value_DACn(AOUTchannel1));
	}

	return (0);
}

