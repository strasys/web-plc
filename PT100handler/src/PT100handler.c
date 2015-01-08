/*
 * PT100handler.c
 *
 *  Created on: 28.12.2014
 *      Author: Johannes Strasser
 *
 *This program is supposed to be called from the server
 *to read the PT100's on the strasys board.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "AIN-handler.h"
#include "24AA256-EEPROM.h"

//The following function calculates the temperature
//based on an PT100 resistance input.
//The linear equation is based on a standard PT100
//between -20 to +40 °C.
double getPT100temp(double PT100resistance){

	return ((PT100resistance -100)/0.3893090909); //Temperature in °C.
}

double getWireResistance(double specRes, double length, double area){

	return((2*length*specRes)/area);			//Resistance in Ohm.
}

/*
 * The following function is based on the simulated
 * electronic measurement circuit.
 * The curve is derived by simulating at different
 * PT100 resistances.
 */
double getCircuitTemp(int bitvalue){

	return (0.0148651303*bitvalue - 18.785514); //Temperature in °C;
}

// The following function writes the circuit related offset to the cap EEPROM.
void setCircuitOffset(double calResistor, int calBitvalue, int channel){
	//double specResistance = 0.0175; //Coper at 20°C
	double circuitOffset;
	unsigned int EEPROMregister = 0;
	char datatoEEPROM[64] = {};

	circuitOffset = getPT100temp(calResistor)-getCircuitTemp(calBitvalue);

	sprintf(datatoEEPROM, "R=%5.1f:PT100temp=%6.2f:CircuitTemp=%6.2f:CircuitOffset=%5.2f",
										calResistor,
										getPT100temp(calResistor),
										getCircuitTemp(calBitvalue),
										circuitOffset
										);

	if (channel == 1){
		EEPROMregister = 128;
	}
	if (channel == 2){
		EEPROMregister = 192;
	}

	EEPROMwriteblock64(EEPROMregister, datatoEEPROM);
}

void getCircuitOffsetData(int channel, double data[]){
	unsigned int EEPROMaddressPT100_1 = 138;
	unsigned int EEPROMaddressPT100_2 = 192, address;
	//int EEPROMoffsetR = 0, EEPROMoffsetPT100temp = 15, EEPROMoffsetCircuitTemp = 32, EEPROMoffsetCircuitOffset = 51;
	char EEPROMdata[255] = {};
	char *token = NULL;
	char Rcal[6], PT100temp[7], CircuitTemp[7], CircuitOffset[6];

	if (channel == 1){
		address = EEPROMaddressPT100_1;
		EEPROMreadbytes(address, EEPROMdata, 64);

	}
	if (channel == 2){
		address = EEPROMaddressPT100_2;
		EEPROMreadbytes(address, EEPROMdata, 64);

	} else {
		fprintf(stderr, "Channel Number error: %s\n", strerror( errno ));
	}

	token = strtok(EEPROMdata,"=");
	token = strtok(NULL, ":");
	strcpy(Rcal, token);
	token = strtok(NULL, "=");
	token = strtok(NULL, ":");
	strcpy(PT100temp, token);
	token = strtok(NULL, "=");
	token = strtok(NULL, ":");
	strcpy(CircuitTemp, token);
	token = strtok(NULL, "=");
	token = strtok(NULL, ":");
	strcpy(CircuitOffset, token);


	data[0] = atof(Rcal);
	data[1] = atof(PT100temp);
	data[2] = atof(CircuitTemp);
	data[3] = atof(CircuitOffset);
}
/*
double getTempOffset(int channel){
	double calResistor, wireArea, length, wireOffset, specResistance,
	wireRes;
	int calBitvalue, i;
	FILE *f = NULL;
	char DIR_PT100offset[16] = "PT100offset.txt";
	char EEPROMdataSet[255] = {};
	unsigned char EEPROMdataGet[255] = {};


	calResistor = 99.5;	//example channel 0
	calBitvalue = 1293;
	wireArea = 0.22;
	length = 1;

	wireRes = getWireResistance(specResistance, length, wireArea);
	wireOffset = getPT100temp(wireRes+100);



	f = fopen(DIR_PT100offset, "r+" );
	fprintf(f,"PT100_1:\n offsetWire = %0.2f\n offestCircuit = %0.2f\n",wireOffset, circuitOffset);
	fclose(f);
	sprintf(EEPROMdataSet,"calResistor=%6.2f",calResistor);
	printf("EEPROMdataSet value: %s\n", EEPROMdataSet);

	EEPROMwritebyte(65,'A');
	EEPROMreadbytes(0, EEPROMdataGet, 64);
	printf("EEPROMdataGet:\n");
	for(i=0; i<=64; i++){
	printf("%c", EEPROMdataGet[i]);
	}
	printf("\n");

	return (circuitOffset - wireOffset);
}
*/

int main(int argc, char *argv[], char *env[]){
	int channel, calbitValue;
	double temperature, calResistor, lengthWire, areaWire;
	double tempOffsetCircuitdata[4];
	char setget[2] = {};
	char init[1] = {};

	if (argv[1] != 0){
		//Helper process to check the EEPROM init function!
		sscanf(argv[1], "%c", &init[0]);
		if (init[0] == 'i'){
			EEPROMinit(1, 0x54);
		} else {
			channel = atoi(argv[1]);
		}


		if (argv[2] != 0){
			sscanf(argv[2], "%c", &setget[0]);				// Set argument necessary to set the circuit and wire length offset.

			if ((setget[0] == 's') && ((argv[3] && argv[4] && argv[5]) != 0)){
				sscanf(argv[3], "%c", &setget[1]);

				if (setget[1] == 'c'){				// c = circuit offset argument.
					calResistor = atol(argv[4]);
					calbitValue = atoi(argv[5]);
					setCircuitOffset(calResistor, calbitValue, channel);
					getCircuitOffsetData(channel, tempOffsetCircuitdata);
					printf("Offset temperature of channel %d set to %5.2f", channel, tempOffsetCircuitdata[3]);
				}
				if (setget[1] == 'w'){				// w = wire offset of wire length
					lengthWire = atol(argv[4]);		// value in meter
					areaWire = atol(argv[5]);		// value in mm²
					//todo: add setWireOffset incl. file write
					//todo: add getWireOffset
				}
			} else {
				fprintf(stderr, "Arguments mismatch: %s\n", strerror( errno ));
			}

			if (setget[0] == 'g'){
				sscanf(argv[2], "%c", &setget[1]);

				temperature = getCircuitTemp(get_iio_value_n(channel)) + getTempOffset();
				printf("temperature (channel %i) = %d",channel, temperature);

			} else {
				fprintf(stderr, "Arguments mismatch: %s\n", strerror( errno ));
			}
		}


	}else {
			fprintf(stderr, "No arguments added: %s\n", strerror( errno ));
	}

	return 0;
}
