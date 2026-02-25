/*
 * thw_platform_time.c
 *
 *  Created on: 25 févr. 2026
 *      Author: AurelienPajadon
 */

#include <cmsis_os2.h>
#include <stdint.h>
#include <TestHardwareCore/interfaces/thw_time_if.h>

//------------------------------------------------------------------------------
/// \fn 		platform_getTickMs
/// \brief 	Return a monotonic tick in milliseconds
//------------------------------------------------------------------------------
static uint32_t platform_getTickMs(void)
{
    return osKernelGetTickCount();
}

//------------------------------------------------------------------------------
// Time interface implementation for THW
//------------------------------------------------------------------------------
static thw_time_if_t platform_time =
{
    .getTickMs = platform_getTickMs
};

//------------------------------------------------------------------------------
/// \fn 	thw_platform_time_getInterface
/// \brief 	Return a pointer to the time interface implementation for THW
//------------------------------------------------------------------------------
thw_time_if_t* thw_platform_time_getInterface(void)
{
	return &platform_time;
}

