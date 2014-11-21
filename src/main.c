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
//#include "common.h"
#include "functions/GPIO.h"

// Franz moved I2C2_path

void init(void){



	init_RTC();
	//init_GPIO();
	//RTC_print_status();

}

void decode_value(const char *key, char *value, int size)
{
	int length = 0, i = 0, j = 0;
	char *pos1 = '\0', *pos2 = '\0';
	//if the string key is in the query string
	if( ( pos1 = strstr((char *) getenv("QUERY_STRING"), key)) != NULL )
	{
		//find start of value for this key
		pos1 += strlen(key);

		//printf("pos1:%s\n<br> ",pos1);

		//find length of the value
		if( (pos2 = strstr(pos1,"&")) != NULL ){
			//printf("pos2:%s\n<br> ",pos2 );
			length = pos2 - pos1;
		}
		else{
			length = strlen(pos1);
			//printf("pos2_else: %i\n<br>", length);
		}
		//character by character, copy value from query string
		for(i = 0, j = 0; i <  length ; i++, j++)
		{
			if(j < size) value[j] = pos1[i];
		}
		// Franz: better strncpy(value,pos1,length);

		//add NULL character to end of the value
		if(j < size) value[j] = '\0';
		else value[size-1] = '\0';
		// Frnaz easier value[length] = '\0';

	}
}

int main(int argc, char *argv[], char *env[])
{

	int timeset[3] = {0};
	unsigned char buf[3] = {0};
	char *value, decode[255] = "";
	init();
	// Franz
	char formatted[255];

	RTC_get_time(buf);
	// Franz
	RTC_get_formatted(formatted);
	//transfer_from_bb_to_file();

	//printf("Content-type:text/html\n\n<html><body bgcolor=#23abe2>\n");
	//printf("<p><b>System Time</b></p>\n");
	printf("%2i:%2i:%2i\n", buf[0], buf[1], buf[2]);
	//Franz
	//printf("<p>%s</p><br>\n",formatted);

	//printf("<p><b>Set new time:</b><p><br>\n");
	//printf("<form>\n");

	value = getenv("QUERY_STRING");
	//printf("QUERY_STRING: %s<br>\n", value);

	if (value != NULL){
	strncpy(decode,(char *) getenv("QUERY_STRING"),255);
	//printf("QUERY STRING: %s<BR>\n", decode);
	decode_value( "hours=", (char *) &decode, 255);
	// Franz RTC RTCInfo;
	timeset[0] = atoi(decode);
	// Franz RTC_Info.RTC_hours etc
	//printf("<input type=\"TEXT\" name=\"hours\" size=\"2\" maxlength=\"2\" value=\"%i\">\n",timeset[0]);
	decode_value( "minutes=", (char *) &decode, 255);
	timeset[1] = atoi(decode);
	//printf("<input type=\"TEXT\" name=\"minutes\" size=\"2\" maxlength=\"2\" value=\"%i\">\n",timeset[1]);
	decode_value( "seconds=", (char *) &decode, 255);
	timeset[2] = atoi(decode);
	//printf("<input type=\"TEXT\" name=\"seconds\" size=\"2\" maxlength=\"2\" value=\"%i\">\n",timeset[2]);
	RTC_set_time(timeset);
	// Franz RTC_set_all
	}
/*	else {
		printf("<input type=\"TEXT\" name=\"hours\" size=\"2\" maxlength=\"2\">\n");
		printf("<input type=\"TEXT\" name=\"minutes\" size=\"2\" maxlength=\"2\">\n");
		printf("<input type=\"TEXT\" name=\"seconds\" size=\"2\" maxlength=\"2\">\n");
	} */
	//printf("<input type=\"SUBMIT\" value=\"set time\"><br>");
	//printf("<a href = \"I2C_handling\">Start page</a>");
	//printf("</form></body></html>\n");

	//transfer_from_bb_to_file();


/*
	struct timeval tim;
	double timeStart, timeCurrent;
		int n;

	while(1){
		int initStatus = 0b00000000;
		gettimeofday(&tim, NULL);
		timeStart = tim.tv_sec + tim.tv_usec/1000000.0;

		gpio_set_value_byte(initStatus);
		n = 0;
			while(n < 9){
				gettimeofday(&tim, NULL);
				timeCurrent = tim.tv_sec + tim.tv_usec/1000000.0;

				if (timeCurrent-timeStart > 0.002) {
					gpio_set_value(IN_OUT[0][0],1);
					gettimeofday(&tim, NULL);
					timeStart = tim.tv_sec + (tim.tv_usec/1000000.0);
					n++;
				}
			}

	}

*/
	return (0);
}

