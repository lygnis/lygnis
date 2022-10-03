#include "Scene.h"

bool Scene::Init()
{
    return true;
}

bool Scene::Frame()
{
    return true;
}

bool Scene::Render()
{
    return true;
}

bool Scene::Release()
{
    return true;
}

bool Scene::SetDevice(ID3D11Device* _pd3dDevice, ID3D11DeviceContext* _pImmediateContext)
{
    m_pd3dDevice = _pd3dDevice;
    m_pImmediateContext = _pImmediateContext;
    return true;
}

bool Scene::GetSwapChain(IDXGISwapChain* _pSwapChain)
{
    m_pSwapChain = _pSwapChain;
    return true;
}
