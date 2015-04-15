/*
 * PT100handler.c
 *
 *  Created on: 28.12.2014
 *      Author: Johannes Strasser
 *
 *This program is supposed to be called from the server
 *to read the PT100's on the strasys board's.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "PT100functions.h"
#include "24AA256-EEPROM.h"


/*
 * PT100handler functions:
 * EEPROM init:
 * it is needed to unbind the relevant EEPROM to read and write with this program
 * set circuit offset (= op-amp circuit on the strasys board):
 * ./PT100handler 1(=channel-number) s(=set) c(=circuit) 100.1(=calibration Resistor) 1(=int Number)
 * set wire offset (= compensation of resistance of 2 wire PT100 sensors):
 * ./PT100handler 1(=channel-number) s(=set) w(=wire) 10.0(=length of wire in meter) 0.25(= area of wire in mm²)
 * get temperature:
 * ./PT100handler 1(=channel-number) g(=get) t(=temperature)
 * get circuit offset Data:
 * ./PT100handler 1(=channel-number) g(=get) c(=circuit)
 * get wire offset Data:
 * ./PT100handler 1(=channel-number) g(=get) w(=wire)
 */

int main(int argc, char *argv[], char *env[]){
	int channel;
	double calResistor=0, lengthWire = 0, areaWire = 0;
	double tempOffsetCircuitData[4];
	double tempOffsetWireData[4];
	char setget[2] = {};
	char init[1] = {};

	if (argv[1] != 0){
		sscanf(argv[1], "%c", &init[0]);
		if (init[0] == 'i'){
			EEPROMinit(1, 54);
		} else {
			channel = atoi(argv[1]);



		if (argv[2] != 0){
			sscanf(argv[2], "%c", &setget[0]);				// Set argument necessary to set the circuit and wire length offset.

			if ((setget[0] == 's') && ((argv[3] && argv[4]) != 0)){
				sscanf(argv[3], "%c", &setget[1]);

				if (setget[1] == 'c'){				// c = circuit offset argument.
					calResistor = atof(argv[4]);
				//	printf("channel:%i \nSet:%c \nCircuit or Wire:%c\n Circuit offset:%5.2f\n",channel,setget[0],setget[1],calResistor);
					setCircuitOffset(calResistor, channel);
				}
				else if (setget[1] == 'w'){			// w = wire offset of wire length
					lengthWire = atof(argv[4]);		// value in meter
					areaWire = atof(argv[5]);		// value in mm²
					setWireOffset(channel,lengthWire, areaWire);
				}
				else
				{
					fprintf(stderr, "Arguments mismatch: %s\n", strerror( errno ));
					return EXIT_FAILURE;
				}
			}
			else if (setget[0] == 'g'){
				sscanf(argv[3], "%c", &setget[1]);

				if (setget[1] == 't'){

					printf("%.01f\n",getTemp(channel));

				}
				else if (setget[1] == 'c') {
					getCircuitOffsetData(channel, tempOffsetCircuitData);
					printf("Calibration information of PT100 channel %i:\n\n", channel);
					printf("R = %5.1f Ohm\n", tempOffsetCircuitData[0]);
					printf("PT100 element temperature at R = %6.2f °C\n", tempOffsetCircuitData[1]);
					printf("Temperature based on simulated / ideal el. circuit = %6.2f °C\n", tempOffsetCircuitData[2]);
					printf("Offset temperature of channel %d set to %5.2f °C\n", channel, tempOffsetCircuitData[3]);
				}
				else if (setget[1] == 'w'){
					getWireOffsetData(channel, tempOffsetWireData);
					printf("Wire offset information of PT100 channel %i:\n\n",channel);
					printf("Wire based offset temperature = %5.2f °C\n",tempOffsetWireData[0]);
					printf("Wire length = %6.2f m\n", tempOffsetWireData[1]);
					printf("Wire area = %4.2f mm²\n", tempOffsetWireData[2]);
					printf("Calculated wire resistance = %5.2f Ohm\n", tempOffsetWireData[3]);
				}
				else {
					fprintf(stderr, "Arguments mismatch: %s\n", strerror( errno ));
					return EXIT_FAILURE;
				}
			}
		} else {
				fprintf(stderr, "Arguments mismatch: %s\n", strerror( errno ));
				return EXIT_FAILURE;
			}
		}

	}
	else
	{
		fprintf(stderr, "No arguments added: %s\n", strerror( errno ));
		return EXIT_FAILURE;
	}

	return 0;
}
