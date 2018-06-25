/*
 * efectos_header.h
 *
 *  Created on: 8 de dic. de 2016
 *      Author: agustin
 */

#ifndef EFECTOS_HEADER_H_
#define EFECTOS_HEADER_H_

#include "header.h"


// ********* FUNCIONES ********** //
	#if (USE_EFECTOS)

		void distorsion(q31_t *in, q31_t *out, uint16_t length, q31_t dist);
		void overdrive(q31_t *in, q31_t *out, uint16_t length, q31_t dist);
		void eco_iir(q31_t *in, q31_t *out, uint16_t length, q31_t profundidad, uint8_t delay);
		void reverb(q31_t *in, q31_t *out, uint16_t length, q31_t profundidad, uint8_t densidad);
		void flanger(q31_t *in, q31_t *out, uint16_t length, q31_t profundidad, uint16_t cos_f, uint8_t delay);

	#endif
// ****************************** //


// ***************** DEFINES ***************** //
	#if (USE_EFECTOS)

	#define LFO_LENGTH_VEL	8000
	#define LFO_LENGTH		320

	// Cantidad de ecos que suma para obtener el efecto reverb
	#define CANT_REVERB 2

	// Cantidad de ecos que suma para obtener el efecto reverb
	#define DELAY_LENGTH 8000

	#define TS	((q31_t) 0x10625)

	#endif
// ******************************************* //


// *************** ESTRUCTURAS *************** //
	#if (USE_EFECTOS)



	#endif
// ******************************************* //


// ************* VARIABLES GLOBALES ************* //
	#if (USE_EFECTOS)



	#endif
// ********************************************** //


// ************* HEADERS ************* //


// ****************************************** //



#endif /* EFECTOS_HEADER_H_ */
