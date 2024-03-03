#include "TwoD.hpp"

TwoD::TwoD() : VGame()
{
	this->window = new class Win32Window(L"SceneView", 300, 300);
	this->graphics = new class D3D11GraphicsEngine(this->window);
	this->input = new class Win32InputSystem();
}

__declspec(align(16))
struct constant
{
	VMatrix4x4 m_world = {};
	VMatrix4x4 m_view = {};
	VMatrix4x4 m_proj = {};
};
struct Vertex
{
	VVector3D pos;
	VVector3D color;
};
struct VertexAndTex
{
	VVector3D pos;
	VVector2D color;
};
Vertex tri[3]
{
	{{-0.5,-0.5,0}, {1,0,0},},
	{{0,0.5,0}, {0,1,0},},
	{{0.5,-0.5,0}, {1,0,1}},
};
VertexAndTex VTtri[3]
{
	{{-0.5,-0.5,0}, {0,1},},
	{{0,0.5,0}, {0.5,0},},
	{{0.5,-0.5,0}, {1,1}},
};

D3D11ConstantBuffer* cb;
D3D11VertexBuffer* vb;
D3D11IndexBuffer* ib;
void TwoD::start()
{
	//create a 2D texture 
	D3D11Texture2D* tex = this->graphics->m_system->createTexture2D("Scr\\VE\\inc\\Graphics\\Textures\\me.jpg");
	this->graphics->m_system->m_deviceContext->setPixelShaderTexture(&tex, 1);
	//set up shaders

	D3D11VertexShader* vs = this->graphics->m_system->createVertexShader(L"Scr\\VE\\inc\\Graphics\\Shaders\\TextureSampling.hlsl");
	this->graphics->m_system->m_deviceContext->setVertexShader(vs);
	D3D11PixelShader* ps = this->graphics->m_system->createPixelShader(L"Scr\\VE\\inc\\Graphics\\Shaders\\TextureSampling.hlsl");
	this->graphics->m_system->m_deviceContext->setPixelShader(ps);
	{
		constant cd = {};
		//cd.World = a;

		cb = this->graphics->m_system->createConstantBuffer(&cd, sizeof(cd));
		this->graphics->m_system->m_deviceContext->setVertexShaderConstantBuffer(&cb, 1);
	}

	//set up vertex Buffer 
	VDX11_VERTEX_BUFFER_DESC desc = {};
	desc.data = VTtri;
	desc.list_size = ARRAYSIZE(VTtri);
	desc.size_vertex = sizeof(VertexAndTex);
	desc.vs = vs;
	vb = this->graphics->m_system->createVertexBuffer(&desc);
	this->graphics->m_system->m_deviceContext->setVertexBuffers(vb);
	//ib = this->m_ge->m_system->createIndexBuffer(index_list, sizeof(WORD), ARRAYSIZE(index_list));
	//this->m_ge->m_system->m_deviceContext->setIndexBuffer(ib);
	auto v = VVector4D(1, 1, 1, 1);
	VMatrix3x3 m = {};
	//VConsole_Log(&m, "Josh's 3x3 Indentity Matrix");
}

void TwoD::getUserInput()
{
	//get user input
	if (this->input->isKey(VKey::_W, VKeyState::down) && this->window->hasUserFocus())
	{
		this->pos.Y += 0.02f;
		//VConsole_Log(&this->pos, "Pos");
	}
	if (this->input->isKey(VKey::_S, VKeyState::down) && this->window->hasUserFocus())
	{
		this->pos.Y -= 0.02f;
		//VConsole_Log(&this->pos, "Pos");
	}
	if (this->input->isKey(VKey::_A, VKeyState::down) && this->window->hasUserFocus())
	{
		this->pos.X -= 0.02f;
		//VConsole_Log(&this->pos, "Pos");
	}
	if (this->input->isKey(VKey::_D, VKeyState::down) && this->window->hasUserFocus())
	{
		this->pos.X += 0.02f;
		//VConsole_Log(&this->pos, "Pos");
	}
}
void TwoD::updateQuad()
{
	VMatrix4x4 temp = {};
	constant cd = {};
	cd.m_world.setScale(VVector3D(0.5f, 0.5f, 0.5f) );

	//set the X, Y values in the temp mateix to the value of pos
	temp.setTranslation(VVector3D(this->pos, 1));
	//multiply the world matrix the change the	Translation on the X,Y, and Z
	cd.m_world *= temp;
	//change the Z axis by 90 in degress
	temp.setRotationZ(30);
	cd.m_world *= temp;

	cd.m_view.setIdentity();
	//ortograhpic projection
	VRect<> wr = this->window->getClientWindowRect();

	cd.m_proj.setOrthoLH
	(
		(wr.right - wr.left) / 400.0f,
		(wr.bottom - wr.top) / 400.0f,
		-4.0f,
		4.0f
	);
	//update the transform data I just change for the positioning of the triangle 
	this->graphics->m_system->m_deviceContext->updateConstBuffer(cb, &cd);
}
void TwoD::render()
{
	this->graphics->m_system->m_deviceContext->clearRenderTarget(1, 0, 0, 1);

	this->graphics->m_system->m_deviceContext->setViewPort(300, 300);
	this->graphics->m_system->m_deviceContext->m_devCon->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//draw the shape
	this->graphics->m_system->m_deviceContext->m_devCon->Draw(3, 0);
	//present what I drew on to the screen
	this->graphics->m_system->swapChain->m_sw->Present(1, 0);
}
void TwoD::update()
{
	this->window->update();
	getUserInput();
	updateQuad();
	render();
}


