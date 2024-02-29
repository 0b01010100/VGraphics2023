#pragma once
#include <windows.h>
template <class T = long>
struct VRect 
{
	VRect()
	{
		this->left = 0;
		this->top = 0;
		this->right = 0;
		this->bottom = 0;
	}
	VRect(T left, T top, T right, T bottom)
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}
	T left;
	T top;
	T right;
	T bottom;
};