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
void setCircuitOffset(int calResistor, int calBitvalue, int channel){
	double specResistance = 0.0175; //Coper at 20°C
	double circuitOffset;
	unsigned int EEPROMregister = 0, i;
	char datatoEEPROM[64] = {};
	unsigned char transferData[64] = {};

	circuitOffset = getPT100temp(calResistor)-getCircuitTemp(calBitvalue);

	sprintf(datatoEEPROM, "R%5.1fPT100temp%6.2fCircuitTemp%6.2fCircuitOffset%5.2f",
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

	for(i = 0; i<=(strlen(datatoEEPROM));i++){
		transferData[i] = datatoEEPROM[i];
	}

	EEPROMwriteblock64(EEPROMregister, transferData);
}

double getTempOffset(){
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
	/*EEPROMreadbytes(0, EEPROMdataGet, 64);
	printf("EEPROMdataGet:\n");
	for(i=0; i<=64; i++){
	printf("%c", EEPROMdataGet[i]);
	}
	printf("\n");
	*/
	return (circuitOffset - wireOffset);
}

int main(int argc, char *argv[], char *env[]){
	int channel, bitVal;
	double temperature, offsetTemp;

	channel = atoi(argv[1]);
	bitVal = get_iio_value_n(channel);
	temperature = getCircuitTemp(bitVal);
	offsetTemp = getTempOffset();
	temperature = temperature + offsetTemp;

	if (argv[2] != 0){


	}


	printf("12 - bit value of channel %i: Temp: %.2f offset: %.2f\n",channel, temperature, offsetTemp);


	return 0;
}
