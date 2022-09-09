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

	ID2D1Factory*			m_d2Factory;					// ���丮 ����
	ID2D1RenderTarget*		m_dRT;							// ����Ÿ�ٺ� ����
	IDWriteFactory*			m_pDWriterFactory;				// �� �ΰ��� �������̽� ��� �������ϸ� ���X
	IDWriteTextFormat*		m_TextFormat;					// �ؽ�Ʈ ��Ʈ ũ�� �� �ʱ�ȭ
	ID2D1SolidColorBrush*	m_pTextColor;					// �ؽ�Ʈ ����
	// IDWriteTextLayout*   ���̾ƿ� ���� ��Ʈ�� ũ��� �ٲܼ� ������ ������ ���ٲ۴�.
	
	std::wstring			m_szOutputText;					// ��� ����
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	bool Set(IDXGISurface* _dxgiSurface);					// ����۸� �޾ƿ��� �Լ�
private:
	bool Draw(float x, float y, std::wstring _text, D2D1_COLOR_F color);	// ����Լ�
};

