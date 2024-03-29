#include "Sample.h"
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    Sample game;
    game.SetWindow(hInstance, L"TestDeviceCore", 800, 600);
    game.Run();

    _CrtDumpMemoryLeaks();
    return 1;
}

bool Sample::Init()
{
    _CrtDumpMemoryLeaks();
    OutputDebugString(L"\n");
    I_Sound.Init();
    I_Sound.LoadAll(L"D:/Git_PJS_C/data/sound/");
    I_Sound.Release();


    m_pSound = I_Sound.GetPtr(L"romance.mid");
    return true;
}
bool Sample::Frame()
{
    if (m_iInput.GetKey(VK_LBUTTON) == KEY_PUSH)
        m_pSound->Play();
    /*if (m_iInput.GetKey(VK_F2) == KEY_PUSH)
        
    if (m_iInput.GetKey(VK_F3) == KEY_PUSH)*/
  
    return true;
}
bool Sample::Render()
{
    return true;
}
bool Sample::Release()
{
    I_Sound.Release();
    return true;
}
