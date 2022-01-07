/*!
file:	common_gameplay.c
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief: includes common variables for gameplay levels

	Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#include "common_gameplay.h"
#include "type_to_kill.h"

unsigned enemiesKilled = 0, enemiesSpawned = 0;

const float BUILD_TIME = 45.0f, WAVE_CLEARED_TIME = 5.0f, SPAWN_TIME = 1.25f;
float wave_dt = 0.0f, wave_clear_msg_dt = 0.0f;
Boolean isBuilding = False, alreadyBuilt = False;

char currGameStateInfo[25], waveClearedInfo[25];

void SetPlayerMaxHealth(float maxHealth);
void RenderBuildTime(void);
void RenderCurrentWave(void);
void RenderWaveCleared(void);

Boolean gameWon = False, isOrthodoxAlive = False, waveCleared = False;

int totalWaves, *currWave, wave_info;

Button* skipBuildTime;

/*!
@brief	Initialised common variables found inside each level

@param	level_file: file path to current level
		enemy_waypoint_file: file path to waypoints of current level
		max_enemies: maximum enemies for the current level
		waves: total waves in this current level
		currWaveIndex: reference to the wave index
		theme: word theme for the current level
		currLevel: current level of the game
*//*____________________________________________________________*/
void CommonLevelInit(const char* level_file, const char* enemy_waypoint_file, unsigned max_enemies, int waves, int *currWaveIndex, WordTheme theme, Level currLevel)
{
	DefaultRenderManager();
	SetBackgroundColor(BACKGROUND_COLOR);

	InitGrid(level_file);

	InitTower();
	InitUI();

	InitTheme(theme, max_enemies);
	EnemyInit(enemy_waypoint_file);

	InitPlayer();

	GoldInit();

	InitWinScreen(currLevel);
	SetNextWord();

	switch (GetGameDifficulty())
	{
		case EASY:
		{
			SetPlayerMaxHealth(200.0f);
			break;
		}
		case MEDIUM:
		{
			SetPlayerMaxHealth(150.0f);
			break;
		}
		case HARD:
		{
			SetPlayerMaxHealth(100.0f);
			break;
		}
	}

	currWave = currWaveIndex;
	totalWaves = waves;
	ResetGameplayVariables();
}

/*!
@brief	common updates of the game

@return	current state of the game
*//*____________________________________________________________*/
GameState CommonLevelUpdate(void)
{
	if (DeathScreenUpdate())
	{
		RenderAll();
		return DEATH_SCREEN;
	}

	SetIsBuilding(True);

	if (GetPaused() && !gameWon)
	{
		PauseGameUpdate();
		return PAUSED;
	}

	if (gameWon)
		return WON;

	UIUpdate();
	UpdatePlayer();
	EnemyUpdate();
	UpdateQuadTree();

	GoldRender();

	TextDraw();

#if !RELEASE_MODE
	DrawQuadTree();
#endif

	if (isBuilding)
	{
		wave_dt -= CP_System_GetDt();
		RenderBuildTime();

		ButtonScaleUp(skipBuildTime, 5.0f, 5.0f, 5.0f);

		if (IsButtonClick(skipBuildTime, MOUSE_BUTTON_LEFT))
			wave_dt = 0.0f;

		if (wave_dt <= 0.0f)
		{
			isBuilding = False;
			wave_dt = BUILD_TIME;
			SetButtonAlpha(skipBuildTime, 0);
			SetButtonClickableState(skipBuildTime, False);
		}

		RenderWaveCleared();
		RenderAll();
		return BUILDING;
	}
	else
	{
		// Render what wave number it is now
		RenderCurrentWave();
	}

	RenderAll();
	return PLAYING;
}

/*!
@brief	Renders the time left to build
*//*____________________________________________________________*/
void RenderBuildTime(void)
{
	sprintf_s(currGameStateInfo, sizeof(currGameStateInfo), "Build time left: %d", (int)wave_dt);
	AddText(currGameStateInfo, GRID_SYSTEM_WIDTH * 11.5f, GRID_SYSTEM_HEIGHT * 28.0f, GRID_SYSTEM_WIDTH, COLOR_RED, CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP, TOP_LAYER);
}

/*!
@brief	Renders current_wave / total_waves
*//*____________________________________________________________*/
void RenderCurrentWave(void)
{
	sprintf_s(currGameStateInfo, sizeof(currGameStateInfo), "Wave: %d/%d", *currWave + 1 < totalWaves ? *currWave + 1 : totalWaves, totalWaves);
	AddText(currGameStateInfo, GRID_SYSTEM_WIDTH * 11.5f, GRID_SYSTEM_HEIGHT * 28.0f, GRID_SYSTEM_WIDTH, COLOR_RED, CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP, TOP_LAYER);
}

