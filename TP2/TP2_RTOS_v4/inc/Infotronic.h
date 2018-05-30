#ifndef KIT_INFO2_H_
#define KIT_INFO2_H_

#include "stdint.h"
#include "board.h"


#define 	ON		1
#define 	OFF		0

#define		P0		0
#define		P1		1
#define		P2		2
#define		P3		3
#define		P4		4

#define 	MODE_GPIO	0
#define		ENTRADA	0
#define		SALIDA	1



//LUCES
#define 	LUZ_ROJA		1
#define		LUZ_AMARILLA	2
#define		LUZ_VERDE		3

//PERIODOS
#define		PERIODO1S		1000
#define		PERIODO500MS	500


//Tiempos
#define		T_R		2000
#define		T_A		2000
#define		T_V		15000

//Rele
#define		RELE0		P2,0
#define		RELE1		P0,23
#define		RELE2		P0,21
#define		RELE3		P0,27

//Buzzer
#define		BUZZER		P0,28


//RGB
#define		RGB_AZUL		2,1			//GPIO2
#define		RGB_ROJO		2,3			//GPIO2
#define		RGB_VERDE		2,2			//GPIO2


//MACROS para prender y apagar luces
#define LUZ_ROJA_ON 		Chip_GPIO_WritePortBit(LPC_GPIO, RGB_ROJO, ON)
#define LUZ_ROJA_OFF 		Chip_GPIO_WritePortBit(LPC_GPIO, RGB_ROJO, OFF)
#define LUZ_VERDE_ON	 	Chip_GPIO_WritePortBit(LPC_GPIO, RGB_VERDE, ON)
#define LUZ_VERDE_OFF 		Chip_GPIO_WritePortBit(LPC_GPIO, RGB_VERDE, OFF)
#define LUZ_AZUL_ON	 		Chip_GPIO_WritePortBit(LPC_GPIO, RGB_AZUL, ON)
#define LUZ_AZUL_OFF 		Chip_GPIO_WritePortBit(LPC_GPIO, RGB_AZUL, OFF)

#define APAGAR_AZUL			Chip_GPIO_WritePortBit(LPC_GPIO, RGB_AZUL, OFF)
#define APAGAR_VERDE		Chip_GPIO_WritePortBit(LPC_GPIO, RGB_VERDE,OFF)
#define APAGAR_ROJO			Chip_GPIO_WritePortBit(LPC_GPIO, RGB_ROJO, OFF)




void Inic_RGB(void);
void prender(uint8_t );
void apagar (uint8_t );
void Apagar_Led(void);




#endif /* KIT_INFO2_H_ */
