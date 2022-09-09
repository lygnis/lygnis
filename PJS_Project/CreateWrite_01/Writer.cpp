#include "Writer.h"

bool Writer::Init()
{
    HRESULT hr;
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_d2Factory);
    hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&m_pDWriterFactory);

    hr = m_pDWriterFactory->CreateTextFormat(
        L"���",
        NULL,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        30,
        L"ko-kr",
        &m_pTextFormat);                // ��Ʈ�� �ʱ�ȭ �Ѵ�.

   /* hr = m_pDWriterFactory->CreateTextLayout(
        m_szDefaultText.c_str(),
        m_szDefaultText.size(),
        m_pTextFormat,
        g_rtClient.right,
        g_rtClient.bottom,
        &m_pTextLayout);*/
    
    return true;
}

bool Writer::Frame()
{
    return true;
}

bool Writer::Render()
{
    
    Draw(0, 0, m_szDefaultText, { 0,0,0,1 });
    return true;
}

bool Writer::Release()
{
    if (m_pTextLayout)
        m_pTextLayout->Release();
    if (m_pTextColor)
        m_pTextColor->Release();
    if (m_pDWriterFactory)
        m_pDWriterFactory->Release();
    if (m_dwRT)
        m_dwRT->Release();
    if (m_d2Factory)
        m_d2Factory->Release();
    return true;
}

bool Writer::Set(IDXGISurface* dxgiSurface)
{
    HRESULT hr;
    // �ſ� �߿�: ����̽� ���� �÷��׸� �����ؾ� �Ѵ�.
    // 3D -> 2D ����
    D2D1_RENDER_TARGET_PROPERTIES props;
    ZeroMemory(&props, sizeof(props));
    props.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;                                                           // Ÿ���� ����Ʈ
    props.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);              // �ȼ������Ѵ�.
    props.dpiX = 96;                                                                                            // dpi : ��Ʈ %��ġ (�ػ� ����) ���� 96���� �������ش�.
    props.dpiY = 96;
    props.usage = D2D1_RENDER_TARGET_USAGE_NONE;
    props.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

    hr = m_d2Factory->CreateDxgiSurfaceRenderTarget(
        dxgiSurface,                    // �����
        &props,                         // ������Ƽ��
        &m_dwRT                         // ����Ÿ��
    );
    if (FAILED(hr))
        return false;

    hr = m_dwRT->CreateSolidColorBrush({ 0,0,0,1 }, &m_pTextColor);         // �����������̽� �߰�
    if (FAILED(hr))
        return false;
    return true;
}

bool Writer::Draw(float x, float y, std::wstring text, D2D1_COLOR_F color)
{
    m_dwRT->BeginDraw();                //����Ÿ�ٺ信�� �̸� �ѹ� �׷��ߵȴ�.

    D2D1_RECT_F rt = { x, y, g_rtClient.right, g_rtClient.bottom };
    m_pTextColor->SetColor(color);
    m_pTextColor->SetOpacity(1.0f);

    m_dwRT->DrawText(text.c_str(), text.size(), m_pTextFormat, rt, m_pTextColor);               // ��ġ ���� �÷��� �޴´�.
    //m_pTextLayout->SetFontSize(50, { 0, (UINT)m_szDefaultText.size() });    //
    //m_pTextLayout->SetFontStyle(DWRITE_FONT_STYLE_ITALIC, { 0, (UINT)m_szDefaultText.size() });
    //m_dwRT->DrawTextLayout({ 400,300 }, m_pTextLayout, m_pTextColor);
    m_dwRT->EndDraw();

    return true;
}
