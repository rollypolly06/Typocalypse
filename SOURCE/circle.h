/*!
file:	circle.h
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

brief:	struct storing data for a circle

	Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#ifndef CIRCLE_H
#define	CIRCLE_H

#include "points.h"

typedef struct Cirlce
{
	Point pos;
	float r;
}Circle;

#endif