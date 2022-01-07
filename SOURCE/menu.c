/*!
file:	menu.c
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
brief:	main menu level

    Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#include "menu.h"

#define MAX_LOGO_Y		((float)CP_System_GetWindowHeight() * 0.175f)  //macro for the Y coordinate of the "Typocalypse" game logo

//Animation of the Typocalyspe logo floating from the bottom of the screen to above the buttons
CP_Image logo, menu_bg;
Button* play, * how_to, * credits, * quit;
float logo_x, logo_y, logo_w, logo_h;
int logo_a;
float const LOGO_SPEED = 200.0f;
int menuButtonAlpha;
Boolean isMenuLoaded = False;

Boolean buttonClicked = False;

// Play section
CP_Image menu_black_overlay, level_num[TOTAL_PLAYING_LEVELS], menu_level;
Button *menu_cross, *map_preview[TOTAL_PLAYING_LEVELS], *menu_left_arrow, *menu_right_arrow;
Boolean playSelection = False;
int preview_index = 0;

// Difficulty selection
CP_Image difficultySelectionBg = NULL, difficultySelectionInfo = NULL;
Button *easy_btn = NULL, *medium_btn = NULL, *hard_btn = NULL;
Boolean difficultySelection = False;

//How to Play Tutorial 
CP_Image tutSlide[23];
Boolean tutorialStart = False;
int slide_index = 0;

//Credits images
CP_Image creditsImgs[8];
Boolean creditsStart = False;
float creditsDt = 0;
int creditsNum = 0;

/*!
@brief	function to set all main menu buttons visible
@param	alpha: value 255, meaning that the button is fully opaque
*//*____________________________________________*/
void SetAllMenuButtonsAlpha(int alpha)
{
	SetButtonAlpha(play, alpha);
	SetButtonAlpha(how_to, alpha);
	SetButtonAlpha(credits, alpha);
	SetButtonAlpha(quit, alpha);
}

/*!
@brief	function to set all main menu buttons to be able to be clicked
@param	status: either True or False, true means button can be clicked and false means button cannot be clicked
*//*____________________________________________*/
void SetAllMenuButtonsStatus(Boolean status)
{
	SetButtonClickableState(play, status);
	SetButtonClickableState(how_to, status);
	SetButtonClickableState(credits, status);
	SetButtonClickableState(quit, status);
}

