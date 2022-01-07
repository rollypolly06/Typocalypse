/*!
file:   level_2.c
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

brief:  level 2 gameplay

Total: 110 enemies

	Copyright © 2020 DigiPen, All rights reserved.
//_____________________________________________________*/
#include "level_2.h"
#include "common_gameplay.h"

void level_2_wave_1(void);
void level_2_wave_2(void);
void level_2_wave_3(void);
void level_2_wave_4(void);
void level_2_wave_5(void);
void level_2_win(void);

const void(*level_2_func_ptr[])(void) = { level_2_wave_1, level_2_wave_2, level_2_wave_3, level_2_wave_4, level_2_wave_5, level_2_win };
int level_2_index;

float level_2_dt;

// how many enemies to kill before going to the next wave
int level_2_wave[] = { 15, 15, 25, 25, 30 };

void level_2_init(void)
{
    unsigned sum = 0;
    for (int i = 0; i < ARRAY_SIZE(level_2_wave); ++i)
        sum += *(level_2_wave + i);

    CommonLevelInit("Assets/Levels/level_2.txt", "Assets/Levels/Waypoints/level_2_waypoints.txt", sum, ARRAY_SIZE(level_2_wave), &level_2_index, SPORTS, LEVEL_2);
    level_2_index = 0;
    level_2_dt = GetSpawnTime();
}

void level_2_wave_1(void)
{
    if (GetEnemiesSpawned() < (unsigned)level_2_wave[level_2_index])
    {
        level_2_dt -= CP_System_GetDt();
        if (level_2_dt < 0.0f)
        {
            level_2_dt = GetSpawnTime();
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

    if (GetEnemiesKilled() >= (unsigned)level_2_wave[level_2_index])
    {
        level_2_dt = GetSpawnTime();
        ResetWave(False);
    }
}

void level_2_wave_2(void)
{
    if (GetEnemiesSpawned() < (unsigned)level_2_wave[level_2_index])
    {
        level_2_dt -= CP_System_GetDt();
        if (level_2_dt < 0.0f)
        {
            level_2_dt = GetSpawnTime();
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

    if (GetEnemiesKilled() >= (unsigned)level_2_wave[level_2_index])
    {
        level_2_dt = GetSpawnTime();
        ResetWave(False);
    }
}

void level_2_wave_3(void)
{
    if (GetEnemiesSpawned() < (unsigned)level_2_wave[level_2_index])
    {
        level_2_dt -= CP_System_GetDt();
        if (level_2_dt < 0.0f)
        {
            level_2_dt = GetSpawnTime();
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

    if (GetEnemiesKilled() >= (unsigned)level_2_wave[level_2_index])
    {
        level_2_dt = GetSpawnTime();
        ResetWave(False);
    }
}

void level_2_wave_4(void)
{
    if (GetEnemiesSpawned() < (unsigned)level_2_wave[level_2_index])
    {
        level_2_dt -= CP_System_GetDt();
        if (level_2_dt < 0.0f)
        {
            level_2_dt = GetSpawnTime();
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

    if (GetEnemiesKilled() >= (unsigned)level_2_wave[level_2_index])
    {
        level_2_dt = GetSpawnTime();
        ResetWave(False);
    }
}

void level_2_wave_5(void)
{
    if (GetEnemiesSpawned() < (unsigned)level_2_wave[level_2_index])
    {
        level_2_dt -= CP_System_GetDt();
        if (level_2_dt < 0.0f)
        {
            level_2_dt = GetSpawnTime();
            int random_chance = CP_Random_RangeInt(0, 9);
            // 50% chance to spawn speedy
            if (random_chance <= 4)
                SpawnEnemy(SPEEDY);
            // 40% chance to spawn normal
            else if (random_chance >= 5 && random_chance <= 8)
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

    if (GetEnemiesKilled() >= (unsigned)level_2_wave[level_2_index])
    {
        level_2_dt = GetSpawnTime();
        ResetWave(True);
    }
}

void level_2_win(void)
{
    WinScreenUpdate();
}

void level_2_update(void)
{
    GameState currState = CommonLevelUpdate();
    if (currState != PLAYING)
        return;
    level_2_func_ptr[level_2_index]();
}

void level_2_exit(void)
{

}

