#include "Sample.h"

int APIENTRY wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    Sample game;
    game.m_gEngine.m_pWindow = new TWindow;
    game.m_gEngine.m_pWindow->SetWindow(hInstance, L"P2_CreateDevice_01", 1024, 768);
    //SetWindow(hInstance, L"P2_CreateDevice_01", 1024, 768);

    if (game.Init() == false)        // 디바이스 생성 못하면 윈도우를 띄우지말고 리턴해준다.
    {
        game.Release();
        return false;
    }
    MSG msg = { 0, };
    bool bGameRun = true;
    while (bGameRun)
    {
        if (WM_QUIT == msg.message)
        {
            break;
        }
        // 장점 : 메세지큐에 메세지가 없어도 반환됨.
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg); // 메세지 번역
            DispatchMessage(&msg);  // 메세지 프로시져에 전달한다.
        }
        else
        {




            if (!game.Frame() || !game.Render())
            {
                bGameRun = false;
            }
        }
    }
    game.Release();

    return 1;
}
bool		Sample::Init()
{
    if (m_gEngine.Init())
    {
        return true;
    }
    return false;
}
bool		Sample::Frame()
{
    if (m_gEngine.Frame())
    {
        return true;
    }
    if (I_Input.GetKey('W') == KeyState::KEY_HOLD)
    {
        INT k = 0;
    }
    return false;
}
bool		Sample::Render()
{
    if (m_gEngine.Render())
    {
        return true;
    }
    return false;
}
bool		Sample::Release()
{   
    if (m_gEngine.Release())
    {
        return true;
    }
    return false;
}

