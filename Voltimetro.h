//******************************************************************************//
//Nombre:   vVoltimetro					                        //
//Funci�n:  Lee la tensi�n en la entrada AN1 y detecta la polaridad de la       // 
//           tensi�n por el pin A7                                              //
//Retorna:  Nada                                                                //
//Le pasan: Nada								//
//******************************************************************************//
void vVoltimetro (void);

//******************************************************************************//
//Nombre:   vRango						                //
//Funci�n:  Env�a el rango al PIC esclavo en la l�nea de I2C para que cambie	//
//			el divisor resistivo del voltimetro			//
//Retorna:  Nada                                                                //
//Le pasan: Valor del rango	(unsigned char)					//
//******************************************************************************//
void vRango (unsigned char rango);
