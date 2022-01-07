/*!
file:	ui.c
author:	Lee Fu Sheng Roy

email:	f.lee@digipen.edu

brief:	Contains functions declared in the ui.h header file. The
		functions defined here executes the rendering of UI and
		updating of events for player's input.

	Copyright © 2020 DigiPen, All rights reserved.

*//*____________________________________________________________*/

#include "ui.h"
#include "player.h"

#define BUTTON_WIDTH		UI_GRID_WIDTH * 2.0f
#define BUTTON_HEIGHT		UI_GRID_HEIGHT * 3.0f
#define HOTKEY_WIDTH		UI_GRID_WIDTH * 0.5f
#define HOTKEY_HEIGHT		UI_GRID_HEIGHT * 0.5f
#define BUTTON_Y			(UI_GRID_HEIGHT * 17.0f) + (BUTTON_HEIGHT * 0.5f)
#define HOTKEY_Y			(UI_GRID_HEIGHT * 17.0f) - (UI_GRID_HEIGHT * 0.25f)
#define INFO_HEIGHT			UI_GRID_HEIGHT * 1.5f
#define INFO_Y				(UI_GRID_HEIGHT * 17.0f) - (INFO_HEIGHT * 0.5f)
#define TYPING_BOX_WIDTH	UI_GRID_WIDTH * 16.0f
#define TYPING_BOX_HEIGHT	UI_GRID_HEIGHT * 5.0f
#define TYPING_BOX_X		UI_GRID_WIDTH * 13.0f
#define TYPING_BOX_O_Y		UI_GRID_HEIGHT * 15.0f

#define FREEZE_COOLDOWN		15.0f
#define AOE_COOLDOWN		15.0f

Button* slowTowerButton;
Button* freezeTowerButton;
Button* aoeTowerButton;
Button* goldTowerButton;

char* slowButtonPath = "Assets/Image/Buttons/slow-button.png";
char* freezeButtonPath = "Assets/Image/Buttons/freeze-button.png";
char* aoeButtonPath = "Assets/Image/Buttons/aoe-button.png";
char* goldButtonPath = "Assets/Image/Buttons/gold-button.png";
char* freezeAbilityPath = "Assets/Image/Buttons/freeze-ability.png";
char* aoeAbilityPath = "Assets/Image/Buttons/aoe-ability.png";
char* freezeAbilityGreyPath = "Assets/Image/Buttons/freeze-ability-grey.png";
char* aoeAbilityGreyPath = "Assets/Image/Buttons/aoe-ability-grey.png";

char* slowInfo = "Assets/Image/Buttons/slow-info.png";
char* freezeInfo = "Assets/Image/Buttons/freeze-info.png";
char* aoeInfo = "Assets/Image/Buttons/aoe-info.png";
char* goldInfo = "Assets/Image/Buttons/gold-info.png";

char* freezeAbilityInfo = "Assets/Image/Buttons/freeze-ability-info.png";
char* aoeAbilityInfo = "Assets/Image/Buttons/aoe-ability-info.png";

char* typingBox = "Assets/Image/Buttons/typing-box.png";

char* hotkey1 = "Assets/Image/Buttons/hotkey-1.png";
char* hotkey2 = "Assets/Image/Buttons/hotkey-2.png";
char* hotkey3 = "Assets/Image/Buttons/hotkey-3.png";
char* hotkey4 = "Assets/Image/Buttons/hotkey-4.png";
char* hotkeyEnter = "Assets/Image/Buttons/hotkey-enter.png";
char* hotkeyEsc= "Assets/Image/Buttons/hotkey-esc.png";
char* hotkeyCtrl= "Assets/Image/Buttons/hotkey-ctrl.png";
char* hotkeyPrev= "Assets/Image/Buttons/hotkey-prev.png";
char* hotkeyNext= "Assets/Image/Buttons/hotkey-next.png";

CP_Image slowInfoImg;
CP_Image freezeInfoImg;
CP_Image aoeInfoImg;
CP_Image goldInfoImg;
CP_Image typingBoxImg;

CP_Image hotkey1Img;
CP_Image hotkey2Img;
CP_Image hotkey3Img;
CP_Image hotkey4Img;
CP_Image hotkeyCtrlImg;
CP_Image hotkeyPrevImg;
CP_Image hotkeyNextImg;

float freezeCooldown = FREEZE_COOLDOWN;
float aoeCoolDown = AOE_COOLDOWN;

TowerAbility ability;
Boolean isEditing = False;
Boolean isFreezing = False;
float freezeTime = 0.0f;
Boolean frozen = False;

Boolean gotAOE = False;
Boolean gotFreeze = False;

int countDownFreeze;
char bufferFreeze[3];
int countDownAoe;
char bufferAoe[3];

Boolean usingFreeze = False;
Boolean usingAOE = False;

