/*!
file:   level_5.c
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

brief:  level 5 gameplay

Total: 180 enemies

	Copyright © 2020 DigiPen, All rights reserved.
//_____________________________________________________*/
#include "level_5.h"
#include "common_gameplay.h"

void level_5_wave_1(void);
void level_5_wave_2(void);
void level_5_wave_3(void);
void level_5_wave_4(void);
void level_5_wave_5(void);
void level_5_wave_6(void);
void level_5_wave_7(void);
void level_5_wave_8(void);
void level_5_win(void);

const void(*level_5_func_ptr[])(void) = { level_5_wave_1, level_5_wave_2, level_5_wave_3, level_5_wave_4, level_5_wave_5, level_5_wave_6, level_5_wave_7, level_5_wave_8, level_5_win };
int level_5_index;

float level_5_dt;

// how many enemies to kill before going to the next wave
int level_5_wave[] = { 15, 15, 20, 20, 25, 25, 30, 30 };

void level_5_init(void)
{
    unsigned sum = 0;
    for (int i = 0; i < ARRAY_SIZE(level_5_wave); ++i)
        sum += *(level_5_wave + i);

    CommonLevelInit("Assets/Levels/level_5.txt", "Assets/Levels/Waypoints/level_5_waypoints.txt", sum, ARRAY_SIZE(level_5_wave), &level_5_index, CITIES, LEVEL_5);
    level_5_index = 0;
    level_5_dt = GetSpawnTime();
}

void level_5_wave_1(void) {
    if (GetEnemiesSpawned() < (unsigned)level_5_wave[level_5_index])
    {
        level_5_dt -= CP_System_GetDt();
        if (level_5_dt < 0.0f)
        {
            level_5_dt = GetSpawnTime();
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

    if (GetEnemiesKilled() >= (unsigned)level_5_wave[level_5_index])
    {
        level_5_dt = GetSpawnTime();
        ResetWave(False);
    }

}

void level_5_wave_2(void) {
    if (GetEnemiesSpawned() < (unsigned)level_5_wave[level_5_index])
    {
        level_5_dt -= CP_System_GetDt();
        if (level_5_dt < 0.0f)
        {
            level_5_dt = GetSpawnTime();
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

    if (GetEnemiesKilled() >= (unsigned)level_5_wave[level_5_index])
    {
        level_5_dt = GetSpawnTime();
        ResetWave(False);
    }
}

void level_5_wave_3(void) {
    if (GetEnemiesSpawned() < (unsigned)level_5_wave[level_5_index])
    {
        level_5_dt -= CP_System_GetDt();
        if (level_5_dt < 0.0f)
        {
            level_5_dt = GetSpawnTime();
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

    if (GetEnemiesKilled() >= (unsigned)level_5_wave[level_5_index])
    {
        level_5_dt = GetSpawnTime();
        ResetWave(False);
    }

}

void level_5_wave_4(void) {
    if (GetEnemiesSpawned() < (unsigned)level_5_wave[level_5_index])
    {
        level_5_dt -= CP_System_GetDt();
        if (level_5_dt < 0.0f)
        {
            level_5_dt = GetSpawnTime();
            int random_chance = CP_Random_RangeInt(0, 9);
            // 50% chance to spawn speedy
            if (random_chance <= 4)
                SpawnEnemy(SPEEDY);
            // 30% chance to spawn normal
            else if (random_chance >= 5 && random_chance <= 7)
                SpawnEnemy(NORMAL);
            // 20% chance to spawn orthodox
            else if (random_chance >= 8)
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

    if (GetEnemiesKilled() >= (unsigned)level_5_wave[level_5_index])
    {
        level_5_dt = GetSpawnTime();
        ResetWave(False);
    }
}

void level_5_wave_5(void) {
    if (GetEnemiesSpawned() < (unsigned)level_5_wave[level_5_index])
    {
        level_5_dt -= CP_System_GetDt();
        if (level_5_dt < 0.0f)
        {
            level_5_dt = GetSpawnTime();
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

    if (GetEnemiesKilled() >= (unsigned)level_5_wave[level_5_index])
    {
        level_5_dt = GetSpawnTime();
        ResetWave(False);
    }

}
void level_5_wave_6(void) {
    if (GetEnemiesSpawned() < (unsigned)level_5_wave[level_5_index])
    {
        level_5_dt -= CP_System_GetDt();
        if (level_5_dt < 0.0f)
        {
            level_5_dt = GetSpawnTime();
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

    if (GetEnemiesKilled() >= (unsigned)level_5_wave[level_5_index])
    {
        level_5_dt = GetSpawnTime();
        ResetWave(False);
    }
}
void level_5_wave_7(void) {
    if (GetEnemiesSpawned() < (unsigned)level_5_wave[level_5_index])
    {
        level_5_dt -= CP_System_GetDt();
        if (level_5_dt < 0.0f)
        {
            level_5_dt = GetSpawnTime();
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

    if (GetEnemiesKilled() >= (unsigned)level_5_wave[level_5_index])
    {
        level_5_dt = GetSpawnTime();
        ResetWave(False);
    }
}

void level_5_wave_8(void) {
    if (GetEnemiesSpawned() < (unsigned)level_5_wave[level_5_index])
    {
        level_5_dt -= CP_System_GetDt();
        if (level_5_dt < 0.0f)
        {
            level_5_dt = GetSpawnTime();
            int random_chance = CP_Random_RangeInt(0, 9);
            // 70% chance to spawn speedy
            if (random_chance <= 6)
                SpawnEnemy(SPEEDY);
            else if (random_chance >= 7)
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

    if (GetEnemiesKilled() >= (unsigned)level_5_wave[level_5_index])
    {
        level_5_dt = GetSpawnTime();
        ResetWave(True);
    }
}
void level_5_win(void)
{
    WinScreenUpdate();
}

void level_5_update(void)
{
    GameState currState = CommonLevelUpdate();
    if (currState != PLAYING)
        return;
    level_5_func_ptr[level_5_index]();
}

void level_5_exit(void)
{

}

