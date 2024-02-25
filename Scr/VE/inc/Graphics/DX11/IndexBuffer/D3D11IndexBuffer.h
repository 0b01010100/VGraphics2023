#pragma once
/*
	An IndexBuffer is an array that holds info 
	that helps us outline how a shape should be draw 
	using less computer memory, compared just only using a 
	vertexBuffer

	Can be thought as a list of indies that refer the a particalar verties. where each 
	three sequencal indies corresponds to a triangle
*/
class D3D11IndexBuffer
{
public:
	D3D11IndexBuffer(void* data, unsigned int index_size, unsigned int list_size, class D3D11RenderSys* parent);
	//Smart-Pointer to The windows sepcifc data structure for a Index Buffer 
	struct ID3D11Buffer* m_indexBuffer;
	//Pointer to the class that called the constructor of this class
	class D3D11RenderSys* m_parent = nullptr;
	//the amount of elements in the indexbuffer array
	unsigned int m_size_list;
	//the size of each element in the indexbuffer array
	unsigned int m_index_size;
};

