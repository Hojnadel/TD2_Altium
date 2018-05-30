#include "Infotronic.h"
#include "H-RGB.h"
#include "H-Botones.h"


void Apagar_Led(void){
	APAGAR_AZUL;
	APAGAR_VERDE;
	APAGAR_ROJO;
}

void prender(uint8_t color){

	switch(color){
		case ROJO:		LUZ_ROJA_ON; break;
		case VERDE:		LUZ_VERDE_ON; break;
		case AMARILLO:	LUZ_VERDE_ON; LUZ_ROJA_ON; break;
		case BLANCO:	LUZ_ROJA_ON; LUZ_VERDE_ON; LUZ_AZUL_ON; break;
		case AZUL:		LUZ_AZUL_ON; break;
		case CIAN:		LUZ_AZUL_ON; LUZ_VERDE_ON; break;
		case VIOLETA:	LUZ_ROJA_ON; LUZ_AZUL_ON; break;
	}
}

uint8_t teclado_HW(void){
	if(!Chip_GPIO_ReadPortBit(LPC_GPIO,BOTON_0)) return BOT_OFF;
	if(!Chip_GPIO_ReadPortBit(LPC_GPIO,BOTON_1)) return BOT_ASC;
	if(!Chip_GPIO_ReadPortBit(LPC_GPIO,BOTON_2)) return BOT_DESC;
	return NO_KEY;
}

