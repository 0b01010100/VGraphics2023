#pragma once

#include <Windows.h>
#include <d3d11.h>
#pragma comment (lib, "d3d11.lib")
#include <d3dcompiler.h>
#pragma comment (lib, "d3dcompiler.lib")
#include <wrl/client.h>
#include <string>
#include <assert.h>
#include <comdef.h> // Include for _com_error

// Macro to check HRESULT and display error details if failed
#define D3D_CHECK_HREASUL_RESULT(hr, errorMsg) \
do { \
    if (FAILED(hr)) \
    { \
        _com_error error(hr); \
        LPCTSTR errorMessage = error.ErrorMessage(); \
        MessageBox(0, errorMessage, errorMsg, 0); \
    } \
} while(0)

struct Devices
{
	Microsoft::WRL::ComPtr < IDXGISwapChain> sw;
	Microsoft::WRL::ComPtr < ID3D11DeviceContext> devCon;
	Microsoft::WRL::ComPtr< ID3D11RenderTargetView> rtv;
};
static LRESULT __stdcall windProc
(
	HWND hwnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (msg)
	{
		//case the user resize the window do
		case WM_SIZE:
		{
			RECT wr = {};
			GetClientRect ( hwnd, &wr );

			// Retrieve the pointer to your Devices object
			Devices& data = reinterpret_cast<Devices&>(*(LONG*)GetWindowLongPtr ( hwnd, GWLP_USERDATA ));

			data.sw->ResizeBuffers ( 1, wr.right - wr.left, wr.bottom - wr.top, DXGI_FORMAT_R8G8B8A8_UNORM, 0 );

			D3D11_VIEWPORT viewport = { 0.0f, 0.0f, static_cast<float>(wr.right - wr.left), static_cast<float>(wr.bottom - wr.top), 0.0f, 1.0f };
			data.devCon->RSSetViewports ( 1, &viewport );
	
			break;
		}
	//Else
		default: 
		{
			break;
		}
	}
	return DefWindowProc ( hwnd, msg, wParam, lParam ); //Call defualt proc
};
//Globally hold that hadle to the window. 
//Here for convience so hwnd doesnt have to be in ever param of the D3D_ functions
alignas(16) struct
{
	HWND hwnd;
}windowHandle = {  };

