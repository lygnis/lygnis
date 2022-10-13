#pragma once
#include "TStd.h"
class TWindow			// ����̽� ���� �����쳪 �� �ݴ�� ����ص� ��� ����.
{
public:
	HINSTANCE   m_hInstance;	// ������ȣ
	HWND		m_hWnd;			// ����ȣ
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
	bool		Init(); // �ʱ�ȭ
	bool		Frame();// �ǽð� ���
	bool		Render();// �ǽð� ������
	bool		Release();// �Ҹ� �� ����	
	LRESULT		MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual HRESULT		ResizeDevice(UINT width, UINT height);
public:
	TWindow();
};

