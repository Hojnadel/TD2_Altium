/*
 * efectos_func.c
 *
 *  Created on: 8 de dic. de 2016
 *      Author: agustin
 */


#include "header.h"


#if (USE_EFECTOS)

	void distorsion(q31_t *in, q31_t *out, uint16_t length, q31_t dist)
	{
		for(int i=0; i<length; i++)
		{
			if(in[i] > (q31_t) 0x10000000)
			{
				out[i] = (q31_t) 0x10000000;
			}
			else if(in[i] < (q31_t) 0xA0000000)
			{
				out[i] = (q31_t) 0xA0000000;
			}
			else
			{
				out[i] = in[i];
			}
				out[i] *= 3;
		}
	}

	void overdrive(q31_t *in, q31_t *out, uint16_t length, q31_t dist)
	{
		for(int i=0; i<length; i++)
		{
			in[i] *= dist;

			if(in[i] > 0)
			{
				arm_sqrt_q31(in[i], &out[i]);
			}
			else
			{
				arm_abs_q31(&in[i], &out[i], 1);
				arm_sqrt_q31(out[i], &out[i]);
				out[i] *= -1;
			}
		}
	}

	volatile static q31_t delay_line[DELAY_LENGTH] __attribute__ ((section (".bss.$RamAHB32"))) = {0} ;

	void eco_iir(q31_t *in, q31_t *out, uint16_t length, q31_t profundidad, uint8_t delay)
	{
		static uint16_t delay_in_idx = 0;   // Indice para agregar muestra al delay_line
		static uint16_t delay_out_idx = 1;  // Indice para sumar al eco una muestra de la delay_line
		static uint8_t densidad_cont = 0;   // Sirve para agregar al delay_line una muestra de cada 'densidad' elementos (suma al eco 'densidad' veces la misma muestra)
		q31_t aux = 0;

		for(int i=0; i<length; i++)
		{
			aux = in[i] >> 8;

			out[i] = 0; // Eco IIR

			out[i] = (aux + (delay_line[delay_out_idx] >> 1)); // Calcula el eco sumando una muestra anterior guardada en la delay_line

				// Una de cada 'delay' muestras, agrega el eco a la delay_line
			densidad_cont++;
			densidad_cont %= delay;

			if(!densidad_cont)
			{
				delay_line[delay_in_idx] = out[i];

				delay_in_idx++;
				delay_in_idx %= DELAY_LENGTH;
				delay_out_idx++;
				delay_out_idx %= DELAY_LENGTH;
			}

			out[i] = out[i] << 7;
		}
	}

	void reverb(q31_t *in, q31_t *out, uint16_t length, q31_t profundidad, uint8_t densidad)
	{
		static uint16_t delay_in_idx = DELAY_LENGTH;                  					 // Indice para agregar muestra al delay_line
		static uint16_t delay_out_idx[CANT_REVERB] = {DELAY_LENGTH/3, DELAY_LENGTH/2};   // Indice para sumar al eco una muestra de la delay_line
		static uint8_t densidad_cont = 0;                								 // Sirve para agregar al delay_line una muestra de cada 'densidad' elementos (suma al eco 'densidad' veces la misma muestra)

		uint16_t aux = 0;

		for(int i=0; i<length; i++)
		{
			out[i] = 0; // Reverb

			out[i] = in[i] >> 8;

			for(int i=0; i<CANT_REVERB; i++)
			{
				aux = delay_out_idx[i];
				out[i] += (delay_line[aux] >> i); // Calcula el eco sumando una muestra anterior guardada en la delay_line
			}

			// Una de cada 'densidad' muestras, agrega el eco a la delay_line
			densidad_cont++;
			densidad_cont %= densidad;

			if(!densidad_cont)
			{
				delay_in_idx++;
				delay_in_idx %= DELAY_LENGTH;

				for(int i=0; i<CANT_REVERB; i++)
				{
					delay_out_idx[i]++;
					delay_out_idx[i] %= DELAY_LENGTH;
				}

				delay_line[delay_in_idx] = out[i];
			}

			out[i] = out[i] << 6;
		}
	}

	volatile static int lfo[LFO_LENGTH] = { 0,77,153,230,306,382,458,534,610,686,761,836,910,985,1059,1132,1205,1278,1350,1421,1492,
	1563,1633,1702,1771,1838,1906,1972,2038,2103,2167,2230,2292,2354,2414,2474,2533,2591,2647,2703,2758,2811,2864,2915,2966,3015,3063,3110,3155,3200,3243,3285,3325,3365,
	3403,3439,3475,3509,3542,3573,3603,3632,3659,3685,3709,3732,3754,3774,3792,3809,3825,3839,3852,3863,3873,3881,3888,3893,3897,3899,3900,3899,3897,3893,3888,3881,3873,
	3863,3852,3839,3825,3809,3792,3774,3754,3732,3709,3685,3659,3632,3603,3573,3542,3509,3475,3439,3403,3365,3325,3285,3243,3200,3155,3110,3063,3015,2966,2915,2864,2811,
	2758,2703,2647,2591,2533,2474,2414,2354,2292,2230,2167,2103,2038,1972,1906,1838,1771,1702,1633,1563,1492,1421,1350,1278,1205,1132,1059,985,910,836,761,686,610,534,458,
	382,306,230,153,77,0,-77,-153,-230,-306,-382,-458,-534,-610,-686,-761,-836,-910,-985,-1059,-1132,-1205,-1278,-1350,-1421,-1492,-1563,-1633,-1702,-1771,-1838,-1906,-1972,
	-2038,-2103,-2167,-2230,-2292,-2354,-2414,-2474,-2533,-2591,-2647,-2703,-2758,-2811,-2864,-2915,-2966,-3015,-3063,-3110,-3155,-3200,-3243,-3285,-3325,-3365,-3403,-3439,
	-3475,-3509,-3542,-3573,-3603,-3632,-3659,-3685,-3709,-3732,-3754,-3774,-3792,-3809,-3825,-3839,-3852,-3863,-3873,-3881,-3888,-3893,-3897,-3899,-3900,-3899,-3897,-3893,
	-3888,-3881,-3873,-3863,-3852,-3839,-3825,-3809,-3792,-3774,-3754,-3732,-3709,-3685,-3659,-3632,-3603,-3573,-3542,-3509,-3475,-3439,-3403,-3365,-3325,-3285,-3243,-3200,
	-3155,-3110,-3063,-3015,-2966,-2915,-2864,-2811,-2758,-2703,-2647,-2591,-2533,-2474,-2414,-2354,-2292,-2230,-2167,-2103,-2038,-1972,-1906,-1838,-1771,-1702,-1633,-1563,
	-1492,-1421,-1350,-1278,-1205,-1132,-1059,-985,-910,-836,-761,-686,-610,-534,-458,-382,-306,-230,-153,-77 };

	void flanger(q31_t *in, q31_t *out, uint16_t length, q31_t profundidad, uint16_t cos_f, uint8_t delay)
	{
		static uint16_t flanger_in_idx = 0;		// Indice para agregar muestra al delay_line
		static uint8_t densidad_cont = 0;		// Sirve para agregar al delay_line una muestra de cada 'densidad' elementos (suma al eco 'densidad' veces la misma muestra)
		static uint16_t lfo_idx = 0;			// Indice para recorrer el seno, aumenta de a 10 muestras procesadas
		static uint16_t lfo_idx_aux = 0;		// Indice para recorrer el seno, aumenta de a 10 muestras procesadas
		int16_t flanger_idx;					// Para calcular el indice del delay_line segun una funcion coseno

		for(int i=0; i<length; i++)
		{
			flanger_idx = flanger_in_idx - DELAY_LENGTH/2 + lfo[lfo_idx];
			if(flanger_idx < 0)
				flanger_idx += DELAY_LENGTH;

			in[i] = in[i] >> 8;

			out[i] = (in[i] + (delay_line[flanger_idx] >> 1)); // Calcula el eco sumando una muestra anterior guardada en la delay_line

			lfo_idx_aux ++;
			lfo_idx_aux %= LFO_LENGTH_VEL;

			if(!lfo_idx_aux)
			{
				lfo_idx ++;
				lfo_idx %= LFO_LENGTH;
			}

			// Una de cada 'delay' muestras, agrega el eco a la delay_line
			densidad_cont++;
			densidad_cont %= delay;

			if(!densidad_cont)
			{
				delay_line[flanger_in_idx] = out[i];

				flanger_in_idx++;
				flanger_in_idx %= DELAY_LENGTH;
			}

			out[i] = out[i] << 7;
		}
	}

#endif

