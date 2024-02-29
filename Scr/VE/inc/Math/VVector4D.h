#pragma once
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
	}
	//SET THE VALUES IN THE 4D VECTOR TO THE VLAUSE PASSED IN THE PARMETERS
	VVector4D(float X, float Y, float Z, float W)
	{
		this->X = X;
		this->Y = Y;
		this->Z = Z;
		this->W = W;
	}
	//X and vec[0] share the same memory location 
	//Y and vec[1] share the same memory location 
	//Z and vec[2] share the same memory location 
	//W and vec[3] share the same memory location 
	//Our custom vector 4
	union
	{
			//access vector values via single float name like X
			float X, Y, Z, W;
			//access vector values via array like vec an index 2 (vec[2])
			float vec[4];
	};
}VMatrix4x1, Vfloat4;
//multiplies all the values in the 4d vector by the same value 
static struct VVector4D mul(struct VVector4D a, float scale)
{
	struct VVector4D v = {};
	v.X = a.X * scale;
	v.Y = a.Y * scale;
	v.Z = a.Z * scale;
	v.W = a.W * scale;
	return v;
}