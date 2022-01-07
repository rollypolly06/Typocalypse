/*!
file:	rectangle.h
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

brief:	struct storing data for a rectangle

	Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#ifndef RECTANGLE_H
#define	RECTANGLE_H

#include "points.h"

typedef struct Rect
{
	Point Min;
	Point Max;
	float w;
	float h;
} Rect;

#endif