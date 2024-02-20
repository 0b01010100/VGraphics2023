#pragma once
/*
	 Provides methods for uploading vertex data 
	 (position, normal vector, color, etc.) for primitive shaps like
	 (triangles, cubes, lines) to the video 
	 device
*/
class D3D11VertexBuffer
{
public:
	D3D11VertexBuffer(void* data, unsigned int size_vertex, unsigned int list_size, class D3D11RenderSys* parent);
	//Smart-Pointer to The windows sepcifc data structure for a Vertex Buffer 
	struct ID3D11Buffer * m_vertexBuffer;
	class Microsoft::WRL::ComPtr< struct ID3D11InputLayout > m_inputLayout;
	//Pointer to the class that called the constructor of this class
	class D3D11RenderSys * m_parent = nullptr;

	unsigned int m_size_vertex;
	unsigned int m_size_list;

};

