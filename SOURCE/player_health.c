/*!
file:	player_health.c
author:	Lee Fu Sheng Roy

email:	f.lee@digipen.edu

brief:	function definitions for functions declared in the player_health.h header file

	Copyright � 2020 DigiPen, All rights reserved.

*//*__________________________________________________________________________________________________________*/
#include "player_health.h"

float health, max_health;
Castle castle;
char healthBuffer[6];

/*!
@brief -	Initializes the default health
*//*_____________________________________________________________________________*/
void InitHealth(void)
{
	health = max_health;
	castle.x = 0.0f;
	castle.y = 0.0f;
	castle.width = CASTLE_WIDTH;
	castle.height = CASTLE_HEIGHT;
}

/*!
@brief -		Initializes the default health

@param x -		x coordinates of the castle
@param y -		y coordinates of the castle
@param width -	Width of the castle
@param height -	Height of the castle
*//*_____________________________________________________________________________*/
void InitCastle(float x, float y, float width, float height)
{
	castle.x = x;
	castle.y = y;

	castle.width = width;
	castle.height = height;
}

/*!
@brief -			Reduces the health by amount

@param amount -		amount of health to decrease
*//*_____________________________________________________________________________*/
void HealthDeplete (unsigned int amount)
{
	if (health > 0)
	{
		health -= amount;
	}
	if (health < 0)
		health = 0;
}

/*!
@brief -			Increases the health by amount

@param amount -		amount of health to increase
*//*_____________________________________________________________________________*/
void HealthAdd(unsigned int amount)
{
	if (health < max_health)
	{
		health += amount;
	}
	if (health > max_health)
		health = max_health;
}

/*!
@brief -	Renders 2 rectangle, 1 red and 1 green over the red. Red represents
			max health and the green represents current health
*//*_____________________________________________________________________________*/
void RenderHealth(void)
{
	AddRect(HEALTH_X, HEALTH_Y, HEALTH_UNIT, HEALTH_HEIGHT, 0.1f, COLOR_RED, UI_LAYER);
	if (health != 0)
		AddRect(HEALTH_X, HEALTH_Y, HEALTH_UNIT * (health/ max_health), HEALTH_HEIGHT, 0.1f, COLOR_GREEN, UI_LAYER);
	sprintf_s(healthBuffer, 6, "%.f%%", (health / max_health) * 100.0);
	AddText(healthBuffer, castle.x, HEALTH_Y + (HEALTH_HEIGHT * 0.5f), 10.0f, COLOR_BLACK, CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE, UI_LAYER);
}

/*!
@brief -	Calls RenderHealth() to render the health bar with every loop
*//*_____________________________________________________________________________*/
void HealthUpdate(void)
{
	RenderHealth();
}

/*!
@brief -	Returns True if health is zero, else returns False
*//*_____________________________________________________________________________*/
Boolean HealthZero(void)
{
	if (health == 0)
		return True;
	else
		return False;
}

/*!
@brief -			Sets max amount of health the player can have

@param maxHealth -	Total health the player can have
*//*_____________________________________________________________________________*/
void SetPlayerMaxHealth(float maxHealth)
{
	max_health = maxHealth;
	health = maxHealth;
}