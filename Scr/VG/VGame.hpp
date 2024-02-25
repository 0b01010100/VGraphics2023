#pragma once
#include <Debuging/DebugUtils.h>
class VGame
{
public:
	VGame();
	void start();
	void updateQuad();
	void update();

	class Win32Window* m_wnd;
	class D3D11GraphicsEngine* m_ge;
	class VInputSystem* m_input;

	VVector2D pos = { -0.540000, 0.840000, };

};

