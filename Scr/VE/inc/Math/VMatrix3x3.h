#pragma once
#include "VVector3D.h"
//a 3 by 3 Matrix 
struct VMatrix3x3
{
	VMatrix3x3() 
	{
		this->i00 = 0B0;
		this->i01 = 0B0;
		this->i02 = 0B0;

		this->i10 = 0B0;
		this->i11 = 0B0;
		this->i12 = 0B0;

		this->i20 = 0B0;
		this->i21 = 0B0;
		this->i22 = 0B0;
	}
	union
	{
		float mat[3][3];
		struct
		{
			float i00, i01, i02;
			float i10, i11, i12;
			float i20, i21, i22;
		};
	};
};
//Multiplies a 3 by 3 matrix by a 3 by 3 and returns th e value 
static struct VMatrix3x3 mul(struct VMatrix3x3 a, struct VMatrix3x3 b)
{
	struct VMatrix3x3 m = {};
	for (char i = 0; i < 3;)
	{
		for (char j = 0; j < 3; )
		{
			m.mat[i][j] +=
				a.mat[i][0] * b.mat[0][j] +
				a.mat[i][1] * b.mat[1][j] +
				a.mat[i][2] * b.mat[2][j];
			j++;
		}
		i++;
	}
	return m;
}