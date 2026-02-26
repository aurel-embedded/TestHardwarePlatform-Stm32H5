
/*
 * thw_main.c
 *
 * Ce composant s'occupe de gérer l'affichage et les actions sur le menu
 *  principal.\n
 * Ces fonctions sont appelées par le composant principal Hardware Test.\n\n
 *
 *  Created on: 7 nov. 2022
 *      Author: apajadon
 */
#ifdef MODE_THW
#include <Tests/THW_user/thw.h>
#include <stddef.h>
#include <stdint.h>

static const char menuName[] = "Main";

//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------
//****************************************
//			*** Main Menu ***
//****************************************
static const st_thw_menuItem menuTab[] = {
		{.name = "Drivers", 			.pActionFn = thw_drv_setActive, 	.info = 0},
		{.name = "Components", 			.pActionFn = thw_cmp_setActive, 	.info = 0},
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
    .refreshPeriodInMs = 100
};

//------------------------------------------------------------------------------
/// \fn thw_drv_uartThw_setActive(void*)
/// \brief
//------------------------------------------------------------------------------
void thw_main_setActive(void*)
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
}

#endif // MODE_THW
