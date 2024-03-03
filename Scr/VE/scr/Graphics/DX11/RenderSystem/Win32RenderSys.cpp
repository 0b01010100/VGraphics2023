#include <Graphics/DX11/Requirements.hpp>
enum D3D_DRIVER_TYPE drivers[3]
{
	//Drawing is mainly Executed to the GPU when using this Driver
	D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
	//This is a very fast Driver that has the CPU to do most of the Math to get thing draw on the screen.
	D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_WARP,
	//Compatbale with most DirectX Features, but is pretty slow compared the the First two Drivers.
	D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_REFERENCE
};
D3D11RenderSys::D3D11RenderSys(class D3D11GraphicsEngine* engine)
{
	this->m_engine = engine;

	//Create Device, for rendering and creating resources
	struct ID3D11DeviceContext* DevCon = nullptr;
	//The rendering feature from DirectX to target 
	enum D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};
	HRESULT hr = {};
	for (int i = 0; i < ARRAYSIZE(drivers); i++) {
		hr = ::D3D11CreateDevice(nullptr, drivers[i], 0, 0, feature_levels, ARRAYSIZE(feature_levels),
		D3D11_SDK_VERSION, &this->m_dev, 
		0, &DevCon);
		//if the creation of devices SUCCEEDED exit the loop
		if (SUCCEEDED(hr)) 
		{
			break;
		}
	}
	//if the creation of devices FAILED throw Error
	DX11_ERROR(hr, L"Faild to get rendering Devices for DirectX 11 ");
	//else continue on, to get IDXGIDevice struct
	DX11_ERROR(m_dev->QueryInterface(__uuidof(struct IDXGIDevice), (void**)&m_dxgi_dev), L"Faild to get a rendering Device for DirectX 11. Device is IDXGIDevice");
	//else continue on, to get IDXGIAdapter struct
	DX11_ERROR(m_dxgi_dev->GetAdapter(&this->m_adpt), L"Faild to get a rendering Device for DirectX 11. Device is IDXGIAdapter( or Graphics Adapter)");
	//else continue on, to get IDXGIFactory struct
	DX11_ERROR(m_adpt->GetParent(__uuidof(struct IDXGIFactory), (void**)&this->m_fac), L"Faild to get a rendering Device for DirectX 11. Device is IDXGIFactory");
	//make an instant of the custom DeviceContext to encapsulat DX11
	this->m_deviceContext = new class D3D11DeviceContext(DevCon, this);
}

void D3D11RenderSys::createSwapChain()
{
	swapChain = new class D3D11SwapChain( this );
}

class D3D11VertexBuffer* D3D11RenderSys::createVertexBuffer(VDX11_VERTEX_BUFFER_DESC* desc)
{
	class D3D11VertexBuffer* buffer = new class D3D11VertexBuffer(desc, this);
	return buffer;
}

class D3D11VertexShader* D3D11RenderSys::createVertexShader(const wchar_t* file_path)
{
	class D3D11VertexShader* vs = new class D3D11VertexShader(file_path, this);
	return vs;
}

class D3D11PixelShader* D3D11RenderSys::createPixelShader(const wchar_t* file_path)
{
	class D3D11PixelShader* ps = new class D3D11PixelShader(file_path, this);
	return ps;
}

class D3D11ConstantBuffer* D3D11RenderSys::createConstantBuffer(const void* constData, const unsigned int dataSize)
{
	class D3D11ConstantBuffer* cb = new class D3D11ConstantBuffer(constData, dataSize, this);
	return cb;
}

class D3D11Texture2D* D3D11RenderSys::createTexture2D(const char* file_path)
{
	class D3D11Texture2D*  tex = new class D3D11Texture2D(file_path, this);
	return tex;
}

class D3D11IndexBuffer* D3D11RenderSys::createIndexBuffer(void* data, unsigned int index_size, unsigned int list_size)
{
	class D3D11IndexBuffer* ib = new class D3D11IndexBuffer(data, index_size, list_size, this);
	return ib;
}
