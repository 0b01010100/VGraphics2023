#pragma once
#include "../App/EngineSystem/RenderingSystem/RenderingSystem.h"
#include "EngineSystem/RenderingSystem/RSystem_Prerequisite.h"
class RenderingSystem;
class Renderer
{
public:
	Renderer(HWND wnd, int wnd_hieght, int wnd_width);
private:
	static RenderingSystem* m_system;
private:
	friend class RenderingSystem;
};

