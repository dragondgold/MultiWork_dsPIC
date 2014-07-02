/* Includes */
#include    "mylibs.h"
#include    "definitions.h"
#include    "RunLengthAlgorithm.h"
#include    <crc.h>
#include    <uart.h>
#include    <libpic30.h>              
#include    <stdlib.h>

/* Definiciones */
#define     F40MHz      'A'
#define     F20MHz      'S'
#define     F10MHz      'D'
#define     F4MHz       'F'
#define     F400KHz     'G'
#define     F2KHz       'H'
#define     F10Hz       'J'

#define     noTrigger       'N'
#define     simpleTrigger   'S'

#define writeUART1(data) WriteUART1(data); while(BusyUART1());

/**
 * Definimos la variable tipo extern que fue definida en Main.c
 * Archivo 1:
 *      int VariableGlobal;     // Definici�n
 *      void UnaFunci�n (void); // Declaraci�n externa impl�cita
 *
 *      int main() {
 *          VariableGlobal = 1;
 *          UnaFunci�n();
 *          return 0;
 *      }
 *
 * Archivo 2:
 *      extern int VariableGlobal;  // Declaraci�n externa
 *
 *      void UnaFunci�n (void) {
 *          ++ VariableGlobal;
 *      }
 *
 * En este ejemplo la variable VariableGlobal es definida en el archivo 1.
 * Para utilizar la misma variable en el archivo 2, tiene que ser declarada
 * usando el keyword extern. Independientemente de la cantidad de archivos,
 * una variable global solo se define una vez, sin embargo, tiene que ser declarada
 * usando extern en cualquier archivo aparte de aquel que contiene la definici�n.
 * T�cnicamente, UnaFunci�n es tambi�n externa, pero en C y en C++ todas las funciones
 * son consideradas externas por defecto y normalmente no necesitan ser declaradas.
 *
 * Fuente: http://es.wikipedia.org/wiki/Variable_externa
 */
__attribute__((far,aligned)) extern unsigned char dataBuffer[BUFFER_SIZE];

/**
 * Espero un byte desde el UART1 y lo devuelvo
 * @return byte leido desde el UART
 */
unsigned int mReadUART1 (void){
    while(!DataRdyUART1());
    return ReadUART1();
}

