/*
 * console.h
 *
 *  Created on: 27 janv. 2026
 *      Author: mionnem
 */

#ifndef DRIVERS_CONSOLE_H_
#define DRIVERS_CONSOLE_H_

#include <stdarg.h>
#include <stdbool.h>
#include "main.h"

HAL_StatusTypeDef console_init(void);
HAL_StatusTypeDef console_deinit(void);
HAL_StatusTypeDef THW_printf(const char *fmt, ...);


#ifdef MODE_THW

#define CONSOLE_RX_BUF_SIZE 10
extern char console_rxBuffer[CONSOLE_RX_BUF_SIZE + 1];
bool console_manageRx(void);

#endif //MODE_THW


#endif /* ATRALTECH_DRIVERS_CONSOLE_CONSOLE_H_ */
