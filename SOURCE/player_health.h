/*!
file:	player_health.h
author:	Lee Fu Sheng Roy

email:	f.lee@digipen.edu

brief:	function declarations for player_health.c

	Copyright � 2020 DigiPen, All rights reserved.

*//*__________________________________________________________________________________________________________*/


#ifndef PLAYERHEALTH_H
#define PLAYERHEALTH_H

typedef struct Castle
{
	float x;
	float y;
	float width;
	float height;
}Castle;

#define HEALTH_HEIGHT		GRID_SYSTEM_HEIGHT * 0.5f
#define CASTLE_WIDTH		GRID_SYSTEM_WIDTH * 5.0f
#define CASTLE_HEIGHT		GRID_SYSTEM_HEIGHT * 5.0f
#define HEALTH_UNIT			CASTLE_WIDTH
#define HEALTH_X			castle.x - (castle.width * 0.5f)
#define HEALTH_Y			castle.y - (castle.height * 0.5f) - HEALTH_HEIGHT

#include "common_headers.h"

// Initializes the health to default values
void InitHealth(void);

// Set castle's position, and size according to parameters 
void InitCastle(float x, float y, float width, float height);

// Decreases the health by 1 unit
void HealthDeplete(unsigned int amount);

// Increases the health by 1 unit
void HealthAdd(unsigned int amount);

// Renders 1 red rectangle and 1 green rectangle indicating health bar, above the castle
void RenderHealth(void);

// Renders the health bar and castle onto the screen.  
void HealthUpdate(void);

// Returns True if health is zero. Used by death_screen function. 
Boolean HealthZero(void);

void SetPlayerMaxHealth(float maxHealth);

#endif