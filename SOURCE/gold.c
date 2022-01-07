/*!
file:   gold.c
author:	Lee Fu Sheng Roy (RenderMsg(), GoldRender())
        Nicole Wong (GoldInit(), GoldAdd(), GoldMinus(), GoldAmount())

email:	f.lee@digipen.edu
        n.wong@digipen.edu

brief:  Function definitions for the functions declared in the  
        gold.h header file with regards to functions related to 
        the gold system of the game

    Copyright � 2020 DigiPen, All rights reserved.

*//*___________________________________________________________________*/

#include "gold.h"

#define STARTING_GOLD   50
#define MAX_GOLD        150
#define TEXT_SIZE       25.0f
#define MSG_DURATION    4.0f

int gold;
char goldBuffer[25];

float msgTimer = MSG_DURATION;
char* goldMsg = "BOOO! Not enough Gold, loser!";

/*!
@brief -	Initializes the starting amount of gold
*//*_____________________________________________________________________________*/
void GoldInit(void)
{
    gold = STARTING_GOLD;
    msgTimer = MSG_DURATION;
}

/*!
@brief -	        Increases the gold amount

@param addAmount -  Amount of gold to increase
*//*_____________________________________________________________________________*/
void GoldAdd(unsigned int addAmount)
{
    gold += addAmount;
    if (gold > MAX_GOLD)
        gold = MAX_GOLD;
}

/*!
@brief -	        Decreases the gold amount

@param addAmount -  Amount of gold to decrease
*//*_____________________________________________________________________________*/
void GoldMinus(unsigned int minusAmount)
{
    gold -= minusAmount;
}

/*!
@brief -    Returns the current amount of gold
*//*_____________________________________________________________________________*/
int GoldAmount(void)
{
    return gold;
}

/*!
@brief -    Sets the msgTimer to be 0
*//*_____________________________________________________________________________*/
void RenderMsg(void)
{
    msgTimer = 0.0f;
}

/*!
@brief -    Renders the amount of gold player has and a message to inform player if
            they lack the gold to do certain actions
*//*_____________________________________________________________________________*/
void GoldRender(void)
{
    sprintf_s(goldBuffer, 25, "Gold: %d", gold);
    AddText(goldBuffer, UI_GRID_WIDTH * 29.0f, 0.0f, UI_GRID_WIDTH, COLOR_WHITE, CP_TEXT_ALIGN_H_RIGHT, CP_TEXT_ALIGN_V_TOP, TEXT_LAYER);
    if (msgTimer < MSG_DURATION)
    {
        AddText(goldMsg, UI_GRID_WIDTH * 13.0f, UI_GRID_HEIGHT * 14.0f, UI_GRID_WIDTH, COLOR_RED, CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP, TEXT_LAYER);
        msgTimer += CP_System_GetDt();
    }
}