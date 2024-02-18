#pragma once
/*
	Constant buffers reduce the bandwidth required 
	to update shader constants by allowing shader 
	constants to be grouped together and committed 
	at the same time rather than making individual calls 
	to commit each constant separately. 

	Also that data is constant so It can not modified in the Shaders
	(Pixel/Fragment, Vertex, Hull, ext)

	This is a custom class that encapsulates the Microsoft Windows Spesific constant buffer
*/
class D3D11ConstantBuffer
{
public : 
	D3D11ConstantBuffer(const void* data, const unsigned int data_size, class D3D11RenderSys* parent);
	~D3D11ConstantBuffer(); 
	//Smart-Pointer to The windows sepcifc data structure for a Constant Buffer 
	struct ID3D11Buffer* m_constantBuffer;
	//Pointer to the class that called the constructor of this class
	class D3D11RenderSys* m_parent = nullptr;
};