/*!
@brief	displays main menu and changes the images of buttons of "start game", "how to play", "settings" "credits" "quit" on hover, The following happens when you click the respective buttons:
		1) clicking "start game" launches the level selection screen by calling function "PlaySelection()"
		2) clicking "how to play" launches the tutorial slides by calling function "TutorialSelection()"
		3) clicking "settings" launches the settings page by calling function "SettingsSelection()"
		4) clicking "credits" launches the credits page by calling function "CreditsShowing()"
		4) clicking "quit" frees files used and exits the game
@param	void
*//*____________________________________________*/
void LoadMainMenu(void)
{
	if (!isMenuLoaded && (CP_Input_KeyTriggered(KEY_ANY) || CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)))
	{
		logo_y = MAX_LOGO_Y;
		menuButtonAlpha = ALPHA;
	}

	logo_y -= LOGO_SPEED * CP_System_GetDt();
	if (MAX_LOGO_Y >= logo_y)
	{
		logo_y = MAX_LOGO_Y;

		if (!isMenuLoaded)
			menuButtonAlpha += 5;

		if (ALPHA <= menuButtonAlpha)
		{
			menuButtonAlpha = ALPHA;
			isMenuLoaded = True;
		}

		SetAllMenuButtonsAlpha(menuButtonAlpha);
	}

	if (isMenuLoaded)
	{
		// PLAY
		if (MouseHoveringButton(play))
		{
			SetButtonImageIndex(play, 1);
			if (IsButtonClick(play, MOUSE_BUTTON_LEFT))
			{
				playSelection = True;
				preview_index = 0;
				menuButtonAlpha = 0;
				logo_a = 0;

				buttonClicked = True;

				SetAllMenuButtonsStatus(False);

				SetButtonAlpha(menu_cross, ALPHA);
				SetButtonAlpha(menu_left_arrow, ALPHA);
				SetButtonAlpha(menu_right_arrow, ALPHA);

				SetButtonClickableState(menu_cross, True);
				SetButtonClickableState(menu_left_arrow, True);
				SetButtonClickableState(menu_right_arrow, True);
				
				Point p4 = { WINDOW_WIDTH / 30.0f * 5.0f, HALF_SCREEN_HEIGHT };

				SetButtonPosition(menu_left_arrow, p4);
				p4.x = WINDOW_WIDTH / 30.0f * 25.0f;
				SetButtonPosition(menu_right_arrow, p4);

				for (int i = 0; i < TOTAL_PLAYING_LEVELS; ++i)
					SetButtonAlpha(map_preview[i], ALPHA);
			}
		}
		else if (!MouseHoveringButton(play))
		{
			SetButtonImageIndex(play, 0);
		}

		// HOW TO PLAY
		if (MouseHoveringButton(how_to))
		{
			SetButtonImageIndex(how_to, 1);
			if (IsButtonClick(how_to, MOUSE_BUTTON_LEFT))
			{
				//clear buttons of main menu and clear clickability
				menuButtonAlpha = 0;
				logo_a = 0;
				preview_index = 0;
				SetAllMenuButtonsStatus(False);
				tutorialStart = True; 

				SetButtonAlpha(menu_cross, ALPHA);
				SetButtonAlpha(menu_left_arrow, ALPHA);
				SetButtonAlpha(menu_right_arrow, ALPHA);

				SetButtonClickableState(menu_cross, True);
				SetButtonClickableState(menu_left_arrow, True);
				SetButtonClickableState(menu_right_arrow, True);

				Point p4 = { WINDOW_WIDTH / 30.0f * 2.0f, WINDOW_HEIGHT / 30.0f * 20.0f };

				SetButtonPosition(menu_left_arrow, p4);
				p4.x = WINDOW_WIDTH / 30.0f * 28.0f;
				SetButtonPosition(menu_right_arrow, p4);
			}

		}
		else if (!MouseHoveringButton(how_to))
		{
			SetButtonImageIndex(how_to, 0);
		}

		//CREDITS
		if (MouseHoveringButton(credits))
		{
			SetButtonImageIndex(credits, 1);
			if (IsButtonClick(credits, MOUSE_BUTTON_LEFT))
			{
				//clear buttons of main menu and clear clickability
				menuButtonAlpha = 0;
				logo_a = 0;
				creditsNum = 0;
				SetAllMenuButtonsStatus(False);
				creditsStart = True;

				SetButtonAlpha(menu_cross, ALPHA);
				SetButtonClickableState(menu_cross, True);

			}

		}
		else if (!MouseHoveringButton(credits))
			SetButtonImageIndex(credits, 0);

		// QUIT
		if (MouseHoveringButton(quit))
		{
			SetButtonImageIndex(quit, 1);
			if (IsButtonClick(quit, MOUSE_BUTTON_LEFT))
				ExitGame();

		}
		else if (!MouseHoveringButton(quit))
		{
			SetButtonImageIndex(quit, 0);
		}
	}
}

