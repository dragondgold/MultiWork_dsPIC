#ifndef MYLIBS_H
#define MYLIBS_H

#include "definitions.h"
#include "uart.h"
#include "stdio.h"
#include "stdlib.h"

void float2str(int *buffer, float f);
void printNumber(unsigned int number);

// No permite cambios en Peripheral Pin Select
#define __IOLOCK	__builtin_write_OSCCONL(OSCCON | 0x40);
// Permite cambios en Peripheral Pin Select
#define __IOUNLOCK	__builtin_write_OSCCONL(OSCCON & 0xDF);

#define toggle(bit)     bit ^= 0x01;
#define bitTest(data, n) (data & (1 << n))
#define enableInterrupts() SRbits.IPL = 0;
// Prioridad de interrupción del CPU es 7 de este modo se deshabilitan
//  las demas interrupciones
#define disableInterrupts() SRbits.IPL = 7;

// Macros para DEBUG por el UART2
#if DEBUG_ISIS == FALSE && UART2_DEBUG == TRUE
    #define printDebug(data)              putsUART2((unsigned int *)data); while(BusyUART2());
    #define printNumericDebug(data, x)    printDebug(data); printNumber(x); while(BusyUART2());
    #define printCharDebug(data, x)       printDebug(data); putcUART2((char)x); while(BusyUART2());
#else
    #define printDebug(data)
    #define printNumericDebug(data, x)
    #define printCharDebug(data, x)
#endif

#define BAUD_RATE 9600

#if (((FCY/BAUD_RATE)/16)-1) < 0xFFFF
    #define getSpeedMode() 0
#elif (((FCY/BAUD_RATE)/4)-1) < 0xFFFF
    #define getSpeedMode() 1
#else
    #error No se pudo establecer un baudrate correcto
#endif

#if (((FCY/BAUD_RATE)/16)-1) < 0xFFFF
    #define getBRGVal() (((FCY/BAUD_RATE)/16)-1)
#elif (((FCY/BAUD_RATE)/4)-1) < 0xFFFF
    #define getBRGVal() (((FCY/BAUD_RATE)/4)-1)
#else
    #error No se pudo establecer un baudrate correcto
#endif

