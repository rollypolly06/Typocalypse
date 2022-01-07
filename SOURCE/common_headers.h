/*!
file:	common_headers.h
author:	Wong Man Cong
		Lee Fu Sheng Roy
		Phua Tze Cheng Jennifer
		Thea Sea
		Nicole Wong

email:	w.mancong@digipen.edu
		f.lee@digipen.edu
		p.tzechengjennifer@digipen.edu
		thea.sea@digipen.edu
		n.wong@digipen.edu

brief:	contains common header files for the game project

	Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/

#ifndef	COMMON_HEADERS_H
#define COMMON_HEADERS_H

// To find the size of an array
#define ARRAY_SIZE(array)	(sizeof(array) / sizeof(array[0]))

// Screen
#define SCREEN_WIDTH			1400
#define SCREEN_HEIGHT			900
#define FULL_SCREEN				1
#define HALF_SCREEN_WIDTH		((float)CP_System_GetWindowWidth() * 0.5f)
#define HALF_SCREEN_HEIGHT		((float)CP_System_GetWindowHeight() * 0.5f)
#define WINDOW_WIDTH			((float)CP_System_GetWindowWidth())
#define WINDOW_HEIGHT			((float)CP_System_GetWindowHeight())

// FPS
#define FPS						60

// Common colors
#define COLOR_RED				CP_Color_Create(255, 0, 0, 255)
#define COLOR_GREEN				CP_Color_Create(0, 255, 0, 255)
#define COLOR_BLUE				CP_Color_Create(0, 0, 255, 255)
#define COLOR_WHITE				CP_Color_Create(255, 255, 255, 255)
#define COLOR_BLACK				CP_Color_Create(0, 0, 0, 255)
#define BACKGROUND_COLOR		CP_Color_Create(100, 91, 84, 255)
#define ALPHA					255
#define TRANSLUCENT_RED			CP_Color_Create(255, 0, 0, 20)
#define TRANSLUCENT_BLUE		CP_Color_Create(0, 0, 255, 20)
#define TRANSLUCENT_GREEN		CP_Color_Create(0, 255, 0, 20)
#define TRANSLUCENT_WHITE		CP_Color_Create(255, 255, 255,20)
#define TRANSLUCENT_BLACK		CP_Color_Create(0, 0, 0,20)

// Fonts
#define DEFAULT_FONT			CP_Font_Load("Assets/Fonts/PlayfairDisplay-Regular.ttf")

// Pi Value
#define PI						3.141593f

// Grid Sizes
#define UI_GRID_ROWS			30
#define UI_GRID_COLS			20
#define UI_GRID_WIDTH			((float)CP_System_GetWindowWidth() / UI_GRID_ROWS)
#define UI_GRID_HEIGHT			((float)CP_System_GetWindowHeight() / UI_GRID_COLS)
/*================================================================================================================*/
#define GRID_SYSTEM_ROWS		30
#define GRID_SYSTEM_COLS		30
#define GRID_SYSTEM_WIDTH		((float)CP_System_GetWindowWidth() / GRID_SYSTEM_ROWS)
#define GRID_SYSTEM_HEIGHT		((float)CP_System_GetWindowHeight() / GRID_SYSTEM_COLS)
/*================================================================================================================*/
// Modes
#define LEVEL_EDITOR_MODE		0
#define TEST_MODE				0
#define	RELEASE_MODE			1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "cprocessing.h"
#include "level_manager.h"
#include "geometry.h"
#include "boolean.h"
#include "io_files.h"
#include "text_render.h"
#include "collision_detection.h"
#include "render_manager.h"
#include "game_difficulty.h"
#include "game_state.h"
#include "win_screen.h"
#include "death_screen.h"
#include "buttons.h"

#endif
