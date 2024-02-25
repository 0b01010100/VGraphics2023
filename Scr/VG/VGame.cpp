#include "VGame.hpp"
#include <Graphics/DX11/Requirements.hpp>
#include <Input/Win32/Win32InputSystem.hpp>
#include <Graphics/DX11/Texture/D3D11Texture2D.hpp>


VGame::VGame()
{
	this->m_wnd = new class Win32Window(L"SceneView", 300, 300);
	this->m_ge = new class D3D11GraphicsEngine(this->m_wnd);
	this->m_input = new class Win32InputSystem();

}

struct alignas(16) constant
{
	VMatrix2x2 World;
	VVector3D pos;
	
	
};
struct Vertex
{
	VVector3D pos;
	VVector3D color;
};
Vertex tri[3]
{
	{{-0.5,-0.5,0}, {1,0,0},},
	{{0,0.5,0}, {0,1,0},},
	{{0.5,-0.5,0}, {0,0,1}},
};

D3D11ConstantBuffer* cb;
D3D11VertexBuffer* vb;
D3D11IndexBuffer* ib;
void VGame::start()
{
	//create a 2D texture 
	//D3D11Texture2D* tex = this->m_ge->m_system->createTexture2D("C:\\Users\\josdd\\source\\repos\\VE\\VirtuleEngine\\Scr\\VE\\inc\\Graphics\\Textures\\me.jpg");
	//set up shaders
	D3D11VertexShader* vs = this->m_ge->m_system->createVertexShader(L"Scr\\VE\\inc\\Graphics\\Shaders\\VertexShader.hlsl");
	this->m_ge->m_system->m_deviceContext->setVertexShader(vs);
	D3D11PixelShader* ps = this->m_ge->m_system->createPixelShader(L"Scr\\VE\\inc\\Graphics\\Shaders\\PixelShader.hlsl");
	this->m_ge->m_system->m_deviceContext->setPixelShader(ps);
	VMatrix2x2 a = {
	1,0,
	0,1
	};
	VVector2D b =
	{
		-0.5,-0.5
	};
	mul(a, b);
	constant cd = {};
	cd.World = a;
	cb = this->m_ge->m_system->createConstantBuffer(&cd, sizeof(cd));
	this->m_ge->m_system->m_deviceContext->setVertexShaderConstantBuffer(&cb, 1);



	//set up vertex Buffer 
	vb = this->m_ge->m_system->createVertexBuffer(tri, sizeof(Vertex), ARRAYSIZE(tri));
	this->m_ge->m_system->m_deviceContext->setVertexBuffers(vb);
	//ib = this->m_ge->m_system->createIndexBuffer(index_list, sizeof(WORD), ARRAYSIZE(index_list));
	//this->m_ge->m_system->m_deviceContext->setIndexBuffer(ib);


	
	//this->pos = mul(a, this->pos);
	
	VConsole_Log(&a);
	VConsole_Log(&this->pos);
}

void VGame::updateQuad()
{

}
void VGame::update()
{
	if (this->m_input->isKey(VKey::_W, VKeyState::down) && this->m_wnd->hasUserFocus()) 
	{
		this->pos.Y += 0.02;
		VConsole_Log(&this->pos, "Pos");
	}
	if (this->m_input->isKey(VKey::_S, VKeyState::down) && this->m_wnd->hasUserFocus())
	{
		this->pos.Y -= 0.02;
		VConsole_Log(&this->pos, "Pos");
	}
	if (this->m_input->isKey(VKey::_A, VKeyState::down) && this->m_wnd->hasUserFocus())
	{
		this->pos.X -= 0.02;
		VConsole_Log(&this->pos, "Pos");
	}
	if (this->m_input->isKey(VKey::_D, VKeyState::down) && this->m_wnd->hasUserFocus())
	{
		this->pos.X += 0.02;
		VConsole_Log(&this->pos, "Pos");
	}
	this->m_wnd->update();
	this->m_ge->update();

	updateQuad();

	this->m_ge->m_system->m_deviceContext->clearRenderTarget(0, 0, 0, 1);
	RECT wr = this->m_wnd->getClientWindowRect();
	this->m_ge->m_system->m_deviceContext->setViewPort(300, 300);
	this->m_ge->m_system->m_deviceContext->m_devCon->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	constant cd = {};
	VMatrix2x2 a = {
		1,this->pos.X,
		1,this->pos.Y
	};
	cd.World = a;
	cd.pos = VVector3D(this->pos, 1);
	
	this->m_ge->m_system->m_deviceContext->updateConstBuffer(cb, &cd);
	//this->m_ge->m_system->m_deviceContext->m_devCon->DrawIndexed(ib->m_size_list, 0, 0);
	this->m_ge->m_system->m_deviceContext->m_devCon->Draw(3, 0);

	this->m_ge->m_system->swapChain->m_sw->Present(1, 0);
}
