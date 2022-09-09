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
	ATOM		MyRegisterClass();
	BOOL		InitInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight);
	bool		Run();	
	void		CenterWindow();
public:
	virtual bool		TInit(); // 초기화
	virtual bool		TFrame();// 실시간 계산
	virtual bool		TRender();// 실시간 랜더링
	virtual bool		TRelease();// 소멸 및 삭제	
	virtual LRESULT		MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	TWindow();
};

