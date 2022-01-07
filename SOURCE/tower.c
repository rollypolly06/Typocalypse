/*!
file:	tower.c
author:	Lee Fu Sheng Roy

email:	f.lee@digipen.edu

brief:	includes all function related to tower here. The functions
		here executes creating of tower, placing down of tower and
		initializing of towers

	Copyright © 2020 DigiPen, All rights reserved.

*//*____________________________________________________________*/
#include "tower.h"
#include "ui.h"

Tower* tPtr[MAX_TOWERS] = { NULL };
int towerIndex = 0;
CP_Image towerImages[TOTAL_ABILITIES];
Enemy* typeEnemies[ENEMY_SIZE] = { NULL };
Enemy* slowEnemies[ENEMY_SIZE] = { NULL };
Enemy* freezeEnemies[ENEMY_SIZE] = { NULL };
Enemy* goldEnemies[ENEMY_SIZE] = { NULL };
Enemy* aoeEnemies[ENEMY_SIZE] = { NULL };

Grid towerGridSize[TOTAL_ABILITIES] = { { 2, 2, TOWER }, { 3, 2, TOWER }, { 3, 3, TOWER }, { 4, 3, TOWER } };

int totalEnemiesInTypeArray;

/*!
@brief -	Initializes the Images of the towers by loading the images with its
			respective filepath name
*//*_____________________________________________________________________________*/
void InitTower(void)
{
	for (int i = 0; i < MAX_TOWERS; ++i)
		tPtr[i] = NULL;
	towerIndex = 0;
	towerImages[TOWER_SLOW] = CP_Image_Load("Assets/Image/Towers/TowerSlow.png");
	towerImages[TOWER_FREEZE] = CP_Image_Load("Assets/Image/Towers/TowerFreeze.png");
	towerImages[TOWER_AOE] = CP_Image_Load("Assets/Image/Towers/TowerAoe.png");
	towerImages[TOWER_GOLD] = CP_Image_Load("Assets/Image/Towers/TowerGold.png");

	if (GetGameDifficulty() == HARD) 
		InitPlayerEnemyReference(typeEnemies);

	totalEnemiesInTypeArray = 0;
}

/*!
@brief -	Checks nearby enemies if they are in the tower's radius. Enemies in
			range added to an array to be killed or affected by abilities.
*//*_____________________________________________________________________________*/
void InTowerRange(void)
{
	ClearTowerArray(); // Clears all array to NULL first

	for (int i = 0; i < MAX_TOWERS; ++i)
	{
		if (tPtr[i] == NULL)
			break;

		if(GetGameDifficulty() == HARD)
			GetEnemy(typeEnemies, tPtr[i]->position, tPtr[i]->radius);
		switch (tPtr[i]->ability)
		{
		case TOWER_SLOW:
			GetEnemy(slowEnemies, tPtr[i]->position, tPtr[i]->radius);
			break;
		case TOWER_GOLD:
			GetEnemy(goldEnemies, tPtr[i]->position, tPtr[i]->radius);
			break;
		}
	}

	totalEnemiesInTypeArray = 0;
	for (int i = 0; i < ENEMY_SIZE; ++i)
	{
		if (typeEnemies[i] && typeEnemies[i]->alive)
			++totalEnemiesInTypeArray;
	}
}

/*!
@brief -	Returns the number of Enemy addresses stored in totalEnemiesInTypeArray
*//*_____________________________________________________________________________*/
int GetTotalEnemiesInTypeArray(void)
{
	return totalEnemiesInTypeArray;
}

/*!
@brief -	Slows down the enemies that are within range of the Slow tower
*//*_____________________________________________________________________________*/
void SlowTower(void)
{
	for (int i = 0; i < ENEMY_SIZE; ++i)
	{
		if (slowEnemies[i] == NULL)
			break;
		slowEnemies[i]->speed = slowEnemies[i]->speed * 0.7f;
		slowEnemies[i]->status = ENEMY_SLOW;
	}
}

/*!
@brief -	Increases the gold drop amount of the enemies that are within range
			of the gold tower
*//*_____________________________________________________________________________*/void GoldTower(void)
{
	for (int i = 0; i < ENEMY_SIZE; ++i)
	{
		if (goldEnemies[i] == NULL)
			break;
		goldEnemies[i]->gold = goldEnemies[i]->gold * 2;
	}
}

