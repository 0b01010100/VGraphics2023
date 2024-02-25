#pragma once
/*
	GraphicsEngine for x86 and x64 windows only 
*/
class D3D11GraphicsEngine
{
public:
	//init the GraphicsEngine with a ref to the window 
	D3D11GraphicsEngine(class Win32Window* window);
	D3D11GraphicsEngine() = delete;
	D3D11GraphicsEngine(class D3D11GraphicsEngine&) = delete;
	//called after the start to update the Graphics engine
	void  update();
	class Win32Window* m_window;
	class D3D11RenderSys* m_system;


};

