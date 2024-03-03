#include "Cube.h"
__declspec(align(16))
struct constant
{
	VMatrix4x4 m_world = {};
	VMatrix4x4 m_view = {};
	VMatrix4x4 m_proj = {};
	unsigned int m_time;
};
struct Vertex
{
	VVector3D pos;
	VVector3D color;
};
Vertex cube_vertex_list[] =
{
	//X - Y - Z
	//FRONT FACE
	{VVector3D(-0.5f,-0.5f,-0.5f),    VVector3D(1,1,1) },
	{VVector3D(-0.5f,0.5f,-0.5f),    VVector3D(1,0.2,0)},
	{VVector3D(0.5f,0.5f,-0.5f),   VVector3D(1,1,0) },
	{VVector3D(0.5f,-0.5f,-0.5f),     VVector3D(1,0,0) },

	//BACK FACE
	{ VVector3D(0.5f,-0.5f,0.5f),    VVector3D(0,1,0) },
	{ VVector3D(0.5f,0.5f,0.5f),    VVector3D(0,1,1) },
	{ VVector3D(-0.5f,0.5f,0.5f),   VVector3D(0,1,1)},
	{ VVector3D(-0.5f,-0.5f,0.5f),     VVector3D(0,1,0) }

};
unsigned int cube_index_list[] =
{
	//FRONT SIDE
	0,1,2,  //FIRST TRIANGLE
	2,3,0,  //SECOND TRIANGLE
	//BACK SIDE
	4,5,6,//THIRD TRIANGLE
	6,7,4,//FORTH TRIANGLE
	//TOP SIDE
	1,6,5,//FITH TRIANGLE
	5,2,1,//SIXTH TRIANGLE
	//BOTTOM SIDE
	7,0,3,//SEVENTH TRIANGLE
	3,4,7,//EIGHTH TRIANGLE
	//RIGHT SIDE
	3,2,5,//NINETH
	5,4,3,//TENTH
	//LEFT SIDE
	7,6,1,//ELEVENTH
	1,0,7//TWEELTH
};

void Cube::start()
{
	this->window = new Win32Window(L"CUBE SCENE", 300, 300);
	this->graphics = new D3D11GraphicsEngine(this->window);
	this->input = new Win32InputSystem();

	//set up shaders

	D3D11VertexShader* vs = this->graphics->m_system->createVertexShader(L"Scr\\VE\\inc\\Graphics\\Shaders\\CubeShader.hlsl");
	this->graphics->m_system->m_deviceContext->setVertexShader(vs);
	D3D11PixelShader* ps = this->graphics->m_system->createPixelShader(L"Scr\\VE\\inc\\Graphics\\Shaders\\CubeShader.hlsl");
	this->graphics->m_system->m_deviceContext->setPixelShader(ps);

	//set up vertex Buffer 
	VDX11_VERTEX_BUFFER_DESC desc = {};
	D3D11_INPUT_ELEMENT_DESC ildesc[2] =
	{
		//SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
		{ "POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	desc.inputlayouts = ildesc;
	desc.ILC = 2;
	desc.data = cube_vertex_list;
	desc.list_size = ARRAYSIZE(cube_vertex_list);
	desc.size_vertex = sizeof(Vertex);
	desc.vs = vs;
	vb = this->graphics->m_system->createVertexBuffer(&desc);
	this->graphics->m_system->m_deviceContext->setVertexBuffers(vb);
	ib = this->graphics->m_system->createIndexBuffer(cube_index_list, sizeof(unsigned int), ARRAYSIZE(cube_index_list));
	this->graphics->m_system->m_deviceContext->setIndexBuffer(ib);
	
	constant cd = {};
	//cd.World = a;

	cb = this->graphics->m_system->createConstantBuffer(&cd, sizeof(cd));
	this->graphics->m_system->m_deviceContext->setVertexShaderConstantBuffer(&cb, 1);
}
void Cube::getUserInput()
{
	//get user input
	if (this->input->isKey(VKey::_W, VKeyState::down))
	{
		this->rot.Y += 0.02f;
		//VConsole_Log(&this->pos, "Pos");
	}
	if (this->input->isKey(VKey::_S, VKeyState::down))
	{
		this->rot.Y -= 0.02f;
		//VConsole_Log(&this->pos, "Pos");
	}
	if (this->input->isKey(VKey::_A, VKeyState::down))
	{
		this->rot.X -= 0.02f;
		//VConsole_Log(&this->pos, "Pos");
	}
	if (this->input->isKey(VKey::_D, VKeyState::down))
	{
		this->rot.X += 0.02f;
		//VConsole_Log(&this->pos, "Pos");
	}

	if (this->input->isKey(VKey::_1, VKeyState::down)) 
	{
		this->scale.Y += 0.2f;
	
	}
	if (this->input->isKey(VKey::_2, VKeyState::down))
	{
		this->scale.Y -= 0.2f;
	}
	if (this->input->isKey(VKey::_3, VKeyState::down))
	{
		
		this->scale.X -= 0.2f;
	}
	if (this->input->isKey(VKey::_4, VKeyState::down))
	{
		this->scale.X += 0.2f;
	}

}
void Cube::render()
{
	this->graphics->m_system->m_deviceContext->clearRenderTarget(0, 0, 0, 1);

	this->graphics->m_system->m_deviceContext->setViewPort(300.f, 300.f);
	this->graphics->m_system->m_deviceContext->m_devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//draw the shape
	this->graphics->m_system->m_deviceContext->m_devCon->DrawIndexed(ARRAYSIZE(cube_index_list), 0 , 0);
	//present what I drew on to the screen
	this->graphics->m_system->swapChain->m_sw->Present(1, 0);
}
void Cube::updateCube()
{
	constant cc;
	//SIMULATING TIME
	cc.m_time = ::GetTickCount64();
	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;

	m_delta_scale += m_delta_time / 0.55f;

	//CUBE SCALING 
	cc.m_world.setScale(VVector3D(this->scale.X, this->scale.Y, 2.f));
	
	//CUBE ROTATION 
	VMatrix4x4 temp;
	temp.setIdentity();
	
	temp.setRotationZ(m_delta_scale);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(RadiansToDegrees(this->rot.Y));
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(RadiansToDegrees(this->rot.X));
	cc.m_world *= temp;


	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH
	(
		(this->window->getClientWindowRect().right - this->window->getClientWindowRect().left) / 300.0f,
		(this->window->getClientWindowRect().bottom - this->window->getClientWindowRect().top) / 300.0f,
		-4.0f,
		4.0f
	);
	this->graphics->m_system->m_deviceContext->updateConstBuffer(cb,&cc);
}
void Cube::update()
{
	this->window->update();
	getUserInput();
	updateCube();
	render();
	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount64();

	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
}
