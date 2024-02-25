#pragma once
/*
	Device contexts allows us to set many attributes in the Input layout stage 
	So the GPU can know what do draw and how to draw.
	This is a custom class that encapsulates the Microsoft Windows Spesific DeviceContext
*/
#include <Graphics/DX11/Requirements.hpp>
class D3D11DeviceContext
{
public:
	D3D11DeviceContext(struct ID3D11DeviceContext* devcon, class D3D11RenderSys* system);
	//Clears one of the buffers of the swap chain that are being used 
	void clearRenderTarget(float red, float blue, float green, float alpha);
	//Will set the given VertexBuffer to be used in the Vertex Specification stage(stage were the attributes of a vertex a specified to 
	//be used, for example position, color, texcoord, ect)
	void setVertexBuffers(class D3D11VertexBuffer* pVertexBuffer);
	//Will set the VertexShader given, to be used in the Vertex Shader stage
	void setVertexShader(class D3D11VertexShader* pVertexShader);
	//Will set the PixelShader given to be used in the Pixel Shader stage 
	void setPixelShader(class D3D11PixelShader* pPixelShader);
	//Will set the a constant buffer given, to be used in a specfic VertexShader given
	void setVertexShaderConstantBuffer(class D3D11ConstantBuffer* ppConstBuffer[], unsigned char amount);
	//Will set the a constant buffer given, to be used in a specfic PixelShader given
	void setPixelShaderConstantBuffer(class D3D11ConstantBuffer* ppConstBuffer[], unsigned char amount);
	//Will set the index buffer given, to be used
	void setIndexBuffer(class D3D11IndexBuffer* pIndexBuffer);
	//A view port a 2D rectangle used to project a 3D scene to the position of a virtual camera. 
	//Will specfiy View port attributes like
	//SizeX -> viewport width
	//SizeY -> viewport height 
	//MinDepth -> viewport minimume depth for a 3D scene
	//MaxDepth -> viewport maximume depth for a 3D scene
	void setViewPort(float SizeX, float SizeY, float MinDepth = 0b0, float MaxDepth = 0b1);
	//updates the constant buffer with new constant data
	void updateConstBuffer(class D3D11ConstantBuffer* pConstBuffer, void* data);
	//For telling the Graphics Card what to do with the resources created by ID3D11device
	struct ID3D11DeviceContext* m_devCon;
	//Pointer to the class that called the constructor of this class
	class D3D11RenderSys* m_system = nullptr;
};

