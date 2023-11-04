#include "Window.h"
#include "EngineSystem/WindowSystem/WndSystem.h"
Window::Window(LPCWSTR Name, UINT size_w, UINT size_h, HINSTANCE hInstance)
{
	Window_base d =  WndSystem::createWindow(Name, size_w, size_h, hInstance, Window::SetUpProc, 0, 0, this);
	this->hWnd = d.hWnd;
	this->hieght = d.hieght;
	this->width = d.width;
	WndSystem::showWindow(this);

}

Window::Window(LPCWSTR Name, UINT size_w, UINT size_h, HINSTANCE hInstance, UINT stye)
{
	Window_base d = WndSystem::createWindow(Name, size_w, size_h, hInstance, Window::SetUpProc, stye, 0, this);
	this->hWnd = d.hWnd;
	this->hieght = d.hieght;
	this->width = d.width;
	WndSystem::showWindow(this);

}

LRESULT Window::SetUpProc(HWND hwnd, UINT messages, WPARAM Wparam, LPARAM Lparam)
{		
	if (messages == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(Lparam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Window::StaticEventProc));
		return pWnd->Non_StaticEventProc(hwnd, messages, Wparam, Lparam);
	}
	return DefWindowProc(hwnd, messages, Wparam, Lparam);
}
LRESULT __stdcall Window::StaticEventProc(HWND hwnd, UINT messages, WPARAM Wparam, LPARAM Lparam)
{
	Window* const pWnd = reinterpret_cast<Window*>( GetWindowLongPtr(hwnd, GWLP_USERDATA) );
	return pWnd->Non_StaticEventProc(hwnd, messages, Wparam, Lparam);
}
LRESULT Window::Non_StaticEventProc(HWND hwnd, UINT messages, WPARAM Wparam, LPARAM Lparam)
{
	switch (messages)
	{

		case WM_SETFOCUS:
		{
			OnFocus();
			break;
		}
		case WM_KILLFOCUS: 
		{
			OnFocus();
			break;
		}

		default:
			break;
	}
	return DefWindowProc(hwnd, messages, Wparam, Lparam);
}

void Window::OnFocus()
{

}

void Window::OnKillFocus()
{

}

Window::~Window()
{
	//Window Already Distroyed by Window Proc
}
