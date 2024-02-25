#include <Graphics/DX11/Requirements.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <STB_image/stb_image.h>
//TODO: Finish Texture2D
D3D11Texture2D::D3D11Texture2D(const char * file_path, class D3D11RenderSys* parent)
{
	m_parent = parent;
	//load image data into a unsigned char*
	//m_SizeX-out the size of the X of the image 
	//m_SizeY-out the size of the Y of the image 
	//m_Img_channels-out the amount of color channels of the image
	unsigned char* image_data = stbi_load(file_path, &this->m_Img_Width, &this->m_Img_Height, &this->m_Img_channels, 4);
	//Check for errors if any
	std::stringstream error;
	error <<"Faild to create Texture2D using:\n\n" << file_path << "\n\n";
	NULL_ERROR(image_data, error.str().c_str());

	////get the distance bettween each color channel of the Texture
	int image_pitch = this->m_Img_Width * 4/*Size of each channel*/;

	//Now translate the stbi image data to something that 
	//Can be used by DirectX 
	D3D11_TEXTURE2D_DESC TextureDesc = {};
	//Describe the Width we want for the image
	TextureDesc.Width = this->m_Img_Width;
	//Describe the Height we want for the image
	TextureDesc.Height = this->m_Img_Height;
	//We want one version of the texture
	TextureDesc.MipLevels = 1;
	//the amount of textures we want
	TextureDesc.ArraySize = 1;
	//how the data is storage and interpreted
	//A four-component, 32-bit unsigned-normalized integer sRGB format that supports 8 bits per channel including alpha.
	TextureDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	//Quality and how much to sample the texture
	TextureDesc.SampleDesc = { 1,0 };
	//this data can not be changed
	TextureDesc.Usage = D3D11_USAGE_IMMUTABLE;
	//Bind as shader resource, becuase it will be given the a pixel shader 
	//to shaple out each color channel of the texture to a pixel
	TextureDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
	
	
	D3D11_SUBRESOURCE_DATA TextureSR = {};
	//get image data
	TextureSR.pSysMem = image_data;
	//get the distance bettween each color channel
	TextureSR.SysMemPitch = image_pitch;
	//FINALLY CREATE THE TEXTURE
	DX11_ERROR(parent->m_dev->CreateTexture2D(&TextureDesc, &TextureSR, &this->m_tex), error.str().c_str());

	//Then create a resource view so the pixel shader can view the texture data
	DX11_ERROR(parent->m_dev->CreateShaderResourceView(this->m_tex, nullptr, &this->m_reasourve_view), error.str().c_str());

	//describe how the texture shall be sampled 
	D3D11_SAMPLER_DESC image_sample_desc = {};
	image_sample_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	image_sample_desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	image_sample_desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	image_sample_desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	image_sample_desc.MipLODBias = 0;
	//image_sample_desc.
	// Free allocated memory
	//stbi_image_free(image_data);
}

D3D11Texture2D::~D3D11Texture2D()
{
	if(m_reasourve_view)this->m_reasourve_view->Release();
	if(m_reasourve_view)this->m_tex->Release();
}
