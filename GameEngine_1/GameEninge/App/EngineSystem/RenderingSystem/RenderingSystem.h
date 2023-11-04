#pragma once
#include "Renderer/Renderer.h"
#include "EngineSystem/RenderingSystem/RSystem_Prerequisite.h"
struct Window_base;
class Renderer;
class SwapChain;
class RenderingSystem
{
public:
	RenderingSystem();
	//Only accesable to the Window which to Render on to
private:

	void CreateDevice();
	void CreateSwapChain();
	void CreateVertexBuffer();
	void CreateVertex();
	void CreatePixelShader();
public:
private:
private:
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pImmediateContext = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Device> m_pDevice = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter> m_IDXGIAdapter = nullptr;
	Microsoft::WRL::ComPtr<IDXGIFactory> m_IDXGIFactory = nullptr;
	Microsoft::WRL::ComPtr<IDXGIDevice> m_IDXGIDevice = nullptr;
private:
	friend class Renderer;
	friend class SwapChain;
};

