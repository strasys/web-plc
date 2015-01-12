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
#include "AIN-handler.h"
#include "24AA256-EEPROM.h"

//The following function calculates the temperature
//based on an PT100 resistance input.
//The linear equation is based on a standard PT100
//between -20 to +40 °C.
double getPT100temp(double PT100resistance){

	return ((PT100resistance -100)/0.3893090909); //Temperature in °C.
}

//Since most of the wires are Copper
//the function is limited to Copper.
double getWireResistanceCopper(double length, double area){
	double specRes = 0.0175; // Specific resistance of Copper at 20°C in [Ohm * mm² / m]

	return((2*length*specRes)/area);			//Resistance in Ohm.
}

//This function calculates the wire offset
//and writes / generates and writes the value in the file
//PT100wireOffset.txt
//The wire offset is referenced to 0°C = 100 Ohm!
void setWireOffset(int channel, double length, double wireArea){
	double wireOffset, wireRes;
	FILE *f = NULL;
	char DIR_PT100wireOffset[21] = "PT100wireOffset.txt";
	//fpos_t pos;

	wireRes = getWireResistanceCopper(length, wireArea);
	wireOffset = getPT100temp(wireRes+100);

	//write wire offset to PT100wireOffset.txt
	if (channel == 1){
		f = fopen(DIR_PT100wireOffset, "w" );
		//rewind(f);
		fprintf(f,"PT100_1:TempOffsetWire=%5.2f:WireLength=%6.2f:WireArea=%4.2f:R-wire=%5.2f",wireOffset,length,wireArea,wireRes);
		fclose(f);
	}
	else if (channel == 2) {
		f = fopen(DIR_PT100wireOffset, "w" );
		//rewind(f);
		//todo: Positioning could be more automated to prevent manual counting.
		fprintf(f,"PT100_2:TempOffsetWire=%5.2f:WireLength=%6.2f:WireArea=%4.2f:R-wire=%5.2f",wireOffset,length,wireArea,wireRes);
		fclose(f);
	}
	else {
		fprintf(stderr, "setWireOffset: Could not write wire offset to file! : %s\n", strerror( errno ));
	}
}

/*
 * The following function is based on the simulated
 * electronic measurement circuit.
 * The curve is derived by simulating at different
 * PT100 resistances.
 */
double getCircuitTempSimu(int bitvalue){

	return (0.0148651303*bitvalue - 18.785514); //Temperature in °C;
}

// The following function writes the circuit
// related offset to the cap EEPROM.
void setCircuitOffset(double calResistor, int calBitvalue, int channel){
	double circuitOffset;
	unsigned int EEPROMregister = 0;
	char datatoEEPROM[65] = {};

	circuitOffset = getPT100temp(calResistor)-getCircuitTempSimu(calBitvalue);

	sprintf(datatoEEPROM, "R=%5.1f:PT100temp=%6.2f:CircuitTemp=%6.2f:CircuitOffset=%5.2f",
										calResistor,
										getPT100temp(calResistor),
										getCircuitTempSimu(calBitvalue),
										circuitOffset
										);
	//printf("datatoEEPROM: %s\n",datatoEEPROM);

	if (channel == 1){
		EEPROMregister = 128;
	}
	if (channel == 2){
		EEPROMregister = 192;
	}

	EEPROMwriteblock64(EEPROMregister, datatoEEPROM);
}

