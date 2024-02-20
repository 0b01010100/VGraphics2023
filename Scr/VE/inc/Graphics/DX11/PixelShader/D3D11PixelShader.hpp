#pragma once
/*
	Pixel Shader puts color on the screen
	Also Helps with brightness, Contrast

	This is a custom class that encapsulates the Microsoft Windows Spesific PixelShader
*/
class D3D11PixelShader
{
public:
	D3D11PixelShader(const wchar_t* file_path, class D3D11RenderSys* parent);
	//Smart pointer to the Binary code of the shader 
	class Microsoft::WRL::ComPtr < struct ID3D10Blob > m_pBin_Code = nullptr;
	//Smart pointer to the error code if the shader compiled with errors
	class Microsoft::WRL::ComPtr < struct ID3D10Blob > m_pErr_Code = nullptr;
	//Smart pointer to Windows DX11 version of pixel shader 
	class Microsoft::WRL::ComPtr < struct ID3D11PixelShader > pixel_shader = nullptr;

	//Where the file for Pixel shader is in your drive  
	const wchar_t* m_file_path = nullptr;
	//Pointer to the class that called the constructor of this class
	class D3D11RenderSys* m_parent = nullptr;
};

