#define FCY                 40000000UL      // MIPS para calculos de delay
#define BaudRate            9600

#define START_BYTE          'S'
#define BUFFER_SIZE         16000
#define ACK                 0x06

#define TRUE                1
#define FALSE               0

#define FRECUENCIMETER      0
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

#if DEBUG_ISIS == TRUE && UART2_DEBUG == TRUE
    #error No se puede usar el debugger con el UART2 en la simulacion con ISIS Proteus
#endif