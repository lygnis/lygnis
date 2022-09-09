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
