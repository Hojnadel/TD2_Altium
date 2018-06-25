/*
 * gpio.h
 *
 *  Created on: 31 de oct. de 2016
 *      Author: agustin
 */

#ifndef GPIO_INIT_H_
#define GPIO_INIT_H_

#include "header.h"

#if USE_GPIO
	/* Get divider value */
	STATIC INLINE void gpio_init()
	{
		// LED Alive
		Chip_IOCON_PinMux(LPC_IOCON, LED_Alive, MD_PLN, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, LED_Alive);

		Chip_GPIO_SetPinState(LPC_GPIO, LED_Alive, ENABLE);

		#if (USE_BOTONES)
			// Inicialización de pulsadores
			Chip_IOCON_PinMux(LPC_IOCON, SW1, MD_PUP, IOCON_FUNC0);
			Chip_GPIO_SetPinDIRInput(LPC_GPIO, SW1);

			Chip_IOCON_PinMux(LPC_IOCON, SW2, MD_PUP, IOCON_FUNC0);
			Chip_GPIO_SetPinDIRInput(LPC_GPIO, SW2);

			Chip_IOCON_PinMux(LPC_IOCON, SW3, MD_PUP, IOCON_FUNC0);
			Chip_GPIO_SetPinDIRInput(LPC_GPIO, SW3);

			Chip_IOCON_PinMux(LPC_IOCON, SW4, MD_PUP, IOCON_FUNC0);
			Chip_GPIO_SetPinDIRInput(LPC_GPIO, SW4);
		#endif
	}
#endif


#endif /* GPIO_INIT_H_ */
