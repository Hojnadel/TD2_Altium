/*
 * fft_func.h
 *
 *  Created on: 20 de ene. de 2017
 *      Author: agustin
 */

#ifndef FFT_FUNC_H_
#define FFT_FUNC_H_


	#include "header.h"


	#if USE_FFT
		STATIC INLINE void fft_toCmplx(float32_t fft_in_real[FFT_SIZE], float32_t fft_out_cmplx[FFT_SIZE*2])
		{
			arm_rfft_f32(&fft_inst_f32, fft_in_real, fft_out_cmplx);
		}

		STATIC INLINE void fft_toDep(float32_t fft_in_cmplx[FFT_SIZE*2], float32_t fft_out_dep[FFT_SIZE/2])
		{
			arm_cmplx_mag_f32(fft_in_cmplx, fft_out_dep, FFT_SIZE/2);

			arm_copy_f32(fft_out_dep, fft_in_cmplx, FFT_SIZE/2);

			// Elevo al cuadrado para obtener la densidad espectral de potencia
			arm_mult_f32(
						fft_in_cmplx,
						fft_in_cmplx,
						fft_out_dep,
						FFT_SIZE/2);
		}

		STATIC INLINE void fft_toReal(float32_t fft_in_cmplx[FFT_SIZE], float32_t fft_out_real[FFT_SIZE])
		{
			arm_rfft_f32(&ifft_inst_f32, fft_in_cmplx, fft_out_real);
		}
	#endif



#endif /* FFT_FUNC_H_ */
