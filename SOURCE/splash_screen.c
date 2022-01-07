/*!
file:   splash_screen.c
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

brief:  Struct that contains data for a splash screen

    Copyright © 2020 DigiPen, All rights reserved.
//_____________________________________________________*/
#include "splash_screen.h"
#include "common_headers.h"

#define TOTAL_SPLASH    2

int alpha = 0;
float splashScreenElapsedTime = 0.0f; 
float const TOTAL_TIME = 1.0f;
CP_Image splashImages[TOTAL_SPLASH];
float splashSizeX[TOTAL_SPLASH];
float splashSizeY[TOTAL_SPLASH];
int splashIndex = 0;

void SplashScreen(float speed);

void splashscreen_init(void)
{
    CP_System_SetWindowTitle("Typocalypse");
    alpha = 0;
    splashScreenElapsedTime = 0.0f;
    splashIndex = 0;

    char imageFile[60];
    for (int i = 0; i < TOTAL_SPLASH; ++i)
    {
        memcpy_s(imageFile, sizeof(imageFile), "Assets/Image/splash_screen/splash_screen_", sizeof("Assets/Image/splash_screen/splash_screen_"));
        char num[5]; _itoa_s(i + 1, num, 3, 10);
        strncat_s(imageFile, sizeof(imageFile), num, 3);
        strncat_s(imageFile, sizeof(imageFile), ".png", 5);

        splashImages[i] = CP_Image_Load(imageFile);
    }

    *splashSizeX = WINDOW_WIDTH;
    *splashSizeY = WINDOW_HEIGHT;

    *(splashSizeX + 1) = (float)CP_System_GetWindowWidth();
    *(splashSizeY + 1) = (float)CP_System_GetWindowHeight();

    DefaultRenderManager();
}

void splashscreen_update(void)
{
    // Just go next level
    if (CP_Input_KeyTriggered(KEY_ESCAPE) || splashIndex >= TOTAL_SPLASH)
    {
        SetNextLevel(MENU);
    }
    else if (CP_Input_KeyTriggered(KEY_ANY) || CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
    {
        // Skip images
        if (++splashIndex >= TOTAL_SPLASH)
            splashIndex = TOTAL_SPLASH;
        alpha = 0;
    }

    switch (splashIndex)
    {
        case 0:
        {
            SetBackgroundColor(COLOR_BLACK);
            break;
        }
        case 1:
        {
            SetBackgroundColor(COLOR_WHITE);
            break;
        }
    }

    SplashScreen(25.0f);
    RenderAll();
}

void splashscreen_exit(void)
{
    for (int i = 0; i < TOTAL_SPLASH; ++i)
        CP_Image_Free(&splashImages[i]);
}

void SplashScreen(float speed)
{
    if (splashIndex >= TOTAL_SPLASH)
        return;
    splashScreenElapsedTime += CP_System_GetDt() * speed;
    if (splashScreenElapsedTime > TOTAL_TIME)
    {
        alpha += 5;
        splashScreenElapsedTime = 0.0f;
    }
    AddSprite(splashImages[splashIndex], CP_System_GetWindowWidth() * 0.5f, CP_System_GetWindowHeight() * 0.5f, splashSizeX[splashIndex], splashSizeY[splashIndex], (unsigned char)alpha, BACKGROUND_LAYER);

    if (ALPHA <= alpha)
    {
        alpha = 0;
        ++splashIndex;
    }
}
