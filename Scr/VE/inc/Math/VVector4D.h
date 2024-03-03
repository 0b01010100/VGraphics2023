#pragma once
#include "Requirements.hpp"
#include "Math/VMatrix4x4.h"
//a four D vector or also called a 4 by 1 Matrix
typedef struct VVector4D 
{
	//Intialize all the values in the 4D vector to 0
	VVector4D()
	{
		this->X = 0B0;
		this->Y= 0B0;
		this->Z= 0B0;
		this->W= 0B0;
	}//operator equal(=) to overloaded to once I do this so VVector4D x = VVector4D(); works

	//SET THE VALUES IN THE 4D VECTOR TO THE VLAUSE PASSED IN THE PARMETERS
	VVector4D(float X, float Y, float Z, float W)
	{
		this->X = X;
		this->Y = Y;
		this->Z = Z;
		this->W = W;
	}//operator equal(=) to overloaded to once I do this so VVector4D x = VVector4D(1,1,1); works

	//multiplies the vector components [X,Y,Z] in the 4d vector by a scaler value and returns a copy of the product
	VVector4D operator*(float scale)
	{
		return VVector4D(this->X * scale, this->Y * scale, this->Z * scale, this->W);
	}
	//multiplies the vector components [X,Y,Z] in the 4d vector by a scaler value, sets this VVector4D equal to the result, and then returns a copy of the product
	VVector4D operator*=(float scale)
	{
		return (*this = VVector4D(this->X * scale, this->Y * scale, this->Z * scale, this->W));
	}
	//multiplies a Matrix4x1 (or Vector4D) by a Matrix4x4, sets this Vector4D equal to the result, and returns the result
	VVector4D operator*=(const VMatrix4x4& B)
	{
		this->X = (B.mat[0][0] * X) + (B.mat[0][1] * Y) + (B.mat[0][2] * Z) + (B.mat[0][3] * W);
		this->Y = B.mat[1][0] * (X) + B.mat[1][1] * (Y) + B.mat[1][2] * (Z) + B.mat[1][3] * (W);
		this->Z = B.mat[2][0] * (X) + B.mat[2][1] * (Y) + B.mat[2][2] * (Z) + B.mat[2][3] * (W);
		this->W = B.mat[3][0] * (X) + B.mat[3][1] * (Y) + B.mat[3][2] * (Z) + B.mat[3][3] * (W);
		return (VVector4D(this->X, this->Y, this->Z, this->W));
	}
	//multiplies a Matrix4x1 (or Vector4D) by a Matrix4x4 and returns the result
	VVector4D operator*(const VMatrix4x4& B)
	{
		VVector4D C;
		C.X = (B.mat[0][0] * X) + (B.mat[0][1] * Y) + (B.mat[0][2] * Z) + (B.mat[0][3] * W);
		C.Y = B.mat[1][0] * (X)+B.mat[1][1] * (Y)+B.mat[1][2] * (Z)+B.mat[1][3] * (W);
		C.Z = B.mat[2][0] * (X)+B.mat[2][1] * (Y)+B.mat[2][2] * (Z)+B.mat[2][3] * (W);
		C.W = B.mat[3][0] * (X)+B.mat[3][1] * (Y)+B.mat[3][2] * (Z)+B.mat[3][3] * (W);
		return C;
	}
	//X and vec[0] share the same memory location 
	//Y and vec[1] share the same memory location 
	//Z and vec[2] share the same memory location 
	//W and vec[3] share the same memory location 
	//Our custom vector 4
	union
	{
		struct
		{
			//access vector values via single float name like X
			float X, Y, Z, W;
		};
		struct
		{
			//access vector values via array like vec an index 2 (vec[2])
			float vec[4];
		};

	};
}VMatrix4x1, Vfloat4;
