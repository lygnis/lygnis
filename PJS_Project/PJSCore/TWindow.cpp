#include "TWindow.h"
HWND g_hWnd;
RECT g_rtClient;

TWindow* g_pWindow = nullptr;
LRESULT CALLBACK WndProc(
    HWND hWnd, 
    UINT message, 
    WPARAM wParam, 
    LPARAM lParam)
{    
    _ASSERT(g_pWindow);
    return g_pWindow->MsgProc(hWnd, message, wParam, lParam);
}
LRESULT TWindow::MsgProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
    //msglist.push_back(message);
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0); // �޼���ť�� ���� WM_QUIT
        break;
    }
    // �޼��� ���� ó�� �Ұ� �ϰ� ��� ����.
    return  DefWindowProc(hWnd, message, wParam, lParam);
}
BOOL TWindow::InitInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight)
{
    //m_csStyle = WS_OVERLAPPEDWINDOW;
    RECT rc = { 0,0,iWidth , iHeight };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    // �ü���� ����� �����츦 �����Ѵ�.
    //msglist.clear();
    HWND hWnd = CreateWindowW(
        L"KGCA������",
        szTitle,
        WS_OVERLAPPEDWINDOW,
        0, 0,
        rc.right-rc.left, 
        rc.bottom-rc.top,
        nullptr, nullptr, 
        m_hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }
    m_hWnd = hWnd;
    g_hWnd = hWnd;
    ShowWindow(hWnd, SW_SHOW);
    GetWindowRect(hWnd, &m_rtWindow);
    GetClientRect(hWnd, &m_rtClient);
    g_rtClient = m_rtClient;
    m_iClientWidth = m_rtClient.right - m_rtClient.left;
    m_iClientHeight = m_rtClient.bottom - m_rtClient.top;
    CenterWindow();  
    return TRUE;
}
void TWindow::CenterWindow()
{
    UINT iScreenWidht = GetSystemMetrics(SM_CXFULLSCREEN);
    UINT iScreenHieght = GetSystemMetrics(SM_CYFULLSCREEN);
    UINT cx, cy;
    cx = (iScreenWidht - (m_rtWindow.right - m_rtWindow.left)) * 0.5f;
    cy = (iScreenHieght - (m_rtWindow.bottom - m_rtWindow.top)) * 0.5f;
    MoveWindow(m_hWnd, cx, cy,
        m_rtWindow.right - m_rtWindow.left,
        m_rtWindow.bottom - m_rtWindow.top,
        true);
}
/// <summary>
///  �ü������ ������ ���
/// </summary>
/// <param name="hInstance"></param>
/// <returns></returns>
//ATOM TWindow::MyRegisterClass()
//{
//    
//}
bool TWindow::SetWindow(HINSTANCE hInstance, const WCHAR* szTitle, UINT iWidth, UINT iHeight)
{   
    // ������ ���
    WNDCLASSEXW  wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.hInstance = hInstance;
    wcex.hbrBackground = CreateSolidBrush(RGB(89, 58, 255));
    wcex.lpszClassName = L"KGCA������";// �̸�
    // ������ �޼����� ���� �Լ��� �����Ѵ�.    
    wcex.lpfnWndProc = WndProc;  // ��ȭ��ȣ  
    wcex.hCursor = LoadCursor(nullptr, IDC_WAIT);
    if (!RegisterClassEx(&wcex))
    {
        return false;
    }
    //m_hInstance = hInstance;
    //WORD ret = MyRegisterClass();
    // ���ø����̼� �ʱ�ȭ�� �����մϴ�:
    /*if (!InitInstance(szTitle, iWidth, iHeight))
    {
        return FALSE;
    }*/
    RECT rc = { 0,0,iWidth , iHeight };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    // �ü���� ����� �����츦 �����Ѵ�.
    //msglist.clear();
    HWND hWnd = CreateWindowW(
        L"KGCA������",
        szTitle,
        WS_OVERLAPPEDWINDOW,
        0, 0,
        rc.right - rc.left,
        rc.bottom - rc.top,
        nullptr, nullptr,
        hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }
    m_hWnd = hWnd;
    g_hWnd = hWnd;
    ShowWindow(hWnd, SW_SHOW);
    GetWindowRect(hWnd, &m_rtWindow);
    GetClientRect(hWnd, &m_rtClient);
    g_rtClient = m_rtClient;
    m_iClientWidth = m_rtClient.right - m_rtClient.left;
    m_iClientHeight = m_rtClient.bottom - m_rtClient.top;
    CenterWindow();

    return true;
}
bool TWindow::Init()
{

    return true;
}
bool TWindow::Frame()
{
    return true;
}
bool TWindow::Render()
{
    return true;
}
bool TWindow::Release()
{
    return true;
}
TWindow::TWindow()
{
    g_pWindow = this;
}
bool        TWindow::Run()
{
    MSG msg = { 0, };
    bool bGameRun = true;
    while (WM_QUIT != msg.message)
    {
        // ���� : �޼���ť�� �޼����� ��� ��ȯ��.
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg); // �޼��� ����
            DispatchMessage(&msg);  // �޼��� ���ν����� �����Ѵ�.
        }
        else
        {
            return true;
        }
    }
    return false;
}
