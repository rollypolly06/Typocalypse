/*!
file:   game_state.h
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
brief:  Pause and Play function for the game

	Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/

#include "game_state.h"

CP_Image pauseScreen;
Button* pauseResumeButton, * pauseMainMenuButton;
Boolean gameIsPaused;

void PauseGameInit(void)
{
    gameIsPaused = False; //we start unpaused, assign, initialising

    //load paused screen image first, but dont render
    pauseScreen = CP_Image_Load("Assets/Image/Pause/PauseScreen.png");
    pauseResumeButton = LoadButton("Assets/Image/Pause/pause_button_resume.png", HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT * 1.1f, UI_GRID_WIDTH * 10.0f, UI_GRID_HEIGHT * 2.0f);
    pauseMainMenuButton = LoadButton("Assets/Image/Pause/pause_button_main_menu.png", HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT * 1.3f, UI_GRID_WIDTH * 10.0f, UI_GRID_HEIGHT * 2.0f);

    //resume button: render,visibility,clickability
    SetButtonRenderOrder(pauseResumeButton, PAUSE_BUTTON_LAYER);
    SetButtonAlpha(pauseResumeButton, 0);
    SetButtonClickableState(pauseResumeButton, False);

    //main menu: render,visibility,clickability
    SetButtonRenderOrder(pauseMainMenuButton, PAUSE_BUTTON_LAYER);
    SetButtonAlpha(pauseMainMenuButton, 0);
    SetButtonClickableState(pauseMainMenuButton, False);
}


void PauseGameUpdate(void)
{
    //function to display a paused menu screen IF game is paused
    if (gameIsPaused)
    {
        ButtonScaleUp(pauseMainMenuButton, 5.0f, 5.0f, 5.0f);
        ButtonScaleUp(pauseResumeButton, 5.0f, 5.0f, 5.0f);

        AddSprite(pauseScreen, HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, ALPHA, PAUSE_LAYER);
        SetButtonAlpha(pauseResumeButton, ALPHA);
        SetButtonClickableState(pauseResumeButton, True);
        SetButtonAlpha(pauseMainMenuButton, ALPHA);
        SetButtonClickableState(pauseMainMenuButton, True);

        //if resume button is pressed
        if (IsButtonClick(pauseResumeButton, MOUSE_BUTTON_LEFT))
        {
            gameIsPaused = False;
            SetButtonAlpha(pauseResumeButton, 0);
            SetButtonClickableState(pauseResumeButton, False);
            SetButtonAlpha(pauseMainMenuButton, 0);
            SetButtonClickableState(pauseMainMenuButton, False);
        }

        //if main menu button is pressed
        if (IsButtonClick(pauseMainMenuButton, MOUSE_BUTTON_LEFT))
        {
            SetNextLevel(MENU);
        }
        RenderAll();
    }
}

void SetPaused(Boolean paused) //take in boolean
{
    gameIsPaused = paused;

}

Boolean GetPaused(void)//check if game is paused
{
    return gameIsPaused;
}

void FreeGameState(void)
{

}