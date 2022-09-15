#include "Sample.h"
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    Sample game;
    game.SetWindow(hInstance, L"TestDeviceCore", 800, 600);
    game.Run();


    return 1;
}

bool Sample::Init()
{
   
    return true;
}
bool Sample::Frame()
{
    m_iInput.Frame();
    if (m_iInput.GetKey('W') == KeyType::KEY_PUSH)
    {
        int i = 0;
    }
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
