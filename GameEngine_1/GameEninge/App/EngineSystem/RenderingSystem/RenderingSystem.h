#pragma once
#include "Renderer/Renderer.h"
#include "EngineSystem/RenderingSystem/RSystem_Prerequisite.h"
#include "EngineSystem/RenderingSystem/SwapChain/SwapChain.h"
class RenderingSystem
{
private:
	RenderingSystem();
	~RenderingSystem();
private:
	static RenderingSystem* get();
private:
	static void CreateDevice();
	static void CreateSwapChain(GraphicsWindow* wnd);
	void CreateVertexBuffer();
	void CreateVertex();
	void CreatePixelShader();

private:
	static ID3D11DeviceContext* m_pImmediateContext;
	static ID3D11Device* m_pDevice;
	static IDXGIDevice* m_IDXGIDevice;
	static IDXGIFactory* m_IDXGIFactory;
	static RenderingSystem* system;
private:
	friend class Renderer;
	friend class SwapChain;
	friend class GraphicsWindow;
};

