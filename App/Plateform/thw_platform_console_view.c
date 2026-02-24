/*
 * thw_platform_console_view.c
 *
 *  Created on: 24 févr. 2026
 *      Author: AurelienPajadon
 */

#include "thw_platform_console_view.h"
#include "thw_transport_if.h"

#include <string.h>

#define CONSOLE_RX_BUF_SIZE 128

static thw_transport_if_t* transport = NULL;

static char lineBuffer[CONSOLE_RX_BUF_SIZE];
static size_t lineIndex = 0;

//------------------------------------------------------------------------------
/// \brief Initialize console view with transport
//------------------------------------------------------------------------------
void thw_console_init(thw_transport_if_t* t)
{
    transport = t;
    lineIndex = 0;
}

//------------------------------------------------------------------------------
/// \brief Poll and detect full line
/// \return true if a full line is ready
//------------------------------------------------------------------------------
bool thw_console_pollLine(char* outLine, size_t maxLen)
{
    if (transport == NULL)
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

            size_t copyLen = (lineIndex < maxLen - 1) ? lineIndex : maxLen - 1;

            memcpy(outLine, lineBuffer, copyLen);
            outLine[copyLen] = '\0';

            lineIndex = 0;
            return true;
        }

        if (lineIndex < CONSOLE_RX_BUF_SIZE - 1)
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
