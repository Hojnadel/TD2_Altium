
/*
 * Titulo: TDII - TP2
 * Nombre: TP2_RTOS_v4
 * Descripcion: Secuencia de leds con control de sentido en RTOS
 * Autor: Grupo V
 * Fecha: Mayo 2018
 * Funcionamiento: El programa inicia con el LED apagado. Al presionar el botón SW2 de la Infotronic comienza a recorrer la secuencia
 * 		ascendente a una f=1hz. El botón SW3 es el que invierte la secuencia. Para prender el led por primera vez se pueden utilizar
 * 		cualquiera de los dos botones, cada uno con su respectiva secuencia. Cada vez que se presiona una botón de cambio de sentido (SW2,
 * 		SW3) el efecto se visualizará en el próximo tick, es decir, que no será instantáneo. El único botón que tiene efecto instantáneo
 * 		es el de stop (SW1).
*/

// Biblioteacas
#include "board.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

#include "Infotronic.h"
#include "H-RGB.h"
#include "H-Botones.h"

#include "main.h"

xSemaphoreHandle xSemBoton, xSemSecuencia;

xQueueHandle xQueueSecuencia, xQueueKey;


int main(void)
{
	initHardware();

	vSemaphoreCreateBinary(xSemBoton);				// Semaforo que sincroniza el evento de boton presionado con la decodificacion del boton
	vSemaphoreCreateBinary(xSemSecuencia);			// Semáforo que sincroniza la periodicidad del LED con cambios en la secuencia

	xQueueSecuencia = xQueueCreate(1, sizeof(uint8_t));		// Cola que actúa como buffer entre la decodif. del boton y la secuencia
	xQueueKey = xQueueCreate(1, sizeof(uint8_t));			// Cola que comunica la detección del botón con la decodificación

	xTaskCreate(vTaskSecuenciaLed, (const char *)"Secuencia Led", 128, 0, 1, NULL);
	xTaskCreate(vTaskLeerTecla, (const char *)"Leer Tecla", 128, 0, 1, NULL);
	xTaskCreate(vTaskBotonera, (const char*) "Botonera", 40, 0, 1, NULL);
	xTaskCreate(vTaskTemporizador, (const char*) "Temporizador", 40, (void *) 1000, 1, NULL);

	vTaskStartScheduler();

	while (1) {

	}
}

/* Name: vTaskTemporizador
 * Description: desbloquea a la tarea vTaskSecuencia() de manera periódica cada pvTimeParameter ms
 * Receive:
 * 		void* pvTimeParameter: tiempo que tarde en devolver el semáforo de manera periódica*/
static void vTaskTemporizador(void* pvTimeParameter){
	portTickType tiempo, xLastWakeTime;

	tiempo = (int) pvTimeParameter;
	xLastWakeTime = xTaskGetTickCount();

	while(1){
		xSemaphoreGive(xSemSecuencia);
		vTaskDelayUntil(&xLastWakeTime, tiempo/portTICK_RATE_MS);
	}
}

/* Name: vTaskSecuenciaLed
 * Description: prende el LED según la secuencia que corresponda
 * Receive: void
*/
static void vTaskSecuenciaLed(void){

	static uint8_t cod_led=0;
	uint8_t sec;

	while (1) {

		xSemaphoreTake(xSemSecuencia,portMAX_DELAY);
		xQueueReceive(xQueueSecuencia, &sec, 0);
		Apagar_Led();
		if (sec==ASCENDENTE){
			cod_led = (cod_led==BLANCO) ? AZUL : cod_led+1;
			prender(cod_led);
		}

		else if(sec==DESCENDENTE){
			Apagar_Led();
			cod_led=(cod_led==AZUL || cod_led==APAGADO) ? BLANCO : cod_led-1;
			prender(cod_led);
		}
	}
}


static void vTaskLeerTecla(void){

	uint8_t estado = REPOSO;
	uint8_t tecla_act = NO_KEY, tecla_ant = NO_KEY;
	uint8_t contador = 0;


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
								//tecla = tecla_act;
								xQueueOverwrite(xQueueKey, &tecla_act);
								estado = REPOSO;
								contador++;
								tecla_act = NO_KEY;
								xSemaphoreGive(xSemBoton);
							}
							else
								tecla_ant = tecla_act;
							break;

		}

	}
}


static void vTaskBotonera(void){

	uint8_t sentido = APAGADO, tecla=BOT_OFF;

	xSemaphoreTake(xSemBoton, portMAX_DELAY);

	while(1){
		xSemaphoreTake(xSemBoton, portMAX_DELAY);
		xQueueReceive(xQueueKey, &tecla, 0);
		switch(tecla){
			case BOT_ASC:
					sentido = ASCENDENTE;
					break;

			case BOT_DESC:
					sentido = DESCENDENTE;
					break;

			case BOT_OFF:
					sentido = APAGADO;
					xQueueOverwrite(xQueueSecuencia, &sentido);
					xSemaphoreGive(xSemSecuencia);
					break;

			case NO_KEY:
					break;
		}
		xQueueOverwrite(xQueueSecuencia, &sentido);

	}
}

