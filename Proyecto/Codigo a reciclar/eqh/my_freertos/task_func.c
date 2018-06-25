/*
 * task_func.c
 *
 *  Created on: 6 de nov. de 2016
 *      Author: agustin
 */


#include "header.h"

uint32_t blabla = 0;
uint8_t menu= 0;


#if (USE_RTOS)

	#if (USE_SD)

		void vTaskSD(void *pvParameters)
		{
			TM_ILI9341_Puts(10, 80, "Leyendo tarjeta SD...", &TM_Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_CYAN);

			param_t parameters = {0};
			UINT nbytes;
			char str[30];
			char buffer_read_SD [30] = {0};
			char coeficiente_read_SD[5] = {0};
			int i = 0;
			int j = 0;

			FRESULT SD_flag;
			/* Give a work area to the default drive */

			SD_flag = f_mount(&fs, "", 0);

			/* If this fails, it means that the function could
			 * not register a file system object.
			 * Check whether the SD card is correctly connected */
			if ( SD_flag != FR_OK)
			{}

//			if (f_open(&fp, FILENAME1, FA_WRITE | FA_CREATE_ALWAYS) == FR_OK)
//			{
//				f_write(&fp, "PROFUNDIDAD:345\r\nDISTORSION:123\r\n", strlen("PROFUNDIDAD:345\r\nDISTORSION:123\r\n"), &nbytes);		// NO DEJAR ESPACIOS ENTRE VALORES Y  LOS DOS PUNTOS ":"
//				f_close(&fp);
//			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			// ECO_IIR
			// eco_iir(dma_memory_adc_BUFF, dma_memory_dac_BUFF, DAC_DMA_CANT_MUESTRAS, 0, 16);
			//////////////////////////////////////////////////////////////////////////////////////////////////////////
			if( f_open(&fp, "eco_iir.txt" , FA_READ | FA_OPEN_EXISTING) == FR_OK)
			{
				f_read(&fp, buffer_read_SD, strlen("DELAY:") + 2, &nbytes);		// SOLO HASTA 3 NUMEROS EN PROFUNDIDAD O DISTORSION, CUALQUIER COSA CAMBIAR EL 3 POR UN VALOR.
				f_close(&fp);
			}

			for(i=0; buffer_read_SD[i]!=':';i++)
			{}
			i++;

			for( j=0 ; buffer_read_SD[i]!='\0';j++)									// Parseando los datos
			{
				coeficiente_read_SD[j]=buffer_read_SD[i];
				i++;
			}

			parameters.eco_iir_delay = atoi(coeficiente_read_SD);

			for(j=0 ; j<5 ; j++)
				coeficiente_read_SD[j] = 0;
			for(j=0 ; j<30 ; j++)
				buffer_read_SD[j] = 0;

			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			// OVERDRIVE
			// overdrive(dma_memory_adc_BUFF, dma_memory_dac_BUFF, DAC_DMA_CANT_MUESTRAS, 2);
			//////////////////////////////////////////////////////////////////////////////////////////////////////////
			if( f_open(&fp, "over.txt" , FA_READ | FA_OPEN_EXISTING) == FR_OK)
			{
				f_read(&fp, buffer_read_SD, strlen("DISTORSION:") + 2, &nbytes);		// SOLO HASTA 3 NUMEROS EN PROFUNDIDAD O DISTORSION, CUALQUIER COSA CAMBIAR EL 3 POR UN VALOR.
				f_close(&fp);
			}

			for(i=0; buffer_read_SD[i]!=':';i++)
			{}
			i++;

			for( j=0 ; buffer_read_SD[i]!='\0';j++)									// Parseando los datos
			{
				coeficiente_read_SD[j]=buffer_read_SD[i];
				i++;
			}

			parameters.overdrive_distorsion = atoi(coeficiente_read_SD);

			for(j=0 ; j<5 ; j++)
				coeficiente_read_SD[j] = 0;
			for(j=0 ; j<30 ; j++)
				buffer_read_SD[j] = 0;

			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			// REVERB
			// reverb(dma_memory_adc_BUFF, dma_memory_dac_BUFF, DAC_DMA_CANT_MUESTRAS, 0, 4);
			//////////////////////////////////////////////////////////////////////////////////////////////////////////
			if( f_open(&fp, "reverb.txt" , FA_READ | FA_OPEN_EXISTING) == FR_OK)
			{
				f_read(&fp, buffer_read_SD, strlen("densidad:") + 2, &nbytes);		// SOLO HASTA 3 NUMEROS EN PROFUNDIDAD O DISTORSION, CUALQUIER COSA CAMBIAR EL 3 POR UN VALOR.
				f_close(&fp);
			}

			for(i=0; buffer_read_SD[i]!=':';i++)
			{}
			i++;

			for( j=0 ; buffer_read_SD[i]!='\0';j++)									// Parseando los datos
			{
				coeficiente_read_SD[j]=buffer_read_SD[i];
				i++;
			}

			parameters.reverb_densidad = atoi(coeficiente_read_SD);

			for(j=0 ; j<5 ; j++)
				coeficiente_read_SD[j] = 0;
			for(j=0 ; j<30 ; j++)
				buffer_read_SD[j] = 0;

			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			// FLANGER
			// flanger(dma_memory_adc_BUFF, dma_memory_dac_BUFF, DAC_DMA_CANT_MUESTRAS, 0, 0, 4);
			//////////////////////////////////////////////////////////////////////////////////////////////////////////
			if( f_open(&fp, "flanger.txt" , FA_READ | FA_OPEN_EXISTING) == FR_OK)
			{
				f_read(&fp, buffer_read_SD, strlen("delay:") + 2, &nbytes);		// SOLO HASTA 3 NUMEROS EN PROFUNDIDAD O DISTORSION, CUALQUIER COSA CAMBIAR EL 3 POR UN VALOR.
				f_close(&fp);
			}

			for(i=0; buffer_read_SD[i]!=':';i++)
			{}
			i++;

			for( j=0 ; buffer_read_SD[i]!='\0';j++)									// Parseando los datos
			{
				coeficiente_read_SD[j]=buffer_read_SD[i];
				i++;
			}

			parameters.flanger_delay = atoi(coeficiente_read_SD);

			for(j=0 ; j<5 ; j++)
				coeficiente_read_SD[j] = 0;
			for(j=0 ; j<30 ; j++)
				buffer_read_SD[j] = 0;

			// prueba
			if(parameters.overdrive_distorsion == 0)
				sprintf(str, "overdrive dist = ERROR");
			else
				sprintf(str, "overdrive dist = %d", parameters.overdrive_distorsion);
			TM_ILI9341_Puts( 20, 125, str, &TM_Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_CYAN);

			for(j=0 ; j<30 ; j++)
				str[j] = 0;

			if(parameters.flanger_delay == 0)
				sprintf(str, "flanger delay = ERROR");
			else
				sprintf(str, "flanger delay = %d", parameters.flanger_delay);
			TM_ILI9341_Puts( 20, 150, str, &TM_Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_CYAN);

			for(j=0 ; j<30 ; j++)
				str[j] = 0;

			if(parameters.eco_iir_delay == 0)
				sprintf(str, "eco iir delay = ERROR");
			else
				sprintf(str, "eco iir delay = %d", parameters.eco_iir_delay);
			TM_ILI9341_Puts( 20, 175, str, &TM_Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_CYAN);

			for(j=0 ; j<30 ; j++)
				str[j] = 0;

			if(parameters.reverb_densidad == 0)
				sprintf(str, "reverb densidad = ERROR");
			else
				sprintf(str, "reverb densidad = %d", parameters.reverb_densidad);
			TM_ILI9341_Puts( 20, 200, str, &TM_Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_CYAN);

			xQueueSend(Queue_parametros, &parameters, portMAX_DELAY);

			while(1)
			{
				vTaskDelay(1000/portTICK_RATE_MS);	// Por si hay que hacer algo con la SD

				vTaskDelete(NULL);
			}
		}

	#endif

	#if(USE_GPIO)

		// LED ALIVE
		void vTaskLED_alive(void *pvParameters) {

			while (1) {
				vTaskDelay( 500 / portTICK_RATE_MS );
				Chip_GPIO_SetPinToggle(LPC_GPIO, LED_Alive);
			}
		}


