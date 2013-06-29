#include "definitions.h"
#include "mylibs.h"
#include <libpic30.h>
#include <timer.h>
#include <uart.h>
#include <stdio.h>

//***************************************************************************//
// Nombre:   vLC_Meter  				                     //
// Función:  Muestrea la frecuencia que ingresa por T4CK, se unen los Timer  //
//           4 y 5 para formar uno de 32 bits                                //									//
// Retorna:  Void                                                            //				                        //
// Argumentos: Void                                                          //     														        //
//***************************************************************************//
void vLC_Meter (void){
/*
    unsigned int keepGoing = 1;         // Determina si se sigue muestreando o no
    unsigned long Frecuencia;          	// Frecuencia del oscilador LC

    WriteUART1(LC_METER);               // Indico el modo al que entre

    // Configuración del timer 4/5 para modo de 32bits
    __IOUNLOCK			// Habilito cambio de pines
    RPINR3bits.T2CKR = 5;	// T2CK al pin RP5
    __IOLOCK			// Bloqueo cambio de pines
    T4CONbits.TON = 0;		// Apago Timer4
    T5CONbits.TON = 0; 		// Apago Timer5
    T4CONbits.T32 = 1;          // T4 y T5 forman un timer de 32 bits
    T4CONbits.TSIDL = 0;	// Se apaga en modo IDLE
    T4CONbits.TGATE = 0;	// Tgate apagado (sirve para medir período)
    T4CONbits.TCKPS = 0b00;	// Preescaler 1:1
    T4CONbits.TCS   = 1;	// Clock externo

	while(keepGoing){               // Bucle infinito

            WriteTimer45(0);		//Reinicio timer
            T4CONbits.TON = 1;		//Enciendo el timer
		
            __delay32(40000000);	//Delay de 1 segundo exacto para tomar la frecuencia
	
            T4CONbits.TON = 0;		// Apago el timer
            Frecuencia = ReadTimer45(); // Leo la frecuencia

            WriteUART1(START_BYTE);     // Byte de Start
            WriteUART1(LC_METER);       // Indico proveniencia del dato
            WriteUART1(sizeof(unsigned long));  // Numero de bytes a enviar
            printf("%lu", Frecuencia);
            while(!DataRdyUART1());     // Espero un dato del UART
            keepGoing = ReadUART1();    // Continuo o salgo

        }*/
}