/*!
@brief -	Gets the address of enemies that are within range of the freeze tower
			and stores them in the freezeEnemies array
*//*_____________________________________________________________________________*/
void FreezeArray(void)
{
	//Point mouse;
	//mouse.x = CP_Input_GetMouseX();
	//mouse.y = CP_Input_GetMouseY();
	printf("freeze\n");
	for (int i = 0; i < ENEMY_SIZE; ++i)
	{
		if (freezeEnemies[i] == NULL)
			continue;
		freezeEnemies[i] = NULL;
	}
	for (int i = 0; i < MAX_TOWERS; ++i)
	{
		if (!tPtr[i])
			return;
		if (tPtr[i]->ability == TOWER_FREEZE)
		{
			GetEnemy(freezeEnemies, tPtr[i]->position, TowerRadius(TOWER_FREEZE));
			AddCircle(tPtr[i]->position.x, tPtr[i]->position.y, TowerRadius(TOWER_FREEZE), 0.1f, COLOR_BLUE, RADIUS_LAYER);
		}
	}	
}

/*!
@brief -	Freezes the enemies that are within range of the freeze tower
*//*_____________________________________________________________________________*/
void Freeze(void)
{
	for (int i = 0; i < ENEMY_SIZE; ++i)
	{
		if (freezeEnemies[i] == NULL)
			break;
		freezeEnemies[i]->speed = 0.0f;
		freezeEnemies[i]->status = ENEMY_FROZEN;
		//printf("id: %d\n", freezeEnemies[i]->id);
	}
	//printf("freezing in Freeze function\n");
}

/*!
@brief -	Renders a translucent blue circle that represent the freeze radius.
*//*_____________________________________________________________________________*/
void RenderFreezeRadius(void)
{
	AddCircle(CP_Input_GetMouseX(), CP_Input_GetMouseY(), FREEZE_RADIUS, 0.1f, TRANSLUCENT_BLUE, RADIUS_LAYER);
}

/*!
@brief -	Gets the address of enemies that are within range of the AOE tower
			and stores them in the aoeEnemies array
*//*_____________________________________________________________________________*/
void AoeAttack(void)
{
	//Point mouse;
	//mouse.x = CP_Input_GetMouseX();
	//mouse.y = CP_Input_GetMouseY();
	for (int i = 0; i < ENEMY_SIZE; ++i)
	{
		if (aoeEnemies[i] == NULL)
			continue;
		aoeEnemies[i] = NULL;
	}

	for (int i = 0; i < MAX_TOWERS; ++i)
	{
		if (!tPtr[i])
			continue;
		if (tPtr[i]->ability == TOWER_AOE)
		{
			GetEnemy(aoeEnemies, tPtr[i]->position, TowerRadius(TOWER_AOE));
			AddCircle(tPtr[i]->position.x, tPtr[i]->position.y, TowerRadius(TOWER_AOE), 0.1f, COLOR_RED, RADIUS_LAYER);
		}
	}
	KillEnemies(aoeEnemies);
}

/*!
@brief -	Renders a translucent red circle that represent the AOE radius.
*//*_____________________________________________________________________________*/
void RenderAoeRadius(void)
{
	AddCircle(CP_Input_GetMouseX(), CP_Input_GetMouseY(), AOE_RADIUS, 0.1f, TRANSLUCENT_RED, RADIUS_LAYER);
}

/*!
@brief -	Clears out every ability array and type array byt setting it to NULL
*//*_____________________________________________________________________________*/
void ClearTowerArray(void)
{
	for (int i = 0; i < ENEMY_SIZE; ++i)
	{
		if (typeEnemies[i] == NULL)
			break;
		typeEnemies[i] = NULL;
	}
	for (int i = 0; i < ENEMY_SIZE; ++i)
	{
		if (slowEnemies[i] == NULL)
			break;
		slowEnemies[i] = NULL;
	}
	for (int i = 0; i < ENEMY_SIZE; ++i)
	{
		if (aoeEnemies[i] == NULL)
			break;
		aoeEnemies[i] = NULL;
	}
	for (int i = 0; i < ENEMY_SIZE; ++i)
	{
		if (goldEnemies[i] == NULL)
			break;
		goldEnemies[i] = NULL;
	}
}

/*!
@brief -	Returns the cost of tower based on their tAbility
@param -	The type of tower
*//*_____________________________________________________________________________*/
int GetTowerCost(TowerAbility tAbility)
{
	switch (tAbility)
	{
		case TOWER_SLOW:
			return SLOW_COST;
			break;
		case TOWER_FREEZE:
			return FREEZE_COST;
			break;
		case TOWER_AOE:
			return AOE_COST;
			break;
		case TOWER_GOLD:
			return GOLD_COST;
			break;
	}
	return 0;
}

