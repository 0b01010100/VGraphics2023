#pragma once
#include "EngineSystem/WindowSystem/Window/Window.h"
#include "EngineSystem/RenderingSystem/SwapChain/SwapChain.h"
class SwapChain;
class GraphicsWindow : Window
{
public: 
	GraphicsWindow(LPCWSTR Name, HINSTANCE hInstance);
	void OnUpdate() override;
public:
	SwapChain* m_SwapChain = nullptr;
	friend class SwapChain;
};

