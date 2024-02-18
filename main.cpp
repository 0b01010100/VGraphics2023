#include <Win32/GraphicsEngine/DX11/Requirements.hpp>
int main() 
{
	
	Win32Window w = Win32Window(L"j", 300U, 300U);
	
	while (true) 
	{
		w.update();
	}
	return 0;
}