/*!
file:	AABB.h
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	contain function declarations to handle Axis-Aligned
		Bounding Box (AABB) collision detection

		Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#ifndef	AABB_H
#define AABB_H

#include "common_headers.h"

typedef struct AABB
{
	Point pos;				// position of game object
	float w;				// width length of box
	float h;				// height length of box
} AABB;

AABB GetAxisAlignedBoundingBox(float x, float y, float width, float height);
Boolean CollisionDetectedAABB(AABB a, AABB b);

#endif