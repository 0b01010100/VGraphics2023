#include "GraphicsWindow.h"
#include "EngineSystem/RenderingSystem/Renderer/Renderer.h"
GraphicsWindow::GraphicsWindow(LPCWSTR Name, HINSTANCE hInstance) :
	Window(Name, 960, 560, hInstance, WS_SYSMENU)
{
	RenderingSystem::get()->CreateSwapChain(this);

}

void GraphicsWindow::OnUpdate()
{
	Renderer::Clearbuffer(*m_SwapChain, 0.5, 1, 1);
	Renderer::Draw(*m_SwapChain);

}
