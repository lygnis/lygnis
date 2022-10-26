#include "DxWrite.h"

bool DxWrite::Set(IDXGISurface* _pSurface)
{
    HRESULT hr;
    if (!Init())
    {
        assert(false);
        return false;
    }
    hr = CreateDeviceResource(_pSurface);
    return true;
}

bool DxWrite::Init()
{
    HRESULT hr;
    hr = CreateDeviceIndependentResource();
    if (FAILED(hr))
    {
        assert(false);
        return false;
    }
    return true;
}

bool DxWrite::Begin()
{
    if (m_dRT)
    {
        m_dRT->BeginDraw();
        m_dRT->SetTransform(D2D1::IdentityMatrix());
    }
    return true;
}

HRESULT DxWrite::DrawText(float x, float y, std::wstring pText, D2D1::ColorF Color)
{
    if (m_dRT && m_pTextColor)
    {
        D2D1_RECT_F layout = { x,y,g_rtClient.right, g_rtClient.bottom };
        m_pTextColor->SetColor(Color);
        m_dRT->DrawText(pText.c_str(), pText.size(), m_TextFormat, layout, m_pTextColor);
    }
    return S_OK;
}

bool DxWrite::End()
{
    if (m_dRT && FAILED(m_dRT->EndDraw()))
    {
        return false;
    }
    return true;
}

bool DxWrite::Release()
{
    DiscardDeviceIndependentResource();
    DiscardDeviceResource();
    return true;
}

HRESULT DxWrite::CreateDeviceIndependentResource()
{
    HRESULT hr;
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_d2Factory);
    if (FAILED(hr))
    {   
        assert(false);
        return hr;
    }
    //DisplayInformation::LogicalDpi(&m_fdpiX, &m_fdpiY);
    //m_fDPIScaleX = m_fdpiX / 96.f;
    //m_fDPIScaleY = m_fdpiY / 96.f;

    hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&m_pDWriterFactory));
    if (FAILED(hr))
    {
        assert(false);
        return hr;
    }
    hr = m_pDWriterFactory->CreateTextFormat(L"±Ã¼­", NULL, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL, 20.0f, L"ko-kr", &m_TextFormat);
    if (FAILED(hr))
    {
        assert(false);
        return hr;
    }
    return hr;
}

void DxWrite::DiscardDeviceIndependentResource()
{
    if (m_d2Factory) m_d2Factory->Release();
    if (m_pDWriterFactory)m_pDWriterFactory->Release();
    if (m_TextFormat)m_TextFormat->Release();
}

HRESULT DxWrite::CreateDeviceResource(IDXGISurface* _pSurface)
{
    HRESULT hr;
    D2D1_RENDER_TARGET_PROPERTIES props; 
    props.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
    props.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
    props.dpiX = 96;
    props.dpiY = 96;
    props.usage = D2D1_RENDER_TARGET_USAGE_NONE;
    props.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;
    hr = m_d2Factory->CreateDxgiSurfaceRenderTarget(_pSurface, (const D2D1_RENDER_TARGET_PROPERTIES*)&props, &m_dRT);
    if (FAILED(hr))
    {
        return hr;
    }
    hr = m_dRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &m_pTextColor);
    if (FAILED(hr))
    {
        return hr;
    }
    return hr;
}

void DxWrite::DiscardDeviceResource()
{
    if(m_dRT)
        m_dRT->Release();
    if (m_pTextColor)
        m_pTextColor->Release();
}

void DxWrite::OnResize(UINT width, UINT height, IDXGISurface* pSurface)
{
    CreateDeviceResource(pSurface);
}

DxWrite::DxWrite() :
    m_d2Factory(nullptr),
    m_pDWriterFactory(nullptr),
    m_TextFormat(nullptr),
    m_pTextColor(nullptr)
{
    m_dRT = nullptr;
}

DxWrite::~DxWrite()
{
    Release();
}