static ID3D11Buffer* vb_buffer = nullptr;
//Change the window handle to it could late be us by the D3D_ function 
static void SetWindowHandleTo ( HWND hWnd )
{
	windowHandle.hwnd = hWnd;
}
//Allows us to create a MS Specifc window 
static HWND D3D_CreateWindow
(
	LPCWSTR name,//Specfiy Window Name
	unsigned int width,//Specfiy Desired width
	unsigned int  hieght//Specfiy Desired hieght
)
{
	//Helps me Describ what features that the window shold have
	WNDCLASS wc = { 0 };
	wc.lpszClassName = name;//Name of Window
	wc.lpfnWndProc = DefWindowProc; //Window Event Handler 
	wc.hInstance = GetModuleHandle ( nullptr );//Get Current Apllication instance Handle 

	RECT wr = { 0,0, width, hieght };
	//calculates the required size of a window's client rectangle based on the desired size of the entire window, including borders, title bar, and so on.
	::AdjustWindowRect ( &wr, 0, 0 );

	//Register class window Description to be used by the CreateWindow function
	::RegisterClass ( &wc );

	int screenW = GetSystemMetrics ( SM_CXSCREEN ); // Gets monitor  screen width
	int screenH = GetSystemMetrics ( SM_CYSCREEN ); // Gets monitor screen height

	int posX = (screenW - wr.right) / 2;
	int posY = (screenH - wr.bottom) / 2;

	//m_hWnd : Handle to the window
	HWND hwnd = ::CreateWindow ( name, name, WS_OVERLAPPEDWINDOW /*Style*/, posX/*Center window on the X*/, posY /*Center window on the Y*/, width/*width*/, hieght/*Hieght*/, 0, 0, GetModuleHandle ( nullptr ), 0 );

	::ShowWindow ( hwnd, 0b0000101 );//Make window Visable using SW_SHOW or 0b0000101 cmd 

	
	HRESULT hr = {};
	struct Devices* renderingUtils = new Devices ( );
	//No dangling point here haha!!
	IDXGIDevice* dxgiDev = nullptr;
	IDXGIFactory* factory = nullptr;//Allows us to creart DXGI objects
	ID3D11Device* dev = nullptr;//Allows us to create other resource like shaders and textures
	IDXGIAdapter* adapter = nullptr;//Represent the physical graphics card

	D3D_CHECK_HREASUL_RESULT ( D3D11CreateDevice ( nullptr, D3D_DRIVER_TYPE_WARP, 0, 0, 0, 0, D3D11_SDK_VERSION, &dev, 0, &renderingUtils->devCon), L"Faild to init D3D" );//Create rendring devices
	if (SUCCEEDED ( dev->QueryInterface ( __uuidof(IDXGIDevice), (void**)&dxgiDev ) ))
	{
		if (SUCCEEDED ( dxgiDev->GetAdapter ( &adapter ) ))
		{
			if (SUCCEEDED ( adapter->GetParent ( __uuidof(IDXGIFactory), (void**)&factory ) ))
			{
				///Swap Chain creation. 
				//Swap Chain allows use to swich between multiple buffers and get access to them and draw on them rendertarget views to create a texture.
				DXGI_SWAP_CHAIN_DESC sw_desc = { 0 };//Swap Chain descrition
				sw_desc.BufferCount = 0x1;//basically there are 2 buffers not 1. variable name should be extrabufferCount
				sw_desc.BufferDesc.Width = width;
				sw_desc.BufferDesc.Height = hieght;
				sw_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//bits per color channel
				sw_desc.BufferDesc.RefreshRate = { 60U, 0U };
				sw_desc.Windowed = TRUE;//This window will be presented in windowed mode
				sw_desc.SampleDesc = { 1U, 0U };//Quality of the texture sampling on to each pixel
				sw_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//The buffers will be used as render target views
				sw_desc.OutputWindow = hwnd;//Target window
				sw_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

				//Finally create the swap chain
				HRESULT hr = factory->CreateSwapChain ( dev, &sw_desc, &renderingUtils->sw );
				assert ( SUCCEEDED ( hr ) );//throws error message if this procedure didn't go well

				//Get access to the buffer in the wapchain
				ID3D11Texture2D* buffer = nullptr;
				renderingUtils->sw->GetBuffer ( 0, __uuidof(ID3D11Texture2D), (void**)&buffer );
				assert ( SUCCEEDED ( hr ) );//throws error message if this procedure didn't go well
				//Turn that buffer into a render target view so we can draw on that buffer 
				hr = dev->CreateRenderTargetView ( buffer, 0, &renderingUtils->rtv );
				buffer->Release ( );//decrement ref cound to ID3D11Texture2D 
				buffer = nullptr;//make null
				assert ( SUCCEEDED ( hr ) );//throws error message if this procedure didn't go well

				//Clear the render target texture with the color black
				FLOAT color[0b100] = { 0,0,0,1 };//black(r = 0, g = 0, b = 0, a = 1)
				renderingUtils->devCon->ClearRenderTargetView ( *renderingUtils->rtv.GetAddressOf ( ), color );
				//Set the current render taget view to renderingUtils->rtv
				renderingUtils->devCon->OMSetRenderTargets ( 1, renderingUtils->rtv.GetAddressOf ( ), 0 );



			}
			else { assert ( factory != nullptr ); }//throws error message if this procedure didn't go well
		}
		else { assert ( adapter != nullptr ); }//throws error message if this procedure didn't go well

	}
	else { assert ( dxgiDev != nullptr ); }//throws error message if this procedure didn't go well

	//New proc
	SetWindowLongPtr ( hwnd, GWLP_WNDPROC, reinterpret_cast<LONG>(windProc) );//Change Event Handler
	SetWindowLongPtr ( hwnd, GWLP_USERDATA, reinterpret_cast<LONG>(renderingUtils) );//Upload this data into the CREATESTRUCT structure for later use in the event handler
	D3D11_VIEWPORT viewport = { 0.0f, 0.0f, static_cast<float>(wr.right - wr.left), static_cast<float>(wr.bottom - wr.top), 0.0f, 1.0f };
	renderingUtils->devCon->RSSetViewports ( 1, &viewport );
	//Present the buffer( or texture ) in the render target view so the user can see texture created
	renderingUtils->sw->Present ( 0, 0 );

	return hwnd;
};
//Keeps track of all of the Amount of times to draw 
static unsigned int DrawCalls = 0;
//Allows us to set a Vertex Buffer to be Used
static void D3D_SetVertexBuffer 
(
	void * list_vertices,//Lest of verties 
	UINT size_vertex,//Size of a sigle vertex 
	UINT list_size //The Amount of elements in the list 
) 
{
	
	if (windowHandle.hwnd == 0) MessageBox ( 0, L"NULL REF", L"The SetContext function must be called first", 0 );
	Devices& data = reinterpret_cast<Devices&>(*(LONG*)GetWindowLongPtr ( windowHandle.hwnd, GWLP_USERDATA ));
	Microsoft::WRL::ComPtr< ID3D11Device> dev;
	data.devCon->GetDevice ( &dev );
	D3D11_BUFFER_DESC vb_desc = { 0 };
	vb_desc.Usage = D3D11_USAGE_DEFAULT;
	vb_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//Bind to input Assebly stage as a vertex buffer 
	vb_desc.ByteWidth = size_vertex * list_size;
	DrawCalls += list_size;
	D3D11_SUBRESOURCE_DATA vb_sr = { 0 };
	vb_sr.pSysMem = list_vertices;


	D3D_CHECK_HREASUL_RESULT ( dev->CreateBuffer ( &vb_desc, &vb_sr, &vb_buffer ), L"Coun't create vertex buffer " );
	const UINT Strides = size_vertex;
	const UINT Offsets = 0;
	data.devCon->IASetVertexBuffers ( 0, 1, &vb_buffer, &Strides, &Offsets );
	//release the buffer when done using it



}