Boolean isTowerButtonClick = False;
Boolean isAbilityButtonClick = False;

void DrawGridLine(void);

int freezeEnemyCounter = 0;
int aoeEnemyCounter = 0;

/*!
@brief -	        Initializes the buttons with its filepath name, position and
					its size
*//*_____________________________________________________________________________*/
void InitButtons(void)
{
	// init the image, position, size of button
	slowTowerButton = LoadButton(slowButtonPath, UI_GRID_WIDTH * 22.0f, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);

	freezeTowerButton = LoadButton(freezeButtonPath, UI_GRID_WIDTH * 24.0f, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);

	aoeTowerButton = LoadButton(aoeButtonPath, UI_GRID_WIDTH * 26.0f, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);

	goldTowerButton = LoadButton(goldButtonPath, UI_GRID_WIDTH * 28.0f, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);

	ability = NO_ABILITIES;
	isEditing = False;
	isFreezing = False;
	freezeTime = 0.0f;
	frozen = False;

	gotAOE = False;
	gotFreeze = False;

	usingFreeze = False;
	usingAOE = False;

	isTowerButtonClick = False;
	isAbilityButtonClick = False;

	freezeEnemyCounter = 0;
	aoeEnemyCounter = 0;
}

/*!
@brief -	Initialize the image of the typing box by loading the image with its
			filepath
*//*_____________________________________________________________________________*/
void InitTypingBox(void)
{
	typingBoxImg = CP_Image_Load(typingBox);
}

/*!
@brief -	Adds the typing box image loaded to the Render manager to be rendered
*//*_____________________________________________________________________________*/
void TypingBox(void)
{
	AddSprite(typingBoxImg, TYPING_BOX_X, TYPING_BOX_O_Y + (TYPING_BOX_HEIGHT * 0.5f), TYPING_BOX_WIDTH, TYPING_BOX_HEIGHT, 255, UI_LAYER);
}

/*!
@brief -	Initializes the tower's info to be displayed when mouse is hovering
			over the tower buttons
*//*_____________________________________________________________________________*/
void InfoInit(void)
{
	slowInfoImg = CP_Image_Load(slowInfo);
	freezeInfoImg = CP_Image_Load(freezeInfo);
	aoeInfoImg = CP_Image_Load(aoeInfo);
	goldInfoImg = CP_Image_Load(goldInfo);
	//freezeAbilityInfoImg = CP_Image_Load(freezeAbilityInfo);
	//aoeAbilityInfoImg = CP_Image_Load(aoeAbilityInfo);
}

/*!
@brief -	Initializes the hotkeys image to be displayed over their respective
			buttons
*//*_____________________________________________________________________________*/
void HotkeyInit(void)
{
	hotkey1Img = CP_Image_Load(hotkey1);
	hotkey2Img = CP_Image_Load(hotkey2);
	hotkey3Img = CP_Image_Load(hotkey3);
	hotkey4Img = CP_Image_Load(hotkey4);
	//hotkeyQImg = CP_Image_Load(hotkeyQ);
	//hotkeyEImg = CP_Image_Load(hotkeyE);
	//hotkeyEnterImg = CP_Image_Load(hotkeyEnter);
	//hotkeyEscImg = CP_Image_Load(hotkeyEsc);
	hotkeyCtrlImg = CP_Image_Load(hotkeyCtrl);
	hotkeyPrevImg = CP_Image_Load(hotkeyPrev);
	hotkeyNextImg = CP_Image_Load(hotkeyNext);
}

/*!
@brief -	Adds the hotkey images loaded to the Render Manager to be rendered
*//*_____________________________________________________________________________*/
void RenderHotkeys(void)
{	
	AddSprite(hotkey1Img, UI_GRID_WIDTH * 22, HOTKEY_Y, HOTKEY_WIDTH, HOTKEY_HEIGHT, 255, HOTKEY_LAYER);
	AddSprite(hotkey2Img, UI_GRID_WIDTH * 24, HOTKEY_Y, HOTKEY_WIDTH, HOTKEY_HEIGHT, 255, HOTKEY_LAYER);
	AddSprite(hotkey3Img, UI_GRID_WIDTH * 26, HOTKEY_Y, HOTKEY_WIDTH, HOTKEY_HEIGHT, 255, HOTKEY_LAYER);
	AddSprite(hotkey4Img, UI_GRID_WIDTH * 28, HOTKEY_Y, HOTKEY_WIDTH, HOTKEY_HEIGHT, 255, HOTKEY_LAYER);
	AddSprite(hotkeyPrevImg, UI_GRID_WIDTH * 7.0f, UI_GRID_HEIGHT * 19.0f, UI_GRID_WIDTH * 2.0f, HOTKEY_HEIGHT * 2.0f, 255, HOTKEY_LAYER);
	AddSprite(hotkeyNextImg, UI_GRID_WIDTH * 19.0f, UI_GRID_HEIGHT * 19.0f, UI_GRID_WIDTH * 2.0f, HOTKEY_HEIGHT * 2.0f, 255, HOTKEY_LAYER);
}

