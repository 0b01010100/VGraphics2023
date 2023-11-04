#include "SwapChain.h"
#include "EngineSystem/RenderingSystem/RenderingSystem.h"



SwapChain::SwapChain(RenderingSystem* m_system, DXGI_ADAPTER_DESC setup_desc)
{
	DXGI_SWAP_CHAIN_DESC sw_Desc = {};
	ZeroMemory(&sw_Desc, sizeof(sw_Desc));
	sw_Desc.BufferCount = 1;

	m_system->m_IDXGIFactory->CreateSwapChain(m_system->m_IDXGIDevice.Get(), &sw_Desc, &m_SwapChain);
}

SwapChain::~SwapChain()
{
}
