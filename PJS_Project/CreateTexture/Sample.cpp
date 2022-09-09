#include "Sample.h"
bool		Sample::Init()
{
    DxDevice::Init();       // ����̽� ����
    
    HRESULT hr;
    hr = DirectX::CreateWICTextureFromFile(m_p3dDevice, m_pImmediateContext, L"C:/Users/kgca4153345/Desktop/data/circle_violet.DDS", &m_pResource,
        &m_pShaderResourceView);                // ����̽�, ���ؽ�Ʈ, �ѱ� ���ϰ�ο� �̸� Texture ������� ���� �� ��������� �ޱ�

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
