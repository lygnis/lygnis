#include "DxDevice.h"

bool DxDevice::Init()
{
        // ��ũ�� �ʼ� -� �޼ҵ带 ��������� �����ߴ��� �����ߴ��� ���ϰ��� 0�̸� ����
        HRESULT hr;
        if (FAILED(hr = CreateDevice()))
        {
            return false;
        }
        if (FAILED(hr = CreateDXGIDevice()))
        {
            return false;
        }
        if (FAILED(hr = CreateSwapChain()))
        {
            return false;
        }
        if (FAILED(hr = CreateRenderTargetView()))
        {
            return false;
        }
        CreateViewPort();

        return true;      // ����̽� ����� Init()ȣ��
}
   
bool DxDevice::Frame()
{
    return Frame();
}

bool DxDevice::PreRender()
{
    // �������Ӹ��� �� ���� Ÿ�ٿ� �Ѹ���. (m_pRTV��)
    // ����۸� ���� Ÿ������ ����
    m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL);
    float color[4] = { 1.0f, 1.0f, 1.0f,1.0f };
    m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);      // ����� ����Ÿ�ٺ�(�����)�� ����Ѵ�.
    // ���������� Ŭ���� ������
	return true;
}
//bool DxDevice::Render()
//{
//    PreRender();
//    Render();
//    PostRender();
//    return true;
//}
bool DxDevice::PostRender()
{
    m_pSwapChain->Present(0, 0);    // ����۶� ����Ʈ ���۶� �ٲ�� * �ʼ� �Ѹ���.
    return true;
}

bool DxDevice::Release()
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
HRESULT DxDevice::CreateDevice()
{
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

    //m_p3dDevice �ٸ� �������̽� ������ ����Ѵ�.
    // m_pImmediateContext ������ �������̽��� ���(����, ����)�� ��.

    return hr;

}

HRESULT DxDevice::CreateDXGIDevice()
{

    // 2) ���丮 ����
    //IDXGIFactory* m_pGIFactory = nullptr;		// swapChain ����� ���ػ���
    //IDXGISwapChain* m_pSwapChain = nullptr;
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pGIFactory);      // __uuidof(IDXGIFactory)�� �Ҵ��ؼ� �Ѱ��ش�
    return hr;
}

HRESULT DxDevice::CreateSwapChain()
{
    // 3) �ĸ�(��) ���� ���� -> ���� ����
    DXGI_SWAP_CHAIN_DESC pDesc;         // DX�ý����� � ����ü�� ä���� �Ѱ� ����� ������ �޴´� 
    ZeroMemory(&pDesc, sizeof(pDesc));
    pDesc.BufferCount = 1;  // ���� �ϳ��� �����. ���۴� �ϳ��� �־ ����ϴ�.
    pDesc.BufferDesc.Width = g_rtClient.right;          // Ŭ���̾�Ʈ �����̶� �Ȱ��� �����
    pDesc.BufferDesc.Height = g_rtClient.bottom;
    pDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;       // �ȼ��� 4����Ʈ�� Ŭ���̾�Ʈ���� ���۸� �ϳ� �����.
    pDesc.BufferDesc.RefreshRate.Numerator = 60;                // �ֻ���
    pDesc.BufferDesc.RefreshRate.Denominator = 1;               // 1/60 ���� �����Ѵ�. 60Mhz
    pDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;            // ����� �ϴ� ��� -�� ���۰� ������ ����ε� ���ٰ� ����� �Ұ��̳�
    pDesc.SampleDesc.Count = 1;             // ���ø��� �Ⱦ��ڴ�
    pDesc.SampleDesc.Quality = 0;           // ���ø� : �Ѹ��°� �� �Ѹ��� �ؼ� ����Ƽ�� ��½�Ų��. ��� �ӵ��� ���� ��������� ��ȭ ��Ų��.
    pDesc.OutputWindow = g_hWnd;      // ������ Ŭ���̾�Ʈ�� ���
    pDesc.Windowed = true;          // �����������η� ����.
    pDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    HRESULT hr = m_pGIFactory->CreateSwapChain(m_p3dDevice, &pDesc, &m_pSwapChain);      // swapchain ���Ϲ޴´�.
    if (FAILED(hr))
        return hr;

    /*
     DXGI_MODE_DESC BufferDesc;
     DXGI_SAMPLE_DESC SampleDesc;
    DXGI_USAGE BufferUsage;
    UINT BufferCount;
    HWND OutputWindow;
    BOOL Windowed;
    DXGI_SWAP_EFFECT SwapEffect;
    UINT Flags;*/
}

HRESULT DxDevice::CreateRenderTargetView()
{
    HRESULT hr;
    // 4) ����Ÿ�� �� ����
    ID3D11Texture2D* pBackBuffer = nullptr;             // ���� ���� �̹���
    m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);     // ���۰� �Ѱ��ۿ� ���� ������ 0���� ����´�
    // ������� ����ۿ� �ؽ��ķ� �����Ѵ�.
    // ����Ÿ������ ����� ����ϰڴ�
    hr = m_p3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRTV);       // ����Ÿ���� �ϳ� �����.
    // ������ ����Ÿ�ٿ� �Ѹ��� ����ü�� 0�����ۿ� �Ѹ��°��̴�.
    pBackBuffer->Release();         //dx������ Get�� �ϸ� �ݵ�� ��������� �Ѵ�.

    return hr;
}

void DxDevice::CreateViewPort()
{
    //5) �� ��Ʈ ����
    D3D11_VIEWPORT vp;
    vp.Width = g_rtClient.right;
    vp.Height = g_rtClient.bottom;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 0.0f;

    m_pImmediateContext->RSSetViewports(1, &vp);
}
