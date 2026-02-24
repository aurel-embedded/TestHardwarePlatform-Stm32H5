/*
 * cmp.h
 *
 *  Created on: 1 févr. 2023
 *      Author: apajadon
 */

#ifndef CMP_H_
#define CMP_H_
#include <stdbool.h>
#include <stdint.h>
#include <main.h>

#ifdef __cplusplus
extern "C" {
#endif

// Component Finite State Machine
//--------------------------------
typedef enum{
	CMP_FSM_UNDEF = 0,		// Starting
	CMP_FSM_INIT,			// Initializing
	CMP_FSM_RUNNING,		// Running
	CMP_FSM_DEINIT,			// Deinit
	CMP_FSM_FAILURE,		// Failure
}cmp_fsm_t;

typedef enum
{
	CMP_OK = 0,
	CMP_ERROR,
} cmp_errormanagement_t;

// Component Status
//--------------------------------
typedef enum{
	CMP_MODE_NOTDEFINED = 0,	// Mode non défini
	CMP_MODE_NOMINAL,			// Mode Nominal
	CMP_MODE_DEGRADE,			// Mode Dégradé
	CMP_MODE_FAILURE,			// Mode Failure
}cmp_mode_t;
extern char * cmpModeToString(cmp_mode_t mode);



typedef struct{
	bool 			isTaskRunning;		// Is Thread Task running
	cmp_mode_t		cmpMode;			// Component Mode
	cmp_fsm_t 		fsm;				// Finite State Machine for The Component
	uint8_t 		errNumber;
	bool 			isInitDone;			// Is Thread task initiated
}cmp_status_t;

#ifdef __cplusplus
}
#endif

#endif /* CMP_H_ */
