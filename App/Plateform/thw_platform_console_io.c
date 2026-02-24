/*
 * thw_platform_console_io.c
 *
 *  Created on: 24 févr. 2026
 *      Author: AurelienPajadon
 */

#include <string.h>
#include <TestHardwareCore/interfaces/thw_io_if.h>
#include "thw_platform_transport_uart.h"
#include "thw_platform_console_view.h"

static thw_transport_if_t* transport = NULL;

//------------------------------------------------------------------------------
/// \brief IO init (console + transport)
//------------------------------------------------------------------------------
static bool console_io_init(void)
{
    transport = thw_platform_transport_uart_getInterface();

	if(	transport == NULL ||
		transport->init == NULL ||
		transport->write == NULL ||
		transport->read == NULL ||
		transport->deinit == NULL ||
		transport->flush == NULL)
        return false;

    if (!transport->init())
        return false;

    thw_console_init(transport);

    return true;
}

//------------------------------------------------------------------------------
static void console_io_deinit(void)
{
    if (transport && transport->deinit)
        transport->deinit();
}

//------------------------------------------------------------------------------
static bool console_io_readLine(char* buffer, size_t maxLen)
{
    return thw_console_pollLine(buffer, maxLen);
}

//------------------------------------------------------------------------------
static void console_io_write(const char* text)
{
    if (transport)
        transport->write((const uint8_t*)text, strlen(text));
}

//------------------------------------------------------------------------------
/// \brief IO interface instance
//------------------------------------------------------------------------------
static thw_io_if_t console_io =
{
    .init     = console_io_init,
    .deinit   = console_io_deinit,
    .readLine = console_io_readLine,
    .write    = console_io_write
};

thw_io_if_t* thw_platform_console_io_getInterface(void)
{
    return &console_io;
}
