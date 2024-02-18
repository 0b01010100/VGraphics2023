#pragma once
/*
	The Vertex Shader is the programmable Shader stage 
	in the rendering pipeline that handles the processing of 
	individual vertices of shapes like (points, lines, and triangles)

	This is a custom class that encapsulates the Microsoft Windows Spesific VertexShader
*/
class D3D11VertexShader
{
public:
	D3D11VertexShader(const wchar_t * file_path, class D3D11RenderSys* parent);
	//pointer to the Binary code of the shader 
	struct ID3D10Blob * m_pBin_Code;
	//pointer to the error code if the shader compiled with errors
	struct ID3D10Blob *m_pErr_Code;
	//pointer to Windows DX11 version of vertex shader 
	struct ID3D11VertexShader * vertex_shader;

	//Where the file for Pixel shader is in your drive  
	const wchar_t* m_file_path = nullptr;
	//Pointer to the class that called the constructor of this class
	class D3D11RenderSys* m_parent = nullptr;
};

