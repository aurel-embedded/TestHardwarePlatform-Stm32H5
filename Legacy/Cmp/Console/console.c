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

//-----------------------------------------------------------------------------
// Mutex
//-----------------------------------------------------------------------------
const osMutexAttr_t console_mtx_attr = {
	"console_mtx",                          // human readable mutex name
	osMutexRecursive | osMutexPrioInherit,	// attr_bits
	NULL,                                   // memory for control block
	0U                                      // size for control block
};
osMutexId_t console_mtx_id;

static char console_fmtBuf[256];

#ifdef MODE_THW
volatile uint8_t console_rxBuffer[CONSOLE_RX_BUF_SIZE + 1];
volatile uint8_t rx_char = 0;
#endif //MODE_THW

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//								LOCAL FUNCTION
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/******************************************************************************
 ** Function name:		console_lock()
 ** Descriptions:		Lock le mutex de l'affichage DBG
 ******************************************************************************/
static void console_lock(void)
{
	if(osKernelGetState() == osKernelRunning){
		if(console_mtx_id != NULL){
			osMutexAcquire(console_mtx_id, osWaitForever);
		}
	}
}
/******************************************************************************
 ** Function name:		console_unlock()
 ** Descriptions:		Unlock le mutex de l'affichage DBG
 ******************************************************************************/
static void console_unlock(void)
{
	if(osKernelGetState() == osKernelRunning){
		if(console_mtx_id != NULL){
			osMutexRelease(console_mtx_id);
		}
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//								EXTERNAL FUNCTION
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/******************************************************************************
 ** Function name:		console_init
 ** Descriptions:		UART component Init
 ******************************************************************************/
HAL_StatusTypeDef console_init(void)
{
	console_uartHdl.Instance            = CONSOLE_UART_INSTANCE;
	console_uartHdl.Init.BaudRate       = (115200 * 4);
	console_uartHdl.Init.WordLength     = UART_WORDLENGTH_8B;
	console_uartHdl.Init.StopBits       = UART_STOPBITS_1;
	console_uartHdl.Init.Parity         = UART_PARITY_NONE;
	console_uartHdl.Init.Mode           = UART_MODE_TX_RX;
	console_uartHdl.Init.HwFlowCtl      = UART_HWCONTROL_NONE;
	console_uartHdl.Init.OverSampling   = UART_OVERSAMPLING_16;

	if(HAL_UART_Init(&console_uartHdl) != HAL_OK)
	{
		/* Initialization Error */
		return HAL_ERROR;
	}

	// Create Mutex
	console_mtx_id = osMutexNew(&console_mtx_attr);
	if (console_mtx_id == NULL)  {
		return HAL_ERROR;
	}

	return HAL_OK;
}

/******************************************************************************
 ** Function name:		console_deinit
 ** Descriptions:		UART component deinit
 ******************************************************************************/
HAL_StatusTypeDef console_deinit(void)
{
	// Create Mutex
	if (console_mtx_id != NULL)  {
		osMutexDelete(console_mtx_id);
	}

	HAL_UART_DeInit(&console_uartHdl);

	return HAL_OK;
}


/******************************************************************************
 ** Function name:		console_printf()
 ** Descriptions:		Envoi asysnchrone sur la console d'affichage DBG
 ******************************************************************************/
HAL_StatusTypeDef console_printf(const char *fmt, ...)
{
	va_list argp;
	int len;

	console_lock();
	va_start(argp, fmt);

	// build string
	if(vsnprintf(console_fmtBuf, sizeof(console_fmtBuf), fmt, argp) >= 0){
		len = strlen((char*)console_fmtBuf);
		HAL_UART_Transmit(&console_uartHdl, (uint8_t*)console_fmtBuf, len, 1000);
	}
	va_end(argp);
	console_unlock();
	return HAL_OK;
}

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
