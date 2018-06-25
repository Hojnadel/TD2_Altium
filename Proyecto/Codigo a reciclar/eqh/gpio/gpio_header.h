/*
 * gpio_header.h
 *
 *  Created on: 31 de oct. de 2016
 *      Author: agustin
 */

#ifndef GPIO_HEADER_H_
#define GPIO_HEADER_H_


#include <header.h>



// ********* FUNCIONES ********** //

// ****************************** //


// ***************** DEFINES ***************** //
	#if USE_GPIO

		#define LED_Alive			1,0

		#if (USE_BOTONES)
			// Switch
			#define SW1				1,15
			#define SW2				1,14
			#define SW3				1,10
			#define SW4				1,9

			// Debounce
			#define WAIT_1 0
			#define VALIDATE_1 1
			#define WAIT_0 2
			#define VALIDATE_0 3
		#endif

	#endif

// ******************************************* //


// ************* VARIABLES GLOBALES ************* //
	#if USE_GPIO

//		extern volatile uint8_t flag_volumen_up;
//		extern volatile uint8_t flag_efecto;

	#endif
// ********************************************** //


// ************* INICIALIZACION ************* //
		#include <gpio_init.h>
// ****************************************** //




#endif /* GPIO_HEADER_H_ */
