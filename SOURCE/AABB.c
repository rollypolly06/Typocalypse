/*!
file:	AABB.h
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	contain function definitions to handle Axis-Aligned
		Bounding Box (AABB) collision detection

		Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#include "AABB.h"

/*!
@brief	initialise bounding box
@return	a copy of the bounding box
*//*_____________________________________________________________________________________*/
AABB GetAxisAlignedBoundingBox(float x, float y, float width, float height)
{
	AABB a;
	a.pos.x = x; a.pos.y = y; a.w = width; a.h = height;
	return a;
}

/*!
@brief	check if two bounding box is colliding
@return	true if the two bounding box is colliding
*//*_____________________________________________________________________________________*/
Boolean CollisionDetectedAABB(AABB a, AABB b)
{
	return a.pos.x < b.pos.x + b.w &&
		   a.pos.x + a.w > b.pos.x &&
		   a.pos.y < b.pos.y + b.h &&
		   a.pos.y + a.h > b.pos.y;
}