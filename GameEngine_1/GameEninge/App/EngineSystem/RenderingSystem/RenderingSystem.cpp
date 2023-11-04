#include "RenderingSystem.h"
D3D_DRIVER_TYPE drivers[]
{
    D3D_DRIVER_TYPE_WARP,
    D3D_DRIVER_TYPE_HARDWARE,
    D3D_DRIVER_TYPE_REFERENCE
};
D3D_FEATURE_LEVEL featureLevels[]
{
    D3D_FEATURE_LEVEL_12_2,
    D3D_FEATURE_LEVEL_12_1,
    D3D_FEATURE_LEVEL_12_0,
    D3D_FEATURE_LEVEL_11_1
};
RenderingSystem::RenderingSystem()
{
    CreateDevice();
}
void RenderingSystem::CreateDevice()
{
    // get the DXGI Factory
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(m_IDXGIFactory.GetAddressOf()));

    if(FAILED(hr))
    {
        throw std::exception("Failed to Create Adapter");
    }
    //Use the factory to get information on the Adapter
    DXGI_ADAPTER_DESC adpt_desc = {};
    for (UINT i = 0; m_IDXGIFactory->EnumAdapters(i, &m_IDXGIAdapter) != DXGI_ERROR_NOT_FOUND; i++)
    {
        DXGI_ADAPTER_DESC adapterDesc;
        if (SUCCEEDED(m_IDXGIAdapter->GetDesc(&adapterDesc)))
        {
            //the adapterDesc Will later be used to set up the swap chain correctly
        }
    }
    if (FAILED(hr)) 
    {
        throw std::exception("Could not retrive adapter");
    }
    //----------Device and DeviceContext
    //Enumerating throw driver types and Feature leves to see which one is siuted for the deivce
    for (D3D_DRIVER_TYPE driver : drivers) 
    {
        hr = ::D3D11CreateDevice(m_IDXGIAdapter.Get(), driver, 0, 0, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &m_pDevice, 0, &m_pImmediateContext);
        if (SUCCEEDED(hr))
        {
            break;
        }
    }
    if(FAILED(hr))
    {
          throw std::exception("Could not Create Device, maybe worng drivers");
    }
    //---------DXGI device
    hr = m_pDevice->QueryInterface(__uuidof(IDXGIDevice), static_cast<void**>(&m_IDXGIDevice));
    if (FAILED(hr))
    {
        throw std::exception("Could not Create IDXGI Device");
    }
    //---------SwapChain
    

}

void RenderingSystem::CreateVertexBuffer()
{
}

void RenderingSystem::CreateVertex()
{
}

void RenderingSystem::CreatePixelShader()
{
}

void RenderingSystem::CreateSwapChain()
{

}
