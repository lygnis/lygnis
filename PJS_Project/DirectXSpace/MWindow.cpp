#include "MWindow.h"
#include <exception>
#include "MStd.h"

HWND g_hWnd;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,  WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	// ������ ���� �̺�Ʈ
	case WM_CREATE:
	{
		
		break;
	}
	case WM_SIZE:
	{
		MWindow* window = (MWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		// ������ �����Ͱ� ��������� �߿� �Լ� ȣ���� �� �� �ִ�. ����
		if(window)
			window->OnSize();
		break;
	}
	case WM_SETFOCUS:
	{
		// ������ Ŭ����
		MWindow* window = (MWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (window)
			window->OnFocus();
		break;
	}
	case WM_KILLFOCUS:
	{
		// ������ Ŭ�� ���ҽ�
		MWindow* window = (MWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->OnKillFocus();
		break;
	}
	case WM_DESTROY:
	{
		// ������ ���� �̺�Ʈ��
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

bool MWindow::broadcast()
{
	MSG msg;
	if (!this->_is_init)
	{
		// ������ ��� �� ù ������ �� ����
		SetWindowLongPtr(_hwnd, GWLP_USERDATA, (LONG_PTR)this);
		g_hWnd = _hwnd;
		this->OnCreate();
		this->_is_init = true;
	}
	this->OnUpdate();
	if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	Sleep(0);
	return true;
}

bool MWindow::IsRun()
{
	if (_is_Run)
		broadcast();
	return _is_Run;
}

RECT MWindow::GetClientRect()
{
	RECT rc;
	::GetClientRect(this->_hwnd, &rc);
	// Ŭ���̾�Ʈ â�� ���� ��ġ�� ȭ�� ��ǥ���� â ��ġ�� �Բ��˻�
	::ClientToScreen(this->_hwnd, (LPPOINT)&rc.left);
	::ClientToScreen(this->_hwnd, (LPPOINT)&rc.right);
	return rc;
}

RECT MWindow::GetSizeScreen()
{
	RECT rc;
	rc.right = ::GetSystemMetrics(SM_CXSCREEN);
	rc.bottom = ::GetSystemMetrics(SM_CXSCREEN);
	return rc;
}


void MWindow::OnDestroy()
{
	_is_Run = false;
}

void MWindow::OnFocus()
{
}

void MWindow::OnKillFocus()
{
}

void MWindow::OnSize()
{
}

HWND& MWindow::GetHandel()
{
	return _hwnd;
}

MWindow::MWindow()
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
		throw std::exception("Window not Created Successfully");

	// ������ ���� �� �ڵ� ��ȯ
	_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX App", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, NULL);			// ������ ��ü�� �����ڿ��� ���� �������̱� ������ this ��� NULL
	// ������ �ڵ� ���� ���н�
	if (!_hwnd)
		throw std::exception("Window not Created Successfully");

	// ������ ����
	::ShowWindow(_hwnd, SW_SHOW);
	::UpdateWindow(_hwnd);


	// ������ �������� �÷���
	_is_Run = true;
}

MWindow::~MWindow()
{

}
