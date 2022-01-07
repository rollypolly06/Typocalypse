/*!
file:	player.c
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	function definitions for inputs from player when
		playing different levels

    Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#include "player.h"
#include "typing.h"
#include "enemy.h"
#include "text_render.h"
#include "player_health.h"
#include "ui.h"
#include "type_to_kill.h"

char strInput[STRING_SIZE];				// string inputs from the player
int strLength;							// length of current string
Boolean isTyping;						// only can start typing after pressing enter
Boolean ctrlDown;

Enemy** enemy_list;
int enemyIndex;

int totalLiveEnemyInList;				// check the number of alive enemy in my list

// DEATH SCREEN
int DeathScreenUpdate(void);
void InitDeathScreen(void);

// TOWER
int GetTotalEnemiesInTypeArray(void);

// Inside UI
void IncrementFreezeEnemyCounter(void);
void IncrementAoeEnemyCounter(void);

// PLAYER
void TotalEnemyInList(void);
void SetPlayerTypingIndex(void);

/******************************************************************************
						INITIALIZE FUNCTIONS CALL
******************************************************************************/
/*!
@brief	Reset the values back to it's default
*//*__________________________________________________________________________*/
void DefaultPlayer(void)
{
	strLength = 0;
	CleanInputString(strInput, strLength, STRING_SIZE);
	SetEnemyRenderText("");
}

/*!
@brief	Initialised a reference to enemy
*//*__________________________________________________________________________*/
void InitPlayerEnemyReference(Enemy** enemy)
{
	enemy_list = enemy;
}

/*!
@brief	return's the typing status
*//*__________________________________________________________________________*/
Boolean GetTypingMode(void)
{
	return isTyping;
}

/*!
@brief	Setting default values when the level just started
*//*__________________________________________________________________________*/
void InitPlayer(void)
{	
	DefaultPlayer();
	isTyping = True;
	enemyIndex = 0;	
	totalLiveEnemyInList = 0;
	InitTyping();
	SetCorrectRenderText("");
	PauseGameInit();
	InitDeathScreen();
}

/******************************************************************************
						UPDATE FUNCTIONS CALL
******************************************************************************/
/*!
@brief	Available inputs from the player
*//*__________________________________________________________________________*/
void PlayerControl(void)
{
	// When not in typing mode, press escape show to pause screen
	if (CP_Input_KeyTriggered(KEY_ESCAPE) && !GetIsEditing())
	{
		SetPaused(True);
	}

	if (CP_Input_KeyTriggered(KEY_ESCAPE) && GetIsEditing())
		SetIsEditing(!GetIsEditing());

	if (CP_Input_KeyDown(KEY_LEFT_CONTROL) || CP_Input_KeyDown(KEY_RIGHT_CONTROL))
		ctrlDown = True;
	else
		ctrlDown = False;

	if (CP_Input_KeyDown(KEY_LEFT_SHIFT) && CP_Input_KeyTriggered(KEY_TAB))
	{
		enemyIndex -= 1;
		if (0 > enemyIndex)
		{
			enemyIndex = totalLiveEnemyInList - 1;
			if (enemyIndex < 0)
				enemyIndex = 0;
		}
		//DefaultPlayer();
	}
	else if (CP_Input_KeyTriggered(KEY_TAB))
	{
		enemyIndex += 1;
		if (totalLiveEnemyInList <= enemyIndex)
			enemyIndex = 0;
		//DefaultPlayer();
	}
}

/*!
@brief	Get the length of string input
@return	length of the string
*//*__________________________________________________________________________*/
int StringLength(void)
{
	int len = 0;
	for (int i = 0; strInput[i] != '\0'; ++i)
		++len;

	if (STRING_SIZE < len)
		len = STRING_SIZE;
	return len;
}

/*!
@brief	To compare the words type by player, if it's the same, kill the enemy

@return	true when what the player types corresponds to the word on screen
*//*__________________________________________________________________________*/
Boolean IsEnemyDead(void)
{
	//if (!enemy_list[0])
	//	return False;
	//if (!strcmp(enemy_list[0][enemyIndex].word, ""))
	//	return False;
	//return !strcmp(GetCurrentWord(), strInput);
	return !strcmp(GetCurrentWord(), strInput) || CP_Input_KeyTriggered(KEY_F1);
}

/*!
@brief	Using typing.h functions to capture and store player's input
*//*__________________________________________________________________________*/
void CaptureString(void)
{
	// If player did not go into typing mode, don't capture input.
	// If control btn is down, don't allow storing of input
	if (!isTyping)
	{
		SetEnemyRenderText("");
		return;
	}

	if (TypingHindered()) {
		DefaultPlayer();
		SetEnemyRenderText("Typing hindered");
		return;
	}
		
	if (ctrlDown)
		return;

	SetPlayerTypingIndex();

	strLength = StringLength();
	if (STRING_SIZE > strLength)
	{
		CleanInputString(strInput, strLength, STRING_SIZE);
		if (totalLiveEnemyInList > 0)
			UpdateTyping(&*strInput, strLength);

		// For loop to check for first letter that doesn't match with enemy
		for (int i = 0, len = (int)strlen(strInput); i < len; ++i)
		{
			if (strInput[i] == GetCurrentWord()[i])
				continue;

			// if one is found, the rest at the back should be null terminator
			while (i < len)
			{
				strInput[i++] = '\0';
			}
		}

		SetCorrectRenderText(strInput);
		if(totalLiveEnemyInList > 0)
			SetEnemyRenderText(GetCurrentWord());
	}

	if(enemy_list[0])
		AddRect(enemy_list[0][enemyIndex].position.x, enemy_list[0][enemyIndex].position.y - enemy_list[0][enemyIndex].height * 0.5f, enemy_list[0][enemyIndex].width, enemy_list[0][enemyIndex].height, 0.1f, CP_Color_Create(255, 0, 0, 100), SELECTED_ENEMY_LAYER);

	if (totalLiveEnemyInList > 0 && IsEnemyDead())
	{
		// reset values back to original state
		DefaultPlayer();
		if(enemy_list[0])
			KillEnemy(&enemy_list[0][enemyIndex]);
		IncrementFreezeEnemyCounter();
		IncrementAoeEnemyCounter();
		SetNextWord();

#if DEBUG_PLAYER
		printf("True\n");
#endif
	}
}

/*!
@brief	Count the total enemy alive in my enemy_list
*//*__________________________________________________________________________*/
void TotalEnemyInList(void)
{
	totalLiveEnemyInList = 0;
	if (GetGameDifficulty() != HARD)
		totalLiveEnemyInList = GetAliveEnemies();
	else
		totalLiveEnemyInList = GetTotalEnemiesInTypeArray();
}

void SetPlayerTypingIndex(void)
{
	if (totalLiveEnemyInList <= enemyIndex)
		enemyIndex = totalLiveEnemyInList - 1;
	if (0 > enemyIndex)
		enemyIndex = 0;
}

/*!
@brief	Main update call for player's input
		-> To be called outside of this source file
*//*__________________________________________________________________________*/
void UpdatePlayer(void)
{
	if(!enemy_list[0])
		SetEnemyRenderText("");

	TotalEnemyInList();
	PlayerControl();
	EraseCapturedString(strInput, &strLength);
	CaptureString();
	RenderHealth();
}

void FreePlayer(void)
{
	isTyping = False;
}