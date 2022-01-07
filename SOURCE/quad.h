/*!
file:	quad.h
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	quad tree implementation

    Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#ifndef	QUAD_H
#define QUAD_H

#include "node.h"

typedef struct Quad Quad;

void GetEnemy(Enemy** eArr, Point pos, float radius);
void InitQuadTreeEnemyReference(Enemy* enemy);
void DeleteEnemy(const unsigned id);		// call this function when the enemy dies
void UpdateQuadTree(void);
void DrawQuadTree(void);

#endif