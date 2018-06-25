/*
 * sd_init.h
 *
 *  Created on: 10 de dic. de 2016
 *      Author: agustin
 */

#ifndef SD_INIT_H_
#define SD_INIT_H_

#include "header.h"

	#if (USE_SD)

		STATIC INLINE void SD_Init(void)
		{
			Board_SSP_Init(LPC_SSP1);
			Chip_SSP_Init(LPC_SSP1);
			Chip_SSP_Enable(LPC_SSP1);
		}

	#endif

#endif /* SD_INIT_H_ */
