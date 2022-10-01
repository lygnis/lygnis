#include "Writer.h"

bool Writer::Init()
{
	HRESULT hr;
	// 팩토리 생성
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_d2Factory);
	if (FAILED(hr))	return false;
	// 쓰기 팩토리 생성
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&m_pDWriterFactory);
	if (FAILED(hr))	return false;
	// 폰트 초기화
	hr = m_pDWriterFactory->CreateTextFormat(L"고딕", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 15, L"ko-kr", &m_TextFormat);
	if (FAILED(hr))	return false;

	return true;
}
bool Writer::Frame()
{
	return true;
}
bool Writer::Render()
{
	Draw(1, 1, m_szOutputText, { 1,1,1,1 });
	return true;
}
bool Writer::Release()
{
	if (m_d2Factory)m_d2Factory->Release();
	if (m_dRT)m_dRT->Release();
	if (m_pDWriterFactory)m_pDWriterFactory->Release();
	if (m_TextFormat)m_TextFormat->Release();
	if (m_pTextColor)m_pTextColor->Release();
			
	return true;
}
bool Writer::Set(IDXGISurface* _dxgiSurface)
{
	// 매우 중요 : 디바이스 생성 플래그를 지정해야 한다.
	// 3D->2D 연동 백버퍼를 갖고온다.
	HRESULT hr;
	// 프로퍼티지 생성
	D2D1_RENDER_TARGET_PROPERTIES props;
	props.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	props.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
	props.dpiX =96;
	props.dpiY=96;
	props.usage = D2D1_RENDER_TARGET_USAGE_NONE;
	props.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;
	hr = m_d2Factory->CreateDxgiSurfaceRenderTarget(_dxgiSurface, &props, &m_dRT);
	if (FAILED(hr)) return false;
	hr = m_dRT->CreateSolidColorBrush({ 0,0,0,1 }, &m_pTextColor);
	if (FAILED(hr)) return false;
	return true;
}
bool Writer::Draw(float x, float y, std::wstring _text, D2D1_COLOR_F _color)
{
	// 송출전 렌더타겟에 그려야 한다.
	m_dRT->BeginDraw();
	// 화면상 표시 위치
	D2D1_RECT_F rt = { x,y,g_rtClient.right, g_rtClient.bottom };		
	m_pTextColor->SetColor(_color);
	m_pTextColor->SetOpacity(1.0f);
	m_dRT->DrawText(_text.c_str(), _text.size(), m_TextFormat, rt, m_pTextColor);
	m_dRT->EndDraw();
	return true;
}