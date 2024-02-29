#pragma once
#include <Windows.h>
#include <Math/VRect.h>
//A Application Window
//Warning: This class is for windows x86 and x64
class Win32Window
{
public:
	/*
	Name -> Name  of the window
	SizeX  -> Width  of the window
	SizeY  -> Height of the window
	*/
	Win32Window(const wchar_t* Name, unsigned int SizeX, unsigned int SizeY);
	Win32Window() = delete;
	Win32Window(class Win32Window&) = delete;
	//Peeks for messages and handles user interraction with the window 
	void update();
	//Called when the window is resized 
	virtual void onSize(const RECT& size);
	//Called when the User's focus is on the window 
	virtual void onFocus();
	//Called when the User's focus is no longer on the window 
	virtual void onUnFocus();
	//Checks if the user's attention is on this window
	bool hasUserFocus();
	//Gets the cliend size of the window 
	RECT getClientSize();
	//Since windows can only use static functions as an event handler and static functions can't be virtual 
	//This function is a custom event handler for windows that allows us to set up the StaticEventHandler to be usesed and 
	// then the NonStaticEventHandler event handler will be called inside
	static  LRESULT __stdcall EventHandlerSetUp (HWND hwnd, UINT messages, WPARAM Wparam, LPARAM Lparam);
	static  LRESULT __stdcall StaticEventHandler (HWND hwnd, UINT messages, WPARAM Wparam, LPARAM Lparam);
	//A event handler for each instant of the Win32Window class.
	virtual LRESULT NonStaticEventHandler (HWND hwnd, UINT messages, WPARAM Wparam, LPARAM Lparam);
	//gets the width and height of a the window
	VRect<> getClientWindowRect();
	//retrun a copy to the window handle
	HWND getHwnd() const;
	//handle to window 
	HWND m_hwnd = 0;
	//keeps track of wheather the user's focus is on the window 
	bool isUserFocus = 0;
};

