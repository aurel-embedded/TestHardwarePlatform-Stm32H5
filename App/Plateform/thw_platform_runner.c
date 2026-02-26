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
#define THW_PLATFORM_RUNNER__STACK 			(2048)

//-----------------------------------------------------------------------------
// THREAD RX
//-----------------------------------------------------------------------------
osThreadId_t thw_platform_runner_taskId;
const osThreadAttr_t thw_platform_runner_taskAttr = {
		.name = "thw_platform_runner_tsk",
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
        osDelay(10);
    }
}

//-----------------------------------------------------------------------------
/// \fn     void thw_platform_start(void)
/// \brief  THW main task initialization and start
//-----------------------------------------------------------------------------
thw_status_t thw_platform_start(void)
{
	// Get Dependencies
    thw_io_if_t* io   = thw_platform_console_io_getInterface();
    thw_time_if_t* t  = thw_platform_time_getInterface();

    // Check dependencies
    if (io == NULL)
    {
    	return THW_STATUS_IO_ERROR;
    }
    if (t == NULL)
    {
    	return THW_STATUS_TIME_ERROR;
    }

    // Initialize THW with platform dependencies and entry point
    if(THW_init(io, t, thw_main_setActive) != THW_STATUS_OK)
	{
		return THW_STATUS_ERROR;
	}

    // Create and start THW main task
    if(osThreadNew(thw_task, NULL, &thw_platform_runner_taskAttr) == NULL)
	{
		return THW_STATUS_ERROR;
	}
    return THW_STATUS_OK;
}
