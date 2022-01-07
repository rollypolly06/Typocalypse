/*!
file:	geometry.h
author:	Lee Fu Sheng Roy

email:	f.lee@digipen.edu

brief:	includes all points and vectors function declarations here. 
		each function definitions to be implemented in their own 
		respective source/header files. structs called Vector and 
		Matrix2D also defined here.

	Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/

#ifndef	GEOMETRY_H
#define GEOMETRY_H

#include "common_headers.h"
#include "points.h"

typedef struct Vector
{
	float x;
	float y;
} Vector;

/*
layout of 2x2 matrix is as such:

| a	b |
| c	d |

*/
typedef struct Matrix2D
{
	float a;	float b;
	float c;	float d;
} Matrix2D;

Vector GetVector(Point a, Point b);

Vector NormalizedVector(Vector V);

float GetLengthSquare(Vector V);

float DotProduct(Vector V, Vector W);

float AbsFloat(float value);

Vector TransformVector(Matrix2D A, Vector V);

Matrix2D RotationMatrix2D(float theta);

Vector ProjectionVector(Vector V, Vector floor);

Matrix2D ReflectionMatrix2D(Vector normal);

#endif