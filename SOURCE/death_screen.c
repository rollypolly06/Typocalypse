/*!
file:	death_screen.c
author:	Lee Fu Sheng Roy

email:	f.lee@digipen.edu

brief:	includes all function related to death screen shown when
		player's health reaches zero.

	Copyright © 2020 DigiPen, All rights reserved.

*//*____________________________________________________________*/
#include "death_screen.h"

#define CENTER_X				CP_System_GetWindowWidth() * 0.5f
#define CENTER_Y				CP_System_GetWindowHeight() * 0.5f
#define DEATH_SCREEN_WIDTH		UI_GRID_WIDTH * 22
#define DEATH_SCREEN_HEIGHT		UI_GRID_HEIGHT * 16
#define BUTTON_Y				UI_GRID_HEIGHT * 14
#define BUTTON_WIDTH			UI_GRID_WIDTH * 4
	#define BUTTON_HEIGHT		UI_GRID_HEIGHT * 1.5f

char* deathScreen = "Assets/Image/Death-Screen/death-screen.png";
char* overlay = "Assets/Image/Death-Screen/overlay.png";
CP_Image overlayImg;
CP_Image deathScreenImg;

Button* restartButton;
Button* mainMenuButton;
Boolean buttonLoaded = False;

/*!
@brief -	Initializes the assets to be rendered such as screen image and the
			buttons
*//*_____________________________________________________________________________*/
void InitDeathScreen(void)
{
	overlayImg = CP_Image_Load(overlay);
	deathScreenImg = CP_Image_Load(deathScreen);

	restartButton = LoadButton("Assets/Image/Death-Screen/restart.png", UI_GRID_WIDTH * 10, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
	SetButtonAlpha(restartButton, 0);
	SetButtonClickableState(restartButton, False);

	mainMenuButton = LoadButton("Assets/Image/Death-Screen/main-menu.png", UI_GRID_WIDTH * 20, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
	SetButtonAlpha(mainMenuButton, 0);
	SetButtonClickableState(mainMenuButton, False);
}

/*!
@brief -	renders the death screen and the buttons to restart level, return to
			main menu.
*//*_____________________________________________________________________________*/
void RenderDeathScreenButtons(void)
{
	SetButtonAlpha(restartButton, ALPHA);
	SetButtonClickableState(restartButton, True);

	SetButtonAlpha(mainMenuButton, ALPHA);
	SetButtonClickableState(mainMenuButton, True);

	SetButtonRenderOrder(restartButton, TOP_LAYER);
	SetButtonRenderOrder(mainMenuButton, TOP_LAYER);
}

/*!
@brief -	Constantly calls to RenderDeathScreenButtons() function to update 
			the death screen and the buttons and taking in inputs from player. 
*//*_____________________________________________________________________________*/
int DeathScreenUpdate(void)
{
	if (HealthZero() == False)
		return 0;
	ButtonScaleUp(restartButton, 5.0f, 5.0f, 5.0f);
	ButtonScaleUp(mainMenuButton, 5.0f, 5.0f, 5.0f);

	AddSprite(overlayImg, CENTER_X, CENTER_Y, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight(), 200, TOP_LAYER);
	AddSprite(deathScreenImg, CENTER_X, CENTER_Y, DEATH_SCREEN_WIDTH, DEATH_SCREEN_HEIGHT, 255, TOP_LAYER);
	//AddText("Hiok Hiok Hiok", CENTER_X, CENTER_Y, 30.0f, COLOR_RED, CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_BOTTOM, TOP_LAYER);
	RenderDeathScreenButtons();

	if (IsButtonClick(restartButton, MOUSE_BUTTON_1))
	{
		RestartLevel();
	}

	if (IsButtonClick(mainMenuButton, MOUSE_BUTTON_1))
	{
		SetNextLevel(MENU);
	}
	return 1;
}

/*!
@brief -	Frees the images loaded. Used in pointer_manager.c
*//*_____________________________________________________________________________*/
void FreeDeathScreen(void)
{
	CP_Image_Free(&deathScreenImg);
	CP_Image_Free(&overlayImg);
}