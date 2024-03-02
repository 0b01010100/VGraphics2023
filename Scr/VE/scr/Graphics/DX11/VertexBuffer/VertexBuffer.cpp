#include <Graphics/DX11/Requirements.hpp>

D3D11VertexBuffer::D3D11VertexBuffer(struct VDX11_VERTEX_BUFFER_DESC* desc, class D3D11RenderSys* parent)
{
	this->m_size_vertex = desc->size_vertex;
	this->m_size_list = desc->list_size;
	this->m_parent = parent;

	//describ the attribute for the vertex Buffer 
	D3D11_BUFFER_DESC description = {};
	//Size of the data 
	description.ByteWidth = desc->size_vertex * desc->list_size;
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
	gpu_resource.pSysMem = desc->data;

	//Now create vertex Buffer
	DX11_ERROR(
		this->m_parent->m_dev->CreateBuffer(
		&description, 
		&gpu_resource, 
		&this->m_vertexBuffer
	), L"Faild to create Vertex Buffer in D3D11VertexBuffer class");
	if (desc->inputlayouts == nullptr) {
		//Create Input Layout 
		//Set up atributes that the Vertice will have 
		D3D11_INPUT_ELEMENT_DESC ildesc[2] =
		{
			//SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
			{ "POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "UV", 0,  DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		desc->inputlayouts = ildesc;
		desc->ILC = 2;

	}
	//Finally create vertex buffer
	DX11_ERROR( 
		this->m_parent->m_dev->CreateInputLayout(
		desc->inputlayouts,
		desc->ILC,
		desc->vs->m_pBin_Code->GetBufferPointer(),
		desc->vs->m_pBin_Code->GetBufferSize(),
		&this->m_inputLayout 
	), L"Faild to create input layout for VertexBuffer in D3D11VertexBuffer class");
}