/*
 * thw_platform_transport_uart.c
 *
 *  Created on: 24 févr. 2026
 *      Author: AurelienPajadon
 */

#include "stm32h5xx_hal.h"
#include "thw_transport_if.h"

#define TRANSPORT_UART_INSTANCE USART1

static UART_HandleTypeDef uartHdl;

//------------------------------------------------------------------------------
/// \brief Initialize UART transport
//------------------------------------------------------------------------------
static bool uart_init(void)
{
    uartHdl.Instance            = TRANSPORT_UART_INSTANCE;
    uartHdl.Init.BaudRate       = 115200 * 4;
    uartHdl.Init.WordLength     = UART_WORDLENGTH_8B;
    uartHdl.Init.StopBits       = UART_STOPBITS_1;
    uartHdl.Init.Parity         = UART_PARITY_NONE;
    uartHdl.Init.Mode           = UART_MODE_TX_RX;
    uartHdl.Init.HwFlowCtl      = UART_HWCONTROL_NONE;
    uartHdl.Init.OverSampling   = UART_OVERSAMPLING_16;

    return (HAL_UART_Init(&uartHdl) == HAL_OK);
}

//------------------------------------------------------------------------------
/// \brief Deinitialize UART transport
//------------------------------------------------------------------------------
static bool uart_deinit(void)
{
    if(HAL_UART_DeInit(&uartHdl) != HAL_OK)
	{
    	return false;
	}
	return true;
}

//------------------------------------------------------------------------------
/// \brief Blocking write
//------------------------------------------------------------------------------
static bool uart_write(const uint8_t* data, size_t len)
{
    return (HAL_UART_Transmit(&uartHdl,
                              (uint8_t*)data,
                              len,
                              HAL_MAX_DELAY) == HAL_OK);
}

//------------------------------------------------------------------------------
/// \brief Non-blocking read
/// \return number of bytes read
//------------------------------------------------------------------------------
static size_t uart_read(uint8_t* buffer, size_t maxLen)
{
    size_t count = 0;

    while (count < maxLen)
    {
        if (HAL_UART_Receive(&uartHdl,
                             &buffer[count],
                             1,
                             0) != HAL_OK)
        {
            break;  // No more data
        }
        count++;
    }

    return count;
}

//------------------------------------------------------------------------------
/// \brief Optional flush (not used yet)
//------------------------------------------------------------------------------
static void uart_flush(void)
{
    // Nothing for now
}

//------------------------------------------------------------------------------
/// \brief UART transport interface instance
//------------------------------------------------------------------------------
static thw_transport_if_t thw_transport_uart =
{
    .init   = uart_init,
    .deinit = uart_deinit,
    .write  = uart_write,
    .read   = uart_read,
    .flush  = uart_flush
};

//------------------------------------------------------------------------------
/// \brief Get UART transport interface
//------------------------------------------------------------------------------
thw_transport_if_t* thw_platform_transport_uart_getInterface(void)
{
    return &thw_transport_uart;
}
