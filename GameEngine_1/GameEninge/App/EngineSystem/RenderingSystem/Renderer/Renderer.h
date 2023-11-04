#pragma once
#include "../App/EngineSystem/RenderingSystem/RenderingSystem.h"
#include "EngineSystem/RenderingSystem/RSystem_Prerequisite.h"
class RenderingSystem;
class SwapChain;
class Renderer
{
public:
	static void Clearbuffer(SwapChain& sw,float r, float g, float b);
	static void Draw(const SwapChain& sw);
	static void EndFrame(const SwapChain& sw);
public:
	friend class RenderingSystem;
	friend class GraphicsWindow;
	friend class SwapChain;
};

