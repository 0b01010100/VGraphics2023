#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <wrl/client.h>
#include <memory>
class Win32Window;
class D3D11GraphicsEngine;
class D3D11RenderSys;
class D3D11DeviceContext;
class D3D11SwapChain;
class D3D11VertexBuffer;
class D3D11ConstantBuffer;
class D3D11IndexBuffer;
class D3D11VertexShader;
class D3D11PixelShader;
class D3D11Texture2D;
#include <Window/Win32/Win32Window.hpp>
#include <Graphics/DX11/D3D11GraphicsEngine.hpp>
#include <Graphics/DX11/RenderSystem/D3D11RenderSys.hpp>
#include <Graphics/DX11/DeviceContext/D3D11DeviceContext.hpp>
#include <Graphics/DX11/SwapChain/D3D11SwapChain.hpp>
#include <Graphics/DX11/VertexBuffer/D3D11VertexBuffer.hpp>
#include <Graphics/DX11/ConstantBuffer/D3D11ConstantBuffer.hpp>
#include <Graphics/DX11/IndexBuffer/D3D11IndexBuffer.h>
#include <Graphics/DX11/VertexShader/D3D11VertexShader.hpp>
#include <Graphics/DX11/PixelShader/D3D11PixelShader.hpp>
#include <Graphics/DX11/Texture/D3D11Texture2D.hpp>


#include<string>
#include <sstream>
//Used for Error Handling related to windows only.
#define DX11_ERROR(hr, error)\
{\
	if(FAILED(hr)){\
		std::wostringstream ws; \
		ws << L"DX11 ERROR \n" << error<< L"\n"<< L"Error Code: " << hr << "\n"; \
		OutputDebugString(ws.str().c_str()); \
		MessageBox(0, ws.str().c_str(), L"DX11 ERROR" , 0);\
		return;\
	}\
\
}
//Used for warrning Handling related to windows only.
#define DX11_WARNING(expr,err_code, details)\
{\
	if(expr != 0){\
		std::wostringstream ws; \
		ws << L"DX11 WARNING \n" << details << "\n" << L"Error Code: " << err_code << "\n"; \
		OutputDebugString(ws.str().c_str()); \
		MessageBox(0, ws.str().c_str(), L"DX11 WARNING" , 0);\
	}\
\
}

#include <assert.h>
//Assert if value is null
#define NULL_ERROR(arg, error)\
{\
	if(arg == 0){\
		std::wostringstream ws; \
		ws << error<< L"\n"; \
		OutputDebugString(ws.str().c_str()); \
		MessageBox(0, ws.str().c_str(), L"NULL_ERROR" , 0);\
	}\
}