/*!
@brief	the function that is called when "start game" is clicked, launching the level selection screen
@param	void
*//*____________________________________________*/
void PlaySelection(void)
{
	if (!playSelection || buttonClicked || difficultySelection)
		return;

	for (int i = 0; i < TOTAL_PLAYING_LEVELS; ++i)
	{
		Point p = { WINDOW_WIDTH + 1000.0f , WINDOW_HEIGHT + 1000.0f };
		SetButtonPosition(map_preview[i], p);
		SetButtonClickableState(map_preview[i], True);
	}

	ButtonScaleUp(menu_left_arrow, 5.0f, 5.0f, 5.0f);
	ButtonScaleUp(menu_right_arrow, 5.0f, 5.0f, 5.0f);

	if (IsButtonClick(menu_left_arrow, MOUSE_BUTTON_LEFT))
	{
		if (0 > --preview_index)
		{
			preview_index = TOTAL_PLAYING_LEVELS - 1;
		}
	}
	if (IsButtonClick(menu_right_arrow, MOUSE_BUTTON_LEFT))
	{
		if (TOTAL_PLAYING_LEVELS <= ++preview_index)
		{
			preview_index = 0;
		}
	}

	Point p1 = { HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT };
	SetButtonPosition(map_preview[preview_index], p1);
	SetButtonClickableState(map_preview[preview_index], True);

	Point p2 = { (WINDOW_WIDTH / 30.0f) * -5.0f, HALF_SCREEN_HEIGHT };
	int tmp = 0;
	if (0 > (tmp = preview_index - 1))
	{
		tmp = TOTAL_PLAYING_LEVELS - 1;
	}
	else
	{
		tmp = preview_index - 1;
	}
	SetButtonPosition(map_preview[tmp], p2);

	Point p3 = { (WINDOW_WIDTH / 30.0f) * 35.0f, HALF_SCREEN_HEIGHT };
	SetButtonPosition(map_preview[tmp], p2);
	if (TOTAL_PLAYING_LEVELS <= preview_index + 1)
	{
		tmp = 0;
	}
	else
	{
		tmp = preview_index + 1;
	}
	SetButtonPosition(*(map_preview + tmp), p3);

	// MENU CROSS
	if (MouseHoveringButton(menu_cross))
	{
		SetButtonImageIndex(menu_cross, 1);
	}
	else if (!MouseHoveringButton(menu_cross))
	{
		SetButtonImageIndex(menu_cross, 0);
	}

	// goes back to main menu
	if (IsButtonClick(menu_cross, MOUSE_BUTTON_LEFT))
	{
		playSelection = False;
		menuButtonAlpha = ALPHA;
		logo_a = ALPHA;

		SetAllMenuButtonsStatus(True);

		SetButtonAlpha(menu_cross, 0);
		SetButtonAlpha(menu_left_arrow, 0);
		SetButtonAlpha(menu_right_arrow, 0);

		SetButtonClickableState(menu_cross, False);
		SetButtonClickableState(menu_left_arrow, False);
		SetButtonClickableState(menu_right_arrow, False);

		for (int i = 0; i < TOTAL_PLAYING_LEVELS; ++i)
			SetButtonAlpha(map_preview[i], 0);
	}

	// goes to difficulty selection
	if (IsButtonClick(map_preview[preview_index], MOUSE_BUTTON_LEFT))
	{
		// TODO: Change level difficulty here
		difficultySelection = True;
		
		SetButtonAlpha(easy_btn, ALPHA);
		SetButtonAlpha(medium_btn, ALPHA);
		SetButtonAlpha(hard_btn, ALPHA);

		playSelection = False;
		menuButtonAlpha = 0;
		logo_a = 0;

		SetAllMenuButtonsStatus(False);

		SetButtonAlpha(menu_left_arrow, 0);
		SetButtonAlpha(menu_right_arrow, 0);

		SetButtonClickableState(menu_left_arrow, False);
		SetButtonClickableState(menu_right_arrow, False);

		for (int i = 0; i < TOTAL_PLAYING_LEVELS; ++i)
		{
			SetButtonClickableState(map_preview[i], False);
			SetButtonAlpha(map_preview[i], 0);
		}
	}

	float x = (WINDOW_WIDTH / 30.0f) * 12.5f;
	float y = (WINDOW_HEIGHT / 30.0f) * 5.0f;
	float w = (WINDOW_WIDTH / 30.0f) * 10.0f;
	float h = (WINDOW_HEIGHT / 30.0f) * 2.5f;
	AddSprite(menu_level, x, y, w, h, ALPHA, LEVEL_PREVIEW_LAYER);

	x = (WINDOW_WIDTH / 30.0f) * 20.5f;
	w = (WINDOW_WIDTH / 30.0f) * 2.5f;
	h = (WINDOW_HEIGHT / 30.0f) * 2.5f;
	AddSprite(level_num[preview_index], x, y, w, h, ALPHA, LEVEL_PREVIEW_LAYER);

	AddSprite(menu_black_overlay, HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, 150, OVERLAY_LAYER);
}

