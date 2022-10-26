#pragma once
#include "TStd.h"
#include <assert.h>
class TWindow
{
public:
	//--------------------------------------------------------------------------------------
	// Global Variables
	//--------------------------------------------------------------------------------------
	HINSTANCE               m_hInstance;		// �ν��Ͻ� �ڵ�
	HWND                    m_hWnd;				// ������ �ڵ�
	DWORD					m_dwWindowStyle;	// ������ ��Ÿ��
	RECT					m_rcWindowBounds;   // ������ ����
	RECT					m_rcWindowClient;   // Ŭ���̾�Ʈ ����	
	UINT					m_iWindowWidth;		// Ŭ���̾�Ʈ ���� ����ũ��
	UINT					m_iWindowHeight;	// �����̾�Ʈ ���� ����ũ��
public:
	// ������ ����
	bool				InitWindow( HINSTANCE hInstance, int nCmdShow, const WCHAR* strWindowTitle );	
	// ������ ��ġ ȭ�� �߾����� �̵�
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
