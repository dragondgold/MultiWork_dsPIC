#include "definitions.h"
#include "mylibs.h"
#include <timer.h>
#include <uart.h>
#include <stdio.h>
#include <libpic30.h>

//***************************************************************************//
// Nombre:   vFrecuencimetro				                     //
// Función:  Muestrea la frecuencia que ingresa por T2CK, se unen los Timer  //
//           2 y 3 para formar uno de 32 bits                                //									//
// Retorna:  Void                                                            //				                        //
// Argumentos: Void                                                          //     														        //
//***************************************************************************//
void vFrecuencimetro (void){

    unsigned int keepGoing = 1; // Determina si se debe continuar o no el muestreo
    unsigned long Frecuencia;   // Frecuencia
    unsigned int IPL;

    IPL = SRbits.IPL;           // Guardo el estado de las interrupciones
    SRbits.IPL = 0b111;         // Deshabilito interrupciones

    WriteUART1(FRECUENCIMETER); // Envío el modo actual

    /* Configuración del timer 2/3 para modo de 32bits */
    __IOUNLOCK			// Habilito cambio de pines
    RPINR3bits.T2CKR = 5;	// T2CK al pin RP5
    __IOLOCK			// Bloqueo cambio de pines
    T2CONbits.TON = 0;		// Apago Timer2
    T3CONbits.TON = 0; 		// Apago Timer3
    T2CONbits.T32 = 1;          // T2 y T3 forman un timer de 32 bits
    T2CONbits.TSIDL = 0;	// Se apaga en modo IDLE
    T2CONbits.TGATE = 0;	// Tgate apagado (sirve para medir período)
    T2CONbits.TCKPS = 0b00;	// Preescaler 1:1
    T2CONbits.TCS   = 1;	// Clock externo

    while(keepGoing){

	WriteTimer23(0);		// Reinicio timer
	T2CONbits.TON = 1;		// Enciendo el timer

	__delay32(40000000);            // Delay de 1 segundo exacto a 40MIPS
	
	T2CONbits.TON = 0;		// Apago el timer
	Frecuencia = ReadTimer23();     // Leo el valor del timer
                                        // (que al estar muestreando durante un segundos son los Hz)
        WriteUART1(START_BYTE);         // Byte de START
        WriteUART1(FRECUENCIMETER);     // Proveniencia del dato
        WriteUART1(sizeof(unsigned long));  // Numero de bytes a enviar
        printf("%lu", Frecuencia);      // Envío la frecuencia por el UART1
        while(!DataRdyUART1());         // Espero a recibir un dato
        keepGoing = ReadUART1();        // Sigo o no con el muestreo
        
    }

    SRbits.IPL = IPL;       // Retorno el estado de las interrupciones
}
