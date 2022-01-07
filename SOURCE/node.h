/*!
file:	node.h
author:	Wong Man Cong
		Lee Fu Sheng Roy
		Phua Tze Cheng Jennifer
		Thea Sea
		Nicole Wong

email:	w.mancong@digipen.edu

brief:	nodes for quad tree data struct

    Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#ifndef	NODE_H
#define NODE_H

#include "boolean.h"
#include "enemy.h"

#define NODE_SIZE		10

typedef struct Node
{
	Enemy* ePtr[NODE_SIZE];			// store the address of the enemy
	unsigned currNodeSize;			// number of enemy it is storing
	Boolean checked;				// if node have been check then don't check again
} Node;

#endif