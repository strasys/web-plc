/*
 * I2C_init.c
 *
 *  Created on: 27.09.2014
 *      Author: Johannes Strasser
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

void init(void){

	init_RTC();
	init_GPIO();
	//RTC_print_status();
}


int main(int argc, char *argv[], char *env[])
{

	init();
	return (0);
}

