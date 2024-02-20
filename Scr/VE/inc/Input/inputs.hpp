#pragma once
#include <Windows.h>
enum class VKeyState : char
{
	null = 0,
	down,
	up,
};
enum class VKey : char
{
	null = 0,
	//Numbers

	_0 = '0',
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,
	//Letters

	_A = 'A',
	_B,
	_C,
	_D,
	_E,
	_F,
	_G,
	_H,
	_I,
	_J,
	_K,
	_L,
	_M,
	_N,
	_O,
	_P,
	//LEFT SHIFT
	_LS,
	//RIGHT SHFT
	_RS,

	//ESCAPE KEY
	_ESC = VK_ESCAPE
};