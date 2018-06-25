/*
 * adc_dac_init.h
 *
 *  Created on: 31 de oct. de 2016
 *      Author: agustin
 */


#ifndef ADC_DAC_INIT_H_
#define ADC_DAC_INIT_H_


#include "header.h"


#if (USE_DMA)
	STATIC INLINE void dma_init()
	{
		/* *** Caracteristicas del DMA:
		 * !!!!!!!!! EL DMA ES UNICAMENTE EN MODO BURST (NO MODO SINGLE) !!!!!!!!!
		 * Eight DMA channels. Each channel can support an unidirectional transfer.
		 * Memory-to-memory, memory-to-peripheral, and peripheral-to-memory transfers are supported.
		 * GPDMA supports the SSP, I2S, UART, A/D Converter, and D/A Converter peripherals.
		 * DMA can also be triggered by a timer match condition.
		 * Memory-to-memory transfers and transfers to or from GPIO are also supported.
		 * 32-bit AHB master bus width.
		 * Supports 8-bit, 16-bit, and 32-bit wide transactions.
		 * Internal four-word FIFO per channel.
		 * Programmable DMA burst size. The DMA burst size can be programmed to more efficiently transfer data.
		 * DMA can operate in Sleep mode. (Note that in Sleep mode the GPDMA cannot access the flash memory).
		 * Big-endian and little-endian support. The DMA Controller defaults to little-endian mode on reset.
		 * * Internally the DMA Controller treats all data as a stream of bytes instead of 16-bit or 32-bit
		 * * quantities. This means that when performing mixed-endian activity, where the endianness
		 * * of the source and destination are different, byte swapping of the data within the 32-bit data
		 * * bus is observed.
		 * AHB master interface is capable of dealing with all types of AHB transactions, including:
		 * * Split, retry, and error responses from slaves.
		 * * (If a peripheral performs a split or retry, the DMA Controller stalls and waits until the transaction can complete)
		 * * Locked transfers for source and destination of each stream.
		 * * Setting of protection bits for transfers on each stream.
		 * An interrupt to the processor can be generated on a DMA completion or when a DMA error has occurred.
		 * * [error] An error during a DMA transfer is flagged directly by the peripheral by asserting an Error
		 * * response on the AHB bus during the transfer. The DMA Controller automatically disables
		 * * the DMA stream after the current transfer has completed, and can optionally generate an
		 * * error interrupt to the CPU. This error interrupt can be masked.
		 * * [completion] A combined interrupt output is generated as an OR function of the individual interrupt
		 * * requests of the DMA Controller and is connected to the interrupt controller.
		 * DMA channel priority is fixed. DMA channel 0 has the highest priority and DMA channel 7
		 * * has the lowest priority.
		 * * If the DMA Controller is transferring data for the lower priority channel and then the higher
		 * * priority channel goes active, it completes the number of transfers delegated to the master
		 * * interface by the lower priority channel before switching over to transfer data for the higher
		 * * priority channel. Transfers delegated to the master interface are staged in the DMA
		 * * channel FIFO, so the amount of data that needs to transfer could be as large as a 4
		 * * words.
		 * * It is recommended that memory-to-memory transactions use the lowest priority channel.
		 * Registros:
		 * * DMACBREQ[15:0] — Burst request signals. These cause a programmed burst number of data to be transferred.
		 * * DMACSREQ[15:0] — Single transfer request signals. These cause a single data to be transferred. The DMA controller transfers a single transfer to or from the peripheral.
		 * * DMACLBREQ[15:0] — Last burst request signals.
		 * * DMACLSREQ[15:0] — Last single transfer request signals.
		 * * * Note that peripherals on this device do not support “last” request types, and many do not support both single and burst request types.
		 * * DMACCLR[15:0] — DMA clear or acknowledge signals. The DMACCLR signal is used by the DMA controller to acknowledge a DMA request from the peripheral.
		 * * DMACTC[15:0] — DMA terminal count signals. The DMACTC signal can be used by the DMA controller to indicate to the peripheral that the DMA transfer is complete.
		 */

		Chip_GPDMA_Init(LPC_GPDMA);

			// Setting GPDMA interrupt
		NVIC_DisableIRQ(DMA_IRQn);
		NVIC_SetPriority(DMA_IRQn, ((0x01<<3)|0x01));
		NVIC_EnableIRQ(DMA_IRQn);


		#if (USE_DAC_EXTERNO)
			// Pido un canal disponible al GPDMA para el DAC
			canal_dac = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, 0);

			#if (USE_BUFFER_SERIE)
				// Preparo el descriptor para el BUFFER_DAC
				Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_descriptor_DAC_BUFFER,
												(uint32_t) dma_memory_dac_BUFF, (uint32_t) GPDMA_CONN_I2S_Channel_0,
												DAC_DMA_CANT_MUESTRAS, GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA, NULL);
				DMA_descriptor_DAC_BUFFER.dst = GPDMA_CONN_I2S_Channel_0;
			#elif (USE_BUFFER_PARALELO)
				// Preparo el descriptor para el BUFFER_A
				Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_descriptor_DAC_BUFFER_A,
												(uint32_t) dma_memory_dac_BUFF_A, (uint32_t) GPDMA_CONN_I2S_Channel_0,
												DAC_DMA_CANT_MUESTRAS, GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA, NULL);
				DMA_descriptor_DAC_BUFFER_A.dst = GPDMA_CONN_I2S_Channel_0;

				// Preparo el descriptor para el BUFFER_B
				Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_descriptor_DAC_BUFFER_B,
												(uint32_t) dma_memory_dac_BUFF_B, (uint32_t) GPDMA_CONN_I2S_Channel_0,
												DAC_DMA_CANT_MUESTRAS, GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA, NULL);
				DMA_descriptor_DAC_BUFFER_B.dst = GPDMA_CONN_I2S_Channel_0;
			#endif
		#elif (USE_DAC_INTERNO)
			// Pido un canal disponible al GPDMA para el DAC
			canal_dac = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, 0);

			#if (USE_BUFFER_SERIE)
				// Preparo el descriptor para el BUFFER_DAC
				Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_descriptor_DAC_BUFFER,
												(uint32_t) dma_memory_dac_BUFF, (uint32_t) GPDMA_CONN_DAC,
												DAC_DMA_CANT_MUESTRAS, GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA, NULL);
				DMA_descriptor_DAC_BUFFER.dst = GPDMA_CONN_DAC;
			#elif (USE_BUFFER_PARALELO)
				// Preparo el descriptor para el BUFFER_A
				Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_descriptor_DAC_BUFFER_A,
												(uint32_t) dma_memory_dac_BUFF_A, (uint32_t) GPDMA_CONN_DAC,
												DAC_DMA_CANT_MUESTRAS, GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA, NULL);
				DMA_descriptor_DAC_BUFFER_A.dst = GPDMA_CONN_DAC;

				// Preparo el descriptor para el BUFFER_B
				Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_descriptor_DAC_BUFFER_B,
												(uint32_t) dma_memory_dac_BUFF_B, (uint32_t) GPDMA_CONN_DAC,
												DAC_DMA_CANT_MUESTRAS, GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA, NULL);
				DMA_descriptor_DAC_BUFFER_B.dst = GPDMA_CONN_DAC;
			#endif
		#endif

		#if (USE_ADC_EXTERNO)
			// Pido un canal disponible al GPDMA para el ADC
			canal_adc = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, 0);

			#if (USE_BUFFER_SERIE)
				// Preparo el descriptor para el BUFFER_ADC
				Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_descriptor_ADC_BUFFER,
												(uint32_t) GPDMA_CONN_I2S_Channel_1, (uint32_t) dma_memory_adc_BUFF,
												ADC_DMA_CANT_MUESTRAS, GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA, NULL);
				DMA_descriptor_ADC_BUFFER.src = GPDMA_CONN_I2S_Channel_1;

			#elif (USE_BUFFER_PARALELO)
				// Preparo el descriptor para el BUFFER_A
				Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_descriptor_ADC_BUFFER_A,
												(uint32_t) GPDMA_CONN_I2S_Channel_1, (uint32_t) dma_memory_adc_BUFF_A,
												ADC_DMA_CANT_MUESTRAS, GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA, NULL);
				DMA_descriptor_ADC_BUFFER_A.src = GPDMA_CONN_I2S_Channel_1;

				// Preparo el descriptor para el BUFFER_B
				Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_descriptor_ADC_BUFFER_B,
												(uint32_t) GPDMA_CONN_I2S_Channel_1, (uint32_t) dma_memory_adc_BUFF_B,
												ADC_DMA_CANT_MUESTRAS, GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA, NULL);
				DMA_descriptor_ADC_BUFFER_B.src = GPDMA_CONN_I2S_Channel_1;

				#if (!USE_RTOS)
					// Inicio la transmición del ADC -> MEMORY usando el BUFFER_A
					Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_adc,
											&DMA_descriptor_ADC_BUFFER_A,
											GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);

					// Inicio la transmición del MEMORY -> DAC usando el BUFFER_A
					Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_dac,
											&DMA_descriptor_DAC_BUFFER_A,
											GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA);
				#endif
			#endif
		#elif (USE_ADC_INTERNO)
			// Pido un canal disponible al GPDMA para el ADC
			canal_adc = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, 0);

			#if (USE_BUFFER_SERIE)
				// Preparo el descriptor para el BUFFER_DAC
				Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_descriptor_ADC_BUFFER,
												(uint32_t) GPDMA_CONN_ADC, (uint32_t) dma_memory_adc_BUFF,
												ADC_DMA_CANT_MUESTRAS, GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA, NULL);
				DMA_descriptor_ADC_BUFFER.src = GPDMA_CONN_ADC;

				// Inicio la transmición del ADC -> MEMORY usando el BUFFER_A
				Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_adc,
										&DMA_descriptor_ADC_BUFFER,
										GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
			#elif (USE_BUFFER_PARALELO)
				// Preparo el descriptor para el BUFFER_A
				Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_descriptor_ADC_BUFFER_A,
												(uint32_t) GPDMA_CONN_ADC, (uint32_t) dma_memory_adc_BUFF_A,
												ADC_DMA_CANT_MUESTRAS, GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA, NULL);
				DMA_descriptor_ADC_BUFFER_A.src = GPDMA_CONN_ADC;

				// Preparo el descriptor para el BUFFER_B
				Chip_GPDMA_PrepareDescriptor(LPC_GPDMA, &DMA_descriptor_ADC_BUFFER_B,
												(uint32_t) GPDMA_CONN_ADC, (uint32_t) dma_memory_adc_BUFF_B,
												ADC_DMA_CANT_MUESTRAS, GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA, NULL);
				DMA_descriptor_ADC_BUFFER_B.src = GPDMA_CONN_ADC;

				Chip_GPDMA_SGTransfer(LPC_GPDMA, canal_adc,
										&DMA_descriptor_ADC_BUFFER_A,
										GPDMA_TRANSFERTYPE_P2M_CONTROLLER_DMA);
			#endif
		#endif


				for(int i = 0; i<ADC_DMA_CANT_MUESTRAS; i++)
				{
					dma_memory_adc_BUFF[i] = 9999;
				}
	}
