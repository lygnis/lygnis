#pragma once
#include "DxDevice.h"
class TWindow : public DxDevice
{
public:
	//--------------------------------------------------------------------------------------
	// Global Variables
	//--------------------------------------------------------------------------------------
	HINSTANCE               m_hInstance;		// 인스턴스 핸들
	HWND                    m_hWnd;				// 윈도우 핸들
	DWORD					m_dwWindowStyle;	// 윈도우 스타일
	RECT					m_rcWindowBounds;   // 윈도우 영역
	RECT					m_rcWindowClient;   // 클라이언트 영역	
	UINT					m_iWindowWidth;		// 클라이언트 영역 가로크기
	UINT					m_iWindowHeight;	// 을라이언트 영역 세로크기
	bool					m_bResizeDrag;		// 윈도우 크기 변경 드래그 시작여부
public:
	// 윈도우 생성
	bool				InitWindow( HINSTANCE hInstance, int nCmdShow, const WCHAR* strWindowTitle );	
	// 윈도우 위치 화면 중앙으로 이동
	void				CenterWindow(HWND hwnd);
	
public:
	virtual bool		Init();
	virtual	bool		Frame();
	virtual	bool		Render();
	virtual bool		Release();
	virtual	bool		Run();
	virtual LRESULT		WndProc( HWND, UINT, WPARAM, LPARAM );
public:
	TWindow(void);
	virtual ~TWindow(void);
};
