#pragma once
#include "EngineSystem/RenderingSystem/RSystem_Prerequisite.h"
#include "EngineSystem/WindowSystem/GraphicsWindow/GraphicsWindow.h"
class RenderingSystem;
class GraphicsWindow;
class Renderer;
class SwapChain
{
public:
	SwapChain(const GraphicsWindow* wnd);
	~SwapChain();
public:
	//Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
	IDXGISwapChain* m_SwapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
public:
	friend class RenderingSystem;
	friend class Renderer;
};

