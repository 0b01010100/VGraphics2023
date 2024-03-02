#pragma once
#include "Requirements.hpp"
//a two D vector or also called a 2 by 1 Matrix
typedef struct VVector2D
{
	VVector2D() 
	{
		this->X = 0B0;
		this->Y = 0B0;
	}
	VVector2D(float X, float Y)
	{
		this->X = X;
		this->Y = Y;
	}
	union
	{
		struct
		{
			float X, Y;
		};
		struct
		{
			float vec[2];
		};
	};
}VMatrix2x1, Vfloat2;
//multiplies the values in one 2d vector by the values in the other 2d vector 
static struct VVector2D mul(struct VVector2D a, struct VVector2D b)
{
	struct VVector2D v = {};
	v.X = a.X * b.X;
	v.Y = a.Y * b.Y;
	return v;
}
//multiplies the values in one 2d vector by the same float value and returns the value
static struct VVector2D mul(struct VVector2D a, float scale)
{
	struct VVector2D v = {};
	v.X = a.X * scale;
	v.Y = a.Y * scale;
	return v;
}