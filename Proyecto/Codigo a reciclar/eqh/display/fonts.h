/*
 * fonts.h
 *
 *  Created on: 7 de nov. de 2016
 *      Author: agustin
 */

#ifndef FONTS_H_
#define FONTS_H_

#include "header.h"

#if (USE_DISPLAY)

// ********* FUNCIONES ********** //
	#if (USE_DISPLAY)


	#endif
// ****************************** //


// ***************** DEFINES ***************** //
	#if (USE_DISPLAY)


	#endif
// ******************************************* //


// *************** ESTRUCTURAS *************** //
	#if (USE_DISPLAY)

		// Font struct
		typedef struct {
			unsigned char FontWidth;
			unsigned char FontHeight;
			const uint16_t *data;
		} TM_FontDef_t;

	#endif
// ******************************************* //


// ************* VARIABLES GLOBALES ************* //
	#if (USE_DISPLAY)

		extern TM_FontDef_t TM_Font_7x10;
		extern TM_FontDef_t TM_Font_11x18;
		extern TM_FontDef_t TM_Font_16x26;

	#endif
// ********************************************** //


// ************* HEADERS ************* //


// ****************************************** //




#endif



#endif /* FONTS_H_ */
