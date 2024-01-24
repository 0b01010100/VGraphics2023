#include "VGame.hpp"
#include <GraphicsEngine/PlatformSpec/req/D3D.hpp>
#include <Math/All.h>
__declspec(align(16))
struct josh
{
	float x;
	float y;
	float z;
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
Vertex sqr[5]
{
	{{-0.5, 0.5, 0}, {1,1,1} },
	{{0.5, 0.5, 0}, {1,1,1} },
	{{0.5, -0.5, 0}, {1,1,1} },
	{{-0.5, -0.5, 0}, {1,1,1} },
	{{-0.5, 0.5, 0}, {1,1,1} },
};
VGame::VGame ( )
{
	m_hwnd = D3D_CreateWindow ( L"Jos", 600, 500 );
	SetWindowHandleTo ( m_hwnd );
}

void VGame::Start ( )
{
	D3D_SetVertexShader ( L"..\\TestGameEngine\\Scr\\GameEngine\\GraphicsEngine\\Shaders\\VertexMeshLayout.hlsl", "vsmain" );
	D3D_SetPixelShader ( L"..\\TestGameEngine\\Scr\\GameEngine\\GraphicsEngine\\Shaders\\PixelShader.hlsl", "psmain" );
}

void VGame::Update ( )
{
	
	//HRESULT hr = CoInitialize ( nullptr );
	MSG msg;
	PeekMessage ( &msg, 0, 0, 0, PM_REMOVE );
	TranslateMessage ( &msg );
	DispatchMessage ( &msg );
	//inputSystem->Update ( );
	D3D_SetVertexBuffer ( sqr, sizeof ( Vertex ), ARRAYSIZE ( sqr ) );


	josh data = {};
	data.x = 1.F;
	data.y = 1.F;
	data.z = 0.F;
	D3D_SetConstantBuffer ( &data, sizeof ( josh ) );

	D3D_Draw ( D3D_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );


	

	D3D_Present ( );
}
