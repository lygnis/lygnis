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
    return true;
}
bool Sample::Frame()
{
    m_pBox->Frame();
    return true;
}
bool Sample::Render()
{
    //m_pDevice->m_pImmediateContext->PSSetSamplers(0, 1, &DxState::g_pDefaultSS);
    m_pBox->Render();
    return true;
}

bool Sample::Release()

{
    m_pBox->Release();
    //DxState::Release();
    return true;
}


