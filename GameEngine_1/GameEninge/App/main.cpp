#include "../App/EngineSystem/RenderingSystem/Renderer/Renderer.h"
#include "../App/EngineSystem/WindowSystem/WndSystem.h"
#include "../App/EngineSystem/WindowSystem/GraphicsWindow/GraphicsWindow.h"
int WINAPI WinMain
(
HINSTANCE hInstance,
HINSTANCE hInstancePrev,
LPSTR,
int nCmd
)
{
	//Window d = Window(L"dwdws", 500, 500, hInstance, WS_SYSMENU);
	//Window d2 = Window(L"dwdws1", 500, 500, hInstance, WS_SYSMENU);
	GraphicsWindow d1 = GraphicsWindow(L"GW0",hInstance);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}