#endif


#if (USE_ADC_EXTERNO)||(USE_DAC_EXTERNO)
	/* Get divider value */
	STATIC Status getClkDiv(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *format, uint16_t *pxDiv, uint16_t *pyDiv, uint32_t *pN)
	{
		uint32_t pClk;
		uint32_t x, y;
		uint64_t divider;
		uint16_t dif;
		uint16_t xDiv = 0, yDiv = 0;
		uint32_t N;
		uint16_t err, ErrorOptimal = 0xFFFF;

	#if defined(CHIP_LPC175X_6X)
		pClk = Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_I2S);
	#else
		pClk = Chip_Clock_GetPeripheralClockRate();
	#endif

		/* divider is a fixed point number with 16 fractional bits */
		divider = (((uint64_t) (format->SampleRate) * 2 * (format->WordWidth) * 2) << 16) / pClk;
		/* find N that make x/y <= 1 -> divider <= 2^16 */
		for (N = 64; N > 0; N--) {
			if ((divider * N) < (1 << 16)) {
				break;
			}
		}
		if (N == 0) {
			return ERROR;
		}
		divider *= N;
		for (y = 255; y > 0; y--) {
			x = y * divider;
			if (x & (0xFF000000)) {
				continue;
			}
			dif = x & 0xFFFF;
			if (dif > 0x8000) {
				err = 0x10000 - dif;
			}
			else {
				err = dif;
			}
			if (err == 0) {
				yDiv = y;
				break;
			}
			else if (err < ErrorOptimal) {
				ErrorOptimal = err;
				yDiv = y;
			}
		}
		xDiv = ((uint64_t) yDiv * (format->SampleRate) * 2 * (format->WordWidth) * N * 2) / pClk;
		if (xDiv >= 256) {
			xDiv = 0xFF;
		}
		if (xDiv == 0) {
			xDiv = 1;
		}

		*pxDiv = xDiv;
		*pyDiv = yDiv;
		*pN = N;
		return SUCCESS;
	}


	/* Configure I2S for Audio Format input */
	STATIC INLINE Status mi_Chip_I2S_TxConfig(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *format)
	{
		uint32_t temp;
		uint16_t xDiv, yDiv;
		uint32_t N;


		if (getClkDiv(pI2S, format, &xDiv, &yDiv, &N) == ERROR)
		{
			return ERROR;
		}

		temp = pI2S->DAO & (~(I2S_DAO_WORDWIDTH_MASK | I2S_DAO_MONO | I2S_DAO_SLAVE | I2S_DAO_WS_HALFPERIOD_MASK));
		if (format->WordWidth <= 8)
		{
			temp |= I2S_WORDWIDTH_8;
		}
		else if (format->WordWidth <= 16)
		{
			temp |= I2S_WORDWIDTH_16;
		}
		else
		{
			temp |= I2S_WORDWIDTH_32;
		}

		temp |= (format->ChannelNumber) == 1 ? I2S_MONO : I2S_STEREO;
		temp |= I2S_MASTER_MODE;
		temp |= I2S_DAO_WS_HALFPERIOD(format->WordWidth - 1);
		pI2S->DAO = temp;

		pI2S->TXMODE = 0x8;

		Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_I2S);

		xDiv = 32;
		yDiv = 125;

		pI2S->TXBITRATE = 5;

		pI2S->TXRATE = yDiv | (xDiv << 8);
		return SUCCESS;
	}


	/* Configure I2S for Audio Format input */
	STATIC INLINE Status mi_Chip_I2S_RxConfig(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *format)
	{
		uint32_t temp;
		uint16_t xDiv, yDiv;
		uint32_t N;

		if (getClkDiv(pI2S, format, &xDiv, &yDiv, &N) == ERROR) {
			return ERROR;
		}
		temp = pI2S->DAI & (~(I2S_DAI_WORDWIDTH_MASK | I2S_DAI_MONO | I2S_DAI_SLAVE | I2S_DAI_WS_HALFPERIOD_MASK));
		if (format->WordWidth <= 8)
		{
			temp |= I2S_WORDWIDTH_8;
		}
		else if (format->WordWidth <= 16)
		{
			temp |= I2S_WORDWIDTH_16;
		}
		else
		{
			temp |= I2S_WORDWIDTH_32;
		}

		temp |= (format->ChannelNumber) == 1 ? I2S_MONO : I2S_STEREO;
		temp |= I2S_MASTER_MODE;
		temp |= I2S_DAI_WS_HALFPERIOD(format->WordWidth - 1);
		pI2S->DAI = temp;

		pI2S->RXMODE = 0x8;

		Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_I2S);

		xDiv = 32;
		yDiv = 125;

		pI2S->RXBITRATE = 5;

		pI2S->RXRATE = yDiv | (xDiv << 8);
		return SUCCESS;
	}

	STATIC INLINE void i2s_init()
	{
		static char init_flag = 0;

		if(!init_flag)
		{
			// Configuro los pines de RX de P0, ver defines
			Chip_IOCON_PinMux(LPC_IOCON, I2SRX_CLK, MD_PLN, IOCON_FUNC1);
			Chip_IOCON_PinMux(LPC_IOCON, I2SRX_SDA, MD_PLN, IOCON_FUNC1);
			Chip_IOCON_PinMux(LPC_IOCON, I2SRX_WS, MD_PLN, IOCON_FUNC1);
			Chip_IOCON_PinMux(LPC_IOCON, RX_MCLK, MD_PLN, IOCON_FUNC1);

			// Configuro los pines del TX de P0, ver defines
			Chip_IOCON_PinMux(LPC_IOCON, I2STX_CLK, MD_PLN, IOCON_FUNC1);
			Chip_IOCON_PinMux(LPC_IOCON, I2STX_SDA, MD_PLN, IOCON_FUNC1);
			Chip_IOCON_PinMux(LPC_IOCON, I2STX_WS, MD_PLN, IOCON_FUNC1);
			Chip_IOCON_PinMux(LPC_IOCON, TX_MCLK, MD_PLN, IOCON_FUNC1);

			// Configuro los pines GPIO del ADC
//			Chip_IOCON_PinMux(LPC_IOCON, ADC_OSR, MD_PLN, IOCON_FUNC0);
//			Chip_GPIO_SetPinDIROutput(LPC_GPIO, ADC_OSR);
//			Chip_GPIO_SetPinState(LPC_GPIO, ADC_OSR, OFF);
//			Chip_IOCON_PinMux(LPC_IOCON, ADC_FSYNC, MD_PLN, IOCON_FUNC0);
//			Chip_GPIO_SetPinDIROutput(LPC_GPIO, ADC_FSYNC);
//			Chip_GPIO_SetPinState(LPC_GPIO, ADC_FSYNC, ON);

			// Configuro los pines GPIO del DAC
			Chip_IOCON_PinMux(LPC_IOCON, DAC_MUTE, MD_PLN, IOCON_FUNC0);
			Chip_GPIO_SetPinDIROutput(LPC_GPIO, DAC_MUTE);
			Chip_GPIO_SetPinState(LPC_GPIO, DAC_MUTE, OFF);
			Chip_IOCON_PinMux(LPC_IOCON, DAC_ZEROA, MD_PLN, IOCON_FUNC0);
			Chip_GPIO_SetPinDIRInput(LPC_GPIO, DAC_ZEROA);

			// Configuro I2S_TX usando la estructura I2S_AUDIO_FORMAT_T y modifico la función
			I2S_AUDIO_FORMAT_T audio_Confg;
			audio_Confg.SampleRate = ADC_FREQ;
			audio_Confg.ChannelNumber = 2;			// 1 mono 2 stereo
			audio_Confg.WordWidth = 32;				// Word Len

			// Configuro el clk del periférico para que trabaje a 96MHz
			Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_I2S, SYSCTL_CLKDIV_1);

			Chip_I2S_Init(LPC_I2S);

			Chip_I2S_RxStop(LPC_I2S);
			Chip_I2S_TxStop(LPC_I2S);
			Chip_I2S_EnableMute(LPC_I2S);


			Chip_I2S_DisableMute(LPC_I2S);
			Chip_I2S_RxStart(LPC_I2S);
			Chip_I2S_TxStart(LPC_I2S);

			Chip_I2S_Int_RxCmd(LPC_I2S, ENABLE, 1);
			Chip_I2S_Int_TxCmd(LPC_I2S, ENABLE, 1);

			// Configuro modo RX
			mi_Chip_I2S_RxConfig(LPC_I2S, &audio_Confg);
			// Configuro modo TX
			mi_Chip_I2S_TxConfig(LPC_I2S, &audio_Confg);

			#if USE_DMA
				Chip_I2S_DMA_RxCmd(LPC_I2S, I2S_DMA_REQUEST_CHANNEL_1, ENABLE, 1);
				Chip_I2S_DMA_TxCmd(LPC_I2S, I2S_DMA_REQUEST_CHANNEL_2, ENABLE, 1);

				NVIC_DisableIRQ(I2S_IRQn);
			#else

				NVIC_EnableIRQ(I2S_IRQn);
			#endif


			init_flag = 1;
		}
	}
