/*
 * adc_dac_header.h
 *
 *  Created on: 31 de oct. de 2016
 *      Author: agustin
 */


#ifndef ADC_DAC_HEADER_H_
#define ADC_DAC_HEADER_H_



#include <header.h>



// ********* FUNCIONES ********** //
	#if (USE_DAC_INTERNO)
		void main_dac();
		void main_dac_aux();
	#endif
// ****************************** //


// ***************** DEFINES ***************** //
	#if USE_ADC
		#define ADC_FREQ 				32000										// PROBAR CAMBIANDO A 32000
		#define ADC_DMA_CANT_MUESTRAS 	1
		#define ADC_DMA_CHANNEL 		1
	#endif

	#if USE_DAC
		#define DAC_FREQ 				ADC_FREQ
		#define DAC_DMA_CANT_MUESTRAS 	ADC_DMA_CANT_MUESTRAS
		#define DAC_DMA_CHANNEL 		0
	#endif

	#if (USE_ADC_EXTERNO)||(USE_DAC_EXTERNO)
		#define	I2S_INT_POLLING		1
		#define I2S_DMA				(!(I2S_INT_POLLING))

	// DAC: LPC 176 9
		#define AOUT				0,26

	// DAC: PCM 1802
		#define I2SRX_CLK			0,4
		#define I2SRX_WS			0,5
		#define I2SRX_SDA			0,6
		#define RX_MCLK				4,28

	// DAC: PCM 1781
		#define I2STX_CLK			0,7
		#define I2STX_WS			0,8
		#define I2STX_SDA			0,9
		#define TX_MCLK				4,29

	// GPIO ADC PCM 1802
		#define ADC_OSR				0,8
		#define ADC_FSYNC			0,7

	// GPIO DAC PCM 1781
		#define DAC_MUTE			1,16
		#define DAC_ZEROA			1,17

		#define CH_L				1
		#define CH_R				2

		#define BUFFER_A			0
		#define	BUFFER_B			1
	#endif


// ******************************************* //








//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SEÑALES DE PRUEBA
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern uint32_t CONT_A, CONT_B;
extern uint32_t CONT_BUSY_BUFF_A_ADC_DAC, CONT_BUSY_BUFF_A_DAC, CONT_BUSY_BUFF_A_ADC, CONT_BUSY_BUFF_B_ADC_DAC, CONT_BUSY_BUFF_B_DAC, CONT_BUSY_BUFF_B_ADC;
extern uint32_t CONT_READY_BUFF_A, CONT_READY_BUFF_B, CONT_ERROR;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//extern uint8_t buffer_state;


extern uint32_t irq_cont;
extern uint32_t task_cont;





// *************** ESTRUCTURAS *************** //
	#if (USE_BUFFER_PARALELO)

//		typedef enum {
//			IDLE_BUFF,
//			BUSY_BUFF_A_ADC_DAC,
//			BUSY_BUFF_A_ADC,
//			BUSY_BUFF_A_DAC,
//			READY_BUFF_A,
//			BUSY_BUFF_B_ADC_DAC,
//			BUSY_BUFF_B_ADC,
//			BUSY_BUFF_B_DAC,
//			READY_BUFF_B
//		} buffer_state_t;
//
//		typedef enum {
//			INT_ERROR,
//			INT_ADC,
//			INT_DAC,
//			INT_BOTH
//		} int_state_t;

		typedef enum {
			BUFFER_A_ADC,
			BUFFER_B_ADC,
			BUFFER_A_DAC,
			BUFFER_B_DAC
		} buffer_state_t;

		typedef enum {
			INT_IDLE,
			INT_ERROR,
			INT_ADC,
			INT_DAC,
			INT_BOTH
		} int_state_t;


	#endif
// ******************************************* //


// ************* VARIABLES GLOBALES ************* //
	#if (USE_ADC && (USE_ADC_INTERNO)||(USE_ADC_EXTERNO))
		extern volatile uint8_t canal_adc;

		#if (USE_BUFFER_SERIE)
			extern DMA_TransferDescriptor_t DMA_descriptor_ADC_BUFFER;

			extern volatile uint32_t dma_memory_adc_BUFF[ADC_DMA_CANT_MUESTRAS];
		#elif (USE_BUFFER_PARALELO)
			extern DMA_TransferDescriptor_t DMA_descriptor_ADC_BUFFER_A;
			extern DMA_TransferDescriptor_t DMA_descriptor_ADC_BUFFER_B;

			extern volatile uint32_t dma_memory_adc_BUFF_A[ADC_DMA_CANT_MUESTRAS];
			extern volatile uint32_t dma_memory_adc_BUFF_B[ADC_DMA_CANT_MUESTRAS];

//			extern volatile uint8_t buffer;
		#endif

	#endif

	#if (USE_DAC && (USE_DAC_INTERNO)||(USE_DAC_EXTERNO))
		extern volatile uint8_t canal_dac;

		#if (USE_BUFFER_SERIE)
			extern DMA_TransferDescriptor_t DMA_descriptor_DAC_BUFFER;

			extern volatile uint32_t dma_memory_dac_BUFF[DAC_DMA_CANT_MUESTRAS];
		#elif (USE_BUFFER_PARALELO)
			extern DMA_TransferDescriptor_t DMA_descriptor_DAC_BUFFER_A;
			extern DMA_TransferDescriptor_t DMA_descriptor_DAC_BUFFER_B;

			extern volatile uint16_t dma_memory_dac_BUFF_A[ADC_DMA_CANT_MUESTRAS];
			extern volatile uint16_t dma_memory_dac_BUFF_B[ADC_DMA_CANT_MUESTRAS];
		#endif

	#endif


	#if (USE_ADC_EXTERNO)||(USE_DAC_EXTERNO)
		extern uint16_t adcFlag;
		extern int32_t data, cont, ch;
	#endif

	#if (USE_BUFFER_PARALELO)

		extern buffer_state_t ESTADO_BUFFERS;

	#endif
// ********************************************** //


// ************* HEADERS ************* //
		#include "adc_dac_func.h"
		#include <adc_dac_init.h>
// ****************************************** //


#endif /* ADC_DAC_HEADER_H_ */

