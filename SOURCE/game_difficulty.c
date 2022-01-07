/*!
file:	buttons.h
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	Setter and getting for game difficulty
		Easy: Global typing with words length <= 10
		Medium: Global typing with words length > 10
		Hard: Typing within tower range with words length > 10

	Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/

#include "game_difficulty.h"

GameDifficulty gameDifficulty;

/*!
@brief	Sets the game difficulty

@param	gd: game difficulty that player have selected
*//*____________________________________________________________*/
void SetGameDifficulty(GameDifficulty gd)
{
	gameDifficulty = gd;
}

/*!
@brief	Return the game difficulty player have selected

@return	Returns player selected difficulty
*//*____________________________________________________________*/
GameDifficulty GetGameDifficulty(void)
{
	return gameDifficulty;
}