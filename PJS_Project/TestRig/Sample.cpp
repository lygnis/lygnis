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
    
    return true;
}
bool Sample::Frame()
{
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
    return true;
}
