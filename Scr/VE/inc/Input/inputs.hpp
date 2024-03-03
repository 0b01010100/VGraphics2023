#pragma once
#include <Windows.h>
//the state of keys
enum class VKeyState : char
{
	null = 0,
	down,
	up,
};
//select a key to check for
enum class VKey : short
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
	_Q,
	_R,
	_S,
	_T,
	_U,
	_V,
	_W,
	_X,
	_Y,
	_Z,
	//ESCAPE KEY
	_ESC = VK_ESCAPE,
	//RIGHT SHFT
	_RS = VK_RSHIFT,
	//LEFT SHIFT
	_LS = VK_LSHIFT,


};