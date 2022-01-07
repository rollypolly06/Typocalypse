/*!
file:	collision_detection.h
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	contain header files and methods for collision detection

	Copyright © 2020 DigiPen, All rights reserved.
*//*_________________________________________________________________*/
#ifndef	COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "AABB.h"
#include "basic_shapes.h"

Boolean CircleRectCollision(Circle cir, Rect rect);
Boolean MouseInRect(Rect rect);

#endif