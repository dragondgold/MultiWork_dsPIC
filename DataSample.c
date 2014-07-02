#ifndef DATASAMPLE_C
#define DATASAMPLE_C

#include <libpic30.h>       // Libreria para delays
#include <uart.h>
#include "definitions.h"

/**
 * Esta funcion muestrea el puerto que le es pasado y guarda los datos en
 * el buffer de destino cuya dirección también es pasada. La velocidad del
 * muestreo es 40MHz. Idem para las demas funciones
 *
 * @param Port dirección de memoria del puerto donde tomar los 8 bits
 * @param Buffer dirección de memoria del buffer donde almacenar el sample
 * @param n tamaño del buffer en bytes-1
 * @param maskByte mascara para filtrar los canales
 */
void vSample40MHz (unsigned char *Port, unsigned char *Buffer, unsigned int n){
    __asm__ volatile ("repeat   w2");                   // Repito n+1 veces (no hay demora 40MHz de sample)
    __asm__ volatile ("mov.b    [w0],[w1++]");          // Leo el puerto y lo copio al buffer
}

void vSample20MHz (unsigned char *Port, unsigned char *Buffer, unsigned char n){
    __asm__ volatile ("do       w2,Loop20M");           // Repito n+1 veces
    __asm__ volatile ("mov.b    [w0],[w1++]");          // Leo el puerto y lo copio al buffer
    __asm__ volatile ("Loop20M:  nop");                 // 2 ciclos de demora (nop + goto) para 20MHz
}

void vSample10MHz (unsigned char *Port, unsigned char *Buffer, unsigned char n){
    __asm__ volatile ("do       w2,Loop10M");           // Repite n veces lo que esta entre esto y Loop
    __asm__ volatile ("mov.b    [w0],[w1++]");          // Leo el puerto y lo copio al buffer
    __asm__ volatile ("nop");                           // Pierdo 2 ciclos + 2 del bucle son 4 para 10MHz
    __asm__ volatile ("nop");
    __asm__ volatile ("Loop10M: nop");
}

void vSample4MHz (unsigned char *Port, unsigned char *Buffer, unsigned char n){
    __asm__ volatile ("do       w2,Loop4M");            // Repite n veces lo que esta entre esto y Loop
    __asm__ volatile ("mov.b    [w0],[w1++]");          // Leo el puerto y lo copio al buffer
    __asm__ volatile ("repeat   #6");                   // Pierdo 8 ciclos + 2 del bucle son 10 para 4MHz
    __asm__ volatile ("nop");
    __asm__ volatile ("Loop4M:  nop");
}

void vSample400KHz (unsigned char *Port, unsigned char *Buffer, unsigned char n){
    __asm__ volatile ("do       w2,Loop400K");          // Repite n veces lo que esta entre esto y Loop
    __asm__ volatile ("mov.b    [w0],[w1++]");          // Leo el puerto y lo copio al buffer
    __asm__ volatile ("repeat   #96");                  // Pierdo 98 ciclos + 2 del bucle son 10 para 400KHz
    __asm__ volatile ("nop");
    __asm__ volatile ("Loop400K: nop");
}

void vSample2KHz (unsigned char *Port, unsigned char *Buffer, int n){
    register unsigned char *portRegister asm("w0") = Port;
    register unsigned char *bufferRegister asm("w1") = Buffer;
    register int counterRegister asm("w2") = n;

    __asm__ volatile ("do       w2,Loop2K");
    __asm__ volatile ("mov.b    [w0],[w1++]");        // Leo el puerto y lo copio al buffer
    __delay_us(500);
    __asm__ volatile ("Loop2K:  nop");
}

/*************************************************************************/
/* Trigger simple, el trigger se analiza cada 125nS osea 8MHz            */
/*************************************************************************/
void vSample40MHzTriggerSimple (unsigned char *Port, unsigned char *Buffer, unsigned int n){
    __asm__ volatile ("Trigger40MHz:");
    __asm__ volatile ("btss     0x0086, #3");     // Bit CNIF de IFS1
    __asm__ volatile ("goto     Trigger40MHz");

    __asm__ volatile ("repeat   w2");             // Repito n+1 veces (no hay demora 40MHz de sample)
    __asm__ volatile ("mov.b    [w0],[w1++]");    // Leo el puerto y lo copio al buffer
}

