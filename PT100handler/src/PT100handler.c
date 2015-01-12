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
	char DIR_PT100wireOffset[255] = {};
	char fopenModus[2] = {};

	wireRes = getWireResistanceCopper(length, wireArea);
	wireOffset = getPT100temp(wireRes+100);

	//write wire offset to PT100wireOffset.txt


	if ((channel == 1) || (channel ==2)) {
		sprintf(DIR_PT100wireOffset, "PT100_%iwireOffset.txt", channel );

		if (access(DIR_PT100wireOffset, (R_OK | W_OK)) != -1){
			sprintf(fopenModus, "r+");
		}
		else
		{
			sprintf(fopenModus, "w");
		}
	}
	else
	{
		fprintf(stderr, "setWireOffset: Invalid channel No. : %i\n", channel);
	}

	f = fopen(DIR_PT100wireOffset, fopenModus );
				fprintf(f,"PT100_%i:TempOffsetWire=%5.2f:WireLength=%6.2f:WireArea=%4.2f:R-wire=%5.2f",
													channel,
													wireOffset,
													length,
													wireArea,
													wireRes);
				fclose(f);
}

int getWireOffsetData(int channel, double data[]){
	FILE *f = NULL;
	char DIR_PT100wireOffset[255] = {};
	float TempOffsetWire, WireLength, WireArea, R_wire;
	int i;


	if ((channel == 1) || (channel == 2)){
		sprintf(DIR_PT100wireOffset, "PT100_%iwireOffset.txt", channel );

		if (access(DIR_PT100wireOffset, (R_OK | W_OK)) != -1){
			f = fopen(DIR_PT100wireOffset,"r");
			fscanf(f, "PT100_%i:TempOffsetWire=%f:WireLength=%f:WireArea=%f:R-wire=%f",
					&i,
					&TempOffsetWire,
					&WireLength,
					&WireArea,
					&R_wire
					);
			fclose(f);
					data[0] = TempOffsetWire;
					data[1] = WireLength;
					data[2] = WireArea;
					data[3] = R_wire;
		}
		else
		{
			fprintf(stderr, "setWireOffsetData: File %s does not exist!\n", DIR_PT100wireOffset);
			return -1;
		}
	}
	else
	{
		fprintf(stderr, "setWireOffset: Invalid channel No. : %i\n", channel);
	}
	return 0;
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
void setCircuitOffset(double calResistor, int channel){
	double circuitOffset;
	unsigned int EEPROMregister = 0;
	char datatoEEPROM[65] = {};
	int calBitvalue;

	if ((channel == 1) || (channel == 2)){
	//Attention: Beaglebone AIN channels start counting at 0 !
	calBitvalue = get_iio_value_n(channel-1);
	circuitOffset = getPT100temp(calResistor)-getCircuitTempSimu(calBitvalue);

	sprintf(datatoEEPROM, "R=%5.1f:PT100temp=%6.2f:CircuitTemp=%6.2f:CircuitOffset=%5.2f",
										calResistor,
										getPT100temp(calResistor),
										getCircuitTempSimu(calBitvalue),
										circuitOffset
										);
	}
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

double getTemp(int channel){
	double circuitOffsetData[4];
	double wireOffsetData[4];
	double PT100temp;

	getCircuitOffsetData(channel, circuitOffsetData);
	getWireOffsetData(channel, wireOffsetData);
	//attention beaglebone channel 1 = 0!
	PT100temp = getCircuitTempSimu(get_iio_value_n(channel-1))
			+ circuitOffsetData[3]
			- wireOffsetData[0];

	return (PT100temp);
}


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
	double calResistor, lengthWire = 0, areaWire = 0;
	double tempOffsetCircuitData[4];
	double tempOffsetWireData[4];
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
				sscanf(argv[3], "%c", &setget[1]);;

				if (setget[1] == 't'){
					printf("temperature (channel %i) = %.1f\n",channel, getTemp(channel));
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
