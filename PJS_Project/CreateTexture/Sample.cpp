#include "Sample.h"
bool		Sample::Init()
{
    DxDevice::Init();       // 디바이스 생성
    
    HRESULT hr;
    hr = DirectX::CreateWICTextureFromFile(m_p3dDevice, m_pImmediateContext, L"C:/Users/kgca4153345/Desktop/data/circle_violet.DDS", &m_pResource,
        &m_pShaderResourceView);                // 디바이스, 컨텍스트, 넘길 파일경로와 이름 Texture 멤버변수 만든 후 멤버변수로 받기

    return true;
}
bool		Sample::Frame()
{
    DxDevice::Frame();
    return true;
}
bool		Sample::Render()
{
    DxDevice::Render();
    return true;
}
bool		Sample::Release()
{   
    if (m_pResource)
        m_pResource->Release();
    if (m_pShaderResourceView)
        m_pShaderResourceView->Release();
    DxDevice::Release();
    return true;
}



GAME_RUN(P2_CreateDevice_01, 1024, 768)
