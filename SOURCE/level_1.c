/*!
file:   level_1.c
author: Wong Man Cong
        Lee Fu Sheng Roy
        Phua Tze Cheng Jennifer
        Thea Sea
        Nicole Wong

email:  w.mancong@digipen.edu
        f.lee@digipen.edu
        p.tzechengjennifer@digipen.edu
        thea.sea@digipen.edu
        n.wong@digipen.edu

brief:  level 1 gameplay

Total: 80 enemies

	Copyright © 2020 DigiPen, All rights reserved.
//_____________________________________________________*/
#include "level_1.h"
#include "common_gameplay.h"

void level_1_wave_1(void);
void level_1_wave_2(void);
void level_1_wave_3(void);
void level_1_wave_4(void);
void level_1_win(void);

const void(*level_1_func_ptr[])(void) = { level_1_wave_1, level_1_wave_2, level_1_wave_3, level_1_wave_4, level_1_win };
int level_1_index;

float level_1_dt;

// how many enemies to kill before going to the next wave
int level_1_wave[] = { 15, 20, 20, 25 };

void level_1_init(void)
{
    unsigned sum = 0;
    for (int i = 0; i < ARRAY_SIZE(level_1_wave); ++i)
        sum += *(level_1_wave + i);

    CommonLevelInit("Assets/Levels/level_1.txt", "Assets/Levels/Waypoints/level_1_waypoints.txt", sum, ARRAY_SIZE(level_1_wave), &level_1_index, FOOD, LEVEL_1);
    level_1_index = 0;
    level_1_dt = GetSpawnTime();
}

void level_1_wave_1(void)
{
    if (GetEnemiesSpawned() < (unsigned)level_1_wave[level_1_index])
    {
        level_1_dt -= CP_System_GetDt();
        if (level_1_dt < 0.0f)
        {
            level_1_dt = GetSpawnTime();
            int random_chance = CP_Random_RangeInt(0, 9);
            // 10% chance to spawn speedy
            if (random_chance <= 0)
                SpawnEnemy(SPEEDY);
            // 90% chance to spawn normal
            else if (random_chance >= 1)
                SpawnEnemy(NORMAL);
            IncrementEnemiesSpawned();
        }
    }

    if (GetEnemiesKilled() >= (unsigned)level_1_wave[level_1_index])
    {        
        level_1_dt = GetSpawnTime();
        ResetWave(False);
    }
}

void level_1_wave_2(void)
{
    if (GetEnemiesSpawned() < (unsigned)level_1_wave[level_1_index])
    {
        level_1_dt -= CP_System_GetDt();
        if (level_1_dt < 0.0f)
        {
            level_1_dt = GetSpawnTime();
            int random_chance = CP_Random_RangeInt(0, 9);
            // 20% chance to spawn speedy
            if (random_chance <= 1)
                SpawnEnemy(SPEEDY);
            // 80% chance to spawn normal
            else if (random_chance >= 2)
                SpawnEnemy(NORMAL);
            IncrementEnemiesSpawned();
        }
    }

    if (GetEnemiesKilled() >= (unsigned)level_1_wave[level_1_index])
    {
        level_1_dt = GetSpawnTime();
        ResetWave(False);
    }
}

void level_1_wave_3(void)
{
    if (GetEnemiesSpawned() < (unsigned)level_1_wave[level_1_index])
    {
        level_1_dt -= CP_System_GetDt();
        if (level_1_dt < 0.0f)
        {
            level_1_dt = GetSpawnTime();
            int random_chance = CP_Random_RangeInt(0, 9);
            // 40% chance to spawn speedy
            if (random_chance <= 3)
                SpawnEnemy(SPEEDY);
            // 60% chance to spawn normal
            else if (random_chance >= 4)
                SpawnEnemy(NORMAL);
            IncrementEnemiesSpawned();
        }
    }

    if (GetEnemiesKilled() >= (unsigned)level_1_wave[level_1_index])
    {
        level_1_dt = GetSpawnTime();
        ResetWave(False);
    }
}

void level_1_wave_4(void)
{
    if (GetEnemiesSpawned() < (unsigned)level_1_wave[level_1_index])
    {
        level_1_dt -= CP_System_GetDt();
        if (level_1_dt < 0.0f)
        {
            level_1_dt = GetSpawnTime();
            int random_chance = CP_Random_RangeInt(0, 9);
            // 40% chance to spawn speedy
            if (random_chance <= 3)
                SpawnEnemy(SPEEDY);
            // 50% chance to spawn normal
            else if (random_chance >= 4 && random_chance <= 8)
                SpawnEnemy(NORMAL);
            // 10% chance to spawn orthodox
            else if (random_chance >= 9)
            {
                if (!GetIsOrthodoxAlive())
                {
                    SpawnEnemy(ORTHODOX);
                    SetIsOrthodoxAlive(True);
                }
                else
                {
                    random_chance = CP_Random_RangeInt(0, 1);
                    if (random_chance <= 0)
                        SpawnEnemy(SPEEDY);
                    else
                        SpawnEnemy(NORMAL);
                }
            }
            IncrementEnemiesSpawned();
        }
    }

    if (GetEnemiesKilled() >= (unsigned)level_1_wave[level_1_index])
    {
        level_1_dt = GetSpawnTime();
        ResetWave(True);    // hard code this true value
    }
}

void level_1_win(void)
{
    WinScreenUpdate();
}

void level_1_update(void)
{
    GameState currState = CommonLevelUpdate();
    if (currState != PLAYING)
        return;
    level_1_func_ptr[level_1_index]();
}

void level_1_exit(void)
{

}
