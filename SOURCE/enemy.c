/*!
file:    enemy.c
authors: Wong Man Cong
         Phua Tze Cheng Jennifer

emails:  w.mancong@digipen.edu
         p.tzechengjennifer@digipen.edu

brief:   Definitions for enemy mechanics for the game

	Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/

#include "enemy.h"
#include "common_headers.h"
#include "word_generator.h"
#include "geometry.h"
#include "player.h"
#include "text_render.h"
#include "quad.h"

int wpNum = 0;
int enemyId = 0;

int maxEnemyType = 5;
float spawnRate = 1.0f;
int alives = 0;
float xSpawn = 0.0f;
float ySpawn = 0.0f;
float defaultSpd[TOTAL_ENEMIES] = { 100.f, 120.0f, 75.0f };
int defaultGold[TOTAL_ENEMIES] = { 3, 5, 7 };
float speedyRadius;
int goldDisplayCount = 0;
int goldOpacity = 0;

float xDist;
float yDist;
float dt = 0;
float hinderDt = 0;
float hinderTime = 3.0f; //amount of time player will get hindered
float hinderCooldown = 10.0f;
float hinderCooldownTimer = 0.0f;

CP_Image non_status_enemy[TOTAL_ENEMIES];
CP_Image frozen_enemy[TOTAL_ENEMIES];
CP_Image slowed_enemy[TOTAL_ENEMIES];
CP_Image goldImg;

Vector movement;
Waypoint* waypoints;
Enemy* enemies; //array of enemies
AnimGold golds[ENEMY_SIZE];

Enemy* allenemies[ENEMY_SIZE] = { NULL }; //array to pointers to enemies

// Grid System
Point GetPositionOnGrid(Point pos, unsigned size_x, unsigned size_y);
// Player's health
void HealthDeplete(unsigned int amount);
// Common gameplay variables
void IncrementEnemiesKilled(void);
void SetIsOrthodoxAlive(Boolean isAlive);

//put all images inside image array
void RenderInit() {

    goldImg = CP_Image_Load("Assets/Image/Gold/Coin.png");

    non_status_enemy[0] = CP_Image_Load("Assets/Image/enemies/normal.png");
    non_status_enemy[1] = CP_Image_Load("Assets/Image/enemies/speedy.png");
    non_status_enemy[2] = CP_Image_Load("Assets/Image/enemies/orthodox.png");

    frozen_enemy[0] = CP_Image_Load("Assets/Image/enemies/frozen_normal.png");
    frozen_enemy[1] = CP_Image_Load("Assets/Image/enemies/frozen_speedy.png");
    frozen_enemy[2] = CP_Image_Load("Assets/Image/enemies/frozen_orthodox.png");

    slowed_enemy[0] = CP_Image_Load("Assets/Image/enemies/slow_normal.png");
    slowed_enemy[1] = CP_Image_Load("Assets/Image/enemies/slow_speedy.png");
    slowed_enemy[2] = CP_Image_Load("Assets/Image/enemies/slow_orthodox.png");
}

// if get cursor input, insert as waypoint
void MakeWayPoint(float x, float y) {

    waypoints[wpNum].position.x = x;
    waypoints[wpNum].position.y = y;
    wpNum++;
}

//reset all enemy values to default
void ResetEnemy() {
    dt = 0.0f;
    wpNum = 0;
    enemyId = 0;
    alives = 0;
    xDist = 0.0f;
    yDist = 0.0f;
    maxEnemyType = 5;
    goldDisplayCount = 0;

    // default value for enemies array
    for (int i = 0; i < ENEMY_SIZE; ++i) {
        enemies[i].enemyType = NO_TYPE;
        enemies[i].speed = 0.0f;
        enemies[i].width = 0.0f;
        enemies[i].height = 0.0f;
        enemies[i].wp = -1;
        enemies[i].id = 0;
        enemies[i].attack = 0;
        enemies[i].alive = False;
        enemies[i].damaged = False;
        enemies[i].position.x = 0.0f;
        enemies[i].position.y = 0.0f;
        enemies[i].dir = 1.0f;
        enemies[i].prevPosition = enemies[i].position;
        enemies[i].img = NULL;
        enemies[i].enemyType = NORMAL;
        enemies[i].status = NONE_STATUS;
        enemies[i].gold = 0;
        enemies[i].opacity = 255;
    }
}

//reset every alive enemy's speed, gold and status
void ResetEnemSpdGold() {
    for (int i = 0; i < alives; i++) {
        enemies[i].gold = defaultGold[enemies[i].enemyType];
        enemies[i].speed = defaultSpd[enemies[i].enemyType];
        enemies[i].status = NONE_STATUS;
    }
}

//spawn an enemy of a certain type given by input parameter
void SpawnEnemy(EnemyType enemType) {
    if (alives < ENEMY_SIZE)
    {
        //default values for all enemies
        enemies[alives].wp = 0;
        enemies[alives].position.x = xSpawn;
        enemies[alives].position.y = ySpawn;
        enemies[alives].prevPosition = enemies[alives].position;
        enemies[alives].dir = 1.0f;
        enemies[alives].alive = True;
        enemies[alives].damaged = False;
        enemies[alives].width = ENEMY_WIDTH;
        enemies[alives].height = ENEMY_HEIGHT;
        enemies[alives].id = ++enemyId;
        enemies[alives].status = NONE_STATUS;
        enemies[alives].opacity = ALPHA;

        switch (enemType) {
        case NORMAL:
            enemies[alives].enemyType = NORMAL;
            enemies[alives].attack = 5;
            enemies[alives].img = non_status_enemy[0]; //normal monster img
            enemies[alives].speed = defaultSpd[enemType];
            enemies[alives].gold = defaultGold[enemType];
            break;
        case SPEEDY:
            enemies[alives].enemyType = SPEEDY;
            enemies[alives].attack = 7;
            enemies[alives].img = non_status_enemy[1]; //brown monster
            enemies[alives].speed = defaultSpd[enemType];
            enemies[alives].gold = defaultGold[enemType];
            break;
        case ORTHODOX:
            enemies[alives].enemyType = ORTHODOX;
            enemies[alives].attack = 12;
            enemies[alives].img = non_status_enemy[2]; //big grey monster
            enemies[alives].speed = defaultSpd[enemType];
            enemies[alives].gold = defaultGold[enemType];
            break;
        }
        dt = 0.0f;
        alives++;
    }
}

#if TEST_MODE
//draw waypoints 
void RenderWaypoints() {
    for (int i = 0; i < wpNum; i++) {
        AddRect(waypoints[i].position.x, waypoints[i].position.y, GRID_SYSTEM_WIDTH, GRID_SYSTEM_HEIGHT, 0.1f, CP_Color_Create(255, 255, 255, 75), TOP_LAYER);
    }
}
#endif

//determines which ways enemies should move based on current waypoint + speed
void EnemyMovement() {
    for (int i = 0; i < alives; i++) {
        xDist = waypoints[enemies[i].wp].position.x - enemies[i].position.x;
        yDist = waypoints[enemies[i].wp].position.y - enemies[i].position.y;

        if (xDist > MIN_DIST_NEG && xDist < MIN_DIST && yDist > MIN_DIST_NEG && yDist < MIN_DIST)
            enemies[i].wp++;

        else {
            movement = NormalizedVector(GetVector(waypoints[enemies[i].wp].position, enemies[i].position));
            enemies[i].position.x += (movement.x * enemies[i].speed) * CP_System_GetDt();
            enemies[i].position.y += (movement.y * enemies[i].speed) * CP_System_GetDt();
        }

        if (enemies[i].enemyType != SPEEDY) {
            if (enemies[i].position.x < enemies[i].prevPosition.x)
                enemies[i].dir = 1.0f;
            else if (enemies[i].position.x > enemies[i].prevPosition.x)
                enemies[i].dir = -1.0f;
        }

        if (enemies[i].wp >= wpNum) {
            enemies[i].speed = 0; //enemy stops at last waypoint
            enemies[i].opacity -= 25;
            // deplete player health
            if (!enemies[i].damaged)
            {
                HealthDeplete(enemies[i].attack);
                enemies[i].damaged = True;
            }
            if (enemies->opacity <= 25)
                KillEnemy(&enemies[i]);
        }
        enemies[i].prevPosition = enemies[i].position;
    }
}

//determines which sprite to display for enemy depending on status and type
CP_Image GetEnemySprite(EnemyStatus status, EnemyType type) {
    switch (type)
    {
    case NORMAL:
    {
        switch (status) {
        case NONE_STATUS:
            return non_status_enemy[type];
        case ENEMY_FROZEN:
            return frozen_enemy[type];
        case ENEMY_SLOW:
            return slowed_enemy[type];
        }
    }
    case SPEEDY: {
        switch (status) {
        case NONE_STATUS:
            return non_status_enemy[type];
        case ENEMY_FROZEN:
            return frozen_enemy[type];
        case ENEMY_SLOW:
            return slowed_enemy[type];
        }
    }
    case ORTHODOX: {
        switch (status) {
        case NONE_STATUS:
            return non_status_enemy[type];
        case ENEMY_FROZEN:
            return frozen_enemy[type];
        case ENEMY_SLOW:
            return slowed_enemy[type];
        }
    }
    default:
        break;
    }
    return NULL;
}

//draw enemy, enemy point is in centre of actual drawn object
void RenderEnemy() {
    for (int i = 0; i < alives; i++) { //check through spawned enemy
        AddSprite(GetEnemySprite(enemies[i].status, enemies[i].enemyType), enemies[i].position.x + GRID_SYSTEM_WIDTH * 0.5f, enemies[i].position.y, enemies[i].dir * enemies[i].width, enemies[i].height, (unsigned char)enemies[i].opacity, ENEMY_LAYER);
    }
}

//put gold positions into golds array based on enemy location
void GetGoldPos(Point enemPos)
{
    golds[goldDisplayCount].pos = enemPos;
    golds[goldDisplayCount].opacity = 0;
    golds[goldDisplayCount].display = True;
    ++goldDisplayCount;
}

//display gold coins on screen and animate them
void RenderGold()
{
    for (int i = 0; i < goldDisplayCount; ++i) {
        if (golds[i].display == True) {
            AddSprite(goldImg, golds[i].pos.x + GRID_SYSTEM_WIDTH * 0.5f, golds[i].pos.y + GRID_SYSTEM_WIDTH * 0.5f, 35.0f, 35.0f, golds[i].opacity, ENEMY_LAYER);
            AddSprite(goldImg, golds[i].pos.x + GRID_SYSTEM_WIDTH * 0.2f, golds[i].pos.y + GRID_SYSTEM_WIDTH * 0.2f, 35.0f, 35.0f, golds[i].opacity, ENEMY_LAYER);
            AddSprite(goldImg, golds[i].pos.x + GRID_SYSTEM_WIDTH * 0.7f, golds[i].pos.y + GRID_SYSTEM_WIDTH * 0.7f, 35.0f, 35.0f, golds[i].opacity, ENEMY_LAYER);
            if (golds[i].opacity <= 100) {
                golds[i].pos.x -= 1;
                golds[i].pos.y -= 5;
            }
            golds[i].pos.y += 3;
            golds[i].pos.x -= 1;
            golds[i].opacity += 8;

            if (golds[i].opacity >= 255)
                golds[i].display = False;
        }
    }
    if (goldDisplayCount > ENEMY_SIZE)
        goldDisplayCount = 0;
}

//speeds up enemies around speedy enemies
void SpeedyAbility(int index, unsigned id) {
    //insert enemies within radius into allenemies
    GetEnemy(allenemies, enemies[index].position, speedyRadius);

    //check for enemies in radius and increase speed
    for (int i = 0; i < ENEMY_SIZE; ++i)
    {
        if (allenemies[i] == NULL)
            break;
        if (allenemies[i]->id == (unsigned)id)
            continue;
        if (allenemies[i]->status != ENEMY_FROZEN)
            allenemies[i]->speed = 1.5f * defaultSpd[allenemies[i]->enemyType];
    }
}

//hinders player from typing
void OrthodoxAbility() {
    hinderDt += CP_System_GetDt(); //count time of ability 
    if (hinderDt >= hinderTime) {
        hinderCooldownTimer = hinderCooldown;
        hinderDt = 0;
    }
}

//counts cooldown of orthodox ability
void OrthodoxCooldown() {
    hinderCooldownTimer -= CP_System_GetDt(); //count cooldown
}

//check if player is still being hidnered from typing
Boolean TypingHindered() {
    if (hinderDt < hinderTime && hinderDt > 0) //still being hindered
        return True;
    return False;
}

//get how much more time player is going to be hindered
float GetRemainingHinderTime() {
    return (hinderTime - hinderDt);
}

//clear enemy array of elements
void ClearEnemyArray() {
    for (int i = 0; i < ENEMY_SIZE; ++i)
    {
        if (allenemies[i] == NULL)
            break;
        allenemies[i] = NULL;
    }
}

//shift dead enemies to back of array
int RearrangeEnemyArray() {
    Enemy tmp[ENEMY_SIZE];

    for (int i = 0; i < ENEMY_SIZE; ++i) {
        tmp[i].enemyType = NO_TYPE;
        tmp[i].speed = 0.0f;
        tmp[i].width = 0.0f;
        tmp[i].height = 0.0f;
        tmp[i].wp = -1;
        tmp[i].id = 0;
        tmp[i].attack = 0;
        tmp[i].alive = False;
        tmp[i].damaged = False;
        tmp[i].position.x = 0.0f;
        tmp[i].position.y = 0.0f;
        tmp[i].prevPosition = tmp[i].position;
        tmp[i].dir = 1.0f;
        tmp[i].img = NULL;
        tmp[i].gold = 0;
        tmp[i].status = NONE_STATUS;
        tmp[i].opacity = 0;
        tmp[i].enemyType = NORMAL;
    }

    int count = 0, index = 0;
    for (int i = 0; i < alives; ++i) {
        if (!(enemies + i) || !(enemies + i)->alive)
            continue;
        tmp[index++] = enemies[i];
        ++count;
    }

    for (int i = 0; i < alives; ++i) {
        enemies[i] = tmp[i];
    }

    return count;
}

//kill a specific enemy, resetting its values and deleting it
void KillEnemy(Enemy* enemy) {
    if (enemy->wp < wpNum) {
        GetGoldPos(enemy->position);
        GoldAdd(enemy->gold);
    }
    DeleteEnemy(enemy->id);

    if (enemy->enemyType == ORTHODOX)
        SetIsOrthodoxAlive(False);

    enemy->enemyType = NO_TYPE;
    enemy->speed = 0.0f;
    enemy->width = 0.0f;
    enemy->height = 0.0f;
    enemy->wp = -1;
    enemy->id = 0;
    enemy->attack = 0;
    enemy->alive = False;
    enemy->damaged = False;
    enemy->position.x = 0.0f;
    enemy->position.y = 0.0f;
    enemy->prevPosition = enemy->position;
    enemy->dir = 1.0f;
    enemy->img = NULL;
    enemy->gold = 0;
    enemy->opacity = 0;

    IncrementEnemiesKilled();
    alives = RearrangeEnemyArray();
}

//kill multiple enemies at once, resetting their values and deleting them
void KillEnemies(Enemy** enemy) {
    for (int i = 0; i < ENEMY_SIZE; ++i)
    {
        if (!enemy[i])
            break;
        GoldAdd(enemy[i]->gold);
        GetGoldPos(enemy[i]->position);

        DeleteEnemy(enemy[i]->id);

        if (enemy[i]->enemyType == ORTHODOX)
            SetIsOrthodoxAlive(False);

        //do this once enemy animation ends
        enemy[i]->enemyType = NO_TYPE;
        enemy[i]->speed = 0.0f;
        enemy[i]->width = 0.0f;
        enemy[i]->height = 0.0f;
        enemy[i]->wp = -1;
        enemy[i]->id = 0;
        enemy[i]->attack = 0;
        enemy[i]->alive = False;
        enemy[i]->damaged = False;
        enemy[i]->position.x = 0.0f;
        enemy[i]->position.y = 0.0f;
        enemy[i]->prevPosition = enemy[i]->position;
        enemy[i]->dir = 1.0f;
        enemy[i]->img = NULL;
        enemy[i]->gold = 0;
        enemy[i]->status = NONE_STATUS;
        enemy[i]->opacity = 0;
        enemy[i]->enemyType = NORMAL;

        IncrementEnemiesKilled();
    }
    alives = RearrangeEnemyArray();
}

//render everything
void Render() {
#if TEST_MODE
    RenderWaypoints();
#endif
    RenderEnemy();
    RenderGold();
}

//get number of enemies that are still alive
int GetAliveEnemies() {
    return alives;
}

//call functions for enemy abilities depending on what enemies are currently onscreen
void CastAbilities() {
    for (int i = 0; i < alives; i++) {
        if (enemies[i].enemyType == SPEEDY)
            SpeedyAbility(i, enemies[i].id);
        else if ((enemies[i].enemyType == ORTHODOX) && hinderCooldownTimer <= 0)
            OrthodoxAbility();
        else if ((enemies[i].enemyType == ORTHODOX) && hinderCooldownTimer >= 0)
            OrthodoxCooldown();
    }
}

//return default speed of an enemy type
float GetEnemyDefaultSpeed(EnemyType type)
{
    return defaultSpd[type];
}

//init data for enemies like waypoint and spawn positions 
void EnemyInit(const char* filePath) {
    RenderInit();
    enemies = (Enemy*)malloc(sizeof(Enemy) * ENEMY_SIZE);
    ResetEnemy();

    FileData fd = ReadFiles(filePath);
    if (fd)
    {
        int wp_size = (int)(fd->rows * 0.5f);
        waypoints = (Waypoint*)malloc(sizeof(Waypoint) * wp_size);
        for (unsigned i = 0; i < fd->rows; i += 2)
        {
            float x = (float)atoi(fd->str[i]);
            float y = (float)atoi(fd->str[i + 1]);
            Point p = { x, y };
            p = GetPositionOnGrid(p, 1, 1);
            p.x -= GRID_SYSTEM_WIDTH * 0.5f;
            p.y -= GRID_SYSTEM_HEIGHT * 0.5f;
            MakeWayPoint(p.x, p.y);
        }

        // spawn location be their first way point
        Point p = { (float)atoi(fd->str[0]), (float)atoi(fd->str[1]) };
        p = GetPositionOnGrid(p, 1, 1);
        xSpawn = p.x - GRID_SYSTEM_WIDTH * 0.5f;
        ySpawn = p.y - GRID_SYSTEM_HEIGHT * 0.5f;
    }
    FreeFileData(&fd);

    speedyRadius = GRID_SYSTEM_WIDTH * 3.0f;

    if (GetGameDifficulty() != HARD) // <------ disable global typing if game difficulty is hard
        InitPlayerEnemyReference(&enemies); // <------- for game mode easy and medium
    InitQuadTreeEnemyReference(enemies);
}

//gets called every update
void EnemyUpdate() {
    CastAbilities();
    EnemyMovement();
    Render();
    ResetEnemSpdGold();
    ClearEnemyArray();

    if (CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT))
        SpawnEnemy(NORMAL);
}

//free pointers to prevent memory leaks
void FreeEnemy() {
    for (int i = 0; i < TOTAL_ENEMIES; ++i) {
        if (non_status_enemy[i]) {
            CP_Image_Free(&non_status_enemy[i]);
            CP_Image_Free(&frozen_enemy[i]);
            CP_Image_Free(&slowed_enemy[i]);
        }
    }

    if (waypoints) {
        free(waypoints);
        waypoints = NULL;
    }

    if (enemies)
    {
        free(enemies);
        enemies = NULL;
    }

}
