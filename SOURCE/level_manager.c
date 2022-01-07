/*!
file:	level_manager.c
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	Manager for switching between different levels. 	

    Copyright © 2020 DigiPen, All rights reserved.	
*//*____________________________________________________________*/
#include "level_manager.h"

Level currLevel;

void RestartLevel(void)
{
	InitRenderManager();
	switch (currLevel)
	{
		case LEVEL_1:
		{
			CP_Engine_SetNextGameStateForced(level_1_init, level_1_update, level_1_exit);
			break;
		}
		case LEVEL_2:
		{
			CP_Engine_SetNextGameStateForced(level_2_init, level_2_update, level_2_exit);
			break;
		}
		case LEVEL_3:
		{
			CP_Engine_SetNextGameStateForced(level_3_init, level_3_update, level_3_exit);
			break;
		}
		case LEVEL_4:
		{
			CP_Engine_SetNextGameStateForced(level_4_init, level_4_update, level_4_exit);
			break;
		}
		case LEVEL_5:
		{
			CP_Engine_SetNextGameStateForced(level_5_init, level_5_update, level_5_exit);
			break;
		}
		case SPLASH_SCREEN:
		{
			CP_Engine_SetNextGameStateForced(splashscreen_init, splashscreen_update, splashscreen_exit);
			break;
		}
		case MENU:
		{
			CP_Engine_SetNextGameStateForced(menu_init, menu_update, menu_exit);
			break;
		}
		case LEVEL_EDITOR:
		{
			CP_Engine_SetNextGameStateForced(level_maker_init, level_maker_update, level_maker_exit);
			break;
		}
		case TEST_LEVEL:
		{
			CP_Engine_SetNextGameStateForced(test_init, test_update, test_exit);
			break;
		}
	}

	SetBackgroundColor(COLOR_BLACK);

	// Deallocates common game entity memory
	FreeMemory();
	FreeImageMemory();
}

void SetNextLevel(Level level)
{
	InitRenderManager();
	switch (currLevel = level)
	{
		case LEVEL_1:
		{
			CP_Engine_SetNextGameState(level_1_init, level_1_update, level_1_exit);
			break;
		}
		case LEVEL_2:
		{
			CP_Engine_SetNextGameState(level_2_init, level_2_update, level_2_exit);
			break;
		}
		case LEVEL_3:
		{
			CP_Engine_SetNextGameState(level_3_init, level_3_update, level_3_exit);
			break;
		}
		case LEVEL_4:
		{
			CP_Engine_SetNextGameState(level_4_init, level_4_update, level_4_exit);
			break;
		}
		case LEVEL_5:
		{
			CP_Engine_SetNextGameState(level_5_init, level_5_update, level_5_exit);
			break;
		}
		case SPLASH_SCREEN:
		{
			CP_Engine_SetNextGameState(splashscreen_init, splashscreen_update, splashscreen_exit);
			break;
		}
		case MENU:
		{
			CP_Engine_SetNextGameState(menu_init, menu_update, menu_exit);
			break;
		}
		case LEVEL_EDITOR:
		{
			CP_Engine_SetNextGameState(level_maker_init, level_maker_update, level_maker_exit);
			break;
		}		
		case TEST_LEVEL:
		{
			CP_Engine_SetNextGameState(test_init, test_update, test_exit);
			break;
		}
	}

	SetBackgroundColor(COLOR_BLACK);

	// Deallocates common game entity memory
	FreeMemory();
	FreeImageMemory();
}

void ExitGame(void)
{
	FreeMemory();
	FreeImageMemory();
	CP_Engine_Terminate();
}