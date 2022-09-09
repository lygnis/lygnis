#include "Sample.h"

int APIENTRY wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    Sample game;
    game.m_pWindow = new TWindow;
    game.m_pWindow->SetWindow(hInstance, L"P2_CreateDevice_01", 1024, 768);
    //SetWindow(hInstance, L"P2_CreateDevice_01", 1024, 768);

    if (game.Init() == false)        // ����̽� ���� ���ϸ� �����츦 ��������� �������ش�.
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
        // ���� : �޼���ť�� �޼����� ��� ��ȯ��.
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg); // �޼��� ����
            DispatchMessage(&msg);  // �޼��� ���ν����� �����Ѵ�.
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
    if (GameCore::Init())
    {
        return true;
    }
    return false;
}
bool		Sample::Frame()
{
    if (GameCore::Frame())
    {
        return true;
    }
    
    return false;
}
bool		Sample::Render()
{
    if (GameCore::Render())
    {
        return true;
    }
    return false;
}
bool		Sample::Release()
{   
    if (GameCore::Release())
    {
        return true;
    }
    return false;
}

