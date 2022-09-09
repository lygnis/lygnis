#pragma once
#include <Windows.h>
#include <string>
#include <set>
class MyWindow
{
public:
	HINSTANCE	m_hInstance;		// 접수번호
	HWND			m_hWnd;			// 등기번호
public:
	virtual bool Init();			// 초기화	
	virtual bool Frame();			// 실시간 계산
	virtual bool Render();		// 렌더링
	virtual bool Realese();		// 소멸 및 삭제
public:
	bool SetWindow(HINSTANCE hInst, const WCHAR* szTitle, UINT iWidth = 1024, UINT iHeight = 768);
	BOOL InitInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight);
	ATOM MyRegisterClass();
	bool Run();
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

