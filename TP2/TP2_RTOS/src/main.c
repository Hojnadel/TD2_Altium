/* Copyright 2015, Pablo Ridolfi
 * All rights reserved.
 *
 * This file is part of lpc1769_template.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** @brief Blinky using FreeRTOS.
 *
 *
 * NOTE: It's interesting to check behavior differences between standard and
 * tickless mode. Set @ref configUSE_TICKLESS_IDLE to 1, increment a counter
 * in @ref vApplicationTickHook and print the counter value every second
 * inside a task. In standard mode the counter will have a value around 1000.
 * In tickless mode, it will be around 25.
 *
 */

/** \addtogroup rtos_blink FreeRTOS blink example
 ** @{ */

/*==================[inclusions]=============================================*/

#include "board.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

#include "Infotronic.h"
#include "H-RGB.h"
#include "H-Botones.h"

#include "main.h"


uint8_t sentido = APAGADO;
uint8_t tecla = NO_KEY;
uint8_t contador = 0;


int main(void)
{
	initHardware();

	xTaskCreate(vTaskSecuenciaLed, (const char *)"Secuencia Led", configMINIMAL_STACK_SIZE*2, 0, tskIDLE_PRIORITY+1, 0);
	xTaskCreate(vTaskLeerTecla, (const char *)"Leer Tecla", configMINIMAL_STACK_SIZE*2, 0, tskIDLE_PRIORITY+1, 0);
	xTaskCreate(vTaskBotonera, (const char*) "Botonera", 40, 0, 1, 0);

	vTaskStartScheduler();

	while (1) {
	}
}


static void vTaskSecuenciaLed(void * a){

	static uint8_t cod_led=0;
	uint8_t sec;

	while (1) {
		sec = sentido;
		if (sec==ASCENDENTE){
			Apagar_Led();
			cod_led=(cod_led==BLANCO)?AZUL:cod_led+1;
			prender(cod_led);
		}
		else if(sec==DESCENDENTE){
			Apagar_Led();
			cod_led=(cod_led==AZUL || cod_led==APAGADO)?BLANCO:cod_led-1;
			prender(cod_led);

		}
		else if(sec == APAGADO)
			Apagar_Led();

		vTaskDelay(T_LED/portTICK_RATE_MS);
	}
}


static void vTaskLeerTecla(void){

	uint8_t estado = REPOSO, tecla_act = NO_KEY, tecla_ant = NO_KEY;

	while(1){
		tecla_act = NO_KEY;
		switch(estado){
			case REPOSO:	vTaskDelay(T_TECLADO/portTICK_RATE_MS);
							tecla_act = teclado_HW();
							if(tecla_act != NO_KEY){
								estado = DETECCION;
								tecla_ant = tecla_act;
							}
							break;

			case DETECCION:	vTaskDelay(T_DEBOUNCE/portTICK_RATE_MS);
							tecla_act = teclado_HW();
							if(tecla_act == tecla_ant){
								tecla = tecla_act;
								estado = REPOSO;
								contador++;
								tecla_act = NO_KEY;
							}
							else
								tecla_ant = tecla_act;
							break;

		}

	}
}


static void vTaskBotonera(void){

	while(1){
		switch(tecla){
			case BOT_ASC:
				sentido = ASCENDENTE;
				break;

			case BOT_DESC:
				sentido = DESCENDENTE;
				break;

			case BOT_OFF:
				sentido = APAGADO;
				break;

			case NO_KEY:
				break;
		}
	}
}

/** @} doxygen end group definition */

/*==================[end of file]============================================*/
