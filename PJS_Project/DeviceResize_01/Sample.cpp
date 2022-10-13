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
    return true;
}
bool Sample::Frame()
{
    return true;
}
bool Sample::Render()
{
    //m_pDevice->m_pImmediateContext->PSSetSamplers(0, 1, &DxState::g_pDefaultSS);

    return true;
}

bool Sample::Release()

{
    //DxState::Release();
    return true;
}


