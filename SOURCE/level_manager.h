/*!
file:	level_manager.h
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	header file that contains function definitions for 
		level manager

    Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#ifndef	LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include "pointer_manager.h"
#include "level.h"

void RestartLevel(void);
void SetNextLevel(Level level);
void ExitGame(void);

#endif