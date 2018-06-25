/*
 * task_init.c
 *
 *  Created on: 6 de nov. de 2016
 *      Author: agustin
 */


#include "header.h"


#if (USE_RTOS)


	void queue_init()
	{
		// Creo queue
		Queue_botones = xQueueCreate(1, sizeof(uint8_t));
		Queue_menu_adc = xQueueCreate(1, sizeof(uint8_t));

		// Creo semaforos
		vSemaphoreCreateBinary(Semaphore_adc_ready);
		vSemaphoreCreateBinary(semaphore_tft_print);


	}



	void task_init()
	{
		// Creo tareas


		#if (USE_GPIO)
			// TAREA LED
			xTaskCreate(vTaskLED_alive, (signed char *) "vTaskLED_alive",
						configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
						(xTaskHandle *) NULL);

		#if (USE_DISPLAY)
			//Tarea pantalla
			xTaskCreate(vDisplayTask, (signed char *) "vDisplayTask",
						configMINIMAL_STACK_SIZE*2, NULL, (tskIDLE_PRIORITY + 2UL),
						(xTaskHandle *) NULL);

		#endif

		#if(USE_BOTONES)
			// Tarea teclado
			xTaskCreate(vControlTask, (signed char *) "vControlTask",
						configMINIMAL_STACK_SIZE*2, NULL, (tskIDLE_PRIORITY + 2UL),
						(xTaskHandle *) NULL);
		#endif

		#endif

		#if (USE_ADC && USE_DAC)
			// Tarea adc
			xTaskCreate(vTaskSIGNAL_PROC, (signed char *) "vTaskSIGNAL_PROC",
						configMINIMAL_STACK_SIZE*32, NULL, (tskIDLE_PRIORITY + 3UL),
						(xTaskHandle *) NULL);
		#endif
	}


#endif

