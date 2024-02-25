#pragma once
//a four D vector or also called a 4 by 1 Matrix
typedef struct VVector4D 
{
	union
	{
		struct
		{
			float X, Y, Z, W;
		};
		struct
		{
			float vec[4];
		};
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