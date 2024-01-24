#include <exception>
#include "WndSystem.h"
Window_base WndSystem::createWindow(LPCWSTR Name, UINT w, UINT h, HINSTANCE Hinstance, const WNDPROC& WndProc , UINT WindowStyle, HBRUSH BackroundColor, LPVOID lParam)
{
    Window_base window_b = {};
    WNDCLASSEX Window = {};
    //0. Window Set Up
    Window.cbSize = sizeof(WNDCLASSEX);
    /* Win 3.x */
    Window.style = 0;
    Window.lpfnWndProc = WndProc;
    Window.cbClsExtra = 0;
    Window.cbWndExtra = 0;
    Window.hInstance = Hinstance;
    Window.hIcon = 0;
    Window.hCursor = LoadIcon(NULL, IDC_ARROW);
    Window.hbrBackground = BackroundColor;
    Window.lpszMenuName = Name;
    Window.lpszClassName = Name;
    /* Win 4.0 */
    Window.hIconSm = 0;
    //1. RedgisterWindow
    if (!RegisterClassEx(&Window))
        throw std::exception("Failed to Create Window, Could set up class for creation");
    //2. Create Window
    window_b.hWnd = CreateWindowEx(
        0,
        Name,
        Name,
        WindowStyle,
        200, 200,
        w, h,
        nullptr,
        nullptr,
        Hinstance,
        lParam);

    if (!window_b.hWnd)
    {
        throw std::exception("Failed to Create Window, hWnd in Null");
    }
    UnregisterClass(Name, Hinstance);
    return window_b;
}
//3. Show Window
void WndSystem::showWindow(const Window_base* wnd, int nCmdShow)
{
    ShowWindow(wnd->hWnd, SW_SHOW);
    
}

void WndSystem::AddExtraData(LONG_PTR data, int typeofData, Window_base& wnd)
{
    ::SetWindowLongPtr(wnd.hWnd, typeofData, data);
}