/*!
@brief -	Renders a translucent green circle centered at the base of tower
			based on their tAbility which indicates the tower's radius
@param -	The type of tower
*//*_____________________________________________________________________________*/
void DrawTowerWithRadius(TowerAbility tAbility)
{
	Point p = { (float)((int)(CP_Input_GetMouseX() / GRID_SYSTEM_WIDTH)), (float)((int)(CP_Input_GetMouseY() / GRID_SYSTEM_HEIGHT)) };

	float pos_x = (p.x * GRID_SYSTEM_WIDTH) + (GRID_SYSTEM_WIDTH * towerGridSize[tAbility].size_x * 0.5f);
	float pos_y = (p.y * GRID_SYSTEM_HEIGHT) + (GRID_SYSTEM_HEIGHT * towerGridSize[tAbility].size_y * 0.5f);

	CP_Color build_radius;
	if (GoldAmount() >= GetTowerCost(tAbility) && AbleToBuild(p, towerGridSize[tAbility]))
		build_radius = CP_Color_Create(0, 255, 0, 150);		// green outline
	else
		build_radius = CP_Color_Create(255, 0, 0, 150);		// red outline

	switch (tAbility)
	{
		case TOWER_SLOW:
			AddCircle(pos_x, pos_y, TowerRadius(TOWER_SLOW), 0.1f, TRANSLUCENT_GREEN, EDITING_LAYER);
			AddRect((int)p.x * GRID_SYSTEM_WIDTH, (int)p.y * GRID_SYSTEM_HEIGHT, GRID_SYSTEM_WIDTH * towerGridSize[tAbility].size_x, GRID_SYSTEM_HEIGHT * towerGridSize[tAbility].size_y, 0.5f, build_radius, ABLE_TO_BUILD_LAYER);
			AddSprite(towerImages[TOWER_SLOW], pos_x, pos_y, GRID_SYSTEM_WIDTH * towerGridSize[tAbility].size_x, GRID_SYSTEM_HEIGHT * towerGridSize[tAbility].size_y, 155, DRAW_TOWER_LAYER);
			break;
		case TOWER_FREEZE:
			AddCircle(pos_x, pos_y, TowerRadius(TOWER_FREEZE), 0.1f, TRANSLUCENT_GREEN, EDITING_LAYER);
			AddRect((int)p.x * GRID_SYSTEM_WIDTH, (int)p.y * GRID_SYSTEM_HEIGHT, GRID_SYSTEM_WIDTH * towerGridSize[tAbility].size_x, GRID_SYSTEM_HEIGHT * towerGridSize[tAbility].size_y, 0.5f, build_radius, ABLE_TO_BUILD_LAYER);
			AddSprite(towerImages[TOWER_FREEZE], pos_x, pos_y, GRID_SYSTEM_WIDTH * towerGridSize[tAbility].size_x, GRID_SYSTEM_HEIGHT * towerGridSize[tAbility].size_y, 155, DRAW_TOWER_LAYER);
			break;
		case TOWER_AOE:
			AddCircle(pos_x, pos_y, TowerRadius(TOWER_AOE), 0.1f, TRANSLUCENT_GREEN, EDITING_LAYER);
			AddRect((int)p.x * GRID_SYSTEM_WIDTH, (int)p.y * GRID_SYSTEM_HEIGHT, GRID_SYSTEM_WIDTH * towerGridSize[tAbility].size_x, GRID_SYSTEM_HEIGHT * towerGridSize[tAbility].size_y, 0.5f, build_radius, ABLE_TO_BUILD_LAYER);
			AddSprite(towerImages[TOWER_AOE], pos_x, pos_y, GRID_SYSTEM_WIDTH * towerGridSize[tAbility].size_x, GRID_SYSTEM_HEIGHT * towerGridSize[tAbility].size_y, 155, DRAW_TOWER_LAYER);
			break;
		case TOWER_GOLD:
			AddRect((int)p.x * GRID_SYSTEM_WIDTH, (int)p.y * GRID_SYSTEM_HEIGHT, GRID_SYSTEM_WIDTH * towerGridSize[tAbility].size_x, GRID_SYSTEM_HEIGHT * towerGridSize[tAbility].size_y, 0.5f, build_radius, ABLE_TO_BUILD_LAYER);
			AddCircle(pos_x, pos_y, TowerRadius(TOWER_GOLD), 0.1f, TRANSLUCENT_GREEN, EDITING_LAYER);
			AddSprite(towerImages[TOWER_GOLD], pos_x, pos_y, GRID_SYSTEM_WIDTH * towerGridSize[tAbility].size_x, GRID_SYSTEM_HEIGHT * towerGridSize[tAbility].size_y, 155, DRAW_TOWER_LAYER);
			break;
	}
}

/*!
@brief -	Draws the tower onto screen only if the tower has been initialized
*//*_____________________________________________________________________________*/
void DrawTower(Tower* tower)
{
	if (MouseInRect(tower->rect) && !GetIsEditing())
		AddCircle((*tower).position.x, (*tower).position.y, (*tower).radius, 0.1f, CP_Color_Create(255, 255, 255, 35), RADIUS_LAYER);
	else
		AddCircle((*tower).position.x, (*tower).position.y, (*tower).radius, 0.1f, CP_Color_Create(255, 255, 255, 15), RADIUS_LAYER);
	AddSprite((*tower).image, (*tower).position.x, (*tower).position.y, (*tower).width, (*tower).height, 255, TOWER_LAYER);
}

