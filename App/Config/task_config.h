#ifndef INC_TASK_CONFIG_H_
#define INC_TASK_CONFIG_H_

#include <cmsis_os2.h>

#ifdef __cplusplus
extern "C" {
#endif

// Task Priority
#define TSK_CFG__PRIO__TSK_THW 				(osPriority_t)osPriorityNormal			// Test Hardware - Main task
#define TSK_CFG__PRIO__TSK_THW_RFS 			(osPriority_t)osPriorityNormal			// Test Hardware - Refresh Task
#define TSK_CFG__PRIO__TSK_NMG 				(osPriority_t)osPriorityNormal			// Net Manager
#define TSK_CFG__PRIO__TSK_NMG_PING 		(osPriority_t)osPriorityNormal			// Net ping - Cyclic task
#define TSK_CFG__PRIO__TSK_NMG_MQTT 		(osPriority_t)osPriorityNormal			// Net mqtt
#define TSK_CFG__PRIO__TSK_PMG   			(osPriority_t)osPriorityNormal		    // IPM Internal Protocol Manager  - Refresh Task

// Stack Size
#define TSK_CFG__STACK__TSK_THW 			(128 * 32)  // Test Hardware - Main task
#define TSK_CFG__STACK__TSK_THW_RFS 		(128 * 16)  // Test Hardware - Refresh Task
#define TSK_CFG__STACK__TSK_NMG 			(128 * 16)  // Net Manager
#define TSK_CFG__STACK__TSK_NMG_PING 		(128 * 16)  // Net ping - cyclic task
#define TSK_CFG__STACK__TSK_NMG_MQTT        (512 * 16)  // MQTT
#define TSK_CFG__STACK__TSK_PMG 			(128 * 16)      // IPM Internal Protocol Manager  - Refresh Task

#ifdef __cplusplus
}
#endif

#endif /* INC_TASK_CONFIG_H_ */
