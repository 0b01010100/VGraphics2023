#pragma once
struct VVector2D
{
	VVector2D() : X(0), Y(0) {}
	VVector2D(float x, float y) : X(x), Y(y) {}
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
};