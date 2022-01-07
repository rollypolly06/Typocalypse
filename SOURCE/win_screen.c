/*!
file:	death_screen.c
author:	Wong Man Cong
		Lee Fu Sheng Roy
		Phua Tze Cheng Jennifer
		Thea Sea
		Nicole Wong

email:	w.mancong@digipen.edu
		f.lee@digipen.edu
		p.tzechengjennifer@digipen.edu
		thea.sea@digipen.edu
		n.wong@digipen.edu

brief:	includes all function related to win screen when a level
		is successfully cleared

*//*____________________________________________________________*/
#include "common_headers.h"
#include "win_screen.h"

#define CENTER_X				CP_System_GetWindowWidth() * 0.5f
#define CENTER_Y				CP_System_GetWindowHeight() * 0.5f
#define WIN_SCREEN_WIDTH		UI_GRID_WIDTH * 22
#define WIN_SCREEN_HEIGHT		UI_GRID_HEIGHT * 16
#define BUTTON_Y				UI_GRID_HEIGHT * 14
#define BUTTON_WIDTH			UI_GRID_WIDTH * 4
#define BUTTON_HEIGHT			UI_GRID_HEIGHT * 1.0f

char* winScreen = "Assets/Image/Win-Screen/win-screen.png";
char* winOverlay = "Assets/Image/Win-Screen/overlay.png";
CP_Image winOverlayImg;
CP_Image winScreenImg;

Button* winRestartButton;
Button* winMainMenuButton;
Button* winNextLevelButton;
//Boolean winButtonLoaded = False;
Boolean winState;
Level winScreenCurrLevel;

void InitWinScreen(Level currLevel)
{
	winState = False;
	winScreenCurrLevel = currLevel;
	winOverlayImg = CP_Image_Load(winOverlay);
	winScreenImg = CP_Image_Load(winScreen);

	winRestartButton = LoadButton("Assets/Image/Win-Screen/restart.png", UI_GRID_WIDTH * 10, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
	SetButtonAlpha(winRestartButton, 0);
	SetButtonClickableState(winRestartButton, False);
	if (currLevel == TOTAL_PLAYING_LEVELS - 1)
	{
		winMainMenuButton = LoadButton("Assets/Image/Win-Screen/main-menu.png", UI_GRID_WIDTH * 20, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
		SetButtonAlpha(winMainMenuButton, 0);
		SetButtonClickableState(winMainMenuButton, False);
	}

	else
	{
		winMainMenuButton = LoadButton("Assets/Image/Win-Screen/main-menu.png", UI_GRID_WIDTH * 15, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
		SetButtonAlpha(winMainMenuButton, 0);
		SetButtonClickableState(winMainMenuButton, False);

		winNextLevelButton = LoadButton("Assets/Image/Win-Screen/next-level.png", UI_GRID_WIDTH * 20, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
		SetButtonAlpha(winNextLevelButton, 0);
		SetButtonClickableState(winNextLevelButton, False);
	}
	
}

void RenderWinScreenButtons(void)
{
	SetButtonAlpha(winRestartButton, ALPHA);
	SetButtonClickableState(winRestartButton, True);

	SetButtonAlpha(winMainMenuButton, ALPHA);
	SetButtonClickableState(winMainMenuButton, True);

	if (winScreenCurrLevel != LEVEL_5)
	{
		SetButtonAlpha(winNextLevelButton, ALPHA);
		SetButtonClickableState(winNextLevelButton, True);
	}
	
	SetButtonRenderOrder(winRestartButton, TOP_LAYER);
	SetButtonRenderOrder(winMainMenuButton, TOP_LAYER);
	SetButtonRenderOrder(winNextLevelButton, TOP_LAYER);
}

void SetWinTrue(void)
{
	winState = True;
}

void WinScreenUpdate(void)
{
	//if (winState == False)
	//	return;
	ButtonScaleUp(winRestartButton, 5.0f, 5.0f, 5.0f);
	ButtonScaleUp(winMainMenuButton, 5.0f, 5.0f, 5.0f);
	ButtonScaleUp(winNextLevelButton, 5.0f, 5.0f, 5.0f);

	AddSprite(winOverlayImg, CENTER_X, CENTER_Y, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight(), 200, TOP_LAYER);
	AddSprite(winScreenImg, CENTER_X, CENTER_Y, WIN_SCREEN_WIDTH, WIN_SCREEN_HEIGHT, 255, TOP_LAYER);
	RenderWinScreenButtons();

	if (IsButtonClick(winRestartButton, MOUSE_BUTTON_1))
	{
		RestartLevel();
	}

	if (IsButtonClick(winMainMenuButton, MOUSE_BUTTON_1))
	{
		SetNextLevel(MENU);
	}

	if (IsButtonClick(winNextLevelButton, MOUSE_BUTTON_1))
	{
		SetNextLevel(winScreenCurrLevel + 1);
	}
}

void FreeWinScreen(void)
{
	CP_Image_Free(&winScreenImg);
	CP_Image_Free(&winOverlayImg);
}