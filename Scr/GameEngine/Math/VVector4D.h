#pragma once

struct VVector4D{
	VVector4D ( ) : X ( 0 ), Y ( 0 ), Z ( 0 ), W ( 0 ) {}
	VVector4D ( float x, float y, float z, float w ) : X ( x ), Y ( y ), Z ( z ), W(w) {}
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
};