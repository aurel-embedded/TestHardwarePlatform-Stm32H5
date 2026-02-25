/*
 * thw_platform_runner.c
 *
 *  Created on: 25 févr. 2026
 *      Author: AurelienPajadon
 */


#include <cmsis_os2.h>
#include "thw_platform_runner.h"
#include "thw_platform_console_io.h"
#include "thw_platform_time.h"
#include <TestHardwareCore/THW_api.h>
#include <Tests/THW_user/thw.h>

#define THW_PLATFORM_RUNNER__PRIO 			(osPriority_t)osPriorityNormal
#define THW_PLATFORM_RUNNER__STACK 			(128 * 32)

//-----------------------------------------------------------------------------
// THREAD RX
//-----------------------------------------------------------------------------
osThreadId_t thw_platform_runner_taskId;
const osThreadAttr_t thw_platform_runner_taskAttr = {
		.name = "thw_tsk",
		.stack_size = 	THW_PLATFORM_RUNNER__STACK,
		.priority = 	THW_PLATFORM_RUNNER__PRIO,
};


//-----------------------------------------------------------------------------
/// \fn     static void thw_task(void *arg)
/// \brief   THW main task
//-----------------------------------------------------------------------------
static void thw_task(void *arg)
{
    while (1)
    {
        THW_process();
        osDelay(100);
    }
}

//-----------------------------------------------------------------------------
/// \fn     void thw_platform_start(void)
/// \brief  THW main task initialization and start
//-----------------------------------------------------------------------------
void thw_platform_start(void)
{
	// Get Dependencies
    thw_io_if_t* io   = thw_platform_console_io_getInterface();
    thw_time_if_t* t  = thw_platform_time_getInterface();

    // Initialize THW with platform dependencies and entry point
    THW_init(io, t, thw_main_setActive);

    // Create and start THW main task
    osThreadNew(thw_task, NULL, &thw_platform_runner_taskAttr);
}
