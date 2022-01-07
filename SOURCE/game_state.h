/*!
file:  game_state.h
author:  Wong Man Cong
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


#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "common_headers.h"

void PauseGameInit(void);

void PauseGameUpdate(void);

void SetPaused(Boolean paused);

Boolean GetPaused(void);

#endif