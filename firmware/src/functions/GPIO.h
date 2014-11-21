/*
 * GPIO.h
 *
 *  Created on: 24.10.2014
 *      Author: Johannes Strasser
 *      www.strasys.at
 */

#ifndef GPIO_H_
#define GPIO_H_

#define GPIO_DIR "/sys/class/gpio"

unsigned int IN_OUT[20][2];
unsigned int RESET_4D[2];
unsigned int TX_434MHz[2];

typedef struct {
	char in[1];	//1 byte in_1 least significant
	int out[2]; //2 byte byte 1 = out_1 least significant bit out_8 is bit 8 and TX_433MHz is bit 1 in byte 2 rest is not defined
	int export[][2]; //
} GPIO;

void init_GPIO();
int gpio_export(int gpio);
int gpio_set_direction(int gpio, int direction);
int gpio_set_value(int gpio, int value);
int gpio_get_value(int gpio);
void gpio_set_value_byte(int statusOut);

#endif /* GPIO_H_ */
