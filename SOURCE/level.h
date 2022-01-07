/*!
file:	buttons.h
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	header file that contains enum of different levels

    Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#ifndef	LEVEL_H
#define LEVEL_H

#include "splash_screen.h"
#include "menu.h"
#include "level_1.h"
#include "level_2.h"
#include "level_3.h"
#include "level_4.h"
#include "level_5.h"
#include "level_maker.h"
#include "test.h"

typedef enum Level
{
	TEST_LEVEL = -3,
	LEVEL_EDITOR = -2,
	NO_LEVEL = -1,
	LEVEL_1,
	LEVEL_2,
	LEVEL_3,
	LEVEL_4,
	LEVEL_5,
	TOTAL_PLAYING_LEVELS,
	SPLASH_SCREEN,
	MENU,
}Level;

#endif