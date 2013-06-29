; W0 -> Direccion del puerto
; W1 -> Direccion del buffer
; W2 -> Tamaño del buffer
; W3 -> Tipo de flanco
; W4 -> Máscara de trigger
.global _vSample40MHz
_vSample40MHz:
    btss    w3, #0
    goto    FlancoSubida_40M
    goto    FlancoBajada_40M

    FlancoSubida_40M:
        mov.b    [w0],w5        ; Tomo el valor actual del puerto
        Again40M:
        and.b    w4,[w0],w6     ; Hago un AND entre el valor actual del puerto y la máscara y lo guardo en W6
        cpslt    w5,w6          ; Comparo entre el primer valor del puerto y el actual, salto si el primer valor
                                ;  era menor y el de ahora es mayor (flanco de subida)
        goto     Again40M;
        goto     Muestreo_40M;
    FlancoBajada_40M:
        mov.b    [w0],w5        ; Tomo el valor actual del puerto
        Again40M_2:
        and.b    w4,[w0],w6     ; Hago un AND entre el valor actual del puerto y la máscara y lo guardo en W6
        cpsgt    w5,w6          ; Comparo entre el primer valor del puerto y el actual, salto si el primer valor
                                ;  era mayor y el de ahora es menor (flanco de bajada)
        goto     Again40M_2;
        goto     Muestreo_40M;

    Muestreo_40M:
        repeat   w2
        mov.b    [w0],[w1++]
.end