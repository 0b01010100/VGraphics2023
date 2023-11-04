#include "RenderingSystem.h"
#include "EngineSystem/WindowSystem/GraphicsWindow/GraphicsWindow.h"
#include "Renderer/Renderer.h"
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
RenderingSystem* RenderingSystem::system = new RenderingSystem();
ID3D11DeviceContext* RenderingSystem::m_pImmediateContext = nullptr;
IDXGIFactory* RenderingSystem::m_IDXGIFactory = nullptr;
IDXGIDevice* RenderingSystem::m_IDXGIDevice = nullptr;
ID3D11Device* RenderingSystem::m_pDevice = nullptr;
RenderingSystem::RenderingSystem()
{
    CreateDevice();
}
RenderingSystem::~RenderingSystem()
{

}
RenderingSystem* RenderingSystem::get()
{
    return system;
}
 void RenderingSystem::CreateDevice()
{
         // get the DXGI Factory
         HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&m_IDXGIFactory));
         IDXGIAdapter* adpt;
         if (FAILED(hr))
         {
             throw std::exception("Failed to Create Adapter");
         }
         //Use the factory to get information on the Adapter
         DXGI_ADAPTER_DESC adpt_desc = {};
         for (UINT i = 0; m_IDXGIFactory->EnumAdapters(i, &adpt) != DXGI_ERROR_NOT_FOUND; i++)
         {
             DXGI_ADAPTER_DESC adapterDesc;
             if (SUCCEEDED(adpt->GetDesc(&adapterDesc)))
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
             hr = ::D3D11CreateDevice(adpt, driver, 0, 0, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &m_pDevice, 0, &m_pImmediateContext);
             if (SUCCEEDED(hr))
             {
                 break;
             }
         }
         if (FAILED(hr))
         {
             throw std::exception("Could not Create Device, maybe worng drivers");
         }
         //---------DXGI device
         hr = m_pDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&m_IDXGIDevice));
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

void RenderingSystem::CreateSwapChain(GraphicsWindow* wnd)
{
    wnd->m_SwapChain =  new SwapChain(wnd);
}