/*!
@brief	the function that is called when "how to play" is clicked, launching the tutorial slides
@param	void
*//*____________________________________________*/
void TutorialSelection(void)
{
	if (!tutorialStart || buttonClicked)
		return;

	ButtonScaleUp(menu_left_arrow, 5.0f, 5.0f, 5.0f);
	ButtonScaleUp(menu_right_arrow, 5.0f, 5.0f, 5.0f);
	
	AddSprite(tutSlide[slide_index], HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, ALPHA, LEVEL_PREVIEW_LAYER);
	
		if (IsButtonClick(menu_left_arrow, MOUSE_BUTTON_LEFT))
		{
			--slide_index;
			if (slide_index < 0)
			{
				slide_index = 22;
			}
			AddSprite(tutSlide[slide_index], HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, ALPHA, LEVEL_PREVIEW_LAYER);

		}
		if (IsButtonClick(menu_right_arrow, MOUSE_BUTTON_LEFT))
		{
			++slide_index;
			if (slide_index > 22)
			{
				slide_index = 0;
			}
			AddSprite(tutSlide[slide_index], HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, ALPHA, LEVEL_PREVIEW_LAYER);

		}

	// MENU CROSS
	if (MouseHoveringButton(menu_cross))
	{
		SetButtonImageIndex(menu_cross, 1);
	}
	else if (!MouseHoveringButton(menu_cross))
	{
		SetButtonImageIndex(menu_cross, 0);
	}

	// goes back to main menu
	if (IsButtonClick(menu_cross, MOUSE_BUTTON_LEFT))
	{
		tutorialStart = False;
		menuButtonAlpha = ALPHA;
		logo_a = ALPHA;

		SetAllMenuButtonsStatus(True);

		SetButtonAlpha(menu_cross, 0);
		SetButtonAlpha(menu_left_arrow, 0);
		SetButtonAlpha(menu_right_arrow, 0);

		SetButtonClickableState(menu_cross, False);
		SetButtonClickableState(menu_left_arrow, False);
		SetButtonClickableState(menu_right_arrow, False);
	}

}

/*!
@brief	the function that is called when a level is selected, displaying the easy, normal and hard mode gameplay difficulty modes to select from
@param	void
*//*____________________________________________*/
void DifficultySelection(void)
{
	if (!difficultySelection)
		return;

	if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
	{
		SetButtonClickableState(easy_btn, True);
		SetButtonClickableState(medium_btn, True);
		SetButtonClickableState(hard_btn, True);
	}

	// MENU CROSS
	if (MouseHoveringButton(menu_cross))
	{
		SetButtonImageIndex(menu_cross, 1);
	}
	else if (!MouseHoveringButton(menu_cross))
	{
		SetButtonImageIndex(menu_cross, 0);
	}

	// go back to level selection
	if (IsButtonClick(menu_cross, MOUSE_BUTTON_LEFT))
	{
		difficultySelection = False;

		SetButtonAlpha(easy_btn, 0);
		SetButtonAlpha(medium_btn, 0);
		SetButtonAlpha(hard_btn, 0);

		SetButtonClickableState(easy_btn, False);
		SetButtonClickableState(medium_btn, False);
		SetButtonClickableState(hard_btn, False);

		playSelection = True;
		menuButtonAlpha = 0;
		logo_a = 0;

		SetAllMenuButtonsStatus(False);

		SetButtonAlpha(menu_left_arrow, ALPHA);
		SetButtonAlpha(menu_right_arrow, ALPHA);

		SetButtonClickableState(menu_left_arrow, True);
		SetButtonClickableState(menu_right_arrow, True);

		for (int i = 0; i < TOTAL_PLAYING_LEVELS; ++i)
		{
			SetButtonClickableState(map_preview[i], True);
			SetButtonAlpha(map_preview[i], ALPHA);
		}
	}

	ButtonScaleUp(easy_btn, 5.0f, 5.0f, 5.0f);
	ButtonScaleUp(medium_btn, 5.0f, 5.0f, 5.0f);
	ButtonScaleUp(hard_btn, 5.0f, 5.0f, 5.0f);

	if (IsButtonClick(easy_btn, MOUSE_BUTTON_LEFT))
	{
		SetGameDifficulty(EASY);
		SetNextLevel((Level)preview_index);
	}
	if (IsButtonClick(medium_btn, MOUSE_BUTTON_LEFT))
	{
		SetGameDifficulty(MEDIUM);
		SetNextLevel((Level)preview_index);
	}
	if (IsButtonClick(hard_btn, MOUSE_BUTTON_LEFT))
	{
		SetGameDifficulty(HARD);
		SetNextLevel((Level)preview_index);
	}

	float x = HALF_SCREEN_WIDTH;
	float y = HALF_SCREEN_HEIGHT;
	float w = UI_GRID_WIDTH * 28.0f;
	float h = UI_GRID_HEIGHT * 10.0f;
	AddSprite(difficultySelectionBg, x, y, w, h, ALPHA, OVERLAY_LAYER);

	y = UI_GRID_HEIGHT * 2.5f;
	w = UI_GRID_WIDTH * 12.5f;
	h = UI_GRID_HEIGHT * 3.5f;
	AddSprite(difficultySelectionInfo, x, y, w, h, ALPHA, OVERLAY_LAYER);
	AddSprite(menu_black_overlay, HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, 150, OVERLAY_LAYER);
}