/*!
@brief	Set the building phase

@param	building: status of buidling phase
*//*____________________________________________________________*/
void SetIsBuilding(Boolean building)
{
	if (alreadyBuilt)
		return;
	alreadyBuilt = True;
	isBuilding = building;

	SetButtonAlpha(skipBuildTime, ALPHA);
	SetButtonClickableState(skipBuildTime, True);
}

/*!
@brief	Set already built so that the update loop won't overlap

@param	built: status of alreadyBuilt
*//*____________________________________________________________*/
void SetAlreadyBuilt(Boolean built)
{
	alreadyBuilt = built;
}

/*!
@brief	Reset gameplay variables to it's default
*//*____________________________________________________________*/
void ResetGameplayVariables(void)
{
	enemiesKilled = 0;
	enemiesSpawned = 0;
	wave_info = 0;
	wave_dt = BUILD_TIME;
	wave_clear_msg_dt = WAVE_CLEARED_TIME;
	isBuilding = False;
	alreadyBuilt = False;
	gameWon = False;
	isOrthodoxAlive = False;
	waveCleared = False;

	skipBuildTime = LoadButton("Assets/Image/Buttons/skip.png", UI_GRID_WIDTH * 15.5f, UI_GRID_HEIGHT * 19.0f, UI_GRID_WIDTH * 1.5f, UI_GRID_HEIGHT);
	SetButtonAlpha(skipBuildTime, 0);
	SetButtonClickableState(skipBuildTime, False);
}

/*!
@brief	Increment the amount of enemies killed to check if 
		current wave is finished
*//*____________________________________________________________*/
void IncrementEnemiesKilled(void)
{
	 //printf("enemy killed\n");
	++enemiesKilled;
}

/*!
@brief	Get the total amount of enemies killed for the current wave

@return	Amount of enemies killed
*//*____________________________________________________________*/
unsigned GetEnemiesKilled(void)
{
	return enemiesKilled;
}

/*!
@brief	Increment the amount of enemies killed to check if 
		current wave can still spawn enemies
*//*____________________________________________________________*/
void IncrementEnemiesSpawned(void)
{
	++enemiesSpawned;
}

/*!
@brief	Get the total amount of enemies spawned for the current wave

@return Amount of enemeis spawned
*//*____________________________________________________________*/
unsigned GetEnemiesSpawned(void)
{
	return enemiesSpawned;
}

/*!
@brief	Set enemies killed in the current wave to become 0
*//*____________________________________________________________*/
void ResetEnemiesKilled(void)
{
	enemiesKilled = 0;
}

/*!
@brief	Set enemies spawned in the current wave to become 0
*//*____________________________________________________________*/
void ResetEnemiesSpawned(void)
{
	enemiesSpawned = 0;
}

/*!
@brief	Render current wave number cleared
*//*____________________________________________________________*/
void RenderWaveCleared(void)
{
	if (!waveCleared)
		return;

	wave_clear_msg_dt -= CP_System_GetDt();
	if (wave_clear_msg_dt <= 0.0f)
	{
		waveCleared = False;
		wave_clear_msg_dt = WAVE_CLEARED_TIME;
	}
	sprintf_s(waveClearedInfo, sizeof(waveClearedInfo), "Wave %d cleared", wave_info);
	AddText(waveClearedInfo, HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT, GRID_SYSTEM_WIDTH, COLOR_RED, CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP, TOP_LAYER);
	SetEnemyRenderText("");
}

/*!
@brief	Reset relevant variables whenever a wave completes

@param	setAlreadyBuilt: status for alreadyBuilt
*//*____________________________________________________________*/
void ResetWave(Boolean setAlreadyBuilt)
{
	ResetEnemiesKilled();
	ResetEnemiesSpawned();
	SetAlreadyBuilt(setAlreadyBuilt);
	waveCleared = True;
	wave_info = *currWave += 1;
}

/*!
@brief	Spawn time for each enemies

@return Spawn time
*//*____________________________________________________________*/
float GetSpawnTime(void)
{
	return SPAWN_TIME;
}

/*!
@brief	Only allow one orthodox enemy to be alive every time
		Set isOrthodoxAlive to true when one is being spawned

@param	isAlive: true if spawning Orthodox enemy
*//*____________________________________________________________*/
void SetIsOrthodoxAlive(Boolean isAlive)
{
	isOrthodoxAlive = isAlive;
}

/*!
@brief	Check to see if the level currenly have one orthodox
		enemy alive

@return	returns true if one orthodox enemy is alive in the level
*//*____________________________________________________________*/
Boolean GetIsOrthodoxAlive(void)
{
	return isOrthodoxAlive;
}


/*!
@brief	Deallocate memory inside common_gameplay.c
*//*____________________________________________________________*/
void FreeCommonGameplay(void)
{
	
}