/***************************************************************************************/
		#if (USE_BOTONES)
			// Debouncer
			void vControlTask(void *pvParameters)
			{
				uint8_t tecla = 0;
				uint16_t cant_rebotes = MAX_REBOTES;

				//SW1 sube y SW4 baja en el menú

				while (1)
				{
					if(!tecla)
					{
						if( Chip_GPIO_GetPinState( LPC_GPIO , SW1 ) == 0 )
							tecla = BOTON_1;
						else if( Chip_GPIO_GetPinState( LPC_GPIO , SW2 ) == 0 )
							tecla = BOTON_2;
						else if( Chip_GPIO_GetPinState( LPC_GPIO , SW3 ) == 0 )
							tecla = BOTON_3;
						else if( Chip_GPIO_GetPinState( LPC_GPIO , SW4 ) == 0 )
							tecla = BOTON_4;
					}
					else
					{
						if( (Chip_GPIO_GetPinState( LPC_GPIO , SW1 ) == 0) && (tecla == BOTON_1))
						{
							cant_rebotes--;
						}
						else if( (Chip_GPIO_GetPinState( LPC_GPIO , SW2 ) == 0) && (tecla == BOTON_2))
						{
							cant_rebotes--;
						}
						else if( (Chip_GPIO_GetPinState( LPC_GPIO , SW3 ) == 0) && (tecla == BOTON_3))
						{
							cant_rebotes--;
						}
						else if( (Chip_GPIO_GetPinState( LPC_GPIO , SW4 ) == 0) && (tecla == BOTON_4))
						{
							cant_rebotes--;
						}
						else
						{
							tecla = 0;
							cant_rebotes = MAX_REBOTES;
						}
					}

					if(!cant_rebotes)
					{
						xQueueSend(Queue_botones, &tecla, portMAX_DELAY);
					}

					vTaskDelay(REBOTES_DELAY_MS/portTICK_RATE_MS);
				}
			}
