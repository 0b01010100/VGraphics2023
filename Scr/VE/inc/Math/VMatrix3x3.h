#pragma once
#include "VVector3D.h"
#include "Requirements.hpp"
static void setIdentity(struct VMatrix3x3* m3x3);
//a 3 by 3 Matrix 
struct VMatrix3x3
{
public:
	
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
		setIdentity(this);
	}
	VMatrix3x3(
		float i00, float i01, float i02,
		float i10, float i11, float i12,
		float i20, float i21, float i22) 
	{
		this->i00 = i00;
		this->i01 = i01;
		this->i02 = i02;

		this->i10 = i10;
		this->i11 = i11;
		this->i12 = i12;

		this->i20 = i20;
		this->i21 = i21;
		this->i22 = i22;
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
static VMatrix3x3 mul(VMatrix3x3 a, VMatrix3x3 b)
{
	VMatrix3x3 c = {};
	for (char i = 0; i < 3;)
	{
		for (char j = 0; j < 3; )
		{
			c.mat[i][j] +=
				a.mat[i][0] * b.mat[0][j] +
				a.mat[i][1] * b.mat[1][j] +
				a.mat[i][2] * b.mat[2][j];
			j++;
		}
		i++;
	}
	return c;
}
/*
\n Matrix Mul
\n
____	|	a	b	c	|	__	|	j	|_____________
A=	|	______	|	*  |  __ |_____________
____	|	d	e	f	|	__	|	k	|_____________
0____	|	______	|	    |  __ |_____________
____	|	g	h	i	|	__	|	l	|_____________
*
n\
n\
n\
\b\b\b returns the value of a 3x3 Matrix times a 3x1 Matrix
*/
static VMatrix3x1 mul(VMatrix3x3 a, VMatrix3x1 b)
{
	VMatrix3x1 c = {};
	//example
	//a = |3    0	 4| b = | 0|
	//	     |5    2	 2|        |2 |
	//	     |8    9	 3|        |2 |
	//c[0] = (3*0) + (0*2) + (4*2)		= 8
	//c[1] = (5 * 0) + (2 * 2) + (2*2) = 8
	//c[2] = (5 * 0) + (2 * 2) + (3*2)= 10
	//
	c.X = (b.X * a.i00) + (b.X * a.i01) + (b.X * a.i02);
	c.Y = (b.Y * a.i10) + (b.Y * a.i11) + (b.Y * a.i12);
	c.Z = (b.Z * a.i20) + (b.Z * a.i21) + (b.Z * a.i22);

	return c;
}

//gives the matrix a numeric identity
//m3x3 = |1    0	  0| 
//____       |0   1	  0|
//____       |0   0	  1|
//know how you can multiply a any number by 1 and get the same thing back
//well matries have something simuliar.
static void setIdentity(VMatrix3x3* m3x3)
{

	m3x3->mat[0][0] = 1;
	m3x3->mat[1][1] = 1;
	m3x3->mat[2][2] = 1;
}