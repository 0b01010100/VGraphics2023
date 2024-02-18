#include <Win32/GraphicsEngine/DX11/Requirements.hpp>
#include <Win32/DebugTools.h>

D3D11VertexShader::D3D11VertexShader(const wchar_t* file_path, class D3D11RenderSys * parent)
{
	this->m_parent = parent;
	this->m_file_path = file_path;

	//Compile Vertex Shader to Binary code then check if compilation Succeeded
	DX11_ERROR(
		D3DCompileFromFile(
		this->m_file_path,
		nullptr, nullptr,
		"vsmain", 
		"vs_5_0", 
		0, 0, 
		&m_pBin_Code,
		&m_pErr_Code
	), L"FAILED to compile Vertex Shader in the D3D11VertexShader class");
	// Check for errors if any
	if (m_pErr_Code)m_pErr_Code->Release();
	DX11_WARNING(
		m_pErr_Code,
		m_pErr_Code->GetBufferPointer()/*Error info in here if any*/,
		L"Vertex Shader Compiled With Errors in the D3D11VertexShader class");
	//Now Create a Vertex Shader using the binary code
	DX11_ERROR( 
		this->m_parent->m_dev->CreateVertexShader(
		this->m_pBin_Code->GetBufferPointer(), 
		this->m_pBin_Code->GetBufferSize(), 
		0, 
		&this->vertex_shader
	), L"Vertex Shader was not created Succesfully in the D3D11VertexShader class");

	this->m_parent->BytecodeLength = this->m_pBin_Code->GetBufferSize();
	this->m_parent->pshader_code = this->m_pBin_Code->GetBufferPointer();
}
