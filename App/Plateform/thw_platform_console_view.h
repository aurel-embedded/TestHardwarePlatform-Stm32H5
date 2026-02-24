/*
 * thw_platform_console_view.h
 *
 *  Created on: 24 févr. 2026
 *      Author: AurelienPajadon
 */

#ifndef THW_PLATFORM_CONSOLE_VIEW_H
#define THW_PLATFORM_CONSOLE_VIEW_H

#include <stdbool.h>
#include <stddef.h>
#include "thw_transport_if.h"

void thw_console_init(thw_transport_if_t* t);
bool thw_console_pollLine(char* outLine, size_t maxLen);

#endif
