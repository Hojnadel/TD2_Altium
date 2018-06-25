/*
 * adc_dac_irq.c
 *
 *  Created on: 31 de oct. de 2016
 *      Author: agustin
 */



//uint8_t buffer_A[234];
//uint8_t buffer_B[234];
//uint8_t *buffer=NULL;



#include "header.h"



volatile uint32_t volumen = 0;
volatile uint32_t direccion = 0;




//uint8_t buffer_ready = 0;
#if USE_DMA

volatile uint32_t counter = 0;

	void DMA_IRQHandler(void)
	{
		#if USE_RTOS
				portBASE_TYPE HPTW = pdFALSE;
		#else
				int i = 0;
		#endif

		#if (USE_ADC)
			#if (USE_BUFFER_SERIE)

//				uint32_t muestra = 0;

				if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_adc)) // Se fija si interrumpio el ADC
				{

				#if (USE_DSP_IRQ)
					switch(flag_efecto)
					{
						case 1:
							distorsion(dma_memory_adc_BUFF, dma_memory_dac_BUFF, DAC_DMA_CANT_MUESTRAS, 0);
							break;
						case 2:
							overdrive(dma_memory_adc_BUFF, dma_memory_dac_BUFF, DAC_DMA_CANT_MUESTRAS, 2);
							break;
						default:
							for(i = 0; i < DAC_DMA_CANT_MUESTRAS; i++)
								dma_memory_dac_BUFF[i] = dma_memory_adc_BUFF[i];
							break;
					}

					// Transmito el BUFFER
					Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_dac,
											&DMA_descriptor_DAC_BUFFER,
											GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);
				#else
					// Aviso a la tarea que puede procesar el buffer del ADC
					xSemaphoreGiveFromISR(Semaphore_adc_ready, &HPTW);
					portEND_SWITCHING_ISR(HPTW);
				#endif
				}

				if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_dac)) // Se fija si interrumpio el DAC
				{
//					xQueueSendToBackFromISR(Queue_new_data, (const void * const) &buffer_ready, &HPTW);
					Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_adc,
											&DMA_descriptor_ADC_BUFFER,
											GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
				}
			#endif

			#if (USE_BUFFER_PARALELO)

				if( LPC_GPDMA->INTTCSTAT == 0x3 )
					CONT_B = 7;


				switch(ESTADO_BUFFERS)
				{
//				case IDLE_BUFF :
//					break;
				case BUSY_BUFF_A_ADC_DAC :								// BUFFER A			---			ADC		=		!!!!			---			DAC		=		!!!!


					CONT_BUSY_BUFF_A_ADC_DAC ++;


					if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_adc))		// 					---			ADC		=		READY			---			DAC		=		!!!!
					{
//						BUFFER_ADC_A = READY;
						ESTADO_BUFFERS = BUSY_BUFF_A_DAC;
					}
					else if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_dac))		// 					---			ADC		=		!!!!			---			DAC		=		READY
					{
//						BUFFER_DAC_A = READY;
						if(ESTADO_BUFFERS == BUSY_BUFF_A_ADC)
							ESTADO_BUFFERS = READY_BUFF_A;
						else
							ESTADO_BUFFERS = BUSY_BUFF_A_ADC;
					}
					else
						while(1);
					break;
				case BUSY_BUFF_A_DAC :									// BUFFER A			---			ADC		=		READY			---			DAC		=		!!!!


					CONT_BUSY_BUFF_A_DAC ++;


					if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_dac))		// 					---			ADC		=		READY			---			DAC		=		READY
					{
						buffer_ready = BUFFER_A;
						ESTADO_BUFFERS = READY_BUFF_A;
					}
					break;
				case BUSY_BUFF_A_ADC :									// BUFFER A			---			ADC		=		!!!!			---			DAC		=		READY


					CONT_BUSY_BUFF_A_ADC++;


					if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_adc))		// 					---			ADC		=		READY			---			DAC		=		READY
					{
						buffer_ready = BUFFER_A;
						ESTADO_BUFFERS = READY_BUFF_A;
					}
					else
						while(1);
					break;
				case BUSY_BUFF_B_ADC_DAC :								// BUFFER B			---			ADC		=		!!!!			---			DAC		=		!!!!


					CONT_BUSY_BUFF_B_ADC_DAC++;


					if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_adc))		// 					---			ADC		=		READY			---			DAC		=		!!!!
					{
//						BUFFER_ADC_B = READY;
						ESTADO_BUFFERS = BUSY_BUFF_B_DAC;
					}
					else if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_dac))		// 					---			ADC		=		!!!!			---			DAC		=		READY
					{
//						BUFFER_DAC_B = READY;
						if(ESTADO_BUFFERS == BUSY_BUFF_B_ADC)
							ESTADO_BUFFERS = READY_BUFF_B;
						else
							ESTADO_BUFFERS = BUSY_BUFF_B_ADC;
					}
					else
						while(1);
					break;
				case BUSY_BUFF_B_DAC :									// BUFFER B			---			ADC		=		READY			---			DAC		=		!!!!


					CONT_BUSY_BUFF_B_DAC++;


					if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_dac))		// 					---			ADC		=		READY			---			DAC		=		READY
					{
						buffer_ready = BUFFER_B;
						ESTADO_BUFFERS = READY_BUFF_B;
					}
					else
						while(1);
					break;
				case BUSY_BUFF_B_ADC :									// BUFFER B			---			ADC		=		!!!!			---			DAC		=		READY


					CONT_BUSY_BUFF_B_ADC++;


					if(Chip_GPDMA_Interrupt(LPC_GPDMA, canal_adc))		// 					---			ADC		=		READY			---			DAC		=		READY
					{
						buffer_ready = BUFFER_B;
						ESTADO_BUFFERS = READY_BUFF_B;
					}
					break;
				default:
					break;
				}

				if (ESTADO_BUFFERS == READY_BUFF_A) 					// BUFFER A			---			ADC		=		READY			---			DAC		=		READY
				{


					CONT_READY_BUFF_A++;


					ESTADO_BUFFERS = BUSY_BUFF_B_ADC_DAC;
					#if USE_RTOS
						// Aviso a la tarea que puede procesar los buffer A del ADC y DAC
						xQueueSendToBackFromISR(Queue_new_data, (const void * const) &buffer_ready, &HPTW);
						portEND_SWITCHING_ISR(HPTW);
					#else
						// Transmito los buffer B del ADC y DAC
						Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_adc,
												&DMA_descriptor_ADC_BUFFER_B,
												GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);

						Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_dac,
												&DMA_descriptor_DAC_BUFFER_B,
												GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);

						// Procesamiento de buffer A del ADC->DAC
						for(i=0; i<DAC_DMA_CANT_MUESTRAS; i++)
							dma_memory_dac_BUFF_A[i] =  set_data (dma_memory_adc_BUFF_A[i]);
					#endif
				}
				else if ( ESTADO_BUFFERS == READY_BUFF_B )					// BUFFER B			---			ADC		=		READY			---			DAC		=		READY
				{

					CONT_READY_BUFF_B++;


					ESTADO_BUFFERS = BUSY_BUFF_A_ADC_DAC;
					#if USE_RTOS
						// Aviso a la tarea que puede procesar los buffer A del ADC y DAC
						xQueueSendToBackFromISR(Queue_new_data, (const void * const) &buffer_ready, &HPTW);
						portEND_SWITCHING_ISR(HPTW);
					#else
						// Transmito los buffer B del ADC y DAC
						Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_adc,
												&DMA_descriptor_ADC_BUFFER_A,
												GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);

						Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_dac,
												&DMA_descriptor_DAC_BUFFER_A,
												GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);

						// Procesamiento de buffer A del ADC->DAC
						for(i=0; i<DAC_DMA_CANT_MUESTRAS; i++)
							dma_memory_dac_BUFF_B[i] =  set_data (dma_memory_adc_BUFF_B[i]);
					#endif
				}
			#endif
		#endif
	}

#endif
