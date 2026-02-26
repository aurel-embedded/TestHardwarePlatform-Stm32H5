/*
 * thw_menuThw.c
 *
 *  Created on: 26 jan 2023
 *      Author: apajadon
 *
 * Ce sous-composant du composant THW s'occupe de gérer les test drivers concernant
 * la communincation utilisé par le THW\n
 * Ces fonctions sont appelées par le composant principal THW.\n\n
 */
#ifdef MODE_THW

#include <cmsis_os2.h>
#include <TestHardwareCore/THW_api.h>
#include <Tests/THW_user/thw.h>
#include <stddef.h>
#include <main.h>

static const char menuName[] = "Drv | Uart Ctrl Panel";

//-------------------------


static const st_thw_menuItem menuTab[] = {
};
const static uint16_t menuTabSize = sizeof(menuTab) / sizeof(st_thw_menuItem);


static void DisplayMenu(void);
static void onInit(void);
static void onExit(void);
static void RefreshFn(void);

static uint8_t cpt = 0;

// Menu instance
static const st_thw_menu actual_menu =
{
    .menu.tab = menuTab,
    .menu.size = menuTabSize,
    .displayMenu = DisplayMenu,
    .onInit = onInit,
    .onExit = onExit,
    .refreshFn = RefreshFn,
    .refreshPeriodInMs = 100
};

//------------------------------------------------------------------------------
/// \fn thw_drv_uartThw_setActive(void*)
/// \brief
//------------------------------------------------------------------------------
void thw_drv_uartThw_setActive(void*)
{
	THW_setMenu(&actual_menu);
}

//------------------------------------------------------------------------------
/// \fn 		void DisplayMenu(void)
/// \brief
//------------------------------------------------------------------------------
static void DisplayMenu(void)
{

	// RAZ screen
	THW_clearScreen();

	// Affichage Menu
	THW_Banner(menuName);
	THW_printf("\r\n");

	THW_printf("cpt :\r\n");
	THW_printf("\r\n");

}

//------------------------------------------------------------------------------
/// \fn     static void onInit(void)
/// \brief  Actions performed when entering the test menu.
//------------------------------------------------------------------------------
static void onInit(void)
{
	cpt = 0;
}

//------------------------------------------------------------------------------
/// \fn     static void onExit(void)
/// \brief  Actions performed when leaving the test menu.
//------------------------------------------------------------------------------
static void onExit(void)
{
	// Return to the previous menu
	thw_drv_setActive(NULL);
}

//------------------------------------------------------------------------------
/// \fn 		void thw_drv_uartThw_RefreshFn(void)
/// \brief
//------------------------------------------------------------------------------
void RefreshFn(void)
{
	THW_goto(3,7);
	THW_printf("%d"VT100_CLEAREOL, cpt++);

}




//*************************************************************************************************
//*************************************************************************************************
// 										TESTING FUNCTIONS
//*************************************************************************************************
//*************************************************************************************************

#endif // MODE_THW
