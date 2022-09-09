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
	ID2D1Factory*			m_d2Factory;				// 팩토리 인터페이스 생성
	ID2D1RenderTarget*		m_dwRT;						// 2D 렌더타겟뷰 생성
	IDWriteFactory*			m_pDWriterFactory;			// 위 두개의 인터페이스로 출력 (위의 인터페이스가 없으면 출력이 안된다.)

	IDWriteTextFormat*		m_pTextFormat;
	ID2D1SolidColorBrush*	m_pTextColor;
	std::wstring			m_szDefaultText;			// 기본 출력 설정해보기

	IDWriteTextLayout*		m_pTextLayout;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	bool Set(IDXGISurface* dxgiSurface);				// 3D에 있는 백버퍼를 인자로 받아온다
	bool Draw(float x, float y, std::wstring text, D2D1_COLOR_F color);
};

