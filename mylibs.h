#ifndef MYLIBS_H
#define MYLIBS_H

#include "definitions.h"

/* Definiciones generales */
// No permite cambios en Peripheral Pin Select
#define __IOLOCK	__builtin_write_OSCCONL(OSCCON | 0x40);
// Permite cambios en Peripheral Pin Select
#define __IOUNLOCK	__builtin_write_OSCCONL(OSCCON & 0xDF);

void float2str(int *buffer, float f);

/**
 * Macro para el calculo de baudios automatico
 * Hay que colocar el define BAUDIOS en la funcioón OpenUSART
 * donde pide el valor de "spbrg" y SPEED_MODE donde pide modo
 * high o low speed:
 * SPEED_MODE hay que colcoarlo en donde se pide el modo de velocidad y BAUDIOS donde
 * se pide el "spbrg"
 */
#if (((FCY/BaudRate)/16)-1) < 0xFFFF
    #define SPEED_MODE 0
    #define BRGVal (((FCY/BaudRate)/16)-1)
#elif (((FCY/BaudRate)/4)-1) < 0xFFFF
    #define SPEED_MODE 1
    #define BRGVal (((FCY/BaudRate)/4)-1)
#else
    #error No se pudo establecer un baudrate correcto
#endif
/***********************************************************************************/

#endif
