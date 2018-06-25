/*
 * display_init.h
 *
 *  Created on: 7 de nov. de 2016
 *      Author: agustin
 */

#ifndef DISPLAY_INIT_H_
#define DISPLAY_INIT_H_


#include "header.h"


#if (USE_DISPLAY)

	STATIC INLINE void TM_ILI9341_InitLCD(void)
	{
		Chip_GPIO_SetPinState(LPC_GPIO, REST,0);
		Chip_GPIO_SetPinState(LPC_GPIO, REST,1);

		TM_ILI9341_SendCommand(ILI9341_RESET);
		TM_ILI9341_Delay(2000000);

		TM_ILI9341_SendCommand(ILI9341_POWERA);
		TM_ILI9341_SendData(0x39);
		TM_ILI9341_SendData(0x2C);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0x34);
		TM_ILI9341_SendData(0x02);
		TM_ILI9341_SendCommand(ILI9341_POWERB);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0xC1);
		TM_ILI9341_SendData(0x30);
		TM_ILI9341_SendCommand(ILI9341_DTCA);
		TM_ILI9341_SendData(0x85);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0x78);
		TM_ILI9341_SendCommand(ILI9341_DTCB);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendCommand(ILI9341_POWER_SEQ);
		TM_ILI9341_SendData(0x64);
		TM_ILI9341_SendData(0x03);
		TM_ILI9341_SendData(0x12);
		TM_ILI9341_SendData(0x81);
		TM_ILI9341_SendCommand(ILI9341_PRC);
		TM_ILI9341_SendData(0x20);
		TM_ILI9341_SendCommand(ILI9341_POWER1);
		TM_ILI9341_SendData(0x23);
		TM_ILI9341_SendCommand(ILI9341_POWER2);
		TM_ILI9341_SendData(0x10);
		TM_ILI9341_SendCommand(ILI9341_VCOM1);
		TM_ILI9341_SendData(0x3E);
		TM_ILI9341_SendData(0x28);
		TM_ILI9341_SendCommand(ILI9341_VCOM2);
		TM_ILI9341_SendData(0x86);
		TM_ILI9341_SendCommand(ILI9341_MAC);
		TM_ILI9341_SendData(0x48);
		TM_ILI9341_SendCommand(ILI9341_PIXEL_FORMAT);
		TM_ILI9341_SendData(0x55);
		TM_ILI9341_SendCommand(ILI9341_FRC);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0x18);
		TM_ILI9341_SendCommand(ILI9341_DFC);
		TM_ILI9341_SendData(0x08);
		TM_ILI9341_SendData(0x82);
		TM_ILI9341_SendData(0x27);
		TM_ILI9341_SendCommand(ILI9341_3GAMMA_EN);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendCommand(ILI9341_COLUMN_ADDR);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0xEF);
		TM_ILI9341_SendCommand(ILI9341_PAGE_ADDR);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0x01);
		TM_ILI9341_SendData(0x3F);
		TM_ILI9341_SendCommand(ILI9341_GAMMA);
		TM_ILI9341_SendData(0x01);
		TM_ILI9341_SendCommand(ILI9341_PGAMMA);
		TM_ILI9341_SendData(0x0F);
		TM_ILI9341_SendData(0x31);
		TM_ILI9341_SendData(0x2B);
		TM_ILI9341_SendData(0x0C);
		TM_ILI9341_SendData(0x0E);
		TM_ILI9341_SendData(0x08);
		TM_ILI9341_SendData(0x4E);
		TM_ILI9341_SendData(0xF1);
		TM_ILI9341_SendData(0x37);
		TM_ILI9341_SendData(0x07);
		TM_ILI9341_SendData(0x10);
		TM_ILI9341_SendData(0x03);
		TM_ILI9341_SendData(0x0E);
		TM_ILI9341_SendData(0x09);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendCommand(ILI9341_NGAMMA);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0x0E);
		TM_ILI9341_SendData(0x14);
		TM_ILI9341_SendData(0x03);
		TM_ILI9341_SendData(0x11);
		TM_ILI9341_SendData(0x07);
		TM_ILI9341_SendData(0x31);
		TM_ILI9341_SendData(0xC1);
		TM_ILI9341_SendData(0x48);
		TM_ILI9341_SendData(0x08);
		TM_ILI9341_SendData(0x0F);
		TM_ILI9341_SendData(0x0C);
		TM_ILI9341_SendData(0x31);
		TM_ILI9341_SendData(0x36);
		TM_ILI9341_SendData(0x0F);
		TM_ILI9341_SendCommand(ILI9341_WCD);
		TM_ILI9341_SendData(0x2C);
		TM_ILI9341_SendCommand(0xC0);
		TM_ILI9341_SendData(0x09);
		TM_ILI9341_SendCommand(ILI9341_SLEEP_OUT);

		TM_ILI9341_Delay(1000000);

		TM_ILI9341_SendCommand(ILI9341_DISPLAY_ON);
		TM_ILI9341_SendCommand(ILI9341_GRAM);
	}

	STATIC INLINE void TM_ILI9341_Init(void)
	{
		// Inicializacion de los pines utilizados por la TFT
		Chip_IOCON_PinMux(LPC_IOCON, DB0, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB0);
		Chip_GPIO_SetPinState(LPC_GPIO, DB0,0);
		Chip_GPIO_SetPinState(LPC_GPIO, DB0,1);
		Chip_GPIO_SetPinState(LPC_GPIO, DB0,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB1, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB1);
		Chip_GPIO_SetPinState(LPC_GPIO, DB1,0);
		Chip_GPIO_SetPinState(LPC_GPIO, DB1,1);
		Chip_GPIO_SetPinState(LPC_GPIO, DB1,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB2, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB2);
		Chip_GPIO_SetPinState(LPC_GPIO, DB2,0);
		Chip_GPIO_SetPinState(LPC_GPIO, DB2,1);
		Chip_GPIO_SetPinState(LPC_GPIO, DB2,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB3, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB3);
		Chip_GPIO_SetPinState(LPC_GPIO, DB3,0);
		Chip_GPIO_SetPinState(LPC_GPIO, DB3,1);
		Chip_GPIO_SetPinState(LPC_GPIO, DB3,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB4, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB4);
		Chip_GPIO_SetPinState(LPC_GPIO, DB4,0);
		Chip_GPIO_SetPinState(LPC_GPIO, DB4,1);								// PISTA CORTADAAAA
		Chip_GPIO_SetPinState(LPC_GPIO, DB4,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB5, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB5);
		Chip_GPIO_SetPinState(LPC_GPIO, DB5,0);
		Chip_GPIO_SetPinState(LPC_GPIO, DB5,1);
		Chip_GPIO_SetPinState(LPC_GPIO, DB5,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB6, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB6);
		Chip_GPIO_SetPinState(LPC_GPIO, DB6,0);
		Chip_GPIO_SetPinState(LPC_GPIO, DB6,1);
		Chip_GPIO_SetPinState(LPC_GPIO, DB6,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB7, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB7);
		Chip_GPIO_SetPinState(LPC_GPIO, DB7,0);
		Chip_GPIO_SetPinState(LPC_GPIO, DB7,1);
		Chip_GPIO_SetPinState(LPC_GPIO, DB7,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB8, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB8);
		Chip_GPIO_SetPinState(LPC_GPIO, DB8,0);
		Chip_GPIO_SetPinState(LPC_GPIO, DB8,1);
		Chip_GPIO_SetPinState(LPC_GPIO, DB8,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB9, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB9);
		Chip_GPIO_SetPinState(LPC_GPIO, DB9,0);
		Chip_GPIO_SetPinState(LPC_GPIO, DB9,1);
		Chip_GPIO_SetPinState(LPC_GPIO, DB9,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB10, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB10);
		Chip_GPIO_SetPinState(LPC_GPIO, DB10,0);
		Chip_GPIO_SetPinState(LPC_GPIO, DB10,1);
		Chip_GPIO_SetPinState(LPC_GPIO, DB10,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB11, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB11);
		Chip_GPIO_SetPinState(LPC_GPIO, DB11,0);
		Chip_GPIO_SetPinState(LPC_GPIO, DB11,1);
		Chip_GPIO_SetPinState(LPC_GPIO, DB11,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB13, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB12);
		Chip_GPIO_SetPinState(LPC_GPIO,DB12,0);
		Chip_GPIO_SetPinState(LPC_GPIO,DB12,1);
		Chip_GPIO_SetPinState(LPC_GPIO,DB12,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB13, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB13);
		Chip_GPIO_SetPinState(LPC_GPIO, DB13,0);
		Chip_GPIO_SetPinState(LPC_GPIO, DB13,1);
		Chip_GPIO_SetPinState(LPC_GPIO, DB13,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB14, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB14);
		Chip_GPIO_SetPinState(LPC_GPIO, DB14,0);
		Chip_GPIO_SetPinState(LPC_GPIO, DB14,1);
		Chip_GPIO_SetPinState(LPC_GPIO, DB14,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB15, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB15);
		Chip_GPIO_SetPinState(LPC_GPIO, DB15,0);
		Chip_GPIO_SetPinState(LPC_GPIO, DB15,1);
		Chip_GPIO_SetPinState(LPC_GPIO, DB15,0);

		Chip_IOCON_PinMux(LPC_IOCON, CS, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, CS);
		Chip_GPIO_SetPinState(LPC_GPIO, CS,1);					// Activa en bajo
		Chip_GPIO_SetPinState(LPC_GPIO, CS,0);					// Activa en bajo
		Chip_GPIO_SetPinState(LPC_GPIO, CS,1);					// Activa en bajo

		Chip_IOCON_PinMux(LPC_IOCON, RS, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, RS);
		Chip_GPIO_SetPinState(LPC_GPIO, RS,0);
		Chip_GPIO_SetPinState(LPC_GPIO, RS,1);								// VER SOLDADURA, PIN OK
		Chip_GPIO_SetPinState(LPC_GPIO, RS,0);

		Chip_IOCON_PinMux(LPC_IOCON, WR, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, WR);
		Chip_GPIO_SetPinState(LPC_GPIO, WR,1);					// Activa en bajo
		Chip_GPIO_SetPinState(LPC_GPIO, WR,0);					// Activa en bajo
		Chip_GPIO_SetPinState(LPC_GPIO, WR,1);					// Activa en bajo

		Chip_IOCON_PinMux(LPC_IOCON, READ_DATA, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, READ_DATA);
		Chip_GPIO_SetPinState(LPC_GPIO, READ_DATA,1);			// Activa en bajo
		Chip_GPIO_SetPinState(LPC_GPIO, READ_DATA,0);			// Activa en bajo
		Chip_GPIO_SetPinState(LPC_GPIO, READ_DATA,1);			// Activa en bajo

		Chip_IOCON_PinMux(LPC_IOCON, REST, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, REST);
		Chip_GPIO_SetPinState(LPC_GPIO, REST,1);				// Activa en bajo
		Chip_GPIO_SetPinState(LPC_GPIO, REST,0);				// Activa en bajo
		Chip_GPIO_SetPinState(LPC_GPIO, REST,1);				// Activa en bajo

		// Envio de comandos de inicializacion
		TM_ILI9341_InitLCD();

		ILI9341_x = ILI9341_y = 0;
		ILI9341_Opts.width = ILI9341_WIDTH;
		ILI9341_Opts.height = ILI9341_HEIGHT;
		ILI9341_Opts.orientation = TM_ILI9341_Landscape;

		TM_ILI9341_Fill(ILI9341_COLOR_CYAN);
	}


	STATIC INLINE void welcome_screen(void)
	{
		//TM_ILI9341_Orientation peperota=TM_ILI9341_Landscape ;
			/* MODOS DE ORIENTACION (funcion TM_ILI9341_Rotate())
			 * 0: MAL
			 * 1: MAL
			 * 2: Vertical con pines arriba
			 * 3: Vertical con pines abajo
			 * 4: Apaisado con pines hacia la izquierda
			 * 5: Apaisado con pines hacia la derecha
			 */

		TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_2);
		TM_ILI9341_Fill(ILI9341_COLOR_CYAN);

		TM_ILI9341_Puts(10, 0, "Cargando...", &TM_Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_CYAN);

		TM_ILI9341_DrawFilledCircle(20, 50, 10, ILI9341_COLOR_YELLOW);
		TM_ILI9341_DrawFilledCircle(60, 50, 10, ILI9341_COLOR_ORANGE);
		TM_ILI9341_DrawFilledCircle(100, 50, 10, ILI9341_COLOR_RED);
		TM_ILI9341_DrawFilledCircle(140, 50, 10, ILI9341_COLOR_GREEN);
		TM_ILI9341_DrawFilledCircle(180, 50, 10, ILI9341_COLOR_BLUE);
		TM_ILI9341_DrawFilledCircle(220, 50, 10, ILI9341_COLOR_MAGENTA);
		TM_ILI9341_DrawFilledCircle(260, 50, 10, ILI9341_COLOR_GRAY);
		TM_ILI9341_DrawFilledCircle(300, 50, 10, ILI9341_COLOR_BROWN);
	}


#endif



#endif /* DISPLAY_INIT_H_ */
