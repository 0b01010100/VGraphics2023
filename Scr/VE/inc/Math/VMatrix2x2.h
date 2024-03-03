#pragma once
#include "Requirements.hpp"
#include "VVector2D.h"
//a 2 by 2 Matrix 
struct VMatrix2x2
{
	VMatrix2x2()
	{
		this->i00 = 0; this->i01 = 0;
		this->i10 = 0; this->i11 = 0;
	}
	VMatrix2x2(float i00, float i01, float i10, float i11)
	{
		this->i00 = i00; this->i01 = i01;
		this->i10 = i10;	this->i11 = i11;
	}
	union
	{
		struct
		{
			float mat[2][2];
		};
		struct 
		{
			float i00, i01;
			float i10, i11;
		};
	};
};
/*
\n Matrix Mul
\n
____	|a		b|____	|e		f|
A = 	|_      _|	__*_	|_      _|		
____	|c		d|____	|g		h|
n\
n\
n\
\b\b\b returns the value of a 2x2 Matrix times a 2x2 Matrix
*/
static struct VMatrix2x2 mul(struct VMatrix2x2 a, struct VMatrix2x2 b)
{
	struct VMatrix2x2 m = {};
	for (char i = 0; i < 2;) 
	{
		for (char j = 0; j < 2; )
		{
			m.mat[i][j] += 
				a.mat[i][0] * b.mat[0][j] + 
				a.mat[i][1] * b.mat[1][j];
			j++;
		}
		i++;
	}
	return m;
}
/*
\n Matrix Mul
\n
____	|	a	b	|	_________	|	(scale) * a	(scale) *b |
A=	|	____	|	* scale =	|	_____________________|
____	|	c	d	|	_________	|	(scale) * c	(scale) * d	|
*
n\
n\
n\
\b\b\b returns the value of a 2x2 Matrix times a scaler value 
*/
static struct VMatrix2x2 mul(struct VMatrix2x2 a, float scale)
{
	struct VMatrix2x2 m = {};
	m.i00 = a.i00 * scale;
	m.i01 = a.i01 * scale;
	m.i10 = a.i10 * scale;
	m.i11 = a.i11 * scale;
	
	return m;
}
/*
\n Matrix Mul
\n
____	|	a	b	|	__	|	e	|_____________|	___ |	a |		_____ |	a |
A=	|	____	|	*  |  __ |_____________|		e * |__ |	  + f *	  |__| 
____	|	c	d	|	__	|	f	|_____________|	___ |	c |		_____ |	c |
*
n\
n\
n\
\b\b\b returns the value of a 2x2 Matrix times a 2x1 Matrix
*/
static VMatrix2x1 mul(struct VMatrix2x2 a, VMatrix2x1 b)
{
	VMatrix2x1 c = {};
	//example
	//a = |3   0 | b = | 0|
	//	     |5    2|        |2 |
	//c[0] = (3*0) + (0*2) = 0
	//c[1] = (5 * 0) + (2 * 2) = 4
	//
	c.X = (a.i00 * b.X) + (a.i01 * b.Y);
	c.Y = (a.i10 * b.X) + (a.i11 * b.Y);
	
	return c;
}
//gives the matrix a numeric identity
//m2x2 = |1    0| 
//____       |0    1|
//know how you can multiply a any number by 1 and get the samw thing back
//well matries have something simular.
static void setIdentity(struct VMatrix2x2* m2x2)
{

	m2x2->mat[0][0] = 1;
	m2x2->mat[1][1] = 1;
}