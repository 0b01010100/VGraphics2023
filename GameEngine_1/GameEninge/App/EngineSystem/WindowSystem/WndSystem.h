#pragma once
#include <Windows.h>
//all window base classes must Inherite from this
struct Window_base
{
public:
	HWND hWnd;
	UINT width;
	UINT hieght;
};

struct WndSystem
{
public:
	static Window_base createWindow(LPCWSTR Name, UINT w, UINT h, HINSTANCE Hinstance, const WNDPROC& WndProc = DefWindowProc, UINT WindowStyle = 0, HBRUSH BackroundColor = 0, LPVOID lParam = nullptr);

	static void showWindow(const Window_base* wnd, int nCmdShow = 0);

	void static AddExtraData(LONG_PTR data, int typeofData, Window_base& wnd);
private:
	friend class Window_base;
};

