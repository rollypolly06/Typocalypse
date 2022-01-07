/*!
file:	common_gameplay.h
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief: includes common variables for gameplay levels

	Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#ifndef	COMMON_GAMEPLAY_H
#define COMMON_GAMEPLAY_H

#include "tower.h" 
#include "ui.h"
#include "enemy.h"
#include "quad.h"
#include "player.h"
#include "win_screen.h"

typedef enum GameState
{
	WON, 
	PAUSED,			// game is paused
	BUILDING,		// let the player some time to build
	PLAYING,		// wave is ongoing
	DEATH_SCREEN,
} GameState;

void CommonLevelInit(const char* level_file, const char* enemy_waypoint_file, unsigned max_enemies, int waves, int* currWaveIndex, WordTheme theme, Level currLevel);
GameState CommonLevelUpdate(void);

void SetIsBuilding(Boolean building);
void SetAlreadyBuilt(Boolean built);

void ResetGameplayVariables(void);
void IncrementEnemiesKilled(void);
void IncrementEnemiesSpawned(void);
unsigned GetEnemiesKilled(void);
unsigned GetEnemiesSpawned(void);
void ResetWave(Boolean setAlreadyBuilt);

float GetSpawnTime(void);

void SetIsOrthodoxAlive(Boolean isAlive);
Boolean GetIsOrthodoxAlive(void);


#endif