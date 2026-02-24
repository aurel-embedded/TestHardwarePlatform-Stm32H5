/*
 * thw.h
 *
 *  Created on: 20 janv. 2023
 *      Author: apajadon
 */

#ifndef THW_THW_H_
#define THW_THW_H_

#include <TestHardwareCore/THW_api.h>



// Main
//------
extern void thw_main_setActive(void*);

// Drivers
//-----------
extern void thw_drv_setActive(void*);
extern void thw_drv_uartThw_setActive(void*);
extern void thw_drv_gpio_setActive(void*);
extern void thw_drv_controlpanel_setActive(void*);

// Components
//-------------
extern void thw_cmp_setActive(void*);

extern void thw_cmp_nmg_setActive(void*);
extern void thw_cmp_nmg_mqtt_setActive(void*);
//extern void thw_cmp_nmg_mqtt_fakeSensor_setActive(void*);
extern void thw_cmp_nmg_netStackCyclone_setActive(void*);
extern void thw_cmp_nmg_services_setActive(void*);

extern void thw_cmp_nmg_user_mqtt_setActive(void*);


// PGM - Protocol Manager
extern void thw_cmp_pgm_setActive(void*);
extern void thw_cmp_pgm_parser_setActive(void*);
extern void thw_cmp_pgm_builder_setActive(void*);
extern void thw_cmp_pgm_dispatcher_setActive(void*);
extern void thw_cmp_pgm_handlers_setActive(void*);
extern void thw_cmp_pgm_interface_setActive(void*);
extern void thw_cmp_pgm_runall_setActive(void*);

extern void thw_cmp_pgm_parser_runall(void*);
extern void thw_cmp_pgm_builder_runall(void*);
extern void thw_cmp_pgm_dispatcher_runall(void*);
extern void thw_cmp_pgm_handlers_runall(void*);
extern void thw_cmp_pgm_interface_runall(void*);

// PGM Test helper functions
extern void THW_PGM_ResetResults(void);
extern void THW_PGM_PrintSummary(void);
extern bool THW_PGM_Assert(bool condition, const char *testName, const char *message);

const st_thw_actualMenu* thw_cmp_gui_getMenuDescription(void);

#endif /* THW_THW_H_ */
