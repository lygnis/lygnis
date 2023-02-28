#include "MWindow.h"
#include <exception>
#include "MStd.h"

HWND g_hWnd;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,  WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	// 윈도우 생성 이벤트
	case WM_CREATE:
	{
		
		break;
	}
	case WM_SIZE:
	{
		MWindow* window = (MWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		// 윈도우 포인터가 만들어지는 중에 함수 호출이 될 수 있다. 방지
		if(window)
			window->OnSize();
		break;
	}
	case WM_SETFOCUS:
	{
		// 윈도우 클릭시
		MWindow* window = (MWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (window)
			window->OnFocus();
		break;
	}
	case WM_KILLFOCUS:
	{
		// 윈도우 클릭 안할시
		MWindow* window = (MWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->OnKillFocus();
		break;
	}
	case WM_DESTROY:
	{
		// 윈도우 종료 이벤트시
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
		// 생성자 대신 맨 첫 프레임 때 동작
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
	// 클라이언트 창의 현재 위치를 화면 좌표에서 창 위치와 함께검색
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
	// 윈도우 프록시져 설정
	wc.lpfnWndProc = &WndProc;


	// 레지스터 클래스가 실패하면 
	if (!::RegisterClassEx(&wc))
		throw std::exception("Window not Created Successfully");

	// 윈도우 생성 및 핸들 반환
	_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX App", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, NULL);			// 윈도우 객체를 생성자에서 아직 생성중이기 때문에 this 대신 NULL
	// 윈도우 핸들 생성 실패시
	if (!_hwnd)
		throw std::exception("Window not Created Successfully");

	// 윈도우 띄우기
	::ShowWindow(_hwnd, SW_SHOW);
	::UpdateWindow(_hwnd);


	// 윈도우 실행중인 플래그
	_is_Run = true;
}

MWindow::~MWindow()
{

}
