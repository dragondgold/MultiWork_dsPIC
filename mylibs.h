#ifndef MYLIBS_H
#define MYLIBS_H

#include "definitions.h"
#include "uart.h"
#include "stdio.h"
#include "stdlib.h"

void float2str(int *buffer, float f);
void printNumber(unsigned int number);

/* Definiciones generales */
// No permite cambios en Peripheral Pin Select
#define __IOLOCK	__builtin_write_OSCCONL(OSCCON | 0x40);
// Permite cambios en Peripheral Pin Select
#define __IOUNLOCK	__builtin_write_OSCCONL(OSCCON & 0xDF);
#define toggle(bit)     bit ^= 0x01;

#if DEBUG_ISIS == FALSE && UART2_DEBUG == TRUE
    // Macros para DEBUG por el UART2
    #define debug(data)                   putsUART2((unsigned int *)data); while(BusyUART2());
    #define printNumericDebug(data, x)    debug(data); printNumber(x); while(BusyUART2());
    #define printCharDebug(data, x)       debug(data); putcUART2((char)x); while(BusyUART2());
#else
    #define debug(data)
    #define printNumericDebug(data, x)
    #define printCharDebug(data, x)
#endif

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
