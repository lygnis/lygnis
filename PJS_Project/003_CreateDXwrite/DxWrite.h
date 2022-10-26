#pragma once
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#include "TStd.h"
#include<d2d1.h>
#include<d2d1helper.h>
#include<dwrite.h>
class DxWrite
{
public:
	/*float					m_fDPIScaleX;
	float					m_fDPIScaleY;
	FLOAT					m_fdpiX;
	FLOAT					m_fdpiY;*/
	ID2D1Factory*			m_d2Factory;					// 팩토리 생성
	ID2D1RenderTarget*		m_dRT;							// 렌더타겟뷰 생성
	IDWriteFactory*			m_pDWriterFactory;				// 위 두개의 인터페이스 출력 설정안하면 출력X
	IDWriteTextFormat*		m_TextFormat;					// 텍스트 폰트 크기 및 초기화
	ID2D1SolidColorBrush*	m_pTextColor;					// 텍스트 색깔
	// IDWriteTextLayout*   레이아웃 설정 폰트랑 크기는 바꿀수 있지만 색깔을 못바꾼다.

public:
	// 초기화
	bool			Set(IDXGISurface* _pSurface);
	bool			Init();
	// 렌더링
	bool			Begin();
	HRESULT			DrawText(float x, float y, std::wstring pText, D2D1::ColorF Color = D2D1::ColorF(1, 0, 0, 1));
	bool			End();
	// 전체 소멸
	bool			Release();
	// 객체 생성 및 소멸
	HRESULT			CreateDeviceIndependentResource();
	void			DiscardDeviceIndependentResource();
	HRESULT			CreateDeviceResource(IDXGISurface* _pSurface);
	void			DiscardDeviceResource();
	// 화면 사이즈 변경
	void			OnResize(UINT width, UINT height, IDXGISurface* pSurface);

public:
	DxWrite();
	~DxWrite();
};

