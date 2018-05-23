#include "infotronic.h"
#include "H-Botones.h"

void initHardware(void){

    SystemCoreClockUpdate();

    Board_Init();

	/* Initializes RGB LED */
	Chip_IOCON_PinMuxSet(LPC_IOCON, RGB_AZUL,MODE_GPIO);
	Chip_IOCON_PinMuxSet(LPC_IOCON, RGB_ROJO,MODE_GPIO);
	Chip_IOCON_PinMuxSet(LPC_IOCON, RGB_VERDE,MODE_GPIO);

	Chip_GPIO_WriteDirBit(LPC_GPIO, RGB_AZUL, SALIDA);
	Chip_GPIO_WriteDirBit(LPC_GPIO, RGB_ROJO, SALIDA);
	Chip_GPIO_WriteDirBit(LPC_GPIO, RGB_VERDE, SALIDA);

	Chip_GPIO_WritePortBit(LPC_GPIO, RGB_AZUL,OFF);
	Chip_GPIO_WritePortBit(LPC_GPIO, RGB_ROJO,OFF);
	Chip_GPIO_WritePortBit(LPC_GPIO, RGB_VERDE,OFF);

	/* Initializes buttons */

	Chip_IOCON_PinMuxSet(LPC_IOCON, BOTON_0,MODE_GPIO || IOCON_MODE_PULLUP);
	Chip_IOCON_PinMuxSet(LPC_IOCON, BOTON_1,MODE_GPIO || IOCON_MODE_PULLUP);
	Chip_IOCON_PinMuxSet(LPC_IOCON, BOTON_2,MODE_GPIO || IOCON_MODE_PULLUP);

	Chip_GPIO_WriteDirBit(LPC_GPIO, BOTON_0, ENTRADA);
	Chip_GPIO_WriteDirBit(LPC_GPIO, BOTON_1, ENTRADA);
	Chip_GPIO_WriteDirBit(LPC_GPIO, BOTON_2, ENTRADA);


    //Board_LED_Set(0, false);
}
