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

__declspec(align(16))
struct constant
{
	VMatrix4x4 m_world = {};
	VMatrix4x4 m_view = {} ;
	VMatrix4x4 m_proj = {} ;
	unsigned int m_time;
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
	{{0.5,-0.5,0}, {1,0,1}},
};

D3D11ConstantBuffer* cb;
D3D11VertexBuffer* vb;
D3D11IndexBuffer* ib;
void VGame::start()
{
	float d = 2.9f;
	//create a 2D texture 
	//D3D11Texture2D* tex = this->m_ge->m_system->createTexture2D("C:\\Users\\josdd\\source\\repos\\VE\\VirtuleEngine\\Scr\\VE\\inc\\Graphics\\Textures\\me.jpg");
	//set up shaders
	D3D11VertexShader* vs = this->m_ge->m_system->createVertexShader(L"Scr\\VE\\inc\\Graphics\\Shaders\\VertexShader.hlsl");
	this->m_ge->m_system->m_deviceContext->setVertexShader(vs);
	D3D11PixelShader* ps = this->m_ge->m_system->createPixelShader(L"Scr\\VE\\inc\\Graphics\\Shaders\\PixelShader.hlsl");
	this->m_ge->m_system->m_deviceContext->setPixelShader(ps);
	{

		constant cd = {};
		//cd.World = a;
	
		cb = this->m_ge->m_system->createConstantBuffer(&cd, sizeof(cd));
		this->m_ge->m_system->m_deviceContext->setVertexShaderConstantBuffer(&cb, 1);
	}




	//set up vertex Buffer 
	vb = this->m_ge->m_system->createVertexBuffer(tri, sizeof(Vertex), ARRAYSIZE(tri));
	this->m_ge->m_system->m_deviceContext->setVertexBuffers(vb);
	//ib = this->m_ge->m_system->createIndexBuffer(index_list, sizeof(WORD), ARRAYSIZE(index_list));
	//this->m_ge->m_system->m_deviceContext->setIndexBuffer(ib);
	auto v = VVector4D(1, 1, 1, 1);
	VMatrix3x3 m = {};
	//VConsole_Log(&m, "Josh's 3x3 Indentity Matrix");

}

void VGame::updateQuad()
{

}
void VGame::update()
{

	if (this->m_input->isKey(VKey::_W, VKeyState::down) && this->m_wnd->hasUserFocus()) 
	{
		this->pos.Y += 0.02f;
		VConsole_Log(&this->pos, "Pos");
	}
	if (this->m_input->isKey(VKey::_S, VKeyState::down) && this->m_wnd->hasUserFocus())
	{
		this->pos.Y -= 0.02f;
		VConsole_Log(&this->pos, "Pos");
	}
	if (this->m_input->isKey(VKey::_A, VKeyState::down) && this->m_wnd->hasUserFocus())
	{
		this->pos.X -= 0.02f;
		VConsole_Log(&this->pos, "Pos");
	}
	if (this->m_input->isKey(VKey::_D, VKeyState::down) && this->m_wnd->hasUserFocus())
	{
		this->pos.X += 0.02f;
		VConsole_Log(&this->pos, "Pos");
	}
	this->m_wnd->update();
	this->m_ge->update();

	updateQuad();
	
	this->m_ge->m_system->m_deviceContext->clearRenderTarget(0, 0, 0, 1);

	this->m_ge->m_system->m_deviceContext->setViewPort(300, 300);
	this->m_ge->m_system->m_deviceContext->m_devCon->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	

	VMatrix4x4 temp = {};
	constant cd = {};
	cd.m_world.setScale(VVector3D(0.5f, 0.5f, 0.5f));
	//set the X, Y values in the temp mateix to the value of pos
	temp.setTranslation(VVector3D(this->pos, 0));
	//multiply the world matrix the change the	Translation on the X,Y, and Z
	cd.m_world *= temp;
	cd.m_view.setIdentity();
	//ortograhpic projection
	VRect wr = this->m_wnd->getClientWindowRect();
	cd.m_proj.setOrthoLH
	(
		(wr.right - wr.left) / 400.0f,
		(wr.bottom - wr.top) / 400.0f,
		-4.0f,
		4.0f
	);
	//update the transform data I just change for the positioning of the triangle 
	this->m_ge->m_system->m_deviceContext->updateConstBuffer(cb, &cd);
	//draw the shape
	this->m_ge->m_system->m_deviceContext->m_devCon->Draw(3, 0);
	//present what I drew on to the screen
	this->m_ge->m_system->swapChain->m_sw->Present(1, 0);
}
