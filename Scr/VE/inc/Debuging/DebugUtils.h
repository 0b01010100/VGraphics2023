#pragma once
#include <Math/All.h>
#include <stdio.h>
//can be used only if  _CONSOLE and _DEBUG is define
#if defined(_DEBUG) && defined(_CONSOLE)
//prints the values in the c string to the console
//displays a 4 byte int on the screen
static void VConsole_Log(const int in)
{
	printf("%d\n", in);
}
//displays a 4 byte float on the screen
static void VConsole_Log(const float in)
{
	printf("%gf\n", in);
}
//displays a 8 byte float on the screen
static void VConsole_Log(const double in)
{
	printf("%glf\n", in);
}
//displays a 64 byte int on the screen
static void VConsole_Log(const long long in)
{
	printf("%lld\n", in);
}
//displays a C-string vlaue on the screen
static void VConsole_Log(const char* in)
{
	printf(in);
}
//prints the values in the 2D vector to the console
static void VConsole_Log(const VVector2D* in, const char* nameLabel = "")
{
	printf("Vector2D: %s\n| %f |\n| %f |\n", nameLabel, in->X, in->Y);
}
//prints the values in the 3D vector to the console
static void VConsole_Log(const VVector3D* in, const char* nameLabel = "")
{
	printf("Vector3D: %s\n| %f |\n| %f |\n| %f |\n", nameLabel, in->X, in->Y, in->Z);
}
//prints the values in the 4D vector to the console
static void VConsole_Log(const VVector4D* in, const char* nameLabel = "")
{
	printf("Vector4D: %s\n| %f |\n| %f |\n| %f |\n| %f |\n", nameLabel, in->X, in->Y, in->Z, in->Z);
}
//prints the values in the 2x2 Matrix to the console
static void VConsole_Log(const VMatrix2x2* in, const char* nameLabel = "")
{
	printf("Matrix2x2: %s\n[ %f %f ]\n[ %f %f %s\n", nameLabel, in->i00, in->i01, in->i10, in->i11, "]");
}
//prints the values in the 3x3 Matrix to the console
static void VConsole_Log(const VMatrix3x3* in, const char* nameLabel = "")
{
	printf("Matrix3x3: %s\n[ %f %f %f ]\n[ %f %f %f ]\n[ %f %f %f %s\n", nameLabel, 
		in->i00, in->i01, in->i02, 
		in->i10, in->i11, in->i12,
		in->i20, in->i21, in->i22,
		"]\n");
}
static void VConsole_Log(const VMatrix4x4* in, const char* nameLabel = "")
{
	printf("Matrix4x4: %s\n[ %f %f %f %f ]\n[ %f %f %f %f ]\n[ %f %f %f %f ]\n[ %f %f %f %f %s\n", nameLabel,
		in->i00, in->i01, in->i02, in->i03,
		in->i10, in->i11, in->i12, in->i13,
		in->i20, in->i21, in->i22, in->i23,
		in->i30, in->i31, in->i32, in->i33,
		"]\n");
}
#else
//if not in debug replace and the function calls with a empty macros so and compile error will not occor 

//Warning you are in debug mode so the VConsole_Log function will not be called
#define VConsole_Log 

#endif

