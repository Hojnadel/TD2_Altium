/*
 * eqh.h
 *
 *  Created on: 31 de oct. de 2016
 *      Author: agustin
 */

#ifndef HEADER_H_
#define HEADER_H_


	#include "cr_dsplib.h"
	#include "config.h"
	#include "fft_header.h"
	#include "ff.h"
	#include "adc_dac_header.h"
	#include "gpio_header.h"
	#include "task_header.h"
	#include "display_header.h"
	#include "efectos_header.h"
	#include "sd_header.h"
	#include "board.h"
	#include "eeprom.h"



// ********* FUNCIONES ********** //
	void main_while();
// ****************************** //

	/* *** MEMORIA *** //
	 *  MFlash512  (xr-) : 	ADDR = 0x0000 0000 -> 0x0007 FFFF,	LENGTH = 0x0008 0000 (512K bytes)
	 *  RamLoc32   (xrw) : 	ADDR = 0x1000 0000 -> 0x1000 7FFF,	LENGTH = 0x0000 8000 (32K bytes)
	 *  Boot ROM   (x--) :	ADDR = 0x1FFF 0000 -> 0x1FFF 1FFF,	LENGTH = 0x0000 2000 (8K bytes)  - 8 kB Boot ROM with flash services.
	 *  RamAHB32_0 (xrw) : 	ADDR = 0x2007 C000 -> 0x2007 FFFF, 	LENGTH = 0x0000 4000 (16K bytes) - AHB SRAM - bank 0
	 *  RamAHB32_1 (xrw) : 	ADDR = 0x2008 0000 -> 0x2008 3FFF, 	LENGTH = 0x0000 4000 (16K bytes) - AHB SRAM - bank 1
	 *
	 *  The LPC1769 contains 64 kB of on-chip static RAM (SRAM) memory. 32 kB of
	 *  SRAM, accessible by the CPU and all three DMA controllers are on a higher-speed bus.
	 *  The LPC1769 have two additional 16 kB SRAM blocks, each
	 *  situated on separate slave ports on the AHB multilayer matrix.
	 *
	 *
	 * *** REGIONES DE MEMORIA *** //
	 * text - shows the code and read-only data in your application (in decimal)
	 * data - shows the read-write data in your application (in decimal)
	 * bss - show the zero initialized ('bss' and 'common') data in your application (in decimal)
	 * dec - total of 'text' + 'data' + 'bss' (in decimal)
	 * hex - hexidecimal equivalent of 'dec'
	 *
	 * .text 			= 	MFlash512
	 * .data.$RAM2		= 	RamLoc32 (NO inicializa)
	 * .bss.$RAM2		= 	RamLoc32 (inicializa en 0)
	 * .data.$RamAHB32	=	RamAHB32 (NO inicializa)
	 * .bss.$RamAHB32	=	RamAHB32 (inicializa en 0)
	 *
	 *
	 * *** NOTAS *** //
	 * the flash consumption of your application will then be (text)
	 * the RAM consumption of your application will then be (data + bss)
	 *
	 * Ejemplo para especificar la seccion de memoria a utilizar para una variable
	 * int variable[1024] __attribute__ ((section (".bss.$RamAHB32")));
	 *
	 * las variables 'const' se guardan en la 'RamLoc32' por default
	 *
	 *
	 * en:
	 * C/C++ Build -> settings -> Tool Settings -> Miscellaneous
	 * agregar:
	 * -print-memory-usage
	 *
	 * en:
	 * C/C++ Build -> settings -> Build steps -> Post-build steps -> Command
	 * agregar:
	 * arm-none-eabi-nm -S --size-sort -s "${BuildArtifactFileName}"
	 */

#endif /* HEADER_H_ */