void getCircuitOffsetData(int channel, double data[]){
	unsigned int EEPROMaddressPT100_1 = 128;
	unsigned int EEPROMaddressPT100_2 = 192, address, length = 64;
	//int EEPROMoffsetR = 0, EEPROMoffsetPT100temp = 15, EEPROMoffsetCircuitTemp = 32, EEPROMoffsetCircuitOffset = 51;
	char EEPROMdata[255] = {};
	char *token = NULL;
	char Rcal[6], PT100temp[7], CircuitTemp[7], CircuitOffset[6];

	if (channel == 1 || channel == 2){
		if (channel == 1){
			address = EEPROMaddressPT100_1;
			EEPROMreadbytes(address, EEPROMdata, length);

		}
		if (channel == 2){
			address = EEPROMaddressPT100_2;
			EEPROMreadbytes(address, EEPROMdata, 64);

		}
	} else {
		fprintf(stderr, "Channel Number error: %s\n", strerror( errno ));
	}

	token = (char *) strtok(EEPROMdata,"=");
	token = (char *) strtok(NULL, ":");
	strcpy(Rcal, token);
	token = (char *) strtok(NULL, "=");
	token = (char *) strtok(NULL, ":");
	strcpy(PT100temp, token);
	token = (char *) strtok(NULL, "=");
	token = (char *) strtok(NULL, ":");
	strcpy(CircuitTemp, token);
	token = (char *) strtok(NULL, "=");
	token = (char *) strtok(NULL, ":");
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

/*
 * PT100handler functions:
 * EEPROM init:
 * it is needed to unbind the relevant EEPROM to read and write with this program
 * set circuit offset (= op-amp circuit on the strasys board):
 * ./PT100handler 1(=channel-number) s(=set) c(=circuit) 100.1(=calibration Resistor) 1650(=Bit value only for testing)
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
	int channel, calbitValue;
	double temperature, calResistor, lengthWire = 0, areaWire = 0;
	double tempOffsetCircuitdata[4];
	char setget[2] = {};
	char init[1] = {};

	if (argv[1] != 0){
		//Helper process to check the EEPROM init function!
		sscanf(argv[1], "%c", &init[0]);
		if (init[0] == 'i'){
			EEPROMinit(1, 54);
		} else {
			channel = atoi(argv[1]);



		if (argv[2] != 0){
			sscanf(argv[2], "%c", &setget[0]);				// Set argument necessary to set the circuit and wire length offset.

			if ((setget[0] == 's') && ((argv[3] && argv[4] && argv[5]) != 0)){
				sscanf(argv[3], "%c", &setget[1]);

				if (setget[1] == 'c'){				// c = circuit offset argument.
					calResistor = atof(argv[4]);
					//todo: calbitValue is only needed for testing!
					//=> In the future the cal. Resistor will be connected and the setup starts.
					calbitValue = atoi(argv[5]);
					setCircuitOffset(calResistor, calbitValue, channel);
					sleep(1);
					getCircuitOffsetData(channel, tempOffsetCircuitdata);
					printf("Calibration information of PT100 channel %i:\n\n", channel);
					printf("R = %5.1f Ohm\n", tempOffsetCircuitdata[0]);
					printf("PT100 element temperature at R = %6.2f °C\n", tempOffsetCircuitdata[1]);
					printf("Temperature based on simulated / ideal el. circuit = %6.2f °C\n", tempOffsetCircuitdata[2]);
					printf("Offset temperature of channel %d set to %5.2f °C\n", channel, tempOffsetCircuitdata[3]);
				}
			 else if (setget[1] == 'w'){				// w = wire offset of wire length
					lengthWire = atof(argv[4]);		// value in meter
					areaWire = atof(argv[5]);		// value in mm²
					setWireOffset(channel,lengthWire, areaWire);
					//todo: add getWireOffset
				}
			 else {
				fprintf(stderr, "Arguments mismatch: %s\n", strerror( errno ));
				return EXIT_FAILURE;
			 }
			}
			else if (setget[0] == 'g'){
				sscanf(argv[3], "%c", &setget[1]);;

				if (setget[1] == 't'){
					temperature = getCircuitTempSimu(get_iio_value_n(channel)); // + getTempOffset();
					printf("temperature (channel %i) = %.1f",channel, temperature);
				}
				else if (setget[1] == 'c') {
					getCircuitOffsetData(channel, tempOffsetCircuitdata);
					printf("Calibration information of PT100 channel %i:\n\n", channel);
					printf("R = %5.1f Ohm\n", tempOffsetCircuitdata[0]);
					printf("PT100 element temperature at R = %6.2f °C\n", tempOffsetCircuitdata[1]);
					printf("Temperature based on simulated / ideal el. circuit = %6.2f °C\n", tempOffsetCircuitdata[2]);
					printf("Offset temperature of channel %d set to %5.2f °C\n", channel, tempOffsetCircuitdata[3]);
				}
				else if (setget[1] == 'w'){

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


	} else {
			fprintf(stderr, "No arguments added: %s\n", strerror( errno ));
			return EXIT_FAILURE;
	}

	return 0;
}
