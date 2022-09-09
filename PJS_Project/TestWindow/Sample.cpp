#include "Sample.h"
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    Sample game;
    game.m_pWindow = new TWindow;
    game.m_pWindow->SetWindow(hInstance, L"P2_CreateDevice_01", 1024, 768);
    game.m_pWindow->Run();
    //SetWindow(hInstance, L"P2_CreateDevice_01", 1024, 768);

    return 1;
}
