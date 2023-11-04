#include "Renderer.h"
#include "EngineSystem/RenderingSystem/RenderingSystem.h"
#include "EngineSystem/WindowSystem/GraphicsWindow/GraphicsWindow.h"


void Renderer::Clearbuffer(SwapChain& sw, float r, float g, float b)
{
	const float col[4] = {r, g, b, 1.0};
	RenderingSystem::m_pImmediateContext->ClearRenderTargetView(sw.m_RenderTargetView.Get(), col);
	RenderingSystem::m_pImmediateContext->OMSetRenderTargets(1, sw.m_RenderTargetView.GetAddressOf(), nullptr);
}

void Renderer::Draw(const SwapChain& sw)
{
	EndFrame(sw);
}

void Renderer::EndFrame(const SwapChain& sw)
{

	sw.m_SwapChain->Present(0, 0u);
}




