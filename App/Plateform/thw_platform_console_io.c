/*
 * thw_platform_console_io.c
 *
 *  Created on: 24 févr. 2026
 *      Author: AurelienPajadon
 */

/*
 * thw_platform_console_io.c
 */

#include "thw_platform_console_io.h"
#include "thw_platform_transport_uart.h"
#include "thw_transport_if.h"

#include <string.h>

#define CONSOLE_RX_BUF_SIZE 128

static thw_transport_if_t* transport = NULL;

static char   lineBuffer[CONSOLE_RX_BUF_SIZE];
static size_t lineIndex = 0;

//------------------------------------------------------------------------------
/// \brief IO init (transport + console state)
//------------------------------------------------------------------------------
static bool console_io_init(void)
{
    transport = thw_platform_transport_uart_getInterface();

    if (transport == NULL ||
        transport->init == NULL ||
        transport->deinit == NULL ||
        transport->write == NULL ||
        transport->read == NULL)
    {
        return false;
    }

    if (!transport->init())
        return false;

    lineIndex = 0;
    return true;
}

//------------------------------------------------------------------------------
static void console_io_deinit(void)
{
    if (transport && transport->deinit)
        transport->deinit();

    transport = NULL;
    lineIndex = 0;
}

//------------------------------------------------------------------------------
/// \brief Read a full line (echo enabled)
//------------------------------------------------------------------------------
static bool console_io_readLine(char* outLine, size_t maxLen)
{
    if (transport == NULL || outLine == NULL || maxLen < 2)
        return false;

    uint8_t byte;

    while (transport->read(&byte, 1) == 1)
    {
        // Echo
        transport->write(&byte, 1);

        if (byte == '\r' || byte == '\n')
        {
            if (lineIndex == 0)
                continue;

            size_t copyLen = (lineIndex < (maxLen - 1)) ? lineIndex : (maxLen - 1);

            memcpy(outLine, lineBuffer, copyLen);
            outLine[copyLen] = '\0';

            lineIndex = 0;
            return true;
        }

        if (lineIndex < (CONSOLE_RX_BUF_SIZE - 1))
        {
            lineBuffer[lineIndex++] = (char)byte;
        }
        else
        {
            // Overflow reset
            lineIndex = 0;
        }
    }

    return false;
}

//------------------------------------------------------------------------------
static void console_io_write(const char* text)
{
    if (transport == NULL || text == NULL)
        return;

    transport->write((const uint8_t*)text, strlen(text));
}

//------------------------------------------------------------------------------
static thw_io_if_t console_io =
{
    .init     = console_io_init,
    .deinit   = console_io_deinit,
    .readLine = console_io_readLine,
    .write    = console_io_write
};

//------------------------------------------------------------------------------
thw_io_if_t* thw_platform_console_io_getInterface(void)
{
    return &console_io;
}
