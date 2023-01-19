#include "MWindow.h"



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,  WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	// ������ ���� �̺�Ʈ
	case WM_CREATE:
	{
		// �ڽ��� ��ü�� �����Ѵ�
		MWindow* window = (MWindow*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		// HWND�� �ĺ��Ǵ� ���������Ϳ� this ������ ����
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		window->SetHWND(hwnd);
		window->OnCreate();
		break;
	}
	case WM_DESTROY:
	{
		MWindow* window = (MWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->OnDestroy();
		::PostQuitMessage(0);
		break;
	}
	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);

	}
	return NULL;
}

bool MWindow::Init()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	// ������ ���Ͻ��� ����
	wc.lpfnWndProc = &WndProc;


	// �������� Ŭ������ �����ϸ� 
	if (!::RegisterClassEx(&wc))
		return false;

	// ������ ���� �� �ڵ� ��ȯ
	_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX App", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, this);
	// ������ �ڵ� ���� ���н�
	if (!_hwnd)
		return false;

	// ������ ����
	::ShowWindow(_hwnd, SW_SHOW);
	::UpdateWindow(_hwnd);

	
	// ������ �������� �÷���
	_is_Run = true;
	return true;
}

bool MWindow::broadcast()
{
	MSG msg;
	this->OnUpdate();
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	Sleep(0);
	return true;
}

bool MWindow::IsRun()
{

	return _is_Run;
}

bool MWindow::Release()
{

	if (!::DestroyWindow(_hwnd))
	{
		return false;
	}
	return true;
}

RECT MWindow::GetClientRect()
{
	RECT rc;
	::GetClientRect(this->_hwnd, &rc);
	return rc;
}

void MWindow::SetHWND(HWND hwnd)
{
	this->_hwnd = hwnd;
}

void MWindow::OnDestroy()
{
	_is_Run = false;
}
