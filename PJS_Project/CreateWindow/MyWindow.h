#pragma once
#include <Windows.h>
#include <string>
#include <set>
class MyWindow
{
public:
	HINSTANCE	m_hInstance;		// ������ȣ
	HWND			m_hWnd;			// ����ȣ
public:
	virtual bool Init();			// �ʱ�ȭ	
	virtual bool Frame();			// �ǽð� ���
	virtual bool Render();		// ������
	virtual bool Realese();		// �Ҹ� �� ����
public:
	bool SetWindow(HINSTANCE hInst, const WCHAR* szTitle, UINT iWidth = 1024, UINT iHeight = 768);
	BOOL InitInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight);
	ATOM MyRegisterClass();
	bool Run();
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

