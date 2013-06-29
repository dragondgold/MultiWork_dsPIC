#ifndef RUNLENGTHALGORITHM_C
#define RUNLENGTHALGORITHM_C

#include "uart.h"

/*
 * File:   RunLengthAlgorithm.c
 * Author: Andres Torti
 *
 * Created on 17 de julio de 2012, 21:16
 * Esta libreria hace uso del algoritmo para compresión de datos
 * Run-length encoding, para una descripción del mismo dirijirse a:
 * http://en.wikipedia.org/wiki/Run-length_encoding
 *
 */
void RLEncode (char *source, char *target, unsigned int bufferLenght){
    unsigned int n, k = 0, dataLenght = 1;

    for(n = 0; n < (bufferLenght-2); ++n){
        dataLenght = 1;
        while(source[n] == source[n+1]){    // Mientras el dato actual se igual al siguiente (continuidad)
            ++dataLenght; ++n;              // Un datos más que es contiguo y paso al siguiente dato
        }
        target[k++] = dataLenght;           // Cuando ya no hay dato contiguo agrego la cantidad de datos contiguos
        target[k++] = source[n];            // Y el dato que era contiguo
    }
}

/**
 * Esta función hace uso del algoritmo para compresión de datos
 * Run-length encoding, para una descripción del mismo dirijirse a:
 * http://en.wikipedia.org/wiki/Run-length_encoding
 * A diferencia de la otra función esta guarda los datos comprimidos en el mismo
 * buffer de origen por lo que se debe tener cuidado de que no halla demasiados
 * datos "sueltos" (1 solo datos sin otro contiguo) porque el buffer puede no ser
 * lo suficientemente grande si esta lleno.
 *
 * El número de datos contiguos es de 16 bits por lo que se almacena primero
 * el LSB y luego el MSB del número. Si no hay suficiente espacio en el array
 * o algún dato se repite menos de 3 veces se retorna -1 (error).
 *
 * @param buffer buffer de datos
 * @param bufferLength tamaño del buffer de datos
 * @return nueva longitud del buffer con los datos decodificados
 */
signed int RLEncodeSaveToSameBuffer (char *buffer, unsigned int bufferLenght){
    unsigned int n, k = 0, dataLenght = 1;

    for(n = 0; (n < (bufferLenght-3)) && (k < bufferLenght); ++n){
        dataLenght = 1;
        while(buffer[n] == buffer[n+1]){    // Mientras el dato actual se igual al siguiente (continuidad)
            ++dataLenght; ++n;              // Un datos más que es contiguo y paso al siguiente dato
        }
        if(dataLenght < 3) return -1;
        buffer[k++] = dataLenght & 0xFF;    // Cuando ya no hay dato contiguo agrego la cantidad de datos contiguos
        buffer[k++] = (dataLenght >> 8) & 0xFF;
        buffer[k++] = buffer[n];            // Y el dato que era contiguo
    }
    return k;
}

/**
 * Esta función hace uso del algoritmo para compresión de datos
 * Run-length encoding, para una descripción del mismo dirijirse a:
 * http://en.wikipedia.org/wiki/Run-length_encoding
 * En vez de almacenar los datos en un buffer los envía directamente por el
 * UART1.
 * @param buffer buffer de datos
 * @param bufferLength tamaño del buffer de datos
 */
void RLEncodeSendBuffer (char *buffer, unsigned int bufferLength){
    unsigned int n, dataLength = 1;

    for(n = 0; n < (bufferLength-1); ++n){
        dataLength = 1;
        while((buffer[n] == buffer[n+1]) && n < (bufferLength-1)){    // Mientras el dato actual se igual al siguiente (continuidad)
            ++dataLength; ++n;              // Un datos más que es contiguo y paso al siguiente dato
        }
        while(U1STAbits.UTXBF == 1);        // LSB
        WriteUART1(dataLength & 0xFF);
        while(U1STAbits.UTXBF == 1);        // MSB
        WriteUART1((dataLength >> 8) & 0xFF);
        while(U1STAbits.UTXBF == 1);        // Dato
        WriteUART1(buffer[n]);
    }
}

#endif
