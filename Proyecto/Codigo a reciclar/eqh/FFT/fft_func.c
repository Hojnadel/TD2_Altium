/*
 * fft_func.c
 *
 *  Created on: 2 de feb. de 2017
 *      Author: aortiz
 */


#include "fft_header.h"

/*****************************************************************************************/
/*****************************************************************************************/
/*****************************************************************************************/
		void Espectro_func(bool espectro_completo, uint8_t parte_de_espectro, uint16_t size_partes)
		{
			uint16_t i, j;


			//convierto a int y escalo en Y, ademas me quedo con 300 puntos
//			arm_q31_to_float((q31_t *)buffer_dep,(float32_t *)buffer_f,FFT_SIZE);

			if(espectro_completo)
			{
				//escalo en Y
				for(i=0; i<(FFT_SIZE/size_partes); i++)
				{
					tfty[i] = 0;

					for(j=0; j<size_partes; j++)
					{
						tfty[i] += buffer_adc[(i*size_partes)+j];
					}

					if(tfty[i] > 100) tfty[i] =100;
				}
			}
			else
			{
				arm_float_to_q31(buffer_adc+(FFT_SIZE/size_partes)*(parte_de_espectro), (q31_t *) tfty, size_partes);
			}
		}

		/*****************************************************************************************/
		/*****************************************************************************************/
		/*****************************************************************************************/

		void THD_func(uint32_t max_i, float32_t max_v)
		{
			int16_t i, j;
			float32_t num = 0;
			float32_t max = 0;
			float32_t THD2 = 0;
			float32_t mean = 0;
			const int MIN_FREC = 20;

			if(max_i<MIN_FREC)
			{
				THD = -1;

				return;
			}

//				// Armado del numerador de la división, sumará armonicos hasta el fin del vector, el denominador es max_val

			arm_mean_f32(buffer_adc, FFT_SIZE/2, &mean);

			for(i = max_i+FFT_ANCHO_LOBULO+1; i < ((FFT_SIZE/2)); i++)
			{
				if(buffer_adc[i] > mean)
					num += buffer_adc[i]*buffer_adc[i];
			}

			for(j = max_i-FFT_ANCHO_LOBULO; j <= max_i+FFT_ANCHO_LOBULO; j++)
			{
				max += buffer_adc[j]*buffer_adc[j];
			}

			// calculo de THD propiamente dicho
			THD2 = (num/max);
			arm_sqrt_f32(THD2, &THD);

			THD *= 100;
		}
