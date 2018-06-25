/*
 * eeprom.h
 *
 *  Created on: 2 de feb. de 2017
 *      Author: aortiz
 */

#ifndef EEPROM_H_
#define EEPROM_H_



#define SDA1			0,0
#define SCL1			0,1

#define SPEED_100KHZ				100000
#define I2C_SLAVE_EEPROM_ADDR		0x50


#define TIMER_match0	0



inline static void eeprom_init ( void )
{
	// I2C
	Chip_IOCON_PinMux(LPC_IOCON, SDA1, IOCON_MODE_INACT, IOCON_FUNC3);
	Chip_IOCON_PinMux(LPC_IOCON, SCL1, IOCON_MODE_INACT, IOCON_FUNC3);
	Chip_IOCON_EnableOD(LPC_IOCON, SDA1);
	Chip_IOCON_EnableOD(LPC_IOCON, SCL1);

	Chip_I2C_Init(I2C1);
	Chip_I2C_SetClockRate(I2C1, SPEED_100KHZ);
	Chip_I2C_SetMasterEventHandler(I2C1, Chip_I2C_EventHandler);

	NVIC_EnableIRQ(I2C1_IRQn);
}



#endif /* EEPROM_H_ */
