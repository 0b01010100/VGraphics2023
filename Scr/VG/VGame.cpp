#include "VGame.hpp"
#include <Graphics/DX11/Requirements.hpp>
#include <Input/Win32/Win32InputSystem.hpp>
VGame::VGame()
{
	this->m_wnd = new class Win32Window(L"SceneView", 300, 300);
	this->m_ge = new class D3D11GraphicsEngine(this->m_wnd);
	this->m_input = new class Win32InputSystem();
}
void VGame::start()
{
	this->m_ge->start();
}
void VGame::update()
{
	this->m_wnd->update();
	this->m_ge->update();
	if (this->m_input->isKey(VKey::_ESC, VKeyState::up))
	{
		printf_s("I love C++\n");
	};
	if (this->m_input->isKey(VKey::_2, VKeyState::down))
	{
		printf_s("C# and other languages are alright, but not sexy like C++\n");
	}
}