/*!
@brief -	Calls the 4 different Initialize functions to initialize the all the
			UI assets
*//*_____________________________________________________________________________*/
void InitUI(void)
{
	InfoInit();
	InitTypingBox();
	InitButtons();
	HotkeyInit();
}

/*!
@brief -	Takes in user inputs for user to interact with the game in real time.
			This function should be called in the game update loop
*//*_____________________________________________________________________________*/
Boolean PlayerControlUpdate(void)
{
	// if player in typing mode
	if (GetTypingMode())
	{
		if (CP_Input_KeyDown(KEY_LEFT_CONTROL))
			return True;
		else
			return False;
	}
	return True;
}

/*!
@brief -	Takes in user inputs for user to interact with the game in real time.
			This function should be called in the game update loop
*//*_____________________________________________________________________________*/
void ButtonsUpdate(void)
{
	ButtonScaleUp(slowTowerButton, 5.0f, 5.0f, 5.0f);
	ButtonScaleUp(freezeTowerButton, 5.0f, 5.0f, 5.0f);
	ButtonScaleUp(aoeTowerButton, 5.0f, 5.0f, 5.0f);
	ButtonScaleUp(goldTowerButton, 5.0f, 5.0f, 5.0f);
	DrawButtons();
	TypingBox();

	// Displays the information when mouse is hovering over the tower button
	if (MouseHoveringButton(slowTowerButton))
	{
		AddSprite(slowInfoImg, UI_GRID_WIDTH * 25.0f, INFO_Y, BUTTON_WIDTH * 4.0f, INFO_HEIGHT, 255, INFO_LAYER);
	}
	if (MouseHoveringButton(freezeTowerButton))
	{
		AddSprite(freezeInfoImg, UI_GRID_WIDTH * 25.0f, INFO_Y, BUTTON_WIDTH * 4.0f, INFO_HEIGHT, 255, INFO_LAYER);
	}
	if (MouseHoveringButton(aoeTowerButton))
	{
		AddSprite(aoeInfoImg, UI_GRID_WIDTH * 25.0f, INFO_Y, BUTTON_WIDTH * 4.0f, INFO_HEIGHT, 255, INFO_LAYER);
	}
	if (MouseHoveringButton(goldTowerButton))
	{
		AddSprite(goldInfoImg, UI_GRID_WIDTH * 25.0f, INFO_Y, BUTTON_WIDTH * 4.0f, INFO_HEIGHT, 255, INFO_LAYER);
	}
	// Actions if towers button is pressed, sets isEditing to True
	if (IsButtonClick(slowTowerButton, MOUSE_BUTTON_1) || CP_Input_KeyTriggered(KEY_1))
	{
		ability = TOWER_SLOW;
		isEditing = True;
		isTowerButtonClick = True;
	}
	if (IsButtonClick(freezeTowerButton, MOUSE_BUTTON_1) || CP_Input_KeyTriggered(KEY_2))
	{
		ability = TOWER_FREEZE;
		isEditing = True;
		isTowerButtonClick = True;
	}
	if (IsButtonClick(aoeTowerButton, MOUSE_BUTTON_1) || CP_Input_KeyTriggered(KEY_3))
	{
		ability = TOWER_AOE;
		isEditing = True;
		isTowerButtonClick = True;
	}
	if (IsButtonClick(goldTowerButton, MOUSE_BUTTON_1) || CP_Input_KeyTriggered(KEY_4))
	{
		ability = TOWER_GOLD;
		isEditing = True;
		isTowerButtonClick = True;
	}
}

/*!
@brief -	Takes in user inputs for players to place down towers and continuously
			render images at the position of their mouse so players can select
			where to place down their towers
*//*_____________________________________________________________________________*/
void TowerPlacementUpdate(void)
{
	if (!isEditing)
		return;

	if (isTowerButtonClick || isAbilityButtonClick)
	{
		DrawGridLine();
		return;
	}

	// Actions when isEditing is True
	DrawGridLine();
	// renders tower with radius
	DrawTowerWithRadius(ability);

	// Actions if isEditing is True and Mouse left button is clicked
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		Point p = { (float)((int)(CP_Input_GetMouseX() / GRID_SYSTEM_WIDTH)), (float)((int)(CP_Input_GetMouseY() / GRID_SYSTEM_HEIGHT)) };

		if (GoldAmount() >= GetTowerCost(ability))
		{
			if (BuildOntoGrid(p, GetTowerGrid(ability), TOWER))
			{
				// initialize the members of the tower and store into a Tower* arr, tPtr
				CreateTower(ability, p);
				GoldMinus(GetTowerCost(ability));
				isEditing = False;				
				return;
			}
		}
		else
			RenderMsg();
	}
}

