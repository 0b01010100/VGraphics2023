#include <Graphics/DX11/Requirements.hpp>

D3D11VertexBuffer::D3D11VertexBuffer(void* data, unsigned int size_vertex, unsigned int list_size, class D3D11RenderSys* parent)
{
	this->m_size_vertex = size_vertex;
	this->m_size_list = list_size;
	this->m_parent = parent;

	//describ the attribute for the vertex Buffer 
	D3D11_BUFFER_DESC description = {};
	//Size of the data 
	description.ByteWidth = size_vertex * list_size;
	//the resource will be read and wirten to by the GPU
	description.Usage = D3D11_USAGE_DEFAULT;
	//Bind to Input l Assembly as a Vertex buffer
	description.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	description.MiscFlags = 0;
	//0 if no CPU access is necessary
	description.CPUAccessFlags = 0;
	//create a helper structer to help tell to GPU what we want to GPU memory
	D3D11_SUBRESOURCE_DATA gpu_resource = {};
	//make the pointer to to the data we want as a vertex buffer 
	gpu_resource.pSysMem = data;

	//Now create vertex Buffer
	DX11_ERROR(
		this->m_parent->m_dev->CreateBuffer(
		&description, 
		&gpu_resource, 
		&this->m_vertexBuffer
	), L"Faild to create Vertex Buffer in D3D11VertexBuffer class");

	//Create Input Layout 
	//Set up atributes that the Vertice will have 
	D3D11_INPUT_ELEMENT_DESC desc[2] =
	{
		//SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
		{ "POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	//Finally create vertex buffer
	DX11_ERROR( 
		this->m_parent->m_dev->CreateInputLayout(
		desc, 
		ARRAYSIZE(desc),
		this->m_parent->pshader_code, 
		this->m_parent->BytecodeLength, 
		&this->m_inputLayout 
	), L"Faild to create input layout for VertexBuffer in D3D11VertexBuffer class");
}
