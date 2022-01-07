/*!
file:	geometry.c
author:	Lee Fu Sheng Roy

email:	f.lee@digipen.edu

brief:	Consist of functions involved in points and vectors arithmetic
		Consist of functions to derive transformed vectors as well as
		compute the transformation matrix.

	Copyright � 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/

#include "common_headers.h"

/*!
@brief -	derive vector between 2 points by subtracting point A with point B

@param a -	Object of type Point which indicates the head of the resultant vector
@param b -	Object of type Point which indicates the tail of the resultant vector
*//*_____________________________________________________________________________*/
Vector GetVector(Point a, Point b)	
{
	Vector V;
	V.x = a.x - b.x;
	V.y = a.y - b.y;
	return V;
}

/*!
@brief -	Returns the squared length of a vector

@param V -	Object of type Vector
*//*_____________________________________________________________________________*/
float GetLengthSquare(Vector V) 
{
	return (V.x * V.x) + (V.y * V.y);
}

/*!
@brief -	Dot product of 2 vectors, does not normalize any of the vectors

@param V -	Object of type Vector
@param W -	Object of type Vector
*//*_____________________________________________________________________________*/
float DotProduct(Vector V, Vector W) 
{
	return ((V.x * W.x) + (V.y * W.y));
}

/*!
@brief -		Converts any negative float value to a positive value

@param value -	Value to be converted from negative to positive
*//*_____________________________________________________________________________*/
float AbsFloat(float value) 
{
	return (value < 0) ? -value : value;
}

/*!
@brief -	Normalizes the vector that is passed into this function

@param V -	Object of type Vector
*//*_____________________________________________________________________________*/
Vector NormalizedVector(Vector V) 
{
	float magnitudeV = (float)sqrt(GetLengthSquare(V));
	V.x = V.x / magnitudeV;
	V.y = V.y / magnitudeV;
	return V;
}

/*!
@brief -	Transform the given Vector according to the 2 by 2 transformation Matrix 
			given

@param A -	Object of type Matrix2D to transform the Vector
@param V -	Object of type Vector to be transformed by the matrix
*//*_____________________________________________________________________________*/
Vector TransformVector(Matrix2D A, Vector V)
{
	Vector transformed;
	transformed.x = (A.a * V.x) + (A.b * V.y);
	transformed.y = (A.c * V.x) + (A.d * V.y);
	return transformed;
}

/*!
@brief -		Returns the tranformation matrix of rotation which takes in the 
				value of the angle of rotation in Radians, E.g. PI/2 is 90 degrees. 
				Positive radian value is for clockwise rotation
				Negative radian value is for counter-clockwise rotation

@param theta -	Angle at which the object to be rotated
*//*_____________________________________________________________________________*/
Matrix2D RotationMatrix2D(float theta) 
{
	Matrix2D rotate;
	rotate.a = cosf(theta);		rotate.b = -sinf(theta);
	rotate.c = sinf(theta);		rotate.d = cosf(theta);
	return rotate;
}

/*!
@brief -		Returns the given vector projected onto another given vector

@param V -		Object of type Vector
@param floor -	Object of type Vector, which indicates the "floor" for the Vector
				to be projected onto.
*//*_____________________________________________________________________________*/
Vector ProjectionVector(Vector V, Vector floor)
{
	float num = DotProduct(V, floor);
	float denom = GetLengthSquare(floor);
	float scale = num / denom;
	floor.x = scale * floor.x;
	floor.y = scale * floor.y;
	return floor;
}

/*!
@brief -		Returns the tranformation matrix of reflection. 

@param normal -	Object of type Vector which refers to the surface the given vector 
				will be reflecting off
*//*_____________________________________________________________________________*/
Matrix2D ReflectionMatrix2D(Vector normal)
{
	Vector e1;
	e1.x = 1;
	e1.y = 0;
	
	Vector projectede1 = ProjectionVector(e1, normal);
	projectede1.x *= 2;
	projectede1.y *= 2;

	projectede1.x = projectede1.x - e1.x;
	projectede1.y = projectede1.y - e1.y;

	Vector e2;

	e2.x = 0;
	e2.y = 1;

	Vector projectede2 = ProjectionVector(e2, normal);
	projectede2.x *= 2;
	projectede2.y *= 2;

	projectede2.x = projectede2.x - e2.x;
	projectede2.y = projectede2.y - e2.y;

	Matrix2D M;
	M.a = projectede1.x;	M.b = projectede2.x;
	M.c = projectede1.y;	M.d = projectede2.y;

	return M;
}