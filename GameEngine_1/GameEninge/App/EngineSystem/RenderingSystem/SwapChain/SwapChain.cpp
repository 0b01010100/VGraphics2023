#include "SwapChain.h"
#include "EngineSystem/RenderingSystem/RenderingSystem.h"
#include "EngineSystem/WindowSystem/GraphicsWindow/GraphicsWindow.h"
class RenderingSystem;
class GraphicsWindow;
SwapChain::SwapChain(const GraphicsWindow* wnd)
{
	ID3D11Device* device = RenderingSystem::get()->m_pDevice;
	HRESULT hr = {};
	DXGI_SWAP_CHAIN_DESC sw_Desc = {};
	sw_Desc.BufferCount = 1;
	sw_Desc.BufferDesc.Width = 0;
	sw_Desc.BufferDesc.Height =0;
	sw_Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sw_Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sw_Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sw_Desc.BufferDesc.RefreshRate.Numerator = 30;
	sw_Desc.BufferDesc.RefreshRate.Denominator = 1;
	sw_Desc.Windowed = TRUE;
	sw_Desc.OutputWindow = wnd->hWnd;
	sw_Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sw_Desc.SampleDesc.Count = 1;
	sw_Desc.SampleDesc.Quality = 0;
	sw_Desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sw_Desc.Flags = 0;
	hr = RenderingSystem::get()->m_IDXGIFactory->CreateSwapChain
	(RenderingSystem::get()->m_pDevice, & sw_Desc, &m_SwapChain);
	if(FAILED(hr))
	{
		throw std::exception("Couldn't create Swap Chain");
	}

	ID3D11Resource* pBackBuffer = nullptr;
	//D3D11_RENDER_TARGET_VIEW_DESC rtv_desc = {};
	
	//Get Buffer
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**> ( & pBackBuffer));
	RenderingSystem::get()->m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, m_RenderTargetView.GetAddressOf());

	pBackBuffer->Release();

}

SwapChain::~SwapChain()
{
}
