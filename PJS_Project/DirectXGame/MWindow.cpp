#include "MWindow.h"



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,  WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	// 윈도우 생성 이벤트
	case WM_CREATE:
	{
		// 자신의 객체를 전달한다
		MWindow* window = (MWindow*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		// HWND로 식별되는 구조데이터에 this 포인터 저장
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
	// 윈도우 프록시져 설정
	wc.lpfnWndProc = &WndProc;


	// 레지스터 클래스가 실패하면 
	if (!::RegisterClassEx(&wc))
		return false;

	// 윈도우 생성 및 핸들 반환
	_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX App", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, this);
	// 윈도우 핸들 생성 실패시
	if (!_hwnd)
		return false;

	// 윈도우 띄우기
	::ShowWindow(_hwnd, SW_SHOW);
	::UpdateWindow(_hwnd);

	
	// 윈도우 실행중인 플래그
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
