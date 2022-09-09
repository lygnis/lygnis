#include "Sample.h"
bool		Sample::Init()
{
    // 1)����̽� ����
    HRESULT hr;                 // ��� DX�� ��ȯ���� HRESULT
    D3D_FEATURE_LEVEL pFeatureLevel;        // ���̷�Ʈ ������ �ϵ���� ������ �ǰԲ� �������̽� ����

    ////////////////////////////////////// CreateDevice ����
    IDXGIAdapter* pAdapter = nullptr;                   // Nullptr�� ���� (�׷���ī�� �������̽�)
    D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;                             // �ϵ���� ������ �������� �Ұų� (GPUó���� �Ѵ�.) ���� GPU�� ������ ���ϸ� CPU����ε� �ӵ� ����
    HMODULE Software = NULL;                                // DX���� �ٸ� ������ ����� ����ϰڴ�
    UINT Flags = 0;
    D3D_FEATURE_LEVEL pFeatureLevels[] = 
    {   
        D3D_FEATURE_LEVEL_11_0, 
        D3D_FEATURE_LEVEL_12_0, 
    };
    UINT FeatureLevels = 2;                 // ���� ��
    UINT SDKVersion = D3D11_SDK_VERSION;

    //1) ����̽��� �����Ѵ�.
    hr = D3D11CreateDevice(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion,        // �̷��� ����
                        &m_p3dDevice, &pFeatureLevel, &m_pImmediateContext);  // ����̽�, ���̷�Ʈ �������� �������̽�,   �� �����ض�
    ///////////////////////////////////////////////////////
    if (FAILED(hr)) // �����ϸ�            // ��ũ�� �ʼ� -� �޼ҵ带 ��������� �����ߴ��� �����ߴ��� ���ϰ��� 0�̸� ����
    {
        return false;
    }

    // 2)���丮 ����
    //IDXGIFactory* m_pGIFactory = nullptr;		// swapChain ����� ���ػ���
    //IDXGISwapChain* m_pSwapChain = nullptr;
    hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pGIFactory);      // __uuidof(IDXGIFactory)�� �Ҵ��ؼ� �Ѱ��ش�
    if (FAILED(hr))
        return false;

    // 3)����  ü�� ����
    // �ĸ�(��) ���� ���� -> ���� ����
    DXGI_SWAP_CHAIN_DESC pDesc;         // DX�ý����� � ����ü�� ä���� �Ѱ� ����� ������ �޴´� 
    ZeroMemory(&pDesc, sizeof(pDesc));
    pDesc.BufferCount = 1;  // ���� �ϳ��� �����. ���۴� �ϳ��� �־ ����ϴ�.
    pDesc.BufferDesc.Width = m_rtClient.right;          // Ŭ���̾�Ʈ �����̶� �Ȱ��� �����
    pDesc.BufferDesc.Height = m_rtClient.bottom;
    pDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;       // �ȼ��� 4����Ʈ�� Ŭ���̾�Ʈ���� ���۸� �ϳ� �����.
    pDesc.BufferDesc.RefreshRate.Numerator = 60;                // �ֻ���
    pDesc.BufferDesc.RefreshRate.Denominator = 1;               // 1/60 ���� �����Ѵ�. 60Mhz
    pDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;            // ����� �ϴ� ��� -�� ���۰� ������ ����ε� ���ٰ� ����� �Ұ��̳�
    pDesc.SampleDesc.Count = 1;             // ���ø��� �Ⱦ��ڴ�
    pDesc.SampleDesc.Quality = 0;           // ���ø� : �Ѹ��°� �� �Ѹ��� �ؼ� ����Ƽ�� ��½�Ų��. ��� �ӵ��� ���� ��������� ��ȭ ��Ų��.
    pDesc.OutputWindow =m_hWnd;      // ������ Ŭ���̾�Ʈ�� ���
    pDesc.Windowed = true;          // �����������η� ����.
    pDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    hr = m_pGIFactory->CreateSwapChain(m_p3dDevice, &pDesc, &m_pSwapChain);      // swapchain ���Ϲ޴´�.
    if (FAILED(hr))
        return false;

    /*
     DXGI_MODE_DESC BufferDesc;
     DXGI_SAMPLE_DESC SampleDesc;
    DXGI_USAGE BufferUsage;
    UINT BufferCount;
    HWND OutputWindow;
    BOOL Windowed;
    DXGI_SWAP_EFFECT SwapEffect;
    UINT Flags;*/

    // 4) ���� Ÿ�ٺ� ����
    ID3D11Texture2D* pBackBuffer = nullptr;             // ���� ���� �̹���
    m_pSwapChain->GetBuffer(0,__uuidof(ID3D11Texture2D),(void**)&pBackBuffer);     // ���۰� �Ѱ��ۿ� ���� ������ 0���� ����´�
    // ������� ����ۿ� �ؽ��ķ� �����Ѵ�.
    // ����Ÿ������ ����� ����ϰڴ�
    m_p3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRTV);       // ����Ÿ���� �ϳ� �����.
    // ������ ����Ÿ�ٿ� �Ѹ��� ����ü�� 0�����ۿ� �Ѹ��°��̴�.
    pBackBuffer->Release();         //dx������ Get�� �ϸ� �ݵ�� ��������� �Ѵ�.

    //5) �� ��Ʈ ����
    D3D11_VIEWPORT vp;
    vp.Width = m_rtClient.right;
    vp.Height = m_rtClient.bottom;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 0.0f;

    m_pImmediateContext->RSSetViewports(1, &vp);

    return true;
}
bool		Sample::Frame()
{
    return true;
}
bool		Sample::Render()
{

    // �������Ӹ��� �� ���� Ÿ�ٿ� �Ѹ���. (m_pRTV��)
    m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL);
    float color[4] = { 1.0f, 0, 0,1.0f };
    m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);
    m_pSwapChain->Present(0, 0);    // ����۶� ����Ʈ ���۶� �ٲ��
    return true;
}
bool		Sample::Release()
{   
    // �������̽��� ����ϸ� ������ �����Ѵ�.
    if (m_p3dDevice)
        m_p3dDevice->Release();
    if (m_pImmediateContext)
        m_pImmediateContext->Release();
    if (m_pGIFactory)
        m_pGIFactory->Release();
    if (m_pSwapChain)
        m_pSwapChain->Release();
    if (m_pRTV)
        m_pRTV->Release();
    return true;
}

GAME_RUN(P2_CreateWidnow2, 1024, 768)