/*!
@brief -	Updates the graphics of the gameplay when called.
*//*_____________________________________________________________________________*/
void TowerUpdate(void)
{
	TowerPlacementUpdate();
	InTowerRange();
	SlowTower();
	GoldTower();
}

/*!
@brief -	Sets to a Boolean if there is any AOE tower placed or not
@params -	Boolean value depending on if AOE tower is present or not
*//*_____________________________________________________________________________*/
void AOEPresent(Boolean boo)
{
	gotAOE = boo;
}

/*!
@brief -	Sets to a Boolean if there is any Freeze tower placed or not
@params -	Boolean value depending on if Freeze tower is present or not
*//*_____________________________________________________________________________*/
void FreezePresent(Boolean boo)
{
	gotFreeze = boo;
}

/*!
@brief -	Calling this function will cause enemies within the range of freeze
			freeze tower to be frozen
*//*_____________________________________________________________________________*/
void UseFreezeAbility(void)
{
	if (!usingFreeze)
		return;

	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		usingFreeze = False;
	}

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1))
	{
		FreezeArray();
		frozen = True;
		isFreezing = True;
		usingFreeze = False;
		freezeCooldown = 0;
	}
	RenderFreezeRadius();
}

/*!
@brief -	Increase the freezeEnemyCounter by 1
*//*_____________________________________________________________________________*/
void IncrementFreezeEnemyCounter(void)
{
	++freezeEnemyCounter;
}

/*!
@brief -	Increase the aoeEnemyCounter by 1
*//*_____________________________________________________________________________*/
void IncrementAoeEnemyCounter(void)
{
	++aoeEnemyCounter;
}

/*!
@brief -	Calls to the FreezeArray() adn Freeze() function for every fixed
			amount of enemies killed
*//*_____________________________________________________________________________*/
void FreezeAbilityUpdate(void)
{  
	if (freezeEnemyCounter != 0 && freezeEnemyCounter % 3 == 0)
	{
		FreezeArray();
		frozen = True;
		freezeEnemyCounter = 0;
	}

	if (frozen)
	{
		if (freezeTime > FREEZE_TIME)
		{
			freezeTime = 0.0f;
			frozen = False;
			isFreezing = False;
		}
		else
		{
			freezeTime += CP_System_GetDt();
			Freeze();
		}
	}
}

/*!
@brief -	Calls to the AoeAttack() function for every fixed amount of enemies
			killed
*//*_____________________________________________________________________________*/
void AOEAbilityUpdate(void)
{  
	if (aoeEnemyCounter != 0 && aoeEnemyCounter % 5 == 0)
	{
		AoeAttack();
		aoeEnemyCounter = 0;
	}
}

/*!
@brief -	Calls to FreezeAbilityUpdate() and AOEAbilityUpdate() functions for
			every game update loop.
*//*_____________________________________________________________________________*/
void AbilityUpdate(void)
{
	FreezeAbilityUpdate();
	AOEAbilityUpdate();  
}

/*!
@brief -	Updates the rendering of the US assets with each game update loop
*//*_____________________________________________________________________________*/
void UIUpdate(void)
{
	RenderHotkeys();
	aoeCoolDown += CP_System_GetDt();
	freezeCooldown += CP_System_GetDt();
	ButtonsUpdate();
	TowerUpdate();
	AbilityUpdate();

	isTowerButtonClick = False;
	isAbilityButtonClick = False;
}

/*!
@brief -	Returns the Boolean of whether isEditing is True or False
*//*_____________________________________________________________________________*/
Boolean GetIsEditing(void)
{
	return isEditing;
}

/*!
@brief -	Sets the Boolean of isEditing to either True or False
*//*_____________________________________________________________________________*/
void SetIsEditing(Boolean status)
{
	isEditing = status;
}

/*!
@brief -	Frees the images previously loaded. Declared in pointer_manager.h
*//*_____________________________________________________________________________*/
void FreeUI(void)
{
	CP_Image_Free(&slowInfoImg);
	CP_Image_Free(&freezeInfoImg);
	CP_Image_Free(&aoeInfoImg);
	CP_Image_Free(&goldInfoImg);
	CP_Image_Free(&typingBoxImg);
	CP_Image_Free(&hotkey1Img);
	CP_Image_Free(&hotkey2Img);
	CP_Image_Free(&hotkey3Img);
	CP_Image_Free(&hotkey4Img);
	CP_Image_Free(&hotkeyCtrlImg);
	CP_Image_Free(&hotkeyPrevImg);
	CP_Image_Free(&hotkeyNextImg);
}