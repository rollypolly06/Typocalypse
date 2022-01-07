/*!
file:  enemy.h
authors:  Wong Man Cong
          Phua Tze Cheng Jennifer

emails:  w.mancong@digipen.edu
        p.tzechengjennifer@digipen.edu

brief:  Declarations for enemy mechanics for the game

	Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#ifndef ENEMY_H
#define ENEMY_H

#include "common_headers.h"
#include "word_generator.h"
#include "gold.h"
//Enemy sizes
#define ENEMY_SIZE			50  //array
#define MIN_DIST			2.0f
#define MIN_DIST_NEG		-2.0f
#define DEFAULT_SPD			3.0f
#define ENEMY_WIDTH			50.0f
#define ENEMY_HEIGHT		50.0f

//enum for enemy types
typedef enum EnemyType {
    NO_TYPE = -1,
    NORMAL,
    SPEEDY,
    ORTHODOX,
    TOTAL_ENEMIES,
}EnemyType;

//enum for enemy sizes
typedef enum EnemyStatus {
    NONE_STATUS = -1,
    ENEMY_FROZEN,
    ENEMY_SLOW,
    ENEMY_SPEDUP,
}EnemyStatus;

//struct for waypoints
typedef struct Waypoint {
    Point position;
} Waypoint;

//struct for enemies
typedef struct Enemy {
    EnemyType enemyType;
    float speed;
    //char* word;
    float width;
    float height;
    int wp;
    unsigned id;
    int gold;
    int opacity;
    unsigned attack;
    float dir;
    EnemyStatus status;
    Boolean alive;
    Boolean damaged;        // check to see if enemy have damaged the player
    Point  position;
    Point prevPosition;     // to check for it's direction
    CP_Image img;
} Enemy;

//struct for animation for gold
typedef struct AnimGold {
    Point pos;
    int opacity;
    Boolean display;
} AnimGold;

//draw enemy, enemy point is in centre of actual drawn object
void RenderEnemy();
//draw gold
void RenderGold();
//get gold positions and put into array based on enemy position
void GetGoldPos(Point enemPos);
//kill and delete a specific enemy
void KillEnemy(Enemy* enemy);
//kill and deltete multiple enemies at once
void KillEnemies(Enemy** enemy);
//init enemy data such as waypoint positions and spawn locations
void EnemyInit(const char* filePath);
//gets called every update
void EnemyUpdate();
//return number of live enemies
int GetAliveEnemies();
//return default speed for each enemy type
float GetEnemyDefaultSpeed(EnemyType type);
//spawn enemy of specific type
void SpawnEnemy(EnemyType enemType);
//checks if player is currently being hindered from typing
Boolean TypingHindered();
//returns remaining time player will be hindered for
float GetRemainingHinderTime();


#endif