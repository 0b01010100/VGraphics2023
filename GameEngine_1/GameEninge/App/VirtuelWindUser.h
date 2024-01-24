#include <Windows.h>
#pragma once
//Types of Windows
#define None 0x0
#define ViewPort 0x1
#define Hierachy 0x2
#define Assets 0x3
#define Animation 0x4
//-------------------------

//Window descripter
struct V_WindowDesc
{
	//Window Name
	LPCWSTR VW_Name;
	unsigned int WndType = None;
	//Window Width
	unsigned int sizeX = 980;
	//Window Hieght
	unsigned int sizeY = 650;
	//Window Position X
	unsigned int PosX = CW_USEDEFAULT;
	//Window Position Y
	unsigned int PosY = CW_USEDEFAULT;
	//Application Instacne
	HINSTANCE Program_Instance = 0;
	//Envents Handler ptr
	WNDPROC WndProc = DefWindowProc;
	//This is data that the Window Proc can Accese. Optional.
	//Solve a very big issue with scope
	LPVOID dataExtra;
	//Backround Color
	HBRUSH BrColor = (HBRUSH)2;
	//Customize How your window looks and interacts with the user
	UINT style = 0;
	//How to show the Window (FullScreen, Not Full Screen).
	int nCmdShow = SW_SHOW;
};
struct VHWND 
{
	HWND hwnd = 0;
};
#define WndCr(desc){ WNDCLASSEX wc = { 0 };\
	ZeroMemory(&wc, 0x50);\
	wc.hInstance = desc.Program_Instance;\
	wc.lpszClassName = desc.VW_Name;\
	wc.lpfnWndProc = desc.WndProc;\
	wc.hbrBackground = desc.BrColor;\
	wc.style = desc.style;\
	RegisterClassEx(&wc);\
	V_hWnd.hwnd = CreateWindow(wc.lpszClassName, wc.lpszClassName, wc.style, desc.PosX, desc.PosY, desc.sizeX, desc.sizeY, 0, 0, desc.Program_Instance, 0); \
	UnregisterClass(wc.lpszClassName, desc.Program_Instance); \
	ShowWindow(V_hWnd.hwnd, desc.nCmdShow); \
}

VHWND* __cdecl V_CreateWindow(V_WindowDesc& desc)
{
	VHWND V_hWnd;
	switch (desc.WndType)
	{
	case ViewPort:
		//Make ViewPort Window
		break;
		WndCr(desc);
	case Hierachy:
		//Make Hierachy Window
		break;
	case Assets:
		//Make Assets Window
		break;
	case Animation:
		//Make Animation Window
	default:
		return nullptr;
		break;
	}
}