/***************************************************************************************/


					#if(USE_DISPLAY)

					#endif
//				}
//			}

		#endif
	#endif

	#if (USE_ADC && USE_DAC)


		void createSin(float amplitude, float fSampling, float fSine, uint32_t size, float *buffer)
		{
			uint32_t i;

			for(i = 0; i < size; i ++)
			{
				buffer[i] += amplitude * sinf(2 * PI * fSine * (float)i / fSampling);
			}
		}

		void dspMatrix_ScalarMultiplication(float *a, float *b, float *c,  uint32_t size)
		{
			uint32_t i;

			for(i = 0; i < size; i++)
			{
				c[i] = a[i] * b[i];
			}
		}

		void adc_tomar_muestras()
		{
			static uint16_t main_buffer_counter = 0;

			uint16_t i;


			// Inicio la transmición del ADC -> MEMORY usando el BUFFER
			Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_adc,
									&DMA_descriptor_ADC_BUFFER,
									GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);

			i=0;
			do
			{
				xSemaphoreTake(Semaphore_adc_ready, portMAX_DELAY);
				{
					if(i==0)
					{
						i=1;
						buffer_adc[main_buffer_counter] = (int) dma_memory_adc_BUFF[0];
						main_buffer_counter++;
					}
					else
					{
						i=0;
					}

					main_buffer_counter %= FFT_SIZE;

					if(main_buffer_counter)
					{
//							// Transmito el BUFFER
//							Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_dac,
//													&DMA_descriptor_DAC_BUFFER,
//													GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);
						Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_adc,
												&DMA_descriptor_ADC_BUFFER,
												GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
					}
				}
			}while(main_buffer_counter);
		}

		// SIGNAL PROCESSING
		void vTaskSIGNAL_PROC(void *pvParameters)
		{
			int i;
			uint8_t menu;
			float32_t max_v=0;
			uint32_t max_i=0;
			const int CANT_PROM = 1;


			#if USE_FFT_TASK
				q31_t num = 0; 	// Es la raiz cuadrada de la suma cuadratica de los armonicos de la DEP (numerador del THD)
			#endif

//			Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_adc,
//									&DMA_descriptor_ADC_BUFFER,
//									GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);

			xSemaphoreTake(Semaphore_adc_ready, portMAX_DELAY);

			while (1)
			{
				xQueueReceive(Queue_menu_adc, &menu, portMAX_DELAY);

					// Obtengo la fft y su maximo

				if(menu == THD_INIT || ESPECTRO_INIT)
				{
					adc_tomar_muestras();

					// Normaliza señal temporal
					arm_abs_f32(buffer_adc, buffer_adc2, FFT_SIZE);
					arm_max_f32(buffer_adc2, FFT_SIZE/2, &max_v, &max_i);
					arm_scale_f32(buffer_adc, 1/(max_v), buffer_adc2, FFT_SIZE);
					arm_copy_f32(buffer_adc2, buffer_adc, FFT_SIZE);

					// Aplica ventana
					dspMatrix_ScalarMultiplication(buffer_adc2, (float *)w, buffer_adc,  FFT_SIZE);

					// Calcula DEP
					fft_toCmplx(buffer_adc, buffer_adc2);
					fft_toDep(buffer_adc2, buffer_adc);

					// Calcula THD
					arm_max_f32(buffer_adc, FFT_SIZE/2, &max_v, &max_i);


					arm_scale_f32(buffer_adc, 1/(max_v), buffer_adc2, FFT_SIZE);


					THD_func(max_i, max_v);

					// Escala señal para imprimir en pantalla
					arm_scale_f32(buffer_adc, 289/(max_v), buffer_adc2, FFT_SIZE/2);
					arm_copy_f32(buffer_adc2, buffer_adc, FFT_SIZE/2);
				}

				xSemaphoreGive(semaphore_tft_print);
			}
		}

	#endif


	#if (USE_DISPLAY)
		/*****************************************************************************************/
		/*****************************************************************************************/
		/*****************************************************************************************/


		void vDisplayTask(void *pvParameters)
		{
			uint8_t pantalla = MENU;
			uint8_t seleccion = MENU_INIT;
			char string[15];
			uint8_t valor_leido = 0;
			uint8_t aux=0;
			int16_t y=0;

			// Leo de la eeprom el valor de calibracion
			uint16_t i = 0;
//			uint8_t data_send[5], data_read[3] = {0};
//			uint32_t valor_calibracion = 0;
//			uint8_t buff[5];
//			char str[10];
//
//			// para pruebas estan grabados los valores 0x5A, 0xFF, 0xOF a partir de la posicion de memoria 0x0FAF
//			// recordar que las direcciones se mandan en partes, primero la alta y luego la baja
//			buff[0] = 0x0F;		// High
//			buff[1] = 0xAF;		// Low
//			buff[2] = 0x5A;		// Data -> 0101 1010
//			buff[3] = 0xFF;
//			buff[4] = 0x0F;
//
//			// para escribir
////			Chip_I2C_MasterSend(I2C1, I2C_SLAVE_EEPROM_ADDR, buff, 5);
////			vTaskDelay( 1000 / portTICK_RATE_MS );
//
//			// para leer primero debemos posicionarlos en la direccion de memoria
//			Chip_I2C_MasterSend(I2C1, I2C_SLAVE_EEPROM_ADDR, buff, 2);
//			Chip_I2C_MasterRead(I2C1, I2C_SLAVE_EEPROM_ADDR, data_read, 3);
//			vTaskDelay( 1000 / portTICK_RATE_MS );
//
//			valor_calibracion = ((uint32_t *) data_read)[0];

			TM_ILI9341_Fill(ILI9341_COLOR_BLACK);

			// pantalla del menu
			TM_ILI9341_Puts( 10, 29, "THD METER", &TM_Font_16x26,  ILI9341_COLOR_WHITE, ILI9341_COLOR_GREEN);
			TM_ILI9341_DrawFilledCircle(30,110,7,ILI9341_COLOR_BLUE);
			TM_ILI9341_Puts( 50, 100, "Calculo de THD", &TM_Font_11x18,  ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
			TM_ILI9341_Puts( 50, 130, "Visualizacion espectral", &TM_Font_11x18,  ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
//			TM_ILI9341_Puts( 50, 160, "Remanente armonico", &TM_Font_11x18,  ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
//			TM_ILI9341_Puts( 50, 190, "Calibracion", &TM_Font_11x18,  ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);

//			sprintf(string, "CAL = %.2f", valor_calibracion);
//			TM_ILI9341_Puts( 200, 29, string, &TM_Font_11x18,  ILI9341_COLOR_WHITE, ILI9341_COLOR_GREEN);

			TM_ILI9341_DrawFilledCircle(30,110,7,ILI9341_COLOR_BLUE);
			TM_ILI9341_DrawFilledCircle(30,140,7,ILI9341_COLOR_BLACK);
//			TM_ILI9341_DrawFilledCircle(30,170,7,ILI9341_COLOR_BLACK);

			while(1)
			{
				// El menu ya esta cargado en la pantalla, si llegamos a apretar una tecla, entonces actualiza la pantalla
				if(xQueueReceive(Queue_botones, &valor_leido, 0))
				{
					// NUEVO BOTON APRETADO

					if(valor_leido == BOTON_UP)
					{
						seleccion = (seleccion+1) % (3);
					}

					if(valor_leido == BOTON_DOWN)
					{
						if(!seleccion)
							seleccion = 1;
						else
							seleccion--;
					}

					if(valor_leido == BOTON_BACK )
					{
						if(pantalla != MENU)
						{
							pantalla = MENU; seleccion = MENU_INIT;

							TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
						}
					}

					if(valor_leido == BOTON_OK)
					{
						if(pantalla == MENU)
						{
							if(seleccion == MENU_THD)
							{
								pantalla = THD_INIT;

								TM_ILI9341_Fill(ILI9341_COLOR_BLACK);

								TM_ILI9341_Puts(0, 0, "THD:", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
							}

							else if(seleccion == MENU_ESPECTRO)
							{
								pantalla = ESPECTRO_INIT;

								TM_ILI9341_Fill(ILI9341_COLOR_BLACK);

								TM_ILI9341_Puts(0, 0, "THD:", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
							}

//							else if(seleccion == MENU_REMANENTE)
//							{
//								pantalla = REMANENTE_INIT;
//
//								TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
//
//								TM_ILI9341_Puts(0, 0, "THD:", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
//							}
						}
					}


					if(pantalla == MENU)
					{
						// el flag "menu" evita la reescritura de la pantalla, la baja la pulsacion de un boton
						switch(seleccion)
						{
							case MENU_THD:
								TM_ILI9341_DrawFilledCircle(30,110,7,ILI9341_COLOR_BLUE);
								TM_ILI9341_DrawFilledCircle(30,140,7,ILI9341_COLOR_BLACK);
//								TM_ILI9341_DrawFilledCircle(30,170,7,ILI9341_COLOR_BLACK);
								break;
							case MENU_ESPECTRO:
								TM_ILI9341_DrawFilledCircle(30,110,7,ILI9341_COLOR_BLACK);
								TM_ILI9341_DrawFilledCircle(30,140,7,ILI9341_COLOR_BLUE);
//								TM_ILI9341_DrawFilledCircle(30,170,7,ILI9341_COLOR_BLACK);
								break;
//							case MENU_REMANENTE:
//								TM_ILI9341_DrawFilledCircle(30,110,7,ILI9341_COLOR_BLACK);
//								TM_ILI9341_DrawFilledCircle(30,140,7,ILI9341_COLOR_BLACK);
//								TM_ILI9341_DrawFilledCircle(30,170,7,ILI9341_COLOR_BLUE);
//								break;
							case MENU_INIT://volvio de otra pantalla
								// pantalla del menu
								TM_ILI9341_Puts( 10, 29, "THD METER", &TM_Font_16x26,  ILI9341_COLOR_WHITE, ILI9341_COLOR_GREEN);
								TM_ILI9341_DrawFilledCircle(30,110,7,ILI9341_COLOR_BLUE);
								TM_ILI9341_Puts( 50, 100, "Calculo de THD", &TM_Font_11x18,  ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
								TM_ILI9341_Puts( 50, 130, "Visualizacion espectral", &TM_Font_11x18,  ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
//								TM_ILI9341_Puts( 50, 160, "Remanente armonico", &TM_Font_11x18,  ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
//								TM_ILI9341_Puts( 50, 190, "Calibracion", &TM_Font_11x18,  ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);

//								sprintf(string, "CAL = %.2f", valor_calibracion);
//								TM_ILI9341_Puts( 200, 29, string, &TM_Font_11x18,  ILI9341_COLOR_WHITE, ILI9341_COLOR_GREEN);

								TM_ILI9341_DrawFilledCircle(30,110,7,ILI9341_COLOR_BLUE);
								TM_ILI9341_DrawFilledCircle(30,140,7,ILI9341_COLOR_BLACK);
								TM_ILI9341_DrawFilledCircle(30,170,7,ILI9341_COLOR_BLACK);

								seleccion=0;
								break;
							default:
								break;
						}
					}
				}
				else
				{
					// NO HAY NUEVO BOTON APRETADO

						// THD

					if(pantalla == THD_INIT)
					{
						// Comienza analisis de señal
						xQueueSend(Queue_menu_adc, &pantalla, portMAX_DELAY);

						pantalla = THD_WAIT;
					}
					else if(pantalla == THD_WAIT)
					{
						if(xSemaphoreTake(semaphore_tft_print, 0))
						{
							pantalla = THD_INIT;

							// Imprime THD
						if(THD < 0)
						{
							sprintf(string, "NO SIGNAL");
						}
						else
						{
							sprintf(string, "%.5f%%", THD);
						}
						TM_ILI9341_Puts(WINDOWWIDTHX2/2-8, WINDOWHEIGTHX2/2-13, string, &TM_Font_16x26, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);

						}
					}
					else if(pantalla == THD_DO)
					{
					}


						// ESPECTRO

					else if(pantalla == ESPECTRO_INIT)
					{
						// Comienza analisis de señal
						xQueueSend(Queue_menu_adc, &pantalla, portMAX_DELAY);

						if(aux<=0) aux=10;


						pantalla = ESPECTRO_WAIT;
					}
					if(pantalla == ESPECTRO_WAIT)
					{
						if(xSemaphoreTake(semaphore_tft_print, 0))
						{
							aux = 10;
						}
						if(aux >= 0)
						{
//							Espectro_func(false, 0, 300);

								// Imprime THD
							if(THD < 0)
							{
								sprintf(string, "NO SIGNAL");
								TM_ILI9341_Puts(WINDOWWIDTHX2/2-8, WINDOWHEIGTHX2/2-13, string, &TM_Font_16x26, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
								TM_ILI9341_FillRect(ILI9341_COLOR_BLACK, 0, 20, WINDOWHEIGTHX2, WINDOWHEIGTHX2);
							}
							else
							{
								sprintf(string, "%.5f%%", THD);
								TM_ILI9341_Puts(50, 0, string, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);

								if(aux == 10)
								{
										// Imprime espectro
									TM_ILI9341_FillRect(ILI9341_COLOR_BLACK, 0, 20, WINDOWHEIGTHX2, WINDOWHEIGTHX2);

									TM_ILI9341_DrawLine(10, WINDOWHEIGTHX2-1, 310, WINDOWHEIGTHX2-1, ILI9341_COLOR_BLUE);

									for(i = 0; i < 300; i++)
									{
										y = WINDOWHEIGTHX2 - 1 - ((int)buffer_adc[i]);
										if(((int)y)<20)
											y = 20;
										TM_ILI9341_DrawLine(i, WINDOWHEIGTHX2-1, i, y, ILI9341_COLOR_GREEN);
									}
								}
							}

							pantalla = ESPECTRO_INIT;

							aux--;
						}
					}

					vTaskDelay(100/portTICK_RATE_MS);	// Por si hay que hacer algo con la SD
				}
			}
		}
		/*****************************************************************************************/
		/*****************************************************************************************/
		/*****************************************************************************************/
	#endif


#endif




