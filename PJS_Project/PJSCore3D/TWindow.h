#pragma once
#include "TStd.h"
class TWindow			// 디바이스 위에 윈도우나 그 반대로 상속해도 상관 없다.
{
public:
	HINSTANCE   m_hInstance;	// 접수번호
	HWND		m_hWnd;			// 등기번호
	RECT		m_rtWindow;
	RECT		m_rtClient;
	DWORD       m_csStyle;
	UINT		m_iClientWidth;
	UINT		m_iClientHeight;
	bool		m_bGameRun;
#ifdef _DEBUG
	std::vector<UINT>  msglist;
#endif
public:
	bool		SetWindow(HINSTANCE hInst, const WCHAR* szTitle, UINT iWidth=1024, UINT iHeight=768);
//	ATOM		MyRegisterClass();
	BOOL		InitInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight);
	virtual bool		Run();	
	void		CenterWindow();
public:
	bool		Init(); // 초기화
	bool		Frame();// 실시간 계산
	bool		Render();// 실시간 랜더링
	bool		Release();// 소멸 및 삭제	
	LRESULT		MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual HRESULT		ResizeDevice(UINT width, UINT height);
public:
	TWindow();
};

