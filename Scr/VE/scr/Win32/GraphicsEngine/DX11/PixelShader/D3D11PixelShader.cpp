#include <Win32/GraphicsEngine/DX11/Requirements.hpp>
#include <Win32/DebugTools.h>

D3D11PixelShader::D3D11PixelShader(const wchar_t* file_path, D3D11RenderSys* parent)
{
	this->m_parent = parent;
	this->m_file_path = file_path;


	//Compile Pixel Shader to Binary code then check if compilation Succeeded
	DX11_ERROR(
		D3DCompileFromFile(
			this->m_file_path,
			nullptr, nullptr,
			"psmain",
			"ps_5_0",
			0, 0,
			&m_pBin_Code,
			&m_pErr_Code
		), L"FAILED to compile Pixel Shader in the D3D11PixelShader class");
	if(m_pErr_Code)m_pErr_Code->Release();
	// Check for errors if any
	DX11_WARNING(
		m_pErr_Code,
		m_pErr_Code->GetBufferPointer()/*Error info in here if any*/,
		L"Pixel Shader Compiled With Errors in the D3D11PixelShader class");
	//Now Create a Pixel Shader using the binary code
	DX11_ERROR(
		this->m_parent->m_dev->CreatePixelShader(
			this->m_pBin_Code->GetBufferPointer(),
			this->m_pBin_Code->GetBufferSize(),
			nullptr,
			&this->pixel_shader
		), L"Pixel Shader was not created Succesfully in the D3D11PixelShader class");
}
