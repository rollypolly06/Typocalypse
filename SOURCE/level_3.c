/*!
file:   level_3.c
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

brief:  level 3 gameplay

Total: 120 enemies

	Copyright © 2020 DigiPen, All rights reserved.
//_____________________________________________________*/
#include "level_3.h"
#include "common_gameplay.h"

void level_3_wave_1(void);
void level_3_wave_2(void);
void level_3_wave_3(void);
void level_3_wave_4(void);
void level_3_wave_5(void);
void level_3_wave_6(void);
void level_3_win(void);

const void(*level_3_func_ptr[])(void) = { level_3_wave_1, level_3_wave_2, level_3_wave_3, level_3_wave_4, level_3_wave_5, level_3_wave_6, level_3_win };
int level_3_index;

float level_3_dt;

// how many enemies to kill before going to the next wave
int level_3_wave[] = { 15, 15, 20, 20, 25, 25 };

void level_3_init(void)
{
    unsigned sum = 0;
    for (int i = 0; i < ARRAY_SIZE(level_3_wave); ++i)
        sum += *(level_3_wave + i);

    CommonLevelInit("Assets/Levels/level_3.txt", "Assets/Levels/Waypoints/level_3_waypoints.txt", sum, ARRAY_SIZE(level_3_wave), &level_3_index, COLOURS, LEVEL_3);
    level_3_index = 0;
    level_3_dt = GetSpawnTime();
}

void level_3_wave_1(void)
{
    if (GetEnemiesSpawned() < (unsigned)level_3_wave[level_3_index])
    {
        level_3_dt -= CP_System_GetDt();
        if (level_3_dt < 0.0f)
        {
            level_3_dt = GetSpawnTime();
            int random_chance = CP_Random_RangeInt(0, 9);
            // 30% chance to spawn speedy
            if (random_chance <= 2)
                SpawnEnemy(SPEEDY);
            // 70% chance to spawn normal
            else if (random_chance >= 3)
                SpawnEnemy(NORMAL);
            IncrementEnemiesSpawned();
        }
    }

    if (GetEnemiesKilled() >= (unsigned)level_3_wave[level_3_index])
    {
        level_3_dt = GetSpawnTime();
        ResetWave(False);
    }
}

void level_3_wave_2(void)
{
    if (GetEnemiesSpawned() < (unsigned)level_3_wave[level_3_index])
    {
        level_3_dt -= CP_System_GetDt();
        if (level_3_dt < 0.0f)
        {
            level_3_dt = GetSpawnTime();
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

    if (GetEnemiesKilled() >= (unsigned)level_3_wave[level_3_index])
    {
        level_3_dt = GetSpawnTime();
        ResetWave(False);
    }
}

void level_3_wave_3(void)
{
    if (GetEnemiesSpawned() < (unsigned)level_3_wave[level_3_index])
    {
        level_3_dt -= CP_System_GetDt();
        if (level_3_dt < 0.0f)
        {
            level_3_dt = GetSpawnTime();
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

    if (GetEnemiesKilled() >= (unsigned)level_3_wave[level_3_index])
    {
        level_3_dt = GetSpawnTime();
        ResetWave(False);
    }
}

void level_3_wave_4(void)
{
    if (GetEnemiesSpawned() < (unsigned)level_3_wave[level_3_index])
    {
        level_3_dt -= CP_System_GetDt();
        if (level_3_dt < 0.0f)
        {
            level_3_dt = GetSpawnTime();
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

    if (GetEnemiesKilled() >= (unsigned)level_3_wave[level_3_index])
    {
        level_3_dt = GetSpawnTime();
        ResetWave(False);
    }
}

void level_3_wave_5(void)
{
    if (GetEnemiesSpawned() < (unsigned)level_3_wave[level_3_index])
    {
        level_3_dt -= CP_System_GetDt();
        if (level_3_dt < 0.0f)
        {
            level_3_dt = GetSpawnTime();
            int random_chance = CP_Random_RangeInt(0, 9);
            // 60% chance to spawn speedy
            if (random_chance <= 5)
                SpawnEnemy(SPEEDY);
            // 30% chance to spawn normal
            else if (random_chance >= 6 && random_chance <= 8)
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

    if (GetEnemiesKilled() >= (unsigned)level_3_wave[level_3_index])
    {
        level_3_dt = GetSpawnTime();
        ResetWave(False);
    }
}

void level_3_wave_6(void)
{
    if (GetEnemiesSpawned() < (unsigned)level_3_wave[level_3_index])
    {
        level_3_dt -= CP_System_GetDt();
        if (level_3_dt < 0.0f)
        {
            level_3_dt = GetSpawnTime();
            int random_chance = CP_Random_RangeInt(0, 9);
            // 70% chance to spawn speedy
            if (random_chance <= 6)
                SpawnEnemy(SPEEDY);
            // 20% chance to spawn normal
            else if (random_chance >= 7 && random_chance <= 8)
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

    if (GetEnemiesKilled() >= (unsigned)level_3_wave[level_3_index])
    {
        level_3_dt = GetSpawnTime();
        ResetWave(True);
    }
}

void level_3_win(void)
{
    WinScreenUpdate();
}

void level_3_update(void)
{
    GameState currState = CommonLevelUpdate();
    if (currState != PLAYING)
        return;
    level_3_func_ptr[level_3_index]();
}

void level_3_exit(void)
{

}

