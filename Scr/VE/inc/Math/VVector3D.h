#pragma once
#include "VVector2D.h"
#include "Requirements.hpp"
//a three D vector or also called a 3 by 1 Matrix
typedef struct VVector3D
{
	//initalizes all the vector components [X, Y, Z] to zero
	VVector3D() 
	{
		this->X = 0B0;
		this->Y = 0B0;
		this->Z = 0B0;
	}
	//initalizes all the vector components [X, Y, Z] to in corresponding order to the parameter
	VVector3D(float X, float Y, float Z)
	{
		this->X = X;
		this->Y = Y;
		this->Z = Z;
	}
	//initalizes to [X, Y] components using a VVector2D and use a normal float vaule to init the [Z] component
	VVector3D(VVector2D vec2, float Z)
	{
		this->X = vec2.X;
		this->Y = vec2.Y;
		this->Z = Z;
	}
	//like *= for normal numbers exp: j *= 9 
	//multiplies the vector component [X, Y] by a scaler 
	//And then set this vector equal to the product and also returns a copy of the result
	VVector3D operator*=(const float scale)
	{
		return (*this = VVector3D(this->X * scale, this->Y * scale, this->Z * scale));
	}
	//like * for normal numbers exp: j * 9
	//multiplies each component in the vector3 by a scaler value
	//Also a the copy of the resulting VVector3D is returned 
	VVector3D operator*(const float scale)
	{
		return (VVector3D(this->X * scale, this->Y * scale, this->Z * scale));
	}
	/*
		multiplies the[X, Y, Z] components of this vector by vector B then
		sets ininalizes a copy of with the values
	*/
	VVector3D operator*(const VVector3D& B)
	{
		return VVector3D(this->X * B.X, this->Y * B.Y, this->Z * B.Z);
	}
	/*
		multiplies the[X, Y, Z] components of this vector by vector B then
		sets this vector's componts equal to the result and returns a copy of this VVector3D
	*/
	VVector3D operator*=(const VVector3D& B)
	{
		return (*this = VVector3D(this->X * B.X, this->Y * B.Y, this->Z * B.Z));
	}

	//X and vec[0] share the same memory location 
	//Y and vec[1] share the same memory location 
	//Z and vec[2] share the same memory location 
	//Our custom vector 3
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
//this same class can also be refered to as VMatrix3x1 or Vfloat3 when use the variable
}VMatrix3x1, Vfloat3;
