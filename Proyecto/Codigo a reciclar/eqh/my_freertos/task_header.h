/*
 * task_header.h
 *
 *  Created on: 6 de nov. de 2016
 *      Author: agustin
 */

#ifndef TASK_HEADER_H_
#define TASK_HEADER_H_



#include <header.h>



// ********* FUNCIONES ********** //
	#if (USE_RTOS)
		void queue_init();
		void task_init();
	#endif
// ****************************** //


// ***************** DEFINES ***************** //

	#define FILENAME1 "overdrive.txt"
	#define FILENAME2 "eco_iir.txt"
	#define FILENAME3 "reverb.txt"
	#define FILENAME4 "flanger.txt"


	#define MAX_REBOTES		5
	#define REBOTES_DELAY_MS	10

	#define BOTON_1			1
	#define BOTON_2			2
	#define BOTON_3			3
	#define BOTON_4			4

	#define BOTON_UP			BOTON_4
	#define BOTON_DOWN		BOTON_3
	#define BOTON_OK			BOTON_2
	#define BOTON_BACK		BOTON_1

	#define MENU_INIT		    		3
	#define MENU_THD		    		0
	#define MENU_ESPECTRO		    	1
//	#define MENU_REMANENTE		    	2

	#define MENU		    		0
	#define THD_INIT			1
	#define THD_WAIT			2
	#define THD_DO			3
	#define ESPECTRO_INIT		4
	#define ESPECTRO_WAIT		5
//	#define REMANENTE_INIT		6
//	#define REMANENTE_WAIT		7
//	#define CALIBRACION_INIT		8
//	#define CALIBRACION_WAIT	9
//	#define CALIBRACION_DO		10

	#define HABILITADO	    		0
	#define DESHABILITADO		1
	#define TERMINO 			2
	#define PENDIENTE			3


// ******************************************* //


// ************* VARIABLES GLOBALES ************* //
	#if (USE_RTOS)

		// Queue
		extern volatile xQueueHandle Queue_botones;
		extern volatile xQueueHandle Queue_menu_adc;

		// Semaforos
		extern volatile xSemaphoreHandle Semaphore_adc_ready;
		extern volatile xSemaphoreHandle semaphore_tft_print;

		extern uint8_t seleccion;
		extern uint8_t pantalla;
		extern uint8_t tecla;
		extern uint8_t calibracion;

		// Semaphore


		#if(USE_SD)
				extern volatile FATFS fs;           /**< FatFs work area needed for each volume */
				extern volatile FIL fp;             /**< File object needed for each open file */
		#endif

	#endif


// ********************************************** //



// ************* INICIALIZACION ************* //
		#include "FreeRTOS.h"
		#include "task.h"
		#include "queue.h"
		#include "semphr.h"

		#include "task_func.h"

// ****************************************** //



#endif /* TASK_HEADER_H_ */