void vLogicAnalizer(void){

    unsigned int keepGoing = 0;             // Determina si debe seguir o no el muestreo
    unsigned int triggerType;               // Tipo de trigger
    unsigned int samplingFrequency;         // Frecuencia de muestreo
    unsigned int channelMask;               // M�scara para filtrar los canales (un 1 en el canal que se desea el trigger, 0 de otro modo)
    int CRC16;

    TRISB |= 0xFF00;                        // Parte alta del puerto B como entrada (hacemos una OR sino modificamos los pines
                                            // UART y deja de funcionar)
    BUFFER_IO_TRIS = 0;                     // Pin de direcci�n del buffer
    BUFFER_IO_PIN = 0;                      // Puerto B del buffer como entrada y A como salida (A <- B)
    CNPU1 = CNPU2 = 0;                      // Deshabilito pull-ups

    disableInterrupts();

    printDebug("\r\nAnalizador Logico");
    // Elimino datos que puedan quedar en el UART
    while(DataRdyUART1()){
        printNumericDebug("\r\nDatos disponibles en el UART: ", ReadUART1());
    }

    // Leo el estado para saber si debo continuar o detenerme
    writeUART1(LOGIC_ANALIZER);
    keepGoing = mReadUART1();
    printNumericDebug("\r\nKeepGoing recibido: ", keepGoing);

    while(keepGoing != 0){
        
        printDebug("\r\nKeep Going!");
        samplingFrequency = mReadUART1();   // Obtengo la frecuencia de muestreo
        triggerType = mReadUART1();         // Obtengo el tipo de trigger
        channelMask = mReadUART1();         // Obtengo la m�scara

        printCharDebug("\r\nSampling Frequency: ", samplingFrequency);
        printNumericDebug("\r\nTrigger Type: ", triggerType);
        printNumericDebug("\r\nChannel Mask: ", channelMask);

        CNEN1 = CNEN2 = 0;
        if(channelMask == 0) triggerType = noTrigger;

        // De acuerdo al bit seteado en el Mask detecto o no el cambio de estado
        // en el pin correspondiente
        if(bitTest(channelMask, 7)) CNEN1bits.CN11IE = 1;
        if(bitTest(channelMask, 6)) CNEN1bits.CN12IE = 1;
        if(bitTest(channelMask, 5)) CNEN1bits.CN13IE = 1;
        if(bitTest(channelMask, 4)) CNEN1bits.CN14IE = 1;
        if(bitTest(channelMask, 3)) CNEN1bits.CN15IE = 1;
        if(bitTest(channelMask, 2)) CNEN2bits.CN16IE = 1;
        if(bitTest(channelMask, 1)) CNEN2bits.CN21IE = 1;
        if(bitTest(channelMask, 0)) CNEN2bits.CN22IE = 1;

        // Habilito interrupciones por cambio de estado en caso de usarlas
        if(triggerType == simpleTrigger){
            IEC1bits.CNIE = 1;
            IFS1bits.CNIF = 0;
        }
        else IEC1bits.CNIE = 0;

        switch(samplingFrequency){
            case F40MHz:
                printDebug("\r\nSampling 40MHz");
                if(triggerType == noTrigger) vSample40MHz((unsigned char *)&PORTB+1, dataBuffer, BUFFER_SIZE);
                else if(triggerType == simpleTrigger) vSample40MHzTriggerSimple((unsigned char *)&PORTB+1, dataBuffer, BUFFER_SIZE, channelMask);
                break;

            case F20MHz:
                printDebug("\r\nSampling 20MHz");
                if(triggerType == noTrigger) vSample20MHz((unsigned char *)&PORTB+1, dataBuffer, BUFFER_SIZE);
                else if(triggerType == simpleTrigger) vSample20MHzTriggerSimple((unsigned char *)&PORTB+1, dataBuffer, BUFFER_SIZE, channelMask);
                break;

            case F10MHz:
                printDebug("\r\nSampling 10MHz");
                if(triggerType == noTrigger) vSample10MHz((unsigned char *)&PORTB+1, dataBuffer, BUFFER_SIZE);
                else if(triggerType == simpleTrigger) vSample10MHzTriggerSimple((unsigned char *)&PORTB+1, dataBuffer, BUFFER_SIZE, channelMask);
                break;

            case F4MHz:
                printDebug("\r\nSampling 4MHz");
                if(triggerType == noTrigger) vSample4MHz((unsigned char *)&PORTB+1, dataBuffer, BUFFER_SIZE);
                else if(triggerType == simpleTrigger) vSample4MHzTriggerSimple((unsigned char *)&PORTB+1, dataBuffer, BUFFER_SIZE, channelMask);
                break;

            case F400KHz:
                printDebug("\r\nSampling 400KHz");
                if(triggerType == noTrigger) vSample400KHz((unsigned char *)&PORTB+1, dataBuffer, BUFFER_SIZE);
                else if(triggerType == simpleTrigger) vSample400KHzTriggerSimple((unsigned char *)&PORTB+1, dataBuffer, BUFFER_SIZE, channelMask);
                break;

            case F2KHz:
                printDebug("\r\nSampling 2KHz");
                //vSample2KHz((char *)&PORTB+1, &Buffer, BUFFER_SIZE);
                break;

            case F10Hz:
                printDebug("\r\nSampling 10Hz");
                //vSample10Hz((char *)&PORTB+1, &Buffer, BUFFER_SIZE);
                break;

            default:
                printDebug("\r\nSampling Default");
                break;
        }

        // Calculo el CRC del buffer
        CRC16 = CRC_Calc_ChecksumByte(dataBuffer, BUFFER_SIZE, 0);

        // Env�o los datos mientras reciba que debo repetir la transmici�n
        do{
            printDebug("\r\nSending data");
            writeUART1(START_BYTE);             // Env�o byte de Start
            writeUART1(LOGIC_ANALIZER);         // Env�o proveniencia del dato

            // Env�o el buffer comprimido
            RLEncodeSendBuffer(dataBuffer, BUFFER_SIZE);
            // Dos 0xFF indican la terminaci�n
            writeUART1(0xFF);
            writeUART1(0xFF);

            // Env�o los dos bytes del CRC16
            writeUART1(CRC16 & 0xFF);           // LSB CRC16
            writeUART1((CRC16 >> 8) & 0xFF);    // MSB CRC16

            keepGoing = mReadUART1();
            printNumericDebug("\r\nKeepGoing recibido: ", keepGoing);
        }while(keepGoing == 'R');
    }

    printDebug("\r\nSale de Analizador Logico");
    enableInterrupts();
}
