/*!
file:	text_render.c
author:	Lee Fu Sheng Roy

email:	f.lee@digipen.edu

brief:	This file contains the codes to functions declared in the
		text_render.h header file. Functions here renders the text
		onto the game window for players to be able to know what
		to type and what they have typed.

	Copyright © 2020 DigiPen, All rights reserved.

*//*____________________________________________________________*/
#include "common_headers.h"

char* correctRenderText;
char* enemyRenderText;

char eText[20][32] = { "" };	// size of second [] needs to be MAX_LENGTH + 2
char cText[20][32] = { "" };	// kiv

/*!
@brief -		Sets the correctRenderText value to the string provided by text

@param	text -	char pointer to the first character in the string of correct text
*//*_____________________________________________________________________________*/
void SetCorrectRenderText(char* text)
{
	correctRenderText = text;
}

/*!
@brief -		Sets the enemyRenderText value to the string provided by text.
				This sets the string to be typed by player

@param	text -	char pointer to the first character in the string of enemy text
*//*_____________________________________________________________________________*/
void SetEnemyRenderText(char* text)
{
	enemyRenderText = text;
}

/*!
@brief -		Set the font by loading the font file from Assets
*//*_____________________________________________________________________________*/
void SetFonts(void)
{
	CP_Font prototypeFont = CP_Font_Load("Assets/Fonts/Orbitron-Regular.ttf");
	CP_Font_Set(prototypeFont);
}

/*!
@brief -			Renders the string to be typed to kill off an enemy.

@param	line[] -	An array of char which represents the line to be rendered
@param	row -		row count of the line of character to be rendered
*//*_____________________________________________________________________________*/
void EnemyText(char line[], int row) //Prototype WIP
{
	int yShift = row * 50;
	AddText(line, UI_GRID_WIDTH * 6.0f, UI_GRID_HEIGHT * 16.0f + yShift, 50.0f, COLOR_BLUE, CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_MIDDLE, TEXT_LAYER);
}

/*!
@brief -			Renders the string that is typed correctly by player in a
					different font color

@param	line[] -	An array of char which represents the line to be rendered
@param	row -		row count of the line of character to be rendered
*//*_____________________________________________________________________________*/
void CorrectText(char line[], int row) //Prototype WIP
{
	int yShift = row * 50;
	AddText(line, UI_GRID_WIDTH * 6.0f, UI_GRID_HEIGHT * 16.0f + yShift, 50.0f, COLOR_RED, CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_MIDDLE, CORRECT_TEXT_LAYER);
}

/*!
@brief -	Clears out the array array of strings to be rendered to Null char
*//*_____________________________________________________________________________*/
void ResetTextArray(void)
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 32; ++j)
		{
			eText[i][j] = '\0';
			cText[i][j] = '\0';
		}
	}
}

/*!
@brief -	Sorts the text from the enemyRenderText based on the number of
			characters set per line. If Character exceeds the char count per line
			bring the current word to the next line and continue. Calls for the
			rendering of texts function.
*//*_____________________________________________________________________________*/
void TextDraw(void)
{
	int maxLength = MAX_LENGTH;

	int rowCount = 0;
	int textLength = (int)strlen(enemyRenderText);
	int wordIndex = 0;
	int firstWordIndex = 0;
	ResetTextArray();

	for (int i = 0; i <= textLength; ++i)
	{
		if (i <= firstWordIndex + maxLength)
		{
			if (enemyRenderText[i + 1] == ' ' || i == textLength - 1)
			{
				wordIndex = i;
			}
		}
		if (i >= firstWordIndex + maxLength || i == textLength - 1)
		{
			eText[rowCount][maxLength + 1] = '\0';	// Size of [] needs to be MAX_LENGTH + 1
			for (int j = 0; j <=  wordIndex - firstWordIndex; ++j)
			{
				eText[rowCount][j] = enemyRenderText[j + firstWordIndex];
				cText[rowCount][j] = correctRenderText[j + firstWordIndex]; // kiv
			}
			++rowCount;
			firstWordIndex = wordIndex + 2;
		}
	}
	for (int x = 0; x < rowCount; ++x)
	{
		EnemyText(eText[x], x);
		CorrectText(cText[x], x);
	}
}
