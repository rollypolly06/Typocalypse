/*!
file:	player.h
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	function declarations for inputs from player when
		playing different levels

    Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#ifndef PLAYER_H
#define PLAYER_H

#define STRING_SIZE		50
#define DEBUG_PLAYER	0

#include "common_headers.h"
#include "enemy.h"

void InitPlayer(void);
void UpdatePlayer(void);
void InitPlayerEnemyReference(Enemy** enemy);
Boolean GetTypingMode(void);

#endif