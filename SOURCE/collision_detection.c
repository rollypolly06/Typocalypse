/*!
file:	collision_detection.c
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	contain function definition for collision detection

	Copyright © 2020 DigiPen, All rights reserved.
*//*_________________________________________________________________*/
#include "collision_detection.h"

/*!
@brief	collision detection between circle and rectangle

@param	cir: circle to be check with rectangle for collision
		rect: rectangle to be check with circle for collision

@return	true if both the shape intersects with each other
*//*______________________________________________________________________*/
Boolean CircleRectCollision(Circle cir, Rect rect)
{
	float dx = max(rect.Min.x, min(cir.pos.x, rect.Max.x)) - cir.pos.x;
	float dy = max(rect.Min.y, min(cir.pos.y, rect.Max.y)) - cir.pos.y;
	return (dx * dx + dy * dy) <= cir.r * cir.r;
}

/*!
@brief	collision detection between mouse point and a rectangle

@param	rect: rectangle to be check collision with mouse position

@return	true if mouse position is inside the rectangle
*//*______________________________________________________________________*/
Boolean MouseInRect(Rect rect)
{
	return CP_Input_GetMouseX() >= rect.Min.x && CP_Input_GetMouseX() <= rect.Max.x &&
		CP_Input_GetMouseY() >= rect.Min.y && CP_Input_GetMouseY() <= rect.Max.y;
}