__declspec(align(0x10))
struct DefualtConstantBuffer
{
	float iResolution[0x2];// width and height
};
//Allows us to set a Constant Buffer to be Used
static void D3D_SetConstantBuffer
(
	void* cdata,
	size_t size_data
)
{
	if (windowHandle.hwnd == 0) MessageBox ( 0, L"NULL REF", L"The SetContext function must be called first", 0 );
	Devices& data = reinterpret_cast<Devices&>(*(LONG*)GetWindowLongPtr ( windowHandle.hwnd, GWLP_USERDATA ));
	Microsoft::WRL::ComPtr< ID3D11Device> dev;
	data.devCon->GetDevice ( &dev );


	// Create a constant buffer description
	D3D11_BUFFER_DESC cb_desc = {};
	cb_desc.Usage = D3D11_USAGE_DEFAULT;
	cb_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//This data will be used a constant buffer 

	// Create a subresource data structure
	D3D11_SUBRESOURCE_DATA cb_sr = { };//Helps us send the data to the GPU

	//Get window Resolution 
	RECT wr = {};
	GetClientRect ( windowHandle.hwnd, &wr);
	//Upload that data in the struct 
	DefualtConstantBuffer defBuff = {};
	defBuff.iResolution[0] = wr.right - wr.left;
	defBuff.iResolution[1] = wr.bottom - wr.top;
	//Then upload the defBuff struct into the subresource data to be sent of into GPU memory
	cb_sr.pSysMem = &defBuff;
	cb_desc.ByteWidth = (UINT)sizeof( defBuff );

	// Create the constant buffers 0 and 1
	HRESULT HR = {};
	ID3D11Buffer* cb_buffer0 = nullptr;
	HR = dev->CreateBuffer ( &cb_desc, &cb_sr, &cb_buffer0 );
	D3D_CHECK_HREASUL_RESULT ( HR, L" Failed to create the defualt constant buffer in D3D_SetConstantBuffer function  " );
	ID3D11Buffer* cb_buffer1 = nullptr;
	cb_desc.ByteWidth = (UINT)size_data;  
	cb_sr.pSysMem = cdata;
	HR = dev->CreateBuffer ( &cb_desc, &cb_sr, &cb_buffer1 );
	D3D_CHECK_HREASUL_RESULT ( HR, L" Failed to create constant buffer in D3D_SetConstantBuffer function  " );
	ID3D11Buffer* buffers[2]{ cb_buffer0 , cb_buffer1 };
	//data.devCon->UpdateSubresource ( cb_buffer, 0, 0, &cdata, 0, 0 );
	//Set the COnstant buffer to be used in the current Pixel Shader
	data.devCon->PSSetConstantBuffers ( 0, 2, buffers );

	//Done Using these Resources
	if (cb_buffer0) cb_buffer0->Release ( );
	if (cb_buffer0) cb_buffer1->Release ( );
	buffers[0] = nullptr;
	buffers[1] = nullptr;
}

