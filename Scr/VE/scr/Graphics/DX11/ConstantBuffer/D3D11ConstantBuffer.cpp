#include <Graphics/DX11/Requirements.hpp>

D3D11ConstantBuffer::D3D11ConstantBuffer(const void* data, const unsigned int data_size, D3D11RenderSys* parent)
{
	m_parent = parent;
	//describ the attribute for the constant Buffer 
	D3D11_BUFFER_DESC description = {};
	//Size of the data 
	description.ByteWidth = data_size;
	//the resource will be read and wirten to by the GPU
	description.Usage = D3D11_USAGE_DEFAULT;
	//Bind to Input l Assembly as a Constant buffer
	description.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//0 if no CPU access is necessary
	description.CPUAccessFlags = 0;
	//create a helper structer to help tell to GPU what we want to GPU memory
	D3D11_SUBRESOURCE_DATA gpu_resource = {};
	//make the pointer to to the data we want as a vertex buffer 
	gpu_resource.pSysMem = data;

	//Now create Constant Buffer
	DX11_ERROR(
		this->m_parent->m_dev->CreateBuffer(
			&description,
			&gpu_resource,
			&this->m_constantBuffer
	), L"Faild to create Constant Buffer in D3D11ConstantBuffer class");
}

D3D11ConstantBuffer::~D3D11ConstantBuffer()
{
	this->m_constantBuffer->Release();
}
