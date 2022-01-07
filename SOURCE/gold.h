/*!
file:	gold.h
author:	Lee Fu Sheng Roy

email:	f.lee@digipen.edu

brief:	Contains the declaration of functions defined in gold.c

	Copyright © 2020 DigiPen, All rights reserved.

*//*____________________________________________________________*/

#ifndef GOLD_H
#define GOLD_H

#include "common_headers.h"
#include "string.h"


// Initializes the amount of gold
void GoldInit(void);

// Increases the gold amount
void GoldAdd(unsigned int addAmount);

// Decreases the gold amount
void GoldMinus(unsigned int minusAmount);

// Returns the amount of gold
int GoldAmount(void);

// Renders not enough gold message
void RenderMsg(void);

// Renders amount of gold
void GoldRender(void);

#endif