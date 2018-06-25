/*
 * task_func.h
 *
 *  Created on: 7 de nov. de 2016
 *      Author: agustin
 */

#ifndef TASK_FUNC_H_
#define TASK_FUNC_H_


#include "header.h"


#if (USE_RTOS)

	void vTaskLED_alive(void *pvParameters);

	#if (USE_ADC && USE_DAC)

		void vTaskSIGNAL_PROC(void *pvParameters);

	#endif


	#if (USE_DISPLAY)

		void vDisplayTask(void *pvParameters);

	#endif

	#if (USE_BOTONES)

		void vControlTask(void *pvParameters);

	#endif

	#if (USE_SD)

		void vTaskSD(void *pvParameters);

	#endif

#endif



#endif /* TASK_FUNC_H_ */
