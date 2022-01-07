/*!
file:	buttons.h
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

brief:	Setter and getting for game difficulty
		Easy: Global typing with words length <= 10
		Medium: Global typing with words length > 10
		Hard: Typing within tower range with words length > 10

	Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#ifndef	GAME_DIFFICULTY_H
#define GAME_DIFFICULTY_H

typedef enum GameDifficulty
{
	EASY,
	MEDIUM,
	HARD
} GameDifficulty;

void SetGameDifficulty(GameDifficulty gd);
GameDifficulty GetGameDifficulty(void);

#endif