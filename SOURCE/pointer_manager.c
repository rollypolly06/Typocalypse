/*!
file:	pointer_manager.h
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

brief:	calling all functions that deallocates common game entities
		memory here (to be used in level manager)

    Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#include "pointer_manager.h"

/*!
@brief	Deallocates all the memory of common
		game entities in the project
*//*______________________________________________________*/
void FreeMemory(void)
{
	FreeQuadTree();
	FreeInOutput();
	FreePlayer();
	FreeWordGenerator();
}

/*!
@brief	Deallocates all the memory of common
		game entities with images in the project
*//*______________________________________________________*/
void FreeImageMemory(void)
{
	FreeGridSystem();
	FreeTower();
	FreeButtonPointers();
	FreeUI();
	FreeDeathScreen();
	FreeWinScreen();
	FreeEnemy();
	FreeGameState();
}

/*!
@brief	Deallocates all the memory of common
		game entities at the end of the program
*//*______________________________________________________*/
void FreeMemoryLast(void)
{
	FreeRenderManager();
}