/*
 * globales.c
 *
 *  Created on: 31 de oct. de 2016
 *      Author: agustin
 */


#include <header.h>





///////////////////////////

uint32_t irq_cont = 0;
uint32_t task_cont = 0;

//buffer_state_t ESTADO_ADC = BUFFER_A_ADC;




///////////////////////////







#if (USE_ADC && (USE_ADC_INTERNO)||(USE_ADC_EXTERNO))
	volatile uint8_t canal_adc;

	#if (USE_BUFFER_SERIE)
		DMA_TransferDescriptor_t DMA_descriptor_ADC_BUFFER;

		volatile uint32_t dma_memory_adc_BUFF[ADC_DMA_CANT_MUESTRAS]
											   = {0};
	#elif (USE_BUFFER_PARALELO)
		DMA_TransferDescriptor_t DMA_descriptor_ADC_BUFFER_A;
		DMA_TransferDescriptor_t DMA_descriptor_ADC_BUFFER_B;

		volatile uint32_t dma_memory_adc_BUFF_A[ADC_DMA_CANT_MUESTRAS];
		volatile uint32_t dma_memory_adc_BUFF_B[ADC_DMA_CANT_MUESTRAS];

		volatile uint8_t buffer = BUFFER_A;
	#endif

#endif

#if (USE_DAC && (USE_DAC_INTERNO)||(USE_DAC_EXTERNO))
	volatile uint8_t canal_dac;

	#if (USE_BUFFER_SERIE)
		DMA_TransferDescriptor_t DMA_descriptor_DAC_BUFFER;

		volatile uint32_t dma_memory_dac_BUFF[DAC_DMA_CANT_MUESTRAS]
												 ;//__attribute__ ((section (".bss.$RamAHB32")));
	#elif (USE_BUFFER_PARALELO)
		DMA_TransferDescriptor_t DMA_descriptor_DAC_BUFFER_A;
		DMA_TransferDescriptor_t DMA_descriptor_DAC_BUFFER_B;

		volatile uint16_t dma_memory_dac_BUFF_A[ADC_DMA_CANT_MUESTRAS];
		volatile uint16_t dma_memory_dac_BUFF_B[ADC_DMA_CANT_MUESTRAS];
	#endif

#endif


#if (USE_ADC_EXTERNO)||(USE_DAC_EXTERNO)
	uint16_t adcFlag = 1;
	int32_t data, cont = 0, ch = 0;
#endif


#if (USE_BUFFER_PARALELO)

//	buffer_state_t ESTADO_BUFFERS = IDLE_BUFF;

#endif
