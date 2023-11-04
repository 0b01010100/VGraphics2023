#pragma once
#include "EngineSystem/RenderingSystem/RSystem_Prerequisite.h"
class RenderingSystem;
class SwapChain
{
	SwapChain(RenderingSystem* m_system, DXGI_ADAPTER_DESC setup_desc);
	~SwapChain();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
private:
	friend class RenderingSystem;
};

