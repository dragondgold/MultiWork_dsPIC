//******************************************************************************//
//Nombre:   vVoltimetro					                        //
//Función:  Lee la tensión en la entrada AN1 y detecta la polaridad de la       // 
//           tensión por el pin A7                                              //
//Retorna:  Nada                                                                //
//Le pasan: Nada								//
//******************************************************************************//
void vVoltimetro (void);

//******************************************************************************//
//Nombre:   vRango						                //
//Función:  Envía el rango al PIC esclavo en la línea de I2C para que cambie	//
//			el divisor resistivo del voltimetro			//
//Retorna:  Nada                                                                //
//Le pasan: Valor del rango	(unsigned char)					//
//******************************************************************************//
void vRango (unsigned char rango);
