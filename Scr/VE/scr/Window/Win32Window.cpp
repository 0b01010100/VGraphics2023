#include <Windows.h>
#include <iostream>
#include <Window/Win32/Win32Window.hpp>

Win32Window::Win32Window(const wchar_t* Name, unsigned int SizeX, unsigned int SizeY)
{
	//Create window
	WNDCLASSEX wc = {};//Description of window
	// Size of data in memory
	wc.cbSize = sizeof(WNDCLASSEX);
	//Get instant of the application
	wc.hInstance = GetModuleHandle(0);
	//Event Handler Proc
	wc.lpfnWndProc = Win32Window::EventHandlerSetUp;
	//Name of window in wide characters 
	wc.lpszClassName = Name;
	//Registers a window class for subsequent use in calls to the CreateWindow or CreateWindowEx function.
	auto classId = ::RegisterClassEx(&wc);

	//Adjust Windows Rect so the the Window is scaled according to the client size of the window
	RECT wr = {};
	wr.right = SizeX;//desired client Size 
	wr.bottom = SizeY;//desired client Size 
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW/*window style*/, 0);
	//Finally create the window
	this->m_hwnd = ::CreateWindowEx(0, Name, Name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top, 0, 0, wc.hInstance, this);

	///Shows the Window Using the SW_SHOW Command in the form or a Macro
	ShowWindow(m_hwnd, SW_SHOW);
	///This WIll Update the Window, ONe Reason WHy this Function is Needed is becuase it will help call the WndProc which checks for Events
	UpdateWindow(m_hwnd);

}

void Win32Window::update()
{
	MSG msg = {};
	//Look for Messages 
	PeekMessage(&msg, this->m_hwnd, 0, 0, PM_REMOVE);

	//Translates virtual-key messages into character messages.
	TranslateMessage(&msg);
	//Dispatches a message to a window procedure.
	DispatchMessage(&msg);

}

void Win32Window::onSize(const RECT& size)
{
	
}
void Win32Window::onFocus()
{
	this->isUserFocus = true;
}
void Win32Window::onUnFocus()
{
	this->isUserFocus = false;
}
bool Win32Window::hasUserFocus()
{
	return this->isUserFocus;
}
RECT Win32Window::getClientSize()
{
	RECT rc = {};
	::GetClientRect(m_hwnd, /*ref OutPut*/&rc);
	::ClientToScreen(m_hwnd, (LPPOINT)&rc.left);
	::ClientToScreen(m_hwnd, (LPPOINT)&rc.right);
	return { rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top };//Return RECT rc variable
}
LRESULT Win32Window::EventHandlerSetUp(HWND hwnd, UINT messages, WPARAM Wparam, LPARAM Lparam)
{
	if (messages == WM_NCCREATE)
	{
		//Get the data that the void pointer is pointing to 
		//CREATESTRUCTW stores alot of info on a window class, Like size, Position, style, and most of all a pointer to custom data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(Lparam);
		//cast the void pointer to custom data to Win32Window*(the data we pased in the last parameter of the CreateWindowEx function)
		Win32Window* const pWnd = static_cast<Win32Window*>(pCreate->lpCreateParams);
		//Storge the pointer to Win32Window for later use 
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		//Set the pointer to StaticEventHandler so this can be used as the event handler 
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Win32Window::StaticEventHandler));
		return pWnd->NonStaticEventHandler(hwnd, messages, Wparam, Lparam);
	}
	return DefWindowProc(hwnd, messages, Wparam, Lparam);
}
LRESULT __stdcall Win32Window::StaticEventHandler(HWND hwnd, UINT messages, WPARAM Wparam, LPARAM Lparam)
{
	//get that pointer to the Win32Window that was passed in earlier by using SetWindowLongPtr macro
	Win32Window* const pWnd = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	//now call the instance function
	return pWnd->NonStaticEventHandler(hwnd, messages, Wparam, Lparam);
}
LRESULT Win32Window::NonStaticEventHandler(HWND hwnd, UINT messages, WPARAM Wparam, LPARAM Lparam)
{
	switch (messages)
	{
		case WM_PAINT:
		{
		
			break;
		}
		case WM_SIZE: 
		{
			Win32Window* window = (Win32Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			if (window) window->onSize(window->getClientSize());
			break;
		}
		case WM_SETFOCUS:
		{
			Win32Window* window = (Win32Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			if (window) window->onFocus();
			break;
		}
		case WM_KILLFOCUS:
		{
			Win32Window* window = (Win32Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			if (window) window->onUnFocus();
			break;
		}

		default:
			break;
	}
	return DefWindowProc(hwnd, messages, Wparam, Lparam);
}
struct VRect<> Win32Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	VRect<> vrc;
	vrc.bottom = rc.bottom;
	vrc.left = rc.left;
	vrc.right = rc.right;
	vrc.top = rc.top;
	return vrc;
}

HWND Win32Window::getHwnd() const
{
	return this->m_hwnd;
}

