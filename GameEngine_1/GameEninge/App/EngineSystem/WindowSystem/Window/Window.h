#pragma once
#include "EngineSystem/WindowSystem/WndSystem.h"
class Window: public Window_base
{
public:
	Window(LPCWSTR Name, UINT size_w, UINT size_h, HINSTANCE hInstance);
	Window(LPCWSTR Name, UINT size_w, UINT size_h, HINSTANCE hInstance, UINT stye);
protected:
	static LRESULT WINAPI SetUpProc(HWND hwnd, UINT messages, WPARAM Wparam, LPARAM Lparam);
	static LRESULT WINAPI StaticEventProc(HWND hwnd, UINT messages, WPARAM Wparam, LPARAM Lparam);
	virtual LRESULT WINAPI Non_StaticEventProc(HWND hwnd, UINT messages, WPARAM Wparam, LPARAM Lparam);

protected:
	virtual void OnFocus();
	virtual void OnKillFocus();
public:
	~Window();
	
};

