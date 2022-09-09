#include "MyWindow.h"

bool MyWindow::Init()
{
    return false;
}

bool MyWindow::Frame()
{
    return false;
}

bool MyWindow::Render()
{
    return false;
}

bool MyWindow::Realese()
{
    return false;
}

bool MyWindow::SetWindow(HINSTANCE hInst, const WCHAR* szTitle, UINT iWidth, UINT iHeight)
{
    m_hInstance = hInst;
    WORD ret = MyRegisterClass();

    // 애플리케이션 초기화를 수행
    if (!InitInstance(szTitle, iWidth, iHeight))
    {
        return FALSE;
    }
    return true;
}

BOOL MyWindow::InitInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight)
{
    HWND hWnd = CreateWindowW(
        L"등록윈도우",
        szTitle,
        WS_OVERLAPPEDWINDOW,
        0, 0,
        iWidth, iHeight,
        nullptr, nullptr,
        m_hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, SW_SHOW);
    //UpdateWindow(hWnd);

    return TRUE;
}

ATOM MyWindow::MyRegisterClass()
{
    WNDCLASSEXW  wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.hInstance = m_hInstance;
    wcex.hbrBackground = CreateSolidBrush(RGB(128, 128, 128));
    wcex.lpszClassName = L"등록윈도우";// 이름
    // 윈도우 메세지를 받을 함수를 지정한다.    
    wcex.lpfnWndProc = WndProc;  // 전화번호  
    wcex.hCursor = LoadCursor(nullptr, IDC_WAIT);
    return RegisterClassEx(&wcex);
    //wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CREATEWINDOW);
    //wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    //wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CREATEWINDOW));
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0); // 메세지큐에 직접 WM_QUIT
        break;
    }
    // 메세지 내가 처리 불가 니가 대신 해줘.
    return  DefWindowProc(hWnd, message, wParam, lParam);
}

bool MyWindow::Run()
{
    Init();

    MSG msg = {0};
    while (WM_QUIT != msg.message)              // 메세지가 나가는 게 아니면 반복한다 (창을 끄는것) 
    {
        // 게임에선 GetMessage가 아닌 PeekMessage를 사용한다. (가만히 있으면 메세지 반환을 안하기 때문에 동작을 안해도 메세지 반환함수 사용)
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);     // 메세지 번역
            DispatchMessageW(&msg);     // 메세지 프로시져에 전달한다.
        }
        else
        {
            Frame();
            Render();
        }
    }
    Realese();

    return true;
}
