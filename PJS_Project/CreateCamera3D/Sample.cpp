#include "Sample.h"


int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    //_CrtSetBreakAlloc(215);
    
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    Sample game;
    game.SetWindow(hInstance, L"DeviceResize", 1000, 800);
    game.Run();
    //_CrtDumpMemoryLeaks();

    return 1;
}

bool Sample::Init()
{
    m_pBox = new ShapeBox;
    m_pBox->SetDevice(m_p3dDevice, m_pImmediateContext);
    m_pBox->Create(L"DefaultObject.txt", L"../../data/1KGCABK.bmp");

    m_pCamera = new MCamera;
    // 카메라 시작 위치, 카메라 타겟 위치 , 가상 업벡터
    m_pCamera->CreateViewMatrix(Vector3D(0, 0, -10), Vector3D(0, 0, 0), Vector3D(0, 1, 0));
    m_pCamera->CreateProjMatrix(1.0f, 100.0f, PI * 0.5f, (float)g_rtClient.right / (float)g_rtClient.bottom);
    return true;
}
bool Sample::Frame()
{
    m_pBox->Frame();
    m_pCamera->Frame();
    return true;
}
bool Sample::Render()
{
    //m_pDevice->m_pImmediateContext->PSSetSamplers(0, 1, &DxState::g_pDefaultSS);
    m_pBox->SetMatrix(&m_pBox->m_cbData.matWorld, &m_pCamera->m_matView, &m_pCamera->m_matProj);
    m_pBox->Render();
    return true;
}

bool Sample::Release()
{
    m_pBox->Release();
    m_pCamera->Release();
    delete m_pCamera;
    delete m_pBox;
    //DxState::Release();
    return true;
}