/*!
@brief -			Creates the tower by via malloc() and storing it in tPtr which
					is an array storing address of object type Tower. towerIndex
					is incremented with every successful creation of towers. The
					members of type Tower is also initialized here with the
					parameters

@param tAbility -	The type of tower to be created
@param p -			The position of the tower to be placed
*//*_____________________________________________________________________________*/
void CreateTower(TowerAbility tAbility, Point p)
{
	if (MAX_TOWERS <= towerIndex)
		return;
	float pos_x = (p.x * GRID_SYSTEM_WIDTH) + (GRID_SYSTEM_WIDTH * towerGridSize[tAbility].size_x * 0.5f);
	float pos_y = (p.y * GRID_SYSTEM_HEIGHT) + (GRID_SYSTEM_HEIGHT * towerGridSize[tAbility].size_y * 0.5f);
	float w = GRID_SYSTEM_WIDTH * towerGridSize[tAbility].size_x;
	float h = GRID_SYSTEM_HEIGHT * towerGridSize[tAbility].size_y;

	tPtr[towerIndex] = (Tower*)malloc(sizeof(Tower));
	if (!tPtr[towerIndex])
		return;
	tPtr[towerIndex]->image = TowerImage(tAbility);
	tPtr[towerIndex]->position.x = pos_x;
	tPtr[towerIndex]->position.y = pos_y;
	tPtr[towerIndex]->width = w;
	tPtr[towerIndex]->height = h;
	tPtr[towerIndex]->radius = TowerRadius(tAbility);
	tPtr[towerIndex]->ability = tAbility;
	tPtr[towerIndex]->rect.Min.x = pos_x - w * 0.5f;
	tPtr[towerIndex]->rect.Min.y = pos_y - h * 0.5f;
	tPtr[towerIndex]->rect.Max.x = pos_x + w * 0.5f;
	tPtr[towerIndex]->rect.Max.y = pos_y + h * 0.5f;
	tPtr[towerIndex]->cost = GetTowerCost(tAbility);

	towerIndex++;
}

/*!
@brief -			Resets the size of the tower's grid by returning an object of
					type Grid based on the type of tower

@param tAbility -	The type of tower
*//*_____________________________________________________________________________*/
Grid GetTowerGrid(TowerAbility ability)
{
	return towerGridSize[ability];
}

/*!
@brief -			Intializes the image member of Tower by returning image loaded
					and stored in an array of images

@param tAbility -	The type of tower
*//*_____________________________________________________________________________*/
CP_Image TowerImage(TowerAbility tAbility)
{
	switch (tAbility)
	{
		case TOWER_SLOW:
			return  towerImages[TOWER_SLOW];
		case TOWER_FREEZE:
			return  towerImages[TOWER_FREEZE];
		case TOWER_AOE:
			return  towerImages[TOWER_AOE];		
		case TOWER_GOLD:
			return  towerImages[TOWER_GOLD];
	}
	return NULL;
}

/*!
@brief -			Initializes the radius of Tower by returning a float based on
					the tAbility of the Tower

@param tAbility -	The type of tower
*//*_____________________________________________________________________________*/
float TowerRadius(TowerAbility tAbility)
{
	switch (tAbility)
	{
		case TOWER_SLOW:
			return  GRID_SYSTEM_WIDTH * ((float)towerGridSize[TOWER_SLOW].size_x + 0.75f);
		case TOWER_FREEZE:
			return  GRID_SYSTEM_WIDTH * ((float)towerGridSize[TOWER_FREEZE].size_x + 0.25f);
		case TOWER_AOE:
			return  GRID_SYSTEM_WIDTH * ((float)towerGridSize[TOWER_AOE].size_x);
		case TOWER_GOLD:
			return  GRID_SYSTEM_WIDTH * ((float)towerGridSize[TOWER_GOLD].size_x);
	}
	return 0;
}

/*!
@brief -	Renders all towers onto the window
*//*_____________________________________________________________________________*/
void TowersRender(void)
{
	for (int i = 0; i < MAX_TOWERS; ++i)
	{
		if (tPtr[i] == NULL) 
			break;
		DrawTower(tPtr[i]);
	}
}

/*!
@brief -	Frees allocated memory from heap for all tower. Called in
			pointer_manager.c
*//*_____________________________________________________________________________*/
void FreeTower(void)
{
	for (int i = 0; i < MAX_TOWERS; ++i)
	{
		if (tPtr[i] == NULL) break;

		free(tPtr[i]);
		tPtr[i] = NULL;
	}

	for (int i = 0; i < TOTAL_ABILITIES; ++i)
	{
		CP_Image_Free(&towerImages[i]);
	}
}