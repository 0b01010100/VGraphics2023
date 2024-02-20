#pragma once

class VGame
{
public:
	VGame();
	void start();
	void update();

	class Win32Window* m_wnd;
	class D3D11GraphicsEngine* m_ge;
	class VInputSystem* m_input;
};

