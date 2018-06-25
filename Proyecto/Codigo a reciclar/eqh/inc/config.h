/*
 * config.h
 *
 *  Created on: 31 de oct. de 2016
 *      Author: agustin
 */


#ifndef CONFIG_H_
#define CONFIG_H_


	#include "FreeRTOS.h"
	#include "task.h"
	#include "board.h"
	#include "chip.h"
	#include "semphr.h"
	#include "queue.h"

	// CMSIS DSP lib
	#include "arm_math.h"

	#ifndef ON
		#define ON	1
	#endif
	#ifndef OFF
		#define OFF	0
	#endif

// ***** PERIFERICOS (init) ***** //
	#define	USE_GPIO		ON
	#define USE_ADC			ON
	#define USE_DAC			ON
	#define USE_DISPLAY		ON
	#define USE_RTOS		ON
	#define USE_EFECTOS		OFF
	#define USE_FFT			ON
	#define USE_SD			OFF
// ****************************** //


// ***** UTILIDADES (main while) ***** //
	#define DEBUG_MODE			OFF

	#if (USE_ADC)
		//Usar ADC interno y/o externo (externo por I2S)
		#define USE_ADC_INTERNO		OFF
		#define USE_ADC_EXTERNO		ON

		#if (USE_ADC_INTERNO)
				// Modo de uso (por interrupcion o por DMA)
				#define ADC_INTERNO_INTERRUPCION	ON
				#define ADC_INTERNO_DMA				OFF
			#define ADC_INTERNO_MODO	ADC_INTERNO_INTERRUPCION
		#endif
		#if (USE_ADC_EXTERNO)
				// Modo de uso (por interrupcion o por DMA)
				#define ADC_EXTERNO_INTERRUPCION	OFF
				#define ADC_EXTERNO_DMA				ON
			#define ADC_EXTERNO_MODO	ADC_EXTERNO_DMA
		#endif
	#endif

	#if (USE_DAC)
		//Usar DAC interno y/o externo (externo por I2S)
		#define USE_DAC_INTERNO		OFF
		#define USE_DAC_EXTERNO		ON

		#if (USE_DAC_INTERNO)
				// Modo de uso (por interrupcion o por DMA)
				#define DAC_INTERNO_INTERRUPCION	ON
				#define DAC_INTERNO_DMA				OFF
			#define DAC_INTERNO_MODO	DAC_INTERNO_INTERRUPCION
		#endif
		#if (USE_DAC_EXTERNO)
				// Modo de uso (por interrupcion o por DMA)
				#define DAC_EXTERNO_INTERRUPCION	ON
				#define DAC_EXTERNO_DMA				OFF
			#define DAC_EXTERNO_MODO	DAC_EXTERNO_DMA
		#endif
	#endif

	#if (USE_GPIO)
		#define USE_BOTONES		ON
	#endif

	#if (USE_FFT)
		#define USE_FFT_TASK	OFF
	#endif
// *********************************** //


// ******** Utilidades implicitas ******** //
	#if ( (defined(ADC_INTERNO_MODO) && ADC_INTERNO_MODO == ADC_INTERNO_DMA) || \
		  (defined(ADC_EXTERNO_MODO) && ADC_EXTERNO_MODO == ADC_EXTERNO_DMA) || \
		  (defined(DAC_INTERNO_MODO) && DAC_INTERNO_MODO == DAC_INTERNO_DMA) || \
		  (defined(DAC_EXTERNO_MODO) && DAC_EXTERNO_MODO == DAC_EXTERNO_DMA) )
		#define USE_DMA				ON
	#else
		#define USE_DMA				OFF
	#endif

	#if (USE_DMA)
		#define USE_BUFFER_SERIE		ON
		#define USE_BUFFER_PARALELO		OFF
	#endif

	#if (USE_BUFFER_SERIE)
		#define USE_DSP_IRQ				OFF
	#endif
// *************************************** //


// ***** FUNCIONES ****** //
	void main_init();
// ********************** //


#endif /* CONFIG_H_ */
