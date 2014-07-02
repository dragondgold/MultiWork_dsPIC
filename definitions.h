#define FCY                 40000000UL          // MIPS para calculos de delay
#define baudRateBT          9600
#define baudRateUSB         9600

#define BUFFER_IO_PIN       PORTBbits.RB7
#define BUFFER_IO_TRIS      TRISBbits.TRISB7

#define START_BYTE          'S'
#define BUFFER_SIZE         16000
#define ACK                 0x06

#define TRUE                1
#define FALSE               0

#define FRECUENCIMETER      'F'
#define LC_METER            1
#define LOGIC_ANALIZER      'L'
#define VOLTMETER           3
#define NO_MODE             4

#define INDUCTANCE_MODE     4
#define CAPACITOR_MODE      5

#define FlancoSubida        0
#define FlancoBajada        1

#define DEBUG_ISIS          FALSE
#define UART2_DEBUG         FALSE

#if DEBUG_ISIS == FALSE
    #include    <p33FJ128GP802.h>
#else
    #include    <p33FJ32MC204.h>
#endif

#if DEBUG_ISIS == TRUE && UART2_DEBUG == TRUE
    #error No se puede usar el debugger con el UART2 en la simulacion con ISIS Proteus
#endif