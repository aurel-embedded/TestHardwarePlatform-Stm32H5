/*
 * thw_cmp.c
 *
 *  Created on: Jun 5, 2025
 *      Author: aurelienp
 */


#ifdef MODE_THW

#include <stddef.h>
#include <stdint.h>
#include <TestHardwareCore/THW_api.h>
#include <Tests/THW_user/thw.h>


static const char menuName[] = "Cmp";

//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------
//****************************************
//			*** Main Menu ***
//****************************************
static const st_thw_menuItem menuTab[] = {
};


static uint16_t menuTabSize = sizeof(menuTab) / sizeof(st_thw_menuItem);


static void DisplayMenu(void);
static void onExit(void);

//------------------------------------------------------------------------------
// DESCRIPTION:         void thw_cmp_setActive(void*)
// PARAMETERS:          void
// RETURN VALUE:        void
// DESIGN INFORMATION:
//------------------------------------------------------------------------------
void thw_cmp_setActive(void*)
{
	// Menu affiché
    thw_actualMenu.menu.tab          = menuTab;
    thw_actualMenu.menu.size         = menuTabSize;
    thw_actualMenu.displayMenu       = DisplayMenu;
    thw_actualMenu.onExit            = onExit;
}


//------------------------------------------------------------------------------
// DESCRIPTION:         void thw_cmp_DisplayMenu(void)
// PARAMETERS:          void
// RETURN VALUE:        void
// DESIGN INFORMATION:
//------------------------------------------------------------------------------
static void DisplayMenu(void)
{
	// Affichage Menu
	THW_Banner(menuName);
	THW_printf("\r\n");

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

