#pragma once
/*
	a Custom class ecapsultes the functionally of the DX11 API
*/
class D3D11RenderSys
{
public: 
	D3D11RenderSys(class D3D11GraphicsEngine* engine);
	//Creates a DX11 swap Chain
	void createSwapChain();
	//Creates a DX11 VertexBuffer
	class D3D11VertexBuffer * createVertexBuffer(void* data, unsigned int size_vertex, unsigned int list_size);
	//Creates a DX11 VertexShader
	class D3D11VertexShader * createVertexShader(const wchar_t * file_path);
	//Creates a DX11 PixelShader
	class D3D11PixelShader * createPixelShader(const wchar_t * file_path);
	//Create a DX11 Constant Buffer
	class D3D11ConstantBuffer* createConstantBuffer(const void * constData, const unsigned int dataSize);
	//create a DX11 2D texture using the given file_path
	class D3D11Texture2D* createTexture2D(const char* file_path); 
	//Create a DX11 Index Buffer
	class D3D11IndexBuffer* createIndexBuffer(void* data, unsigned int index_size, unsigned int list_size);
	//for creating MSVC spesfic resources, like vertex buffers, constant buffer and shader

	 struct ID3D11Device * m_dev;
	//For DXGI objects that produce image data.
	 struct IDXGIDevice * m_dxgi_dev;
	//Represents your Graphics adapter 
	struct IDXGIAdapter * m_adpt;
	/*An IDXGIFactory interface implements methods for generating DXGI objects
	(which handle full screen transitions).*/
	struct IDXGIFactory * m_fac;
	//pointer to a custom class that encapsulates the handling of a DX11 swap Chain
	class D3D11SwapChain * swapChain = nullptr;
	//pointer to custom class that encapsulates the whole DX11 rendering API
	class D3D11GraphicsEngine * m_engine = nullptr;
	//pointer to custom class that encapsulates the set up of the Input layout stage in DX11
	class D3D11DeviceContext * m_deviceContext = nullptr;
	//a pointer to that will be used to point to vertex shader binary code
	void* pshader_code = nullptr;
	///the lenght of the vertex shader code
	SIZE_T BytecodeLength = 0;
};



