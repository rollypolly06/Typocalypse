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

brief:	includes all common memory deallocation function
		declarations here. each function definitions to be implemented
		in their own respective source/header files

    Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#ifndef	POINTER_MANAGER_H
#define POINTER_MANAGER_H

void FreeMemory(void);
void FreeImageMemory(void);
void FreeMemoryLast(void);
// Button
void FreeButtonPointers(void);
// Quad tree
void FreeQuadTree(void);
// IO Files
void FreeInOutput(void);
// Enemy
void FreeEnemy(void);
// Grid System
void FreeGridSystem(void);
// Towers
void FreeTower(void);
// Render Manager
void FreeRenderManager(void);
// void Player
void FreePlayer(void);
// Frees the images needed for the UI
void FreeUI(void);
// Word Generator
void FreeWordGenerator(void);
// Free images used in deathscreen
void FreeDeathScreen(void);
// Free images used in win Screen
void FreeWinScreen(void);
// Game State free images
void FreeGameState(void);
// Free button images inside common_gameplay
void FreeCommonGameplay(void);

#endif