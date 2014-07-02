#include "definitions.h"
#include "mylibs.h"
#include <timer.h>
#include <uart.h>
#include <stdio.h>
#include <libpic30.h>

#define bitTest(data, n) (data & (1 << n))
#define enableUARTInt() U1MODEbits.WAKE = 1; IFS0bits.U1RXIF = 0; IEC0bits.U1RXIE = 1;
#define disableUARTInt() IEC0bits.U1RXIE = 0;

#define sleepWait() enableUARTInt(); Idle(); disableUARTInt();
#define writeUART1(data) WriteUART1(data); while(BusyUART1());

unsigned int mReadUART1 (void){
    while(!DataRdyUART1());
    return ReadUART1();
}

void vFrecuencimetro (void){

    unsigned int keepGoing = 1; // Determina si se debe continuar o no el muestreo
    unsigned long Frecuencia;   // Frecuencia

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

    disableUARTInt();
    
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
        printf("%lu", Frecuencia);          // Envío la frecuencia por el UART1
        sleepWait();                        // Espero a recibir un dato
        keepGoing = mReadUART1();           // Sigo o no con el muestreo
    }
    enableUARTInt();
}
