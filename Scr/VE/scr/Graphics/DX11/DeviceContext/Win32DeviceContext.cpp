#include <Graphics/DX11/Requirements.hpp>

D3D11DeviceContext::D3D11DeviceContext(struct ID3D11DeviceContext* devcon, class D3D11RenderSys* system) : m_system(system)
{
	this->m_devCon = devcon;
}

void D3D11DeviceContext::clearRenderTarget(float red, float blue, float green, float alpha)
{
	FLOAT color[4]{ red, blue, green, alpha };
	this->m_devCon->ClearRenderTargetView(m_system->swapChain->m_rtv, color);
	this->m_devCon->OMSetRenderTargets(1, &m_system->swapChain->m_rtv, 0);
}

void D3D11DeviceContext::setVertexBuffers(class D3D11VertexBuffer* pVertexBuffer)
{
	const UINT stride = pVertexBuffer->m_size_vertex;
	const UINT offset = 0b0;
	this->m_devCon->IASetVertexBuffers(0, 1, &pVertexBuffer->m_vertexBuffer, &stride, &offset);
	this->m_devCon->IASetInputLayout(pVertexBuffer->m_inputLayout);
	if (pVertexBuffer->m_vertexBuffer)pVertexBuffer->m_vertexBuffer->Release();
	if (pVertexBuffer->m_vertexBuffer)pVertexBuffer->m_inputLayout->Release();
}

void D3D11DeviceContext::setVertexShader(class D3D11VertexShader* pVertexShader)
{
	this->m_devCon->VSSetShader(pVertexShader->vertex_shader, nullptr, 0);
	if(pVertexShader) pVertexShader->vertex_shader->Release();
}

void D3D11DeviceContext::setPixelShader(class D3D11PixelShader* pPixelShader)
{
	this->m_devCon->PSSetShader(pPixelShader->pixel_shader, nullptr, 0);
	pPixelShader->pixel_shader->Release();
}

void D3D11DeviceContext::setVertexShaderConstantBuffer(class D3D11ConstantBuffer* pConstBuffer[], unsigned char amount)
{
	for (unsigned char index = 0; index < amount;)
	{
		this->m_devCon->VSSetConstantBuffers(index, 1, &pConstBuffer[index]->m_constantBuffer);
		index +=1;
	}
}

void D3D11DeviceContext::setPixelShaderConstantBuffer(class D3D11ConstantBuffer* pConstBuffer[], unsigned char amount)
{
	for (unsigned char index = 0; index < amount;)
	{
		this->m_devCon->PSSetConstantBuffers(index, 1, &pConstBuffer[index]->m_constantBuffer);
		index += 1;
	}
}

void D3D11DeviceContext::setIndexBuffer(class D3D11IndexBuffer* pIndexBuffer)
{
	this->m_devCon->IASetIndexBuffer(pIndexBuffer->m_indexBuffer, DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
}

void D3D11DeviceContext::setViewPort(float SizeX, float SizeY, float MinDepth, float MaxDepth)
{
 	D3D11_VIEWPORT vp = { 0 };
	vp.Width = SizeX;
	vp.Height = SizeY;
	vp.MinDepth = MinDepth;
	vp.MaxDepth = MaxDepth;
	this->m_devCon->RSSetViewports(1, &vp);
}

void D3D11DeviceContext::updateConstBuffer(class D3D11ConstantBuffer* pConstBuffer, void* data)
{
	this->m_devCon->UpdateSubresource(pConstBuffer->m_constantBuffer, 0, 0, data, 0, 0);
}

void D3D11DeviceContext::setPixelShaderTexture(class D3D11Texture2D* texure[], unsigned char amount)
{
	for (unsigned char index = 0; index < amount;)
	{
		this->m_devCon->PSSetShaderResources(index,1, &texure[index]->m_reasourve_view);
		this->m_devCon->PSSetSamplers(index, 1, &texure[index]->m_sample_state);
		index++;
	}
}


