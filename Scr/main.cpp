#include <Win32/GraphicsEngine/DX11/Requirements.hpp>
int main() 
{
	Win32Window wnd = Win32Window(L"SceneView", 300, 300);
	D3D11GraphicsEngine ge = D3D11GraphicsEngine(&wnd);
	ge.start();
	while (true)
	{
		wnd.update();
		ge.update();
	}
}