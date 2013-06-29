#define TRESHOLD_LOW	32			//nivel de tensi�n inferior para cambiar a un rango m�s bajo (0 a 1024)
#define TRESHOLD_HIGH	1000                    //nivel de tensi�n superior para cambiar a un rango m�s alto (0 a 1024)
#define SAMPLES			200		//numero de muestras para el promedio de la tensi�n
#define SLAVE_W			0x04		//direcci�n de PIC esclavo para escritura	
#define SLAVE_R			0x05		//direcci�n de PIC esclavo para lectura

#include "definitions.h"
#include "Voltimetro.h"
#include "mylibs.h"
#include <p33FJ128GP804.h>
#include <adc.h>
#include <uart.h>
#include <libpic30.h>
#include <stdio.h>

#define TRIS_POLARIDAD          TRISAbits.TRISA10
#define TRIS_RELE1		TRISBbits.TRISB4
#define TRIS_RELE2		TRISAbits.TRISA8
	
#define POLARIDAD		PORTAbits.RA10
#define RELE_1			PORTBbits.RB4
#define RELE_2			PORTAbits.RA8

//******************************************************************************//
//Nombre:   vVoltimetro					                                        //
//Funci�n:  Lee la tensi�n en la entrada AN1 y detecta la polaridad de la		//
//			tensi�n por el pin A7												//
//Retorna:  Nada                                                                //
//Le pasan: Nada																//
//******************************************************************************//
void vVoltimetro (void){

unsigned long	ADC = 0;
float			Tension;
const float		Factor[6] = {0.0 , 304.1825095057, 182.4817518248, 99.009900990, 32.0, 6.4850843060};
unsigned char	rango = 1;
unsigned char	Polaridad;
char			buffer[10];

#if SAMPLES > 255
	unsigned int n;
#else
	unsigned char n;
#endif

WriteUART1(ACK);				//respondo al LCD con un ACK para indicar que entr� en la funci�n

TRIS_POLARIDAD = 1;				//pin para detectar la polaridad como entrada
TRIS_RELE1 = 0;					//pin para activar/descativar rel� 1 como salida
TRIS_RELE2 = 0;      			//pin para activar/desactivar rel� 2 como salida

RELE_1 = 0;						//rel� 1 apagado (NC) modo volt�metro
RELE_2 = 0;						//rel� 2 apagado (NC) modo amper�metro desactivado

AD1CON1bits.ADON = 0;			//ADC apagado
AD1CON1bits.ADSIDL = 1;			//ADC apagado en modo IDLE
AD1CON1bits.ADDMABM = 1;		//El buffer DMA es colocado en el orden del sampling 
AD1CON1bits.AD12B = 1;			//ADC en modo de 12 bits y 1 canal
AD1CON1bits.FORM = 0; 			//Formato de salida entero (DOUT = 0000 dddd dddd dddd) --> d = dato (bit)
AD1CON1bits.SSRC = 0b111;		//Conversi�n autom�tica (no necesita trigger de otro lado)
AD1CON1bits.ASAM = 0;			//El sampling empieza cuando se setea el bit SAMP

AD1CON2bits.VCFG = 0b000;		//Tensi�n de referencia en Avss y Avdd
AD1CON2bits.CSCNA = 0;			//No escanear las entradas <---- REVISAR BIEN QUE ES LO QUE SIGNIFICA
AD1CON2bits.CHPS = 0;			//Conversi�n en el canal 0 unicamente
AD1CON2bits.SMPI = 0;			//Incrementa el DMA por cada conversi�n realizada
AD1CON2bits.BUFM = 0;			//El buffer empieza a llenarse desde el comienzo siempre
AD1CON2bits.ALTS = 0;			//Usa las entradas seleccionadas de SAMPLE A

AD1CON3bits.ADRC = 1;			//Clock RC interno
AD1CON3bits.SAMC = 3;			//Tiempo de sampling 3*Tad
AD1CON3bits.ADCS = 5;   		//Tad = Tcy*(ADCS+1) = (1/40MHz)*(5+1) = 150nS
								//Tiempo de conversi�n para 12bits Tc = 14*Tad = 14 * 150nS = 2100nS (476Khz aprox.)

//Registros para selecci�n de entrada anal�gica (VER BIEN COMO SE CONFIGURA)
AD1CHS123bits.CH123SA = 0;		//MUXA entrada positiva (AN0 en CH1)
AD1CHS123bits.CH123NA = 0;		//MUXA entrada negativa (Vref- en CH1)

AD1CHS0bits.CH0NA = 0;			//MUXA referencia de tensi�n negativa en -Vref	
AD1CHS0bits.CH0SA = 0;			//AN0 como entrada anal�gica		

IEC0bits.AD1IE = 0;				//Interrupcion ADC deshabilitada
AD1CON1bits.ADON = 1;			//Enciendo ADC

	while(1){
   
		if((ADC / SAMPLES) > 1000){		//si la tensi�n es casi 3.3v paso al siguiente mayor rango
			if(rango < 5) ++rango;
			vRango(rango);		//env�o el nuevo rango al PIC esclavo
		}
		else if((ADC / SAMPLES) < 32){	//si la tensi�n es casi 0v paso al siguiente menor rango
			if(rango > 1) --rango;	
			vRango(rango);		//env�o el nuevo rango al PIC esclavo
		}	

		for(n=0;n<=SAMPLES;++n){					//muestreo varias veces para luego hacer un promedio
			AD1CON1bits.SAMP = 1;					//comienza a tomar el sampling el ADC
			while(!AD1CON1bits.DONE);				//espero a que el ADC termine el sample y conversi�n
			ADC = ADC + ADC1BUF0;					//sumo a ADC el valor le�do del ADC
		}
		
		Polaridad = POLARIDAD;						//tomo la polaridad de la se�al (positiva o negativa)

		Tension = ((float)ADC / SAMPLES) * Factor[rango];	//saco el promedio de la tensi�n dividiendo por
		//el n�mero de muestreos y lo multiplico por el factor correspondiente seg�n el rango para pasar a
		//los volts reales antes del divisor resistivo

            if(DataRdyUART1()){         	//si hay un dato de cuando envie la 'N' que no recibi
                    n = ReadUART1();			//leo el dato que hab�a
                    if(n == ACK){				//si el dato es un ACK entonces...
                            float2str(buffer,Tension);		//convierto la tensi�n a string
                                    printf("%s",buffer);		//env�o el string
                            WriteUART1('F');				//fin del string
                            WriteUART1(Polaridad);			//env�o la polaridad de la se�al
                            WriteUART1(rango);				//env�o el rango
                    }
                    else if(n == 'O'){					//si el dato es una 'O' significa salida del programa
                    WriteUART1(ACK);				//env�o un ACK y salgo de la funci�n
                    return;
               }
            }

            else{
                    WriteUART1('N');        		//envio que tengo una nueva medici�n
                    __delay_ms(5);      			//espera para respuesta
                    if(DataRdyUART1()){ 			//si recibi algun dato
                    if(ReadUART1() == ACK){ 			//si es un ACK env�o el voltaje
                                    float2str(buffer,Tension);		//convierto la tensi�n a string
                                            printf("%s",buffer);		//env�o el string
                                    WriteUART1('F');				//fin del string
                                    WriteUART1(Polaridad);			//env�o la polaridad de la se�al
                                    WriteUART1(rango);				//env�o el rango
                    }
                    else if(n == 'O'){				//si el dato es una 'O' significa salida del programa
                            WriteUART1(ACK);			//env�o un ACK y salgo de la funci�n
                    return;
                }
                    }
            }
    }
}

