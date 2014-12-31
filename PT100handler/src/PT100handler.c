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

double getTempOffset(){
	double calResistor, wireArea, length, wireOffset, circuitOffset, specResistance,
	wireRes;
	int calBitvalue;
	FILE *f = NULL;
	char DIR_PT100offset[16] = "PT100offset.txt";

	specResistance = 0.0175; //Coper at 20°C
	calResistor = 99.5;	//example channel 0
	calBitvalue = 1293;
	wireArea = 0.22;
	length = 1;
	wireRes = getWireResistance(specResistance, length, wireArea);
	wireOffset = getPT100temp(wireRes+100);

	circuitOffset = getPT100temp(calResistor)-getCircuitTemp(calBitvalue);
	printf("wireOffset Temp %.2f\n circuitOffset %.2f\n wireRes %.3f\n", wireOffset, circuitOffset,
			wireRes);
	f = fopen(DIR_PT100offset, "r+" );
	fprintf(f,"PT100_1:\n offsetWire = %0.2f\n offestCircuit = %0.2f\n",wireOffset, circuitOffset);
	fclose(f);
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


	printf("12 - bit value of channel %i: Temp: %.2f offset: %.2f\n",channel, temperature, offsetTemp);


	return 0;
}
