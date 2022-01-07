/*!
file:   level_4.c
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

brief:  level 4 gameplay

Total: 150 enemies

	Copyright © 2020 DigiPen, All rights reserved.
//_____________________________________________________*/
#include "level_4.h"
#include "common_gameplay.h"

void level_4_wave_1(void);
void level_4_wave_2(void);
void level_4_wave_3(void);
void level_4_wave_4(void);
void level_4_wave_5(void);
void level_4_wave_6(void);
void level_4_wave_7(void);
void level_4_win(void);

const void(*level_4_func_ptr[])(void) = { level_4_wave_1, level_4_wave_2, level_4_wave_3, level_4_wave_4, level_4_wave_5, level_4_wave_6, level_4_wave_7, level_4_win };
int level_4_index;

float level_4_dt;

// how many enemies to kill before going to the next wave
int level_4_wave[] = { 15, 15, 20, 20, 25, 25, 30 };

void level_4_init(void)
{
    unsigned sum = 0;
    for (int i = 0; i < ARRAY_SIZE(level_4_wave); ++i)
        sum += *(level_4_wave + i);

    CommonLevelInit("Assets/Levels/level_4.txt", "Assets/Levels/Waypoints/level_4_waypoints.txt", sum, ARRAY_SIZE(level_4_wave), &level_4_index, ANIMALS, LEVEL_4);
    level_4_index = 0;
    level_4_dt = GetSpawnTime();
}

void level_4_wave_1(void) {
    if (GetEnemiesSpawned() < (unsigned)level_4_wave[level_4_index])
    {
        level_4_dt -= CP_System_GetDt();
        if (level_4_dt < 0.0f)
        {
            level_4_dt = GetSpawnTime();
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

    if (GetEnemiesKilled() >= (unsigned)level_4_wave[level_4_index])
    {
        level_4_dt = GetSpawnTime();
        ResetWave(False);
    }

}

void level_4_wave_2(void) {
    if (GetEnemiesSpawned() < (unsigned)level_4_wave[level_4_index])
    {
        level_4_dt -= CP_System_GetDt();
        if (level_4_dt < 0.0f)
        {
            level_4_dt = GetSpawnTime();
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

    if (GetEnemiesKilled() >= (unsigned)level_4_wave[level_4_index])
    {
        level_4_dt = GetSpawnTime();
        ResetWave(False);
    }
}

void level_4_wave_3(void) {
    if (GetEnemiesSpawned() < (unsigned)level_4_wave[level_4_index])
    {
        level_4_dt -= CP_System_GetDt();
        if (level_4_dt < 0.0f)
        {
            level_4_dt = GetSpawnTime();
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

    if (GetEnemiesKilled() >= (unsigned)level_4_wave[level_4_index])
    {
        level_4_dt = GetSpawnTime();
        ResetWave(False);
    }

}

void level_4_wave_4(void) {
    if (GetEnemiesSpawned() < (unsigned)level_4_wave[level_4_index])
    {
        level_4_dt -= CP_System_GetDt();
        if (level_4_dt < 0.0f)
        {
            level_4_dt = GetSpawnTime();
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

    if (GetEnemiesKilled() >= (unsigned)level_4_wave[level_4_index])
    {
        level_4_dt = GetSpawnTime();
        ResetWave(False);
    }
}

void level_4_wave_5(void) {
    if (GetEnemiesSpawned() < (unsigned)level_4_wave[level_4_index])
    {
        level_4_dt -= CP_System_GetDt();
        if (level_4_dt < 0.0f)
        {
            level_4_dt = GetSpawnTime();
            int random_chance = CP_Random_RangeInt(0, 9);
            // 60% chance to spawn speedy
            if (random_chance <= 5)
                SpawnEnemy(SPEEDY);
            // 20% chance to spawn normal
            else if (random_chance >= 6 && random_chance <= 7)
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

    if (GetEnemiesKilled() >= (unsigned)level_4_wave[level_4_index])
    {
        level_4_dt = GetSpawnTime();
        ResetWave(False);
    }

}
void level_4_wave_6(void) {
    if (GetEnemiesSpawned() < (unsigned)level_4_wave[level_4_index])
    {
        level_4_dt -= CP_System_GetDt();
        if (level_4_dt < 0.0f)
        {
            level_4_dt = GetSpawnTime();
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

    if (GetEnemiesKilled() >= (unsigned)level_4_wave[level_4_index])
    {
        level_4_dt = GetSpawnTime();
        ResetWave(False);
    }
}
void level_4_wave_7(void) {
        if (GetEnemiesSpawned() < (unsigned)level_4_wave[level_4_index])
        {
            level_4_dt -= CP_System_GetDt();
            if (level_4_dt < 0.0f)
            {
                level_4_dt = GetSpawnTime();
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

        if (GetEnemiesKilled() >= (unsigned)level_4_wave[level_4_index])
        {
            level_4_dt = GetSpawnTime();
            ResetWave(True);
        }
}

void level_4_win(void)
{
    WinScreenUpdate();
}

void level_4_update(void)
{
    GameState currState = CommonLevelUpdate();
    if (currState != PLAYING)
        return;
    level_4_func_ptr[level_4_index]();
}

void level_4_exit(void)
{

}

