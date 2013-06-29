#include <math.h>
#include <stdio.h>

/***********************************************************************************/
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
/***********************************************************************************/
