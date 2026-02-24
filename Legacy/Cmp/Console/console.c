/*
 * console.c
 *
 *  Created on: 27 janv. 2026
 *      Author: mionnem
 */


#include "console.h"
#include <cmsis_os2.h>
#include <stdio.h>
#include <string.h>
#include <Config/console_config.h>

UART_HandleTypeDef console_uartHdl;


#ifdef MODE_THW
volatile uint8_t console_rxBuffer[CONSOLE_RX_BUF_SIZE + 1];
volatile uint8_t rx_char = 0;
#endif //MODE_THW


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//								EXTERNAL FUNCTION
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


#ifdef MODE_THW


//-----------------------------------------------------------------------------
/**
 * @brief Lit une trame reçue de la console via UART.
 * @param frame pointeur sur la trame lu.
 * @return 1: trame disponible; 0: timeout
 */
//-----------------------------------------------------------------------------
bool console_manageRx(void)
{
	bool lineReceived = false;
	static int rx_index = 0;
	static char rx_buffer[CONSOLE_RX_BUF_SIZE];   // Local holding buffer to

	if (HAL_UART_Receive(&console_uartHdl, (uint8_t*)&rx_char, 1, 1) == HAL_OK)
	{
		HAL_UART_Transmit(&console_uartHdl, (uint8_t*)&rx_char, 1, 5); // Send it back for Screen Display
		if ((rx_char == '\r') || (rx_char == '\n')) // Is this an end-of-line condition, either will suffice?
		{
			if (rx_index != 0) // Line has some content
			{
				memcpy((void *)console_rxBuffer, rx_buffer, rx_index); // Copy to static line buffer from dynamic receive buffer
				console_rxBuffer[rx_index] = 0; // Add terminating NUL
				rx_index = 0; // Reset content pointer
				lineReceived = true; // flag new line valid for processing
			}
		}
		else
		{
			if (rx_index == CONSOLE_RX_BUF_SIZE) // If resync or overflows pull back to start
				rx_index = 0;

			rx_buffer[rx_index++] = rx_char; // Copy to buffer and increment
		}
	}
	return lineReceived;
}


#endif //MODE_THW
