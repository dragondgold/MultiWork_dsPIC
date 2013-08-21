#include <math.h>
#include <stdio.h>
#include "definitions.h"

void float2str(char *buffer, float f){
	float fenteros;
	float fdecimales;
	int entero, decimal;

	fenteros = floor(f);
	fdecimales = f - fenteros;
	entero = (int)fenteros;
	decimal = (int)1000 * fdecimales;
        sprintf(buffer, "%d.%03i", entero, decimal);
}

void printNumber(unsigned int number){
#if DEBUG_ISIS == FALSE && UART2_DEBUG == TRUE
    char buffer[5] = {0};
    itoa(buffer, number, 10);
    putsUART2(buffer);
#endif
}
