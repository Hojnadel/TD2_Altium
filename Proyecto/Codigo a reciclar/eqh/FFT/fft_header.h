/*
 * fft_header.h
 *
 *  Created on: 20 de ene. de 2017
 *      Author: agustin
 */

#ifndef FFT_HEADER_H_
#define FFT_HEADER_H_


// ********* MODO DE USO ********** //
//
// *** UTILIDADES.H
// 		Se debe poner USE_FFT en ON para poder utilizar las funciones de FFT
// 		Se puede poner UARTN_TRANSMIT en UART_TRANSMIT_FFT para transmitir automaticamente por UART la fft realizada
//
// *** FFT_HEADER.H
// 		en FFT_SIZE se especifica el tamanio del vector que se quiere transformar.
//
// *** MAIN
// 		primero se debe poner el flag 'fft_status' en FFT_STATUS_EMPTY (para que nadie intente acceder al vector 'fft_vector'),
// 		luego se carga el vector 'fft_vector' con la señal a transformar (solo parte real, tamanio FFT_SIZE),
// 		luego se debe poner el flag 'fft_status' en FFT_STATUS_TO_DO (para indicar que se debe realizar FFT),
// 		finalmente se debe esperar a que el flag 'fft_status' sea igual a FFT_STATUS_DONE (que indica que ya se realizo la FFT).
// 		la senial transformada se encuentra en el mismo vector 'fft_vector'
//
// ******************************** //

	#include "config.h"

// ********* FUNCIONES ********** //
	#if USE_FFT
		void fft_function();
		void Espectro_func(bool espectro_completo, uint8_t parte_de_espectro, uint16_t size_partes);
		void Remanente_func();
		void THD_func(uint32_t max_i, float32_t max_v);
		void filtro_media_movil();
		void dft();
	#endif
// ****************************** //


// ***************** DEFINES ***************** //
	#if (USE_FFT || (USE_ADC && USE_DAC))
			#define     FFT_SIZE_8				8
			#define     FFT_SIZE_32				32
			#define     FFT_SIZE_64				64
			#define     FFT_SIZE_128			128
			#define     FFT_SIZE_256			256
			#define     FFT_SIZE_512			512
			#define     FFT_SIZE_1024			1024
			#define     FFT_SIZE_2048			2048
			#define     FFT_SIZE_4096			4096
		#define     FFT_SIZE    	           	FFT_SIZE_2048	// Tamanio del vector del modulo de la FFT = tamanio parte real de senial a transformar

		#define 	FFT_ANCHO_LOBULO 			6
	#endif
// ******************************************* //


// ************* VARIABLES GLOBALES ************* //
	#if USE_FFT
		extern arm_cfft_radix4_instance_f32 fft_inst_f32_complex;
		extern arm_rfft_instance_f32 fft_inst_f32;			// Estructura para aplicar FFT
		extern arm_rfft_instance_f32 ifft_inst_f32;			// Estructura para aplicar IFFT
		extern arm_fir_instance_f32 S;

		extern Bool flag_dac_send;	// Envia senial por DAC
		extern Bool flag_do_thd;	// Calcula THD
		extern Bool flag_do_rem;	// Calcula senal remanente

		extern int tfty[300];

		extern float32_t THD;

		// *** BUFFERS *** //
			#if (USE_ADC && USE_DAC)
				extern float32_t buffer_adc		[FFT_SIZE];
				extern float32_t buffer_adc2	[FFT_SIZE*2];
				extern const float w			[FFT_SIZE];
				extern const float32_t coef_filtro		[49];
			#endif
		// *************** //
	#endif
// ********************************************** //


// ************* INICIALIZACION ************* //
	#include "header.h"
	#include "fft_init.h"
	#include "fft_func.h"
// ****************************************** //


#endif /* FFT_HEADER_H_ */
