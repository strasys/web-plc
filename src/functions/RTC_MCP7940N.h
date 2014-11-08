/*
 * RTC_MCP7940N.h
 *
 *  Created on: 02.10.2014
 *      Author: Johannes Strasser
 */

#ifndef RTC_MCP7940N_H_
#define RTC_MCP7940N_H_

typedef struct {
	int on; // ?
	int seconds;
	int minutes;
	int hours;
	int mode12;
	int mode24;
	int dayOfWeek;
	int day;
	int month;
	int year;
} RTC;

void init_RTC();
void RTC_start_oscillator(int handler);
int RTC_get_seconds();
int RTC_set_seconds(int seconds);
int RTC_get_minutes();
int RTC_set_minutes(int minutes);
int RTC_get_hours();
int RTC_set_hours(int hours);
void RTC_set_hourmode(int handler, int mode);
int RTC_get_dayOfWeek();
int RTC_set_dayOfWeek(int _day);
int RTC_get_day();
int RTC_set_day(int date);
int RTC_get_year();
int RTC_set_year(int year);
int RTC_get_month();
int RTC_set_month(int month);
int RTC_get_time(unsigned char *_time);
void RTC_set_time(int *buf_time);
int RTC_get_datum(unsigned char *_date);
/*
 * RTC_set_datum: buf_date = {day, date, month, year}
 * day = Weekday starting from monday 1-7
 * year only two digits
 */
void RTC_set_datum(unsigned char *buf_date);
int RTC_get_formatted(char * p_formatted);
RTC RTC_get_all();
void RTC_print_status(void);

#endif /* RTC_MCP7940N_H_ */