//Allows us to set a Vertex Buffer to be Used
static void D3D_SetVertexShader
(
	LPCWSTR file_path,
	LPCSTR entry_point
)
{
	ID3DBlob* pCode = nullptr;
	ID3DBlob* pErrorMsgs = nullptr;
	D3DCompileFromFile ( file_path, 0, 0, entry_point, "vs_5_0", 0, 0, &pCode, &pErrorMsgs );
	if (pErrorMsgs) 
	{ 
		std::wstring warning = L"Warning: Vertex Shader Comilped with Errors";
		MessageBox ( 0, warning.c_str(), L"Warning:", 0 );
	}
	if (windowHandle.hwnd == 0) MessageBox ( 0, L"NULL REF", L"The SetContext function must be called first", 0 );
	Devices& data = reinterpret_cast<Devices&>(*(LONG*)GetWindowLongPtr ( windowHandle.hwnd, GWLP_USERDATA ));
	Microsoft::WRL::ComPtr< ID3D11Device> dev;
	data.devCon->GetDevice ( &dev );
	ID3D11VertexShader* pVertexShader = 0;
	D3D_CHECK_HREASUL_RESULT ( dev->CreateVertexShader ( pCode->GetBufferPointer ( ), pCode->GetBufferSize ( ), 0, &pVertexShader ), L"Major Error: Vertex Shader was not create Succesfully in the D3D_SetVertexShader" );
	data.devCon->VSSetShader ( pVertexShader, 0, 0 );

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		//SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
		{ "POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	UINT size_layout = ARRAYSIZE ( layout );
	ID3D11InputLayout* pInputLayout;
	D3D_CHECK_HREASUL_RESULT ( dev->CreateInputLayout ( layout, size_layout, pCode->GetBufferPointer ( ), pCode->GetBufferSize ( ), &pInputLayout ), L"Failed to create the InputLayout for the shader in the  D3D_SetVertexShader and therefor the shader was not set to be used yet." );

	data.devCon->IASetInputLayout ( pInputLayout );
	//Done Using these Resources
	if(pInputLayout) pInputLayout->Release ( );
	if(pVertexShader)pVertexShader->Release ( );
}
//Allows us to set a Pixel Buffer to be Used
static void D3D_SetPixelShader
(
	LPCWSTR file_path,
	LPCSTR entry_point
)
{
	ID3DBlob* pCode = nullptr;
	ID3DBlob* pErrorMsgs = nullptr;
	D3DCompileFromFile ( file_path, 0, 0, entry_point, "ps_5_0", 0, 0, &pCode, &pErrorMsgs );
	if (pErrorMsgs)
	{
		std::wstring warning = L"Warning: Pixel Shader Comilped with Errors";
		MessageBox ( 0, warning.c_str ( ), L"Warning:", 0 );
		pErrorMsgs->Release ( );
	}

	if (windowHandle.hwnd == 0) MessageBox ( 0, L"NULL REF", L"The SetContext function must be called first", 0 );
	Devices& data = reinterpret_cast<Devices&>(*(LONG*)GetWindowLongPtr ( windowHandle.hwnd, GWLP_USERDATA ));
	Microsoft::WRL::ComPtr< ID3D11Device> dev;
	data.devCon->GetDevice ( &dev );

	ID3D11PixelShader* pPixelShader = nullptr;
	D3D_CHECK_HREASUL_RESULT ( dev->CreatePixelShader ( pCode->GetBufferPointer ( ), pCode->GetBufferSize ( ), 0, &pPixelShader ) , L"Major Error: Pixel Shader was not create Succesfully in the D3D_SetPixelShader function " );

	data.devCon->PSSetShader ( pPixelShader, nullptr, 0 );

	//Done Using these Resources
	if (pCode) pCode->Release ( );
	if (pPixelShader) pPixelShader->Release ( );
};

static void D3D_Draw 
( 
	D3D_PRIMITIVE_TOPOLOGY typology//How to draw the shape
)
{

	if (windowHandle.hwnd == 0) MessageBox ( 0, L"NULL REF", L"The SetContext function must be called first", 0 );
	Devices& data = reinterpret_cast<Devices&>(*(LONG*)GetWindowLongPtr ( windowHandle.hwnd, GWLP_USERDATA ));
	UINT strides = 0;
	data.devCon->IASetPrimitiveTopology ( typology );
	data.devCon->Draw ( DrawCalls, 0);
	DrawCalls = 0;
}
static void D3D_Present
(
)
{
	if (windowHandle.hwnd == 0) MessageBox ( 0, L"NULL REF", L"The SetContext function must be called first", 0 );
	Devices& data = reinterpret_cast<Devices&>(*(LONG*)GetWindowLongPtr ( windowHandle.hwnd, GWLP_USERDATA ));
	data.sw->Present ( 1, 0 );
}