#pragma once
class D3D11Texture2D
{
public:
	D3D11Texture2D(const char* file_path, class D3D11RenderSys* parent);
	// Release texture to avoid memory leak
	~D3D11Texture2D();
	//width of the image
	int m_Img_Width;
	//height of the image
	int m_Img_Height;
	//the amount of color channels
	int m_Img_channels;
	//pointer to DX11 texture interface 
	struct ID3D11Texture2D* m_tex;
	//allows a shader to view a shader resource
	struct ID3D11ShaderResourceView* m_reasourve_view;
	//pointer to render custom render system class
	class D3D11RenderSys* m_parent;
	//keeps track of how to sample a texture 
	struct ID3D11SamplerState* m_sample_state;
};

