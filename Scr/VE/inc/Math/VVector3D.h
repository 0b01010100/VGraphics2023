#pragma once
#include "VVector2D.h"
#include "Requirements.hpp"
//a three D vector or also called a 3 by 1 Matrix
typedef struct VVector3D
{
	VVector3D() 
	{
		this->X = 0B0;
		this->Y = 0B0;
		this->Z = 0B0;
	}
	VVector3D(float X, float Y, float Z)
	{
		this->X = X;
		this->Y = Y;
		this->Z = Z;
	}
	VVector3D(VVector2D vec2, float Z)
	{
		this->X = vec2.X;
		this->Y = vec2.Y;
		this->Z = Z;
	}
	union
	{
		struct
		{
			float X, Y, Z;
		};
		struct
		{
			float vec[3];
		};
	};

}VMatrix3x1, Vfloat3;
//multiplies the values in the 3d vector by the same value
static struct VVector3D mul(struct VVector3D a, float scale)
{
	struct VVector3D v = {};
	v.X = a.X * scale;
	v.Y = a.Y * scale;
	v.Z = a.Z * scale;
	return v;
}