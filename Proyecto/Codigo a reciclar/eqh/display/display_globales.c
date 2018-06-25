/*
 * display_globales.c
 *
 *  Created on: 7 de nov. de 2016
 *      Author: agustin
 */

#include "header.h"

#if (USE_DISPLAY)

	volatile uint16_t ILI9341_x;
	volatile uint16_t ILI9341_y;

	volatile TM_ILI931_Options_t ILI9341_Opts;

	volatile uint8_t ILI9341_INT_CalledFromPuts = 0;

	volatile uint8_t using_tft = 0;

#endif
