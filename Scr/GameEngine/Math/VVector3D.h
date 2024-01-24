#pragma once
struct VVector3D
{
	VVector3D ( ) : X ( 0 ), Y ( 0 ), Z ( 0 ) {}
	VVector3D ( float x, float y, float z ) : X ( x ), Y ( y ), Z ( z ) {}
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

};
