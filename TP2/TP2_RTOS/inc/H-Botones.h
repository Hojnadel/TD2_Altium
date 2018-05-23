#ifndef _H_BOTONES_H
#define _H_BOTONES_H

#define		APAGADO		0
#define		ASCENDENTE	1
#define		DESCENDENTE	2

#define		NO_KEY		0xFF

#define 	T_TECLADO	50
#define 	T_DEBOUNCE	100


#define		BOTON_0		2,10
#define		BOTON_1		0,18
#define		BOTON_2		0,11

#define		BOT_OFF		0
#define		BOT_ASC		1
#define		BOT_DESC	2

#define		REPOSO		0
#define		DETECCION	1

void Inic_botones(void);
uint8_t teclado_HW(void);
void teclado_SW(uint8_t);
void maquina_botones (uint8_t );



#endif
