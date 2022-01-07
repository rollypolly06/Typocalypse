/*---------------------------------------------------------
 * file:	main.c
 * author:	[NAME]
 * email:	[DIGIPEN EMAIL ADDRESS]
* 
 * brief:	Main entry point for the sample project
			* of the CProcessing library
* 
 * documentation link:
 * https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
* 
 * Copyright © 2020 DigiPen, All rights reserved.
* ---------------------------------------------------------*/
#include "common_headers.h"
#include <crtdbg.h>

/* Entry point */
int main(void)
{
#if FULL_SCREEN
    CP_System_Fullscreen();
#else
    CP_System_SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
#endif

#if LEVEL_EDITOR_MODE
    SetNextLevel(LEVEL_EDITOR);
#elif TEST_MODE
    SetNextLevel(TEST_LEVEL);
#else
    SetNextLevel(SPLASH_SCREEN);
#endif

    CP_System_SetFrameRate(FPS);
#if !RELEASE_MODE
    CP_System_ShowConsole();
#endif
    CP_Engine_Run();

    // For when user force close program
    FreeMemory();
    FreeImageMemory();
    FreeMemoryLast();

    //int mem_leak = _CrtDumpMemoryLeaks();
    //printf("%d", mem_leak);

    return 0;
}