/*!
@brief	the function that is called when "credits" is clicked, launching the credits screen
@param	void
*//*____________________________________________*/
void CreditsShowing(void) {
	if (!creditsStart || buttonClicked)
		return;

	AddSprite(creditsImgs[creditsNum], WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, ALPHA, LEVEL_PREVIEW_LAYER);

	if ((CP_Input_KeyTriggered(KEY_SPACE)) || (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)))
	{
		++creditsNum;
		if (creditsNum > 7)
			creditsNum = 0;

		AddSprite(creditsImgs[creditsNum], WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, ALPHA, LEVEL_PREVIEW_LAYER);
	}

	// MENU CROSS
	if (MouseHoveringButton(menu_cross))
		SetButtonImageIndex(menu_cross, 1);
	else if (!MouseHoveringButton(menu_cross))
		SetButtonImageIndex(menu_cross, 0);

	// goes back to main menu
	if (IsButtonClick(menu_cross, MOUSE_BUTTON_LEFT))
	{
		creditsStart = False;
		menuButtonAlpha = ALPHA;
		logo_a = ALPHA;

		SetAllMenuButtonsStatus(True);

		SetButtonAlpha(menu_cross, 0);
		SetButtonAlpha(menu_left_arrow, 0);
		SetButtonAlpha(menu_right_arrow, 0);

		SetButtonClickableState(menu_cross, False);
		SetButtonClickableState(menu_left_arrow, False);
		SetButtonClickableState(menu_right_arrow, False);
	}
}

