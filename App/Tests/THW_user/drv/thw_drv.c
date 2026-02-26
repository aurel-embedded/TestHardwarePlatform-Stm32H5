/*
 * thw_drv.c
 *
 *  Created on: Jun 5, 2025
 *      Author: aurelienp
 */


#ifdef MODE_THW

#include <stddef.h>
#include <stdint.h>
#include <TestHardwareCore/THW_api.h>
#include <Tests/THW_user/thw.h>


static const char menuName[] = "Drv";

//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------
//****************************************
//			*** Main Menu ***
//****************************************
static const st_thw_menuItem menuTab[] = {
		{.name = "Uart Control Panel", 				.pActionFn = thw_drv_uartThw_setActive, 			.info = 0},
};


static const uint16_t menuTabSize = sizeof(menuTab) / sizeof(st_thw_menuItem);


static void DisplayMenu(void);
static void onInit(void);
static void onExit(void);

// Menu instance
static const st_thw_menu actual_menu =
{
    .menu.tab = menuTab,
    .menu.size = menuTabSize,
    .displayMenu = DisplayMenu,
    .onInit = onInit,
    .onExit = onExit,
    .refreshFn = NULL,
    .refreshPeriodInMs = 0
};

//------------------------------------------------------------------------------
/// \fn thw_drv_setActive(void*)
/// \brief
//------------------------------------------------------------------------------
void thw_drv_setActive(void*)
{
	THW_setMenu(&actual_menu);
}


//------------------------------------------------------------------------------
/// \fn 		void DisplayMenu(void)
/// \brief
//------------------------------------------------------------------------------
static void DisplayMenu(void)
{
	// Affichage Menu
	THW_Banner(menuName);
	THW_printf("\r\n");

}

//------------------------------------------------------------------------------
/// \fn     static void onInit(void)
/// \brief  Actions performed when entering the test menu.
//------------------------------------------------------------------------------
static void onInit(void)
{
}

//------------------------------------------------------------------------------
/// \fn     static void onExit(void)
/// \brief  Actions performed when leaving the test menu.
//------------------------------------------------------------------------------
static void onExit(void)
{
	// Return to the previous menu
	thw_main_setActive(NULL);
}

#endif	// MODE_THW

