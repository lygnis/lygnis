#include "MWindow.h"
#include <exception>
#include <Windows.h>

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
			window->OnSize(window->GetClientSize());
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
	case WM_CLOSE:
	{
		// ���� �޽���
		::PostQuitMessage(0);
		break;
	}
	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);

	}
	return NULL;
}

//bool MWindow::broadcast()
//{
//	MSG msg;
//	if (!this->_is_init)
//	{
//		// ������ ��� �� ù ������ �� ����
//		SetWindowLongPtr(_hwnd, GWLP_USERDATA, (LONG_PTR)this);
//		g_hWnd = _hwnd;
//		this->OnCreate();
//		this->_is_init = true;
//	}
//	this->OnUpdate();
//	if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//	Sleep(0);
//	return true;
//}

//bool MWindow::IsRun()
//{
//	if (_is_Run)
//		broadcast();
//	return _is_Run;
//}

TMath::Rect MWindow::GetClientSize()
{
	RECT rc = {};
	auto hwnd = static_cast<HWND>(_hwnd);
	::GetClientRect(hwnd, &rc);
	// Ŭ���̾�Ʈ â�� ���� ��ġ�� ȭ�� ��ǥ���� â ��ġ�� �Բ��˻�
	::ClientToScreen(hwnd, (LPPOINT)&rc.left);
	::ClientToScreen(hwnd, (LPPOINT)&rc.right);
	return {0,0,rc.right - rc.left, rc.bottom - rc.top };
}

TMath::Rect MWindow::GetScreenSize()
{
	RECT rc = {};
	rc.right = ::GetSystemMetrics(SM_CXSCREEN);
	rc.bottom = ::GetSystemMetrics(SM_CXSCREEN);
	return { 0,0,rc.right - rc.left, rc.bottom - rc.top };
}


void MWindow::OnDestroy()
{
}

void MWindow::OnFocus()
{
}

void MWindow::OnKillFocus()
{
}

void MWindow::OnSize(const TMath::Rect& size)
{

}

MWindow::MWindow()
{
	WNDCLASSEX wc = {};
	
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.lpszClassName = L"MyWindowClass";

	// ������ ���Ͻ��� ����
	wc.lpfnWndProc = &WndProc;


	// �������� Ŭ������ �����ϸ� 
	auto classID = RegisterClassEx(&wc);
	if (!classID)
		DX3DError("Window not Created Successfully");
	RECT rc = { 0,0,size_.width, size_.height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// ������ ���� �� �ڵ� ��ȯ
	_hwnd = ::CreateWindowEx(NULL,MAKEINTATOM(classID),  L"MyEngine | DirectX 3D Game", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right-rc.left, rc.bottom-rc.top,
		NULL, NULL, NULL, NULL);			// ������ ��ü�� �����ڿ��� ���� �������̱� ������ this ��� NULL
	// ������ �ڵ� ���� ���н�
	if (!_hwnd)
		DX3DError("Window not Created Successfully");

	auto hwnd = static_cast<HWND>(_hwnd);
	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
	// ������ ����
	::ShowWindow(hwnd, SW_SHOW);
	::UpdateWindow(hwnd);
}

MWindow::~MWindow()
{
	DestroyWindow(static_cast<HWND>(_hwnd));
}