/*!
@brief	handle loading of all assets and buttons
@param	void
*//*____________________________________________*/
void menu_init(void)
{
	DefaultRenderManager();

	// LOGO
	logo = CP_Image_Load("Assets/Image/logo/game_logo.png");
	logo_x = HALF_SCREEN_WIDTH;
	logo_y = CP_System_GetWindowHeight() + 50.0f;
	logo_w = (CP_System_GetWindowWidth() / 30.0f) * 20.0f;
	logo_h = (CP_System_GetWindowHeight() / 40.0f) * 10.0f;
	logo_a = ALPHA;

	// MENU
	menu_bg = CP_Image_Load("Assets/Image/background/menu_bg.png");

	menuButtonAlpha = 0;
	isMenuLoaded = False;

	buttonClicked = False;

	float buttonX = HALF_SCREEN_WIDTH;								// button's x pos
	float buttonY = (CP_System_GetWindowHeight() / 40.0f) * 15.0f;	// button's y pos
	float buttonW = (CP_System_GetWindowWidth() / 30.0f) * 11.0f;	// button's width
	float buttonH = (CP_System_GetWindowHeight() / 40.0f) * 2.5f;	// button's height

	// PLAY
	play = LoadButton("Assets/Image/Buttons/play_1.png", buttonX, buttonY, buttonW, buttonH);
	AdditionalButtonImage(play, "Assets/Image/Buttons/play_2.png");
	SetButtonAlpha(play, 0);

	// HOW TO
	buttonY = (CP_System_GetWindowHeight() / 40.0f) * 21.0f;
	buttonW = (CP_System_GetWindowWidth() / 30.0f) * 12.5f;
	how_to = LoadButton("Assets/Image/Buttons/how_to_play_1.png", buttonX, buttonY, buttonW, buttonH);
	AdditionalButtonImage(how_to, "Assets/Image/Buttons/how_to_play_2.png");
	SetButtonAlpha(how_to, 0);

	//CREDITS
	buttonY = (CP_System_GetWindowHeight() / 40.0f) * 28.0f;
	buttonW = (CP_System_GetWindowWidth() / 30.0f) * 8.0f;
	credits = LoadButton("Assets/Image/Buttons/credits_1.png", buttonX, buttonY, buttonW, buttonH);
	AdditionalButtonImage(credits, "Assets/Image/Buttons/credits_2.png");
	SetButtonAlpha(credits, 0);

	// QUIT
	buttonY = (CP_System_GetWindowHeight() / 40.0f) * 35.0f;
	buttonW = (CP_System_GetWindowWidth() / 30.0f) * 5.0f;
	quit = LoadButton("Assets/Image/Buttons/quit_1.png", buttonX, buttonY, buttonW, buttonH);
	AdditionalButtonImage(quit, "Assets/Image/Buttons/quit_2.png");
	SetButtonAlpha(quit, 0);

	// Play section
	menu_black_overlay = CP_Image_Load("Assets/Image/overlay/black_overlay.png");

	menu_level = CP_Image_Load("Assets/Image/level_preview/level.png");

	char imageFile[75];
	for (int i = 0; i < TOTAL_PLAYING_LEVELS; ++i)
	{
		memcpy_s(imageFile, sizeof(imageFile), "Assets/Image/level_preview/", sizeof("Assets/Image/level_preview/"));
		char num[5]; _itoa_s(i + 1, num, 3, 10);
		strncat_s(imageFile, sizeof(imageFile), num, 3);
		strncat_s(imageFile, sizeof(imageFile), ".png", 5);

		level_num[i] = CP_Image_Load(imageFile);
	}

	for (int i = 0; i < TOTAL_PLAYING_LEVELS; ++i)
	{
		memcpy_s(imageFile, sizeof(imageFile), "Assets/Image/level_preview/map_", sizeof("Assets/Image/level_preview/map_"));
		char num[5]; _itoa_s(i + 1, num, 3, 10);
		strncat_s(imageFile, sizeof(imageFile), num, 3);
		strncat_s(imageFile, sizeof(imageFile), ".png", 5);

		buttonX = WINDOW_WIDTH + 1000.0f;
		buttonY = WINDOW_HEIGHT + 1000.0f;
		buttonW = (WINDOW_WIDTH / 30.0f) * 15.0f;
		buttonH = (WINDOW_HEIGHT / 30.0f) * 12.5f;

		map_preview[i] = LoadButton(imageFile, buttonX, buttonY, buttonW, buttonH);
		SetButtonAlpha(map_preview[i], 0);
		SetButtonRenderOrder(map_preview[i], LEVEL_PREVIEW_LAYER);
	}

	buttonX = (WINDOW_WIDTH / 30.0f) * 27.5f;
	buttonY = (WINDOW_HEIGHT / 40.0f) * 3.0f;
	buttonW = (WINDOW_WIDTH / 30.0f) * 2.5f;
	buttonH = (WINDOW_HEIGHT / 30.0f) * 2.5f;
	menu_cross = LoadButton("Assets/Image/level_preview/cross_1.png", buttonX, buttonY, buttonW, buttonH);
	AdditionalButtonImage(menu_cross, "Assets/Image/level_preview/cross_2.png");
	SetButtonAlpha(menu_cross, 0);
	SetButtonClickableState(menu_cross, False);

	buttonX = (WINDOW_WIDTH / 30.0f) * 5.0f;
	buttonY = HALF_SCREEN_HEIGHT;
	menu_left_arrow = LoadButton("Assets/Image/Buttons/left_arrow.png", buttonX, buttonY, buttonW, buttonH);
	buttonX = (WINDOW_WIDTH / 30.0f) * 25.0f;
	menu_right_arrow = LoadButton("Assets/Image/Buttons/right_arrow.png", buttonX, buttonY, buttonW, buttonH);

	SetButtonAlpha(menu_left_arrow, 0);
	SetButtonAlpha(menu_right_arrow, 0);
	SetButtonClickableState(menu_left_arrow, False);
	SetButtonClickableState(menu_right_arrow, False);

	playSelection = False;
	preview_index = 0;

	//HOW TO PLAY TUTORIAL
	for (int i = 0; i < 23; ++i)
	{
		memcpy_s(imageFile, sizeof(imageFile), "Assets/Tutorial/", sizeof("Assets/Tutorial/"));
		char num[5];
		_itoa_s(i, num, 3, 10);
		strncat_s(imageFile, sizeof(imageFile), num, 3);
		strncat_s(imageFile, sizeof(imageFile), ".png", 5);

		tutSlide[i] = CP_Image_Load(imageFile);
	}

	// DIFFICULTY SELECTION
	difficultySelectionBg = CP_Image_Load("Assets/Image/overlay/difficulty_selection_menu.png");
	difficultySelectionInfo = CP_Image_Load("Assets/Image/level_preview/difficulty_selection.png");

	buttonX = UI_GRID_WIDTH * 15.0f;
	buttonY = UI_GRID_HEIGHT * 7.0f;
	buttonW = UI_GRID_WIDTH * 25.0f;
	buttonH = UI_GRID_HEIGHT * 2.0f;
	easy_btn = LoadButton("Assets/Image/Buttons/easy.png", buttonX, buttonY, buttonW, buttonH);
	SetButtonAlpha(easy_btn, 0);
	SetButtonClickableState(easy_btn, False);

	buttonY = UI_GRID_HEIGHT * 10.0f;
	medium_btn = LoadButton("Assets/Image/Buttons/medium.png", buttonX, buttonY, buttonW, buttonH);
	SetButtonAlpha(medium_btn, 0);
	SetButtonClickableState(medium_btn, False);

	buttonY = UI_GRID_HEIGHT * 13.0f;
	hard_btn = LoadButton("Assets/Image/Buttons/hard.png", buttonX, buttonY, buttonW, buttonH);
	SetButtonAlpha(hard_btn, 0);
	SetButtonClickableState(hard_btn, False);

	difficultySelection = False;

	//CREDITS
	creditsImgs[0] = CP_Image_Load("Assets/Image/Credits/1.png");
	creditsImgs[1] = CP_Image_Load("Assets/Image/Credits/2.png");
	creditsImgs[2] = CP_Image_Load("Assets/Image/Credits/3.png");
	creditsImgs[3] = CP_Image_Load("Assets/Image/Credits/4.png");
	creditsImgs[4] = CP_Image_Load("Assets/Image/Credits/5.png");
	creditsImgs[5] = CP_Image_Load("Assets/Image/Credits/6.png");
	creditsImgs[6] = CP_Image_Load("Assets/Image/Credits/7.png");
	creditsImgs[7] = CP_Image_Load("Assets/Image/Credits/8.png");
}

/*!
@brief	handle gamestate and what is displayed when main menu is launched
@param	void
*//*____________________________________________*/
void menu_update(void)
{
	buttonClicked = False;
	LoadMainMenu();
	PlaySelection();
	TutorialSelection();
	DifficultySelection();
	CreditsShowing();

	AddSprite(logo, logo_x, logo_y, logo_w, logo_h, logo_a, LOGO_LAYER);
	AddSprite(menu_bg, HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, ALPHA, BACKGROUND_LAYER);
	RenderAll();
}

/*!
@brief	exit menu
@param	void
*//*____________________________________________*/
void menu_exit(void)
{
	FreeMemory();
	CP_Image_Free(&logo);
	CP_Image_Free(&menu_bg);
	CP_Image_Free(&menu_black_overlay);

	for (int i = 0; i < TOTAL_PLAYING_LEVELS; ++i)
		CP_Image_Free(&level_num[i]);

	CP_Image_Free(&menu_level);
	CP_Image_Free(&difficultySelectionBg);
	CP_Image_Free(&difficultySelectionInfo);

	for (int i = 0; i < 8; ++i)
		CP_Image_Free(&creditsImgs[i]);

	for (int i = 0; i < 23; ++i)
		CP_Image_Free(&tutSlide[i]);
}