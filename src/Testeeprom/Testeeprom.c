#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "24AA256-EEPROM.h"

int main(int argc, char *argv[], char *env[]){
	char character[63] = "Hallo schreiben funktioniert!";
	//int i;
	unsigned int reg = 128;
	char EEPROMdata[255] = {};




	EEPROMwriteblock64(reg, character);
	//EEPROMwritebyte(reg, character);
	sleep(1);
	EEPROMreadbytes(reg, EEPROMdata, 29);

	printf("Ausgabe: %s\n",EEPROMdata);

/*	for (i=1; i<11; i++){
	printf("%c", EEPROMdata[i]);
	}
*/
	return 0;

}
