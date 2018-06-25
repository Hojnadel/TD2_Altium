/*
 * adc_dac_func.c
 *
 *  Created on: 31 de oct. de 2016
 *      Author: agustin
 */


#include "header.h"


	uint32_t set_data (uint32_t data)
	{
		uint32_t aux = 0;

		aux = data;

		if(aux < 0)
			aux = (aux >> 8);
		else
		{
			aux = aux >> 8 ;
//			aux &= (0x00FFFFFF);
		}

		if(aux < 16777216)		// 2^24
			aux = aux + 8388608;
		else
			aux = aux - 8388608;

		aux &= (0x00FFFFFF);

		return (aux >> 8);
	}