void vSample20MHzTriggerSimple (unsigned char *Port, unsigned char *Buffer, unsigned char n){
    __asm__ volatile ("Trigger20MHz:");
    __asm__ volatile ("btss     0x0086, #3");     // Bit CNIF de IFS1
    __asm__ volatile ("goto     Trigger20MHz");

    __asm__ volatile ("do       w2,LoopTrigger20M");    // Repito n+1 veces
    __asm__ volatile ("mov.b    [w0],[w1++]");          // Leo el puerto y lo copio al buffer
    __asm__ volatile ("LoopTrigger20M:  nop");          // 2 ciclos de demora (nop + goto) para 20MHz
}

void vSample10MHzTriggerSimple (unsigned char *Port, unsigned char *Buffer, unsigned int n){
    __asm__ volatile ("Trigger10MHz:");
    __asm__ volatile ("btss     0x0086, #3");     // Bit CNIF de IFS1
    __asm__ volatile ("goto     Trigger10MHz");

    __asm__ volatile ("do       w2,LoopTrigger10M");    // Repite n veces lo que esta entre esto y Loop
    __asm__ volatile ("mov.b    [w0],[w1++]");          // Leo el puerto y lo copio al buffer
    __asm__ volatile ("nop");                           // Pierdo 2 ciclos + 2 del bucle son 4 para 10MHz
    __asm__ volatile ("nop");
    __asm__ volatile ("LoopTrigger10M: nop");
}

void vSample4MHzTriggerSimple (unsigned char *Port, unsigned char *Buffer, unsigned int n){
    __asm__ volatile ("Trigger4MHz:");
    __asm__ volatile ("btss     0x0086, #3");     // Bit CNIF de IFS1
    __asm__ volatile ("goto     Trigger4MHz");

    __asm__ volatile ("do       w2,LoopTrigger4M");     // Repite n veces lo que esta entre esto y Loop
    __asm__ volatile ("mov.b    [w0],[w1++]");          // Leo el puerto y lo copio al buffer
    __asm__ volatile ("repeat   #6");                   // Pierdo 8 ciclos + 2 del bucle son 10 para 4MHz
    __asm__ volatile ("nop");
    __asm__ volatile ("LoopTrigger4M:  nop");
}

void vSample400KHzTriggerSimple (unsigned char *Port, unsigned char *Buffer, unsigned int n){
    __asm__ volatile ("Trigger400KHz:");
    __asm__ volatile ("btss     0x0086, #3");     // Bit CNIF de IFS1
    __asm__ volatile ("goto     Trigger400KHz");

    __asm__ volatile ("do       w2,LoopTrigger400K");   // Repite n veces lo que esta entre esto y Loop
    __asm__ volatile ("mov.b    [w0],[w1++]");          // Leo el puerto y lo copio al buffer
    __asm__ volatile ("repeat   #96");                  // Pierdo 98 ciclos + 2 del bucle son 10 para 400KHz
    __asm__ volatile ("nop");
    __asm__ volatile ("LoopTrigger400K: nop");
}

void vSample2KHzTriggerSimple (unsigned char *Port, unsigned char *Buffer, unsigned char n){
    register unsigned char *portRegister asm("w0") = Port;
    register unsigned char *bufferRegister asm("w1") = Buffer;
    register int res1 asm("w2");
    register int res2 asm("w3");
    register int res3 asm("w4");
    register int res4 asm("w5");
    register int res5 asm("w6");

    __asm__ volatile ("Trigger2KHz:");
    __asm__ volatile ("btss     0x0086, #3");     // Bit CNIF de IFS1
    __asm__ volatile ("goto     Trigger2KHz");

    __asm__ volatile ("do       w2,LoopTrigger2K");
    __asm__ volatile ("mov.b    [w0],[w1++]");        // Leo el puerto y lo copio al buffer
    __delay_us(500);
    __asm__ volatile ("LoopTrigger2K:  nop");
}


void vSample10Hz (char *Port, unsigned char *Buffer, int n){
    register unsigned char *uartRegister asm("w3") = (unsigned char *)&U1TXREG;
    register char *portRegister asm("w4") = Port;
    register unsigned char *bufferRegister asm("w5") = Buffer;

    unsigned int k;
    for(k = 0; k < n; ++k){     // Leo el puerto cada 100mS para muestrear a 10Hz
        __asm__ volatile ("mov.b    [w4],[w5++]");      // Leo el puerto y lo copio al buffer
        //__asm__ volatile ("mov.b    [w5++],[w3]");    // Envío el buffer por el UART
        __delay_ms(100);
    }
}
#endif
