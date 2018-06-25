/*
 * fft_init.h
 *
 *  Created on: 20 de ene. de 2017
 *      Author: agustin
 */

#ifndef FFT_INIT_H_
#define FFT_INIT_H_


	#include "header.h"
	#include "fft_func.h"
	#include "display_header.h"
	#include "display_init.h"
	#include "display_func.h"
	#include "gpio_header.h"


	#define FFT_INIT_FFT_LENGTH 	FFT_SIZE
	#define FFT_INIT_DO_FFT 		FALSE
	#define FFT_INIT_DO_IFFT 		TRUE
	#define FFT_INIT_BIT_REVERSE 	TRUE

	//** Inicializacion de señal de entrada
	#define	X_SIZE				FFT_SIZE
	#define	X_AMPLITUDE			1.0
	#define	X_FS					51200.0
	#define	X_FREC				1000.0



	#if USE_FFT
		STATIC INLINE void fft_init()
		{
			if(arm_rfft_init_f32(&fft_inst_f32, &fft_inst_f32_complex, FFT_INIT_FFT_LENGTH, FFT_INIT_DO_FFT, FFT_INIT_BIT_REVERSE) == ARM_MATH_ARGUMENT_ERROR)
			{
				while(1);
			}

//			if(arm_rfft_init_f32(&ifft_inst_f32, &fft_inst_f32_complex, FFT_INIT_FFT_LENGTH, FFT_INIT_DO_IFFT, FFT_INIT_BIT_REVERSE) == ARM_MATH_ARGUMENT_ERROR)
//			{
//				while(1);
//			}
		}
	#endif


#endif /* FFT_INIT_H_ */


