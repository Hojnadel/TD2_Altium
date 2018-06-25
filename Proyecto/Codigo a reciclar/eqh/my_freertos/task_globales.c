/*
 * task_globales.c
 *
 *  Created on: 6 de nov. de 2016
 *      Author: agustin
 */

#include <header.h>

#if (USE_RTOS)

	// Queue
	volatile xQueueHandle Queue_botones;
	volatile xQueueHandle Queue_menu_adc;

	// Semaforos
	volatile xSemaphoreHandle Semaphore_adc_ready;
	volatile xSemaphoreHandle semaphore_tft_print;

//	volatile xSemaphoreHandle Mutex_DSP;

	volatile FATFS fs;           /**< FatFs work area needed for each volume */
	volatile FIL fp;             /**< File object needed for each open file */





#endif

