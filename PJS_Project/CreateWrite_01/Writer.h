#pragma once
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#include "TStd.h"
#include<d2d1.h>
#include<d2d1helper.h>
#include<dwrite.h>

class Writer
{
public:
	ID2D1Factory*			m_d2Factory;				// ���丮 �������̽� ����
	ID2D1RenderTarget*		m_dwRT;						// 2D ����Ÿ�ٺ� ����
	IDWriteFactory*			m_pDWriterFactory;			// �� �ΰ��� �������̽��� ��� (���� �������̽��� ������ ����� �ȵȴ�.)

	IDWriteTextFormat*		m_pTextFormat;
	ID2D1SolidColorBrush*	m_pTextColor;
	std::wstring			m_szDefaultText;			// �⺻ ��� �����غ���

	IDWriteTextLayout*		m_pTextLayout;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	bool Set(IDXGISurface* dxgiSurface);				// 3D�� �ִ� ����۸� ���ڷ� �޾ƿ´�
	bool Draw(float x, float y, std::wstring text, D2D1_COLOR_F color);
};

