#pragma once
#include <Math/All.h>
#include <stdio.h>
//can be used only if  _CONSOLE is define
#if defined(_DEBUG) && defined(_CONSOLE)
//prints the values in the c string to the console
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
	printf("Vector2D: %s\n| %f |\n| %f |\n %f |\n", nameLabel, in->X, in->Y, in->Z);
}
//prints the values in the 2x2 Matrix to the console
static void VConsole_Log(const VMatrix2x2* in, const char* nameLabel = "")
{
	printf("Matrix2x2: %s\n[ %f %f ]\n[ %f %f %s\n", nameLabel, in->i00, in->i01, in->i10, in->i11, "]");
}
#else
//if not in debug replace and the function calls with a empty macros so and compile error will not occor 
#define VConsole_Log 

#endif

