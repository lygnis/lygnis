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

    // ���ø����̼� �ʱ�ȭ�� ����
    if (!InitInstance(szTitle, iWidth, iHeight))
    {
        return FALSE;
    }
    return true;
}

BOOL MyWindow::InitInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight)
{
    HWND hWnd = CreateWindowW(
        L"���������",
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
    wcex.lpszClassName = L"���������";// �̸�
    // ������ �޼����� ���� �Լ��� �����Ѵ�.    
    wcex.lpfnWndProc = WndProc;  // ��ȭ��ȣ  
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
        PostQuitMessage(0); // �޼���ť�� ���� WM_QUIT
        break;
    }
    // �޼��� ���� ó�� �Ұ� �ϰ� ��� ����.
    return  DefWindowProc(hWnd, message, wParam, lParam);
}

bool MyWindow::Run()
{
    Init();

    MSG msg = {0};
    while (WM_QUIT != msg.message)              // �޼����� ������ �� �ƴϸ� �ݺ��Ѵ� (â�� ���°�) 
    {
        // ���ӿ��� GetMessage�� �ƴ� PeekMessage�� ����Ѵ�. (������ ������ �޼��� ��ȯ�� ���ϱ� ������ ������ ���ص� �޼��� ��ȯ�Լ� ���)
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);     // �޼��� ����
            DispatchMessageW(&msg);     // �޼��� ���ν����� �����Ѵ�.
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
