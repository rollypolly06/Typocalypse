/*!
file:	tower.h
author:	Lee Fu Sheng Roy

email:	f.lee@digipen.edu

brief:	includes all function declarations related to tower here.

	Copyright © 2020 DigiPen, All rights reserved.
		
*//*____________________________________________________________*/

#ifndef TOWER_H
#define TOWER_H

#include "enemy.h"
#include "quad.h"
#include "buttons.h"
#include "render_manager.h"
#include "grid_system.h"

// Radius of the defence tower
#define SLOW_RADIUS			100
#define FREEZE_RADIUS		100
#define AOE_RADIUS			100
#define GOLD_RADIUS			100

#define TOWER_WIDTH			100
#define TOWER_HEIGHT		150


#define SLOW_COST			15
#define FREEZE_COST			20
#define AOE_COST			25
#define GOLD_COST			30

#define MAX_TOWERS			20
#define FREEZE_TIME			4.0f

typedef enum TowerAbility{
	NO_ABILITIES = -1, TOWER_SLOW, TOWER_FREEZE, TOWER_AOE, TOWER_GOLD, TOTAL_ABILITIES
} TowerAbility;

typedef struct Tower
{
	Point position;
	float width;
	float height;
	CP_Image image;
	float radius;
	TowerAbility ability;
	Rect rect;
	int cost;
} Tower;

// calls GetEnemy() to store Enemy address of those in tower's range
void InTowerRange(void);

// reduce the speed of all addresses in the slowEnemies array
void SlowTower(void);

// Increases the gold drop of enemies eliminated within radius
void GoldTower(void);

// Gets address of all enemies in the area selected and store in freezeEnemies Array
void FreezeArray(void);

// Renders a blue translucent circle indicating the area of freeze effect
void RenderFreezeRadius(void);

// All enemy addresses in the freezeEnemies array will have speed reduced to 0.0f
void Freeze(void);

// Kills all enemy within the radius of the AOE attack
void AoeAttack(void);

// Renders a red translucent circle indicating the area of freeze effect
void RenderAoeRadius(void);

// Set all Enemies array to NULL address
void ClearTowerArray(void);

// Load the images of the towers
void InitTower(void);

// Returns the cost of tower
int GetTowerCost(TowerAbility tAbility);

// set the values for Tower's image, position, width, height, radius and ability
// ability need to be passed as argument to determine the radius and ability type of tower
void CreateTower(TowerAbility ability, Point mouse);

// reset the size of the tower's grid
Grid GetTowerGrid(TowerAbility ability);

// Draw image of 1 tower
// Called by TowersRender() function
void DrawTower(Tower* tower);

// Calls DrawTower to render all existing towers onto screen
void TowersRender(void);

// Returns which image to be loaded depending on ability
// Called by CreateTower() function to initialize tower's image
CP_Image TowerImage(TowerAbility tAbility);

// Returns the radius of tower depending on ability
// Called by CreateTower() function to initialize tower's radius
float TowerRadius(TowerAbility tAbility);

// Renders the type of tower with its radius if available
// Called only in TowerUpdate()
void DrawTowerWithRadius(TowerAbility tAbility);

// Sets if there is any AOE towers placed or not in ui.h
void AOEPresent(Boolean boo);

// Sets if there is any Freeze towers placed or not in ui.h
void FreezePresent(Boolean boo);
#endif