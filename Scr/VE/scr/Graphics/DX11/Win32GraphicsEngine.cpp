#include <Graphics/DX11/Requirements.hpp>
#include <Math/All.h>
D3D11GraphicsEngine::D3D11GraphicsEngine(class Win32Window* window)
{
	this->m_window = window;
	this->m_system = new D3D11RenderSys(this);
	this->m_system->createSwapChain();
}

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
	{{-0.5, 0.5, 0}, {1,0,1} },
	{{0.5, 0.5, 0}, {1,1,0} },
	{{0.5, -0.5, 0}, {0,1,1} },
	{{-0.5, -0.5, 0}, {1,1,1} },
	{{-0.5, 0.5, 0}, {1,1,1} },
};
Vertex index_sqr[4]
{
	{{-0.2, 0.5, 0}, {1,0,1} },
	{{0.5, 0.5, 0}, {1,1,0} },
	{{0.5, -0.2, 0}, {0,1,1} },
	{{-0.5, -0.5, 0}, {1,1,1} },
};
struct alignas(16) 
{
	float x = 0.2f;
	float y = 1;
	float z = 0.2f;
}ConstData;

unsigned int index_buffer[]
{
	0, 1, 2, 0, 3,
};
void D3D11GraphicsEngine::start()
{
	D3D11VertexShader* vs = this->m_system->createVertexShader(L"Scr\\VE\\inc\\Graphics\\Shaders\\VertexShader.hlsl");
	this->m_system->m_deviceContext->setVertexShader(vs);
	D3D11PixelShader* ps = this->m_system->createPixelShader(L"Scr\\VE\\inc\\Graphics\\Shaders\\PixelShader.hlsl");
	this->m_system->m_deviceContext->setPixelShader(ps);
}
void D3D11GraphicsEngine::update()
{
	RECT wr = {}; 
	
	GetClientRect(this->m_window->m_hwnd, &wr);

	this->m_system->m_deviceContext->setViewPort( 300, 300);

	this->m_system->m_deviceContext->clearRenderTarget(0, 0, 0, 0);

	this->m_system->m_deviceContext->m_devCon->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	D3D11VertexBuffer* vb = this->m_system->createVertexBuffer
	(index_sqr, sizeof(Vertex), ARRAYSIZE(index_sqr));
	this->m_system->m_deviceContext->setVertexBuffers(vb);

	D3D11ConstantBuffer* cb = this->m_system->createConstantBuffer(&ConstData, sizeof(ConstData));
	this->m_system->m_deviceContext->setVertexShaderConstantBuffer(&cb, 1);
	this->m_system->m_deviceContext->setPixelShaderConstantBuffer(&cb, 1);

	D3D11IndexBuffer* ib = this->m_system->createIndexBuffer(index_buffer, sizeof(unsigned int), ARRAYSIZE(index_buffer));
	this->m_system->m_deviceContext->setIndexBuffer(ib);
	this->m_system->m_deviceContext->m_devCon->DrawIndexed(5, 0, 0);
	this->m_system->swapChain->m_sw->Present(1, 0);
}
