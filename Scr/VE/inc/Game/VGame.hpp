#pragma once
#include <Debuging/DebugUtils.h>
#include <Window/Win32/Win32Window.hpp>
#include <Graphics/DX11/Requirements.hpp>
#include <Input/Win32/Win32InputSystem.hpp>
class VGame
{
public:
	virtual void start() = 0;
	virtual void getUserInput() = 0;
	virtual void render() = 0;
	virtual void update() = 0;
	
	Win32Window* window;
	D3D11GraphicsEngine* graphics;
	Win32InputSystem* input;
};

