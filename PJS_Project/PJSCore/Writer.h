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

	ID2D1Factory*			m_d2Factory;					// 팩토리 생성
	ID2D1RenderTarget*		m_dRT;							// 렌더타겟뷰 생성
	IDWriteFactory*			m_pDWriterFactory;				// 위 두개의 인터페이스 출력 설정안하면 출력X
	IDWriteTextFormat*		m_TextFormat;					// 텍스트 폰트 크기 및 초기화
	ID2D1SolidColorBrush*	m_pTextColor;					// 텍스트 색깔
	// IDWriteTextLayout*   레이아웃 설정 폰트랑 크기는 바꿀수 있지만 색깔을 못바꾼다.
	
	std::wstring			m_szOutputText;					// 출력 글자
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	bool Set(IDXGISurface* _dxgiSurface);					// 백버퍼를 받아오는 함수
private:
	bool Draw(float x, float y, std::wstring _text, D2D1_COLOR_F color);	// 출력함수
};

