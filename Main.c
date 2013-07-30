/* 
 * File:   Main.c
 * Author: Andres Torti
 *
 * Created on 24 de mayo de 2012, 21:15
 */

/* Definiciones */
#include "definitions.h"
#include "mylibs.h"
/* Includes generales */
#include <libpic30.h>               // Libreria para delays
#include <stdio.h>
#include <stdlib.h>
#include <uart.h>
/* Cabeceras de funciones */
#include "BluetoothInterface.h"
#include "LogicAnalizer.h"
#include "Frecuencimetro.h"

#if DEBUG_ISIS == TRUE
    #include    <p33FJ32MC204.h>
    // FBS
    #pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
    #pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
    // FGS
    #pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
    #pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)
    // FOSCSEL
    #pragma config FNOSC = PRIPLL           // Oscillator Mode (Primary Oscillator (XT, HS, EC) w/ PLL)
    #pragma config IESO = OFF               // Internal External Switch Over Mode (Start-up device with user-selected oscillator source)
    // FOSC
    #pragma config POSCMD = HS              // Primary Oscillator Source (HS Oscillator Mode)
    #pragma config OSCIOFNC = OFF           // OSC2 Pin Function (OSC2 pin has clock out function)
    #pragma config IOL1WAY = OFF            // Peripheral Pin Select Configuration (Allow Multiple Re-configurations)
    #pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)
    // FWDT
    #pragma config WDTPOST = PS256          // Watchdog Timer Postscaler (1:256)
    #pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
    #pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
    #pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)
    // FPOR
    #pragma config FPWRT = PWR2             // POR Timer Value (2ms)
    #pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)
    // FICD
    #pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
    #pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)
#else
    #include    <p33FJ128GP802.h>
    // FBS
    #pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
    #pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
    #pragma config RBS = NO_RAM             // Boot Segment RAM Protection (No Boot RAM)
    // FSS
    #pragma config SWRP = WRPROTECT_OFF     // Secure Segment Program Write Protect (Secure segment may be written)
    #pragma config SSS = NO_FLASH           // Secure Segment Program Flash Code Protection (No Secure Segment)
    #pragma config RSS = NO_RAM             // Secure Segment Data RAM Protection (No Secure RAM)
    // FGS
    #pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
    #pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)
    // FOSCSEL
    #pragma config FNOSC = PRIPLL           // Oscillator Mode (Primary Oscillator (XT, HS, EC) w/ PLL)
    #pragma config IESO = OFF               // Internal External Switch Over Mode (Start-up device with user-selected oscillator source)
    // FOSC
    #pragma config POSCMD = HS              // Primary Oscillator Source (HS Oscillator Mode)
    #pragma config OSCIOFNC = OFF           // OSC2 Pin Function (OSC2 pin has clock out function)
    #pragma config IOL1WAY = OFF            // Peripheral Pin Select Configuration (Allow Multiple Re-configurations)
    #pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)
    // FWDT
    #pragma config WDTPOST = PS256          // Watchdog Timer Postscaler (1:256)
    #pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
    #pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
    #pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)
    // FPOR
    #pragma config FPWRT = PWR2             // POR Timer Value (2ms)
    #pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)
    // FICD
    #pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
    #pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)
#endif

/* RAM contigua para buffer */
__attribute__((far,aligned)) unsigned char Buffer[BUFFER_SIZE];
volatile unsigned int mode = NO_MODE;           // Modo para el USART

/**
 * Interrupcion de recepcion de dato en el UART 1 que es el que se comunica
 * con el modulo bluetooth
 */
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void){
    if(DataRdyUART1()){         // Compruebo por las dudas de que en verdad halla un dato
        mode = ReadUART1();     // Leo el dato desde el UART
    }
    U1STAbits.OERR = 0;
    IFS0bits.U1RXIF = 0;
}

int main (void) {

    // Configuración del oscilador para usar un cristal de 4MHz y lograr 40MIPS
    PLLFBDbits.PLLDIV = 78;		// M=80
    CLKDIVbits.PLLPOST = 0;   		// N1=2
    CLKDIVbits.PLLPRE  = 0;   		// N2=2
    OSCTUN             = 0;   		// Tune FRC oscillator, if FRC is used
    RCONbits.SWDTEN = 0;    	  	// WDT desactivado
    //while(OSCCONbits.LOCK!=1);	// Espero que se estabilize el PLL

    __IOUNLOCK
    #if DEBUG_ISIS == TRUE
        RPINR18bits.U1RXR = 0b11001;        // RX en RP25
        RPOR12bits.RP24R = 0b00011;         // TX en RP24
    #else
        RPINR18bits.U1RXR = 0b110;          // RX en RP6
        RPOR3bits.RP7R = 0b00011;           // TX en RP7
    #endif
    __IOLOCK

    // Configuración UART 1
    U1MODEbits.USIDL = 1;       // Continúa operando en modo IDLE
    U1MODEbits.IREN = 0;        // IrDa deshabilitado
    U1MODEbits.RTSMD = 1;       // Pin RTS no se utiliza
    U1MODEbits.UEN = 0b00;      // Pines RTS y CTS no se usan, solo TX y RX
    U1MODEbits.WAKE = 1;        // UART habilitado en sleep
    U1MODEbits.LPBACK = 0;      // No usa modo Loop-back
    U1MODEbits.ABAUD = 0;       // Auto-Baud apagado
    U1MODEbits.BRGH = SPEED_MODE;
    U1BRG = BRGVal;
    U1MODEbits.PDSEL = 0b00;    // 8 bits no parity
    U1MODEbits.STSEL = 0;       // 1 bit de stop

    U1STAbits.UTXISEL0 = 0;     // Deshabilitada interrupción por envío
    U1STAbits.UTXISEL1 = 0;
    U1STAbits.UTXEN = 1;        // Pin TX habilitado
    U1STAbits.URXISEL = 0b00;   // Con solo un caracter la interrupcion por recepcion es lanzada
    U1STAbits.ADDEN = 0;        // Address mode apagado

    IEC0bits.U1RXIE = 1;        // Activo interrupción del UART (al parecer la función no lo hace)
    IFS0bits.U1RXIF = 0;        // Borro el flag de interrupción
    U1STAbits.OERR = 0;         // Borro el flag de error
    U1MODEbits.UARTEN = 1;      // Módulo UART habilitado

    __delay_ms(10);             // Pequeño delay de arranque para estabilizacion

    printf(" ");                // Debo enviar algo por printf() para que el TX
                                // comienze a funcionar, de otro modo el primer byte no se envia nunca,
                                // no se si es un bug
    while(TRUE){
        //Idle();                           // El PIC se mantiene en modo Idle esperando un dato del UART
        switch(mode){                       // Eligo el modo que se envio a traves del UART
            case FRECUENCIMETER:
                vFrecuencimetro();
                mode = NO_MODE;
                break;

            case LC_METER:
                vLC_Meter();
                mode = NO_MODE;
                break;

            case VOLTMETER:
                mode = NO_MODE;
                break;
                
            case LOGIC_ANALIZER:
                vLogicAnalizer();
                mode = NO_MODE;
                break;
        }
    }

    return (EXIT_SUCCESS);
}
