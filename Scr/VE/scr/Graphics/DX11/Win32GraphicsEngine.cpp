#include <Graphics/DX11/Requirements.hpp>

D3D11GraphicsEngine::D3D11GraphicsEngine(class Win32Window* window)
{
	this->m_window = window;
	this->m_system = new D3D11RenderSys(this);
	this->m_system->createSwapChain();
}

void D3D11GraphicsEngine::update()
{
	
}
