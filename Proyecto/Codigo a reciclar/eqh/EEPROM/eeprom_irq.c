/*
 * eeprom_irq.c
 *
 *  Created on: 2 de feb. de 2017
 *      Author: aortiz
 */

#include "header.h"

void I2C1_IRQHandler(void)
{
	Chip_I2C_MasterStateHandler(I2C1);
}
