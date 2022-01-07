/*!
file:	death_screen.h
author:	Lee Fu Sheng Roy

email:	f.lee@digipen.edu

brief:	includes all declarations to functions defined in 
		death_screen.h

	Copyright © 2020 DigiPen, All rights reserved.

*//*____________________________________________________________*/
#ifndef DEATHSCREEN_H
#define DEATHSCREEN_H

#include "common_headers.h"
#include "player_health.h"
#include "buttons.h"

void InitDeathScreen(void);

void RenderDeathScreenButtons(void);

int DeathScreenUpdate(void);

#endif