#endif


#if (USE_ADC_INTERNO)
	STATIC INLINE void adc_init()
	{
		Chip_IOCON_PinMux (LPC_IOCON, 0, 23, MD_PLN, IOCON_FUNC1 ); // P0[23] -> AD0.0 (entrada de ADC)

		ADC_CLOCK_SETUP_T adc;

		Chip_ADC_Init(LPC_ADC, &adc);
		NVIC_DisableIRQ(ADC_IRQn);
		Chip_ADC_EnableChannel(LPC_ADC, ADC_CH0, ENABLE);
		Chip_ADC_SetSampleRate(LPC_ADC, &adc, ADC_FREQ);
		Chip_ADC_Int_SetChannelCmd(LPC_ADC, ADC_CH0, ENABLE);
		Chip_ADC_SetBurstCmd(LPC_ADC, ENABLE);
		//Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING); // cuando NO es modo Burst
	}
#endif


#if (USE_DAC_INTERNO)
	STATIC INLINE void dac_init()
	{
		#if DEBUG_MODE
//		printf("[info] Init DAC \r\n");
//		printf("\t DAC freq %d \r\n", DAC_FREQ);
//		printf("\t DMA buff size %d \r\n", DAC_DMA_CANT_MUESTRAS);
		#endif

		Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_DAC, SYSCTL_CLKDIV_4);

		Chip_IOCON_PinMux (LPC_IOCON, AOUT, MD_PLN, IOCON_FUNC2 ); // P0[26] -> AOUT (salida de DAC)

		Chip_DAC_Init(LPC_DAC);

			//	Bias == 0 => 	f_max = 1 MHz, 		I_max = 700 uA
			//	Bias == 1 => 	f_max = 400 kHz, 	I_max = 350 uA
		Chip_DAC_SetBias(LPC_DAC, 1);

		Chip_DAC_SetDMATimeOut(LPC_DAC, (SystemCoreClock/4) / (DAC_FREQ * DAC_DMA_CANT_MUESTRAS) ); // Se configura el TimeOut.

		Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_DBLBUF_ENA | DAC_CNT_ENA | DAC_DMA_ENA); // Se habilita el DMA y soporte de cuenta.

	}
#endif




#endif /* ADC_DAC_INIT_H_ */



