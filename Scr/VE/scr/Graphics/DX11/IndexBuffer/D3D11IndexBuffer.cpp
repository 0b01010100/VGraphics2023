#include <Graphics/DX11/Requirements.hpp>
D3D11IndexBuffer::D3D11IndexBuffer(void* data, unsigned int index_size, unsigned int list_size, D3D11RenderSys* parent)
{
	this->m_index_size = index_size;
	this->m_size_list = list_size;
	this->m_parent = parent;

	//describ the attribute for the index Buffer 
	struct D3D11_BUFFER_DESC description = { 0 };
	//Size of the whole data 
	description.ByteWidth = index_size * list_size;
	//the resource will be read and wirten to by the GPU
	description.Usage = D3D11_USAGE_DEFAULT;
	//Bind to Input l Assembly as a Vertex buffer
	description.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//0 if no CPU access is necessary
	description.CPUAccessFlags = 0;

	//create a helper structer to help tell to GPU what we want to GPU memory
	D3D11_SUBRESOURCE_DATA gpu_resource = {};
	//make the pointer to to the data we want as a index buffer 
	gpu_resource.pSysMem = data;

	//Now create index Buffer
	DX11_ERROR(
		this->m_parent->m_dev->CreateBuffer(
			&description,
			&gpu_resource,
			&this->m_indexBuffer
		), L"Faild to create Vertex Buffer in D3D11IndexBuffer class");
}
