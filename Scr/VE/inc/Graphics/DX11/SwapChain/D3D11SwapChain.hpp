#pragma once
/*
	A swap chain is a collection of buffers
	that are used for displaying frames to the user. 
	Each time an application presents a new frame 
	for display, the first buffer in the swap chain takes 
	the place of the displayed buffer. This process is 
	called swapping or flipping.
*/
class D3D11SwapChain
{
public:
	D3D11SwapChain(class D3D11RenderSys* system);
	~D3D11SwapChain();
	//load swap chain buffer
	void loadBuffers(HWND hwnd);
	//Pointer to Microsoft Windows specfic SwapChain
	struct IDXGISwapChain * m_sw;
	//RenderTargetViews allows us to draw on a swap chain buffer 
	//This is a pointer to a Microsoft Windows specfic RenderTargetView
	struct ID3D11RenderTargetView * m_rtv;
	//Pointer to my custom render system class that ecapsulates the functionally of DX11 render system
	class D3D11RenderSys* m_system;
};

