#include <Graphics/DX11/Requirements.hpp>

D3D11SwapChain::D3D11SwapChain(class D3D11RenderSys* system)
{
	this->m_system = system;
	
	struct DXGI_SWAP_CHAIN_DESC description = {};
	description.BufferCount = 1;// one extrax buffer so two will be used. 
	//Get window handle  
	HWND hwnd = this->m_system->m_engine->m_window->getHwnd();
	//Get client size of the window 
	RECT wr = {};
	GetClientRect(hwnd, &wr);
	//Adjust the Width of the window based on the Width of the client of the window 
	description.BufferDesc.Width = wr.right - wr.left;
	//Adjust the Height of the window based on the Height of the client of the window 
	description.BufferDesc.Height = wr.bottom - wr.top;
	//Set window to present frame buffers on
	description.OutputWindow = hwnd;
	//Yes output should be in windowed mode. 
	description.Windowed = TRUE;
	//Allows us to change the size of the swapchain buffer and swicth from Windowed mode to another mode
	description.Flags = DXGI_SWAP_CHAIN_FLAG::DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	//How to format the color channels of each the pixel 
	description.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	//Setting RefreshRate
	description.BufferDesc.RefreshRate = { 60U, 0U };
	//How well to sample colors from a texture on to each pixel
	description.SampleDesc = { 1U, 0U };
	//Yes the buffer will be used a Render target view to draw on them 
	description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//discard the contents of the back buffer after we call IDXGISwapChain::Present.
	description.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
	
	//finally try to create swap Chain and do Error checking to make sure creation was ok
	DX11_ERROR( this->m_system->m_fac->CreateSwapChain
	(
		this->m_system->m_dev.Get(),
		&description,
		&m_sw
	), L"Faild to Create SwapChain for DirectX 11 in Win32SwapChain class\n");

	//get 1 Buffer/Texture from the swapChain view
	ID3D11Texture2D * TEX = nullptr;
	DX11_ERROR
	(
		m_sw->GetBuffer(0,
		__uuidof(ID3D11Texture2D),
		(void**)&TEX
	), L"Faild to get a buffer from the swap chain in Win32SwapChain class\n");

	//create render target view and give it the TEX variable, so we can draw to the Buffer/Texture
	DX11_ERROR
	(
		this->m_system->m_dev->CreateRenderTargetView(
		TEX, 
		0, 
		&m_rtv
	), L"Faild to create render target view in Win32SwapChain class");

	//Release ref to resource when done using it
	TEX->Release();
}

D3D11SwapChain::~D3D11SwapChain()
{
	if(m_rtv) this->m_rtv->Release();
}
