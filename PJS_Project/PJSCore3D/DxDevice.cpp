#include "DxDevice.h"
#include <cassert>
bool DxDevice::Init()
{
        // ��ũ�� �ʼ� -� �޼ҵ带 ��������� �����ߴ��� �����ߴ��� ���ϰ��� 0�̸� ����
        HRESULT hr;
        if (FAILED(hr = CreateDevice()))
        {
            assert(false);
            return false;
        }
        if (FAILED(hr = CreateDXGIDevice()))
        {
            assert(false);
            return false;
        }
        if (FAILED(hr = CreateSwapChain()))
        {
            assert(false);
            return false;
        }
        if (FAILED(hr = CreateRenderTargetView()))
        {
            assert(false);
            return false;
        }
        CreateViewPort();

        return true;      // ����̽� ����� Init()ȣ��
}
   
bool DxDevice::Frame()
{
    return Frame();
}

HRESULT DxDevice::DeleteDXResource()
{
    return S_OK;
}

HRESULT DxDevice::CreateDXResource()
{
    return S_OK;
}

bool DxDevice::PreRender()
{
    // �������Ӹ��� �� ���� Ÿ�ٿ� �Ѹ���. (m_pRTV��)
    // ����۸� ���� Ÿ������ ����
    m_pImmediateContext->OMSetRenderTargets(1, m_pRTV.GetAddressOf(), NULL);
    float color[4] = { 1.0f, 1.0f, 1.0f,1.0f };
    m_pImmediateContext->ClearRenderTargetView(m_pRTV.Get(), color);      // ����� ����Ÿ�ٺ�(�����)�� ����Ѵ�.
    // ���������� Ŭ���� ������

	return true;
}

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
	return true;
}
HRESULT DxDevice::CreateDevice()
{
    HRESULT hr;                             
    D3D_FEATURE_LEVEL pFeatureLevel;                            // ���̷�Ʈ ������ �ϵ���� ������ �ǰԲ� �������̽� ����

    ////////////////////////////////////// CreateDevice ����
    IDXGIAdapter* pAdapter = nullptr;                           // Nullptr�� ���� (�׷���ī�� �������̽�)
    D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;      // �ϵ���� ������ �������� �Ұų� (GPUó���� �Ѵ�.) ���� GPU�� ������ ���ϸ� CPU����ε� �ӵ� ����
    HMODULE Software = NULL;                                    // DX���� �ٸ� ������ ����� ����ϰڴ�
    UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;              // �÷��׷� write ���� �ſ��߿�
    D3D_FEATURE_LEVEL pFeatureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_12_0,
    };
    UINT FeatureLevels = 2;                 // ���� ��
    UINT SDKVersion = D3D11_SDK_VERSION;
    //1) ����̽��� �����Ѵ�.
    hr = D3D11CreateDevice(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion,        
        &m_p3dDevice, &pFeatureLevel, &m_pImmediateContext);    // ����̽�, ���̷�Ʈ �������� �������̽�,   �� �����ض�
    assert(SUCCEEDED(hr));


    return hr;
}

HRESULT DxDevice::CreateDXGIDevice()
{
    // 2) ���丮 ����
    //IDXGIFactory* m_pGIFactory = nullptr;		// swapChain ����� ���ػ���
    //IDXGISwapChain* m_pSwapChain = nullptr;
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pGIFactory);      // __uuidof(IDXGIFactory)�� �Ҵ��ؼ� �Ѱ��ش�
    assert(SUCCEEDED(hr));

    return hr;
}

HRESULT DxDevice::CreateSwapChain()
{
    // 3) �ĸ�(��) ���� ���� -> ���� ����
    DXGI_SWAP_CHAIN_DESC pDesc;                                         // DX�ý����� � ����ü�� ä���� �Ѱ� ����� ������ �޴´� 
    ZeroMemory(&pDesc, sizeof(pDesc));
    pDesc.BufferCount = 1;                                              // ���� �ϳ��� �����. ���۴� �ϳ��� �־ ����ϴ�.
    pDesc.BufferDesc.Width = g_rtClient.right;                          // Ŭ���̾�Ʈ �����̶� �Ȱ��� �����
    pDesc.BufferDesc.Height = g_rtClient.bottom;
    pDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;               // �ȼ��� 4����Ʈ�� Ŭ���̾�Ʈ���� ���۸� �ϳ� �����.
    pDesc.BufferDesc.RefreshRate.Numerator = 60;                        // �ֻ���
    pDesc.BufferDesc.RefreshRate.Denominator = 1;                       // 1/60 ���� �����Ѵ�. 60Mhz
    pDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;                // ����� �ϴ� ��� -�� ���۰� ������ ����ε� ���ٰ� ����� �Ұ��̳�
    pDesc.SampleDesc.Count = 1;                                         // ���ø��� �Ⱦ��ڴ�
    pDesc.SampleDesc.Quality = 0;                                       // ���ø� : ����Ƽ�� ��½�Ų��. ��� �ӵ��� ���� ��������� ��ȭ ��Ų��.
    pDesc.OutputWindow = g_hWnd;                                        // ������ Ŭ���̾�Ʈ�� ���
    pDesc.Windowed = true;                                              // �����������η� ����.
    pDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    HRESULT hr = m_pGIFactory->CreateSwapChain(m_p3dDevice, &pDesc, &m_pSwapChain);      
    
    assert(SUCCEEDED(hr));
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
    ID3D11Texture2D* pBackBuffer = nullptr;                                             // ���� ���� �̹���
    m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);        // ���۰� �Ѱ��ۿ� ���� ������ 0���� ����´�
    // ������� ����ۿ� �ؽ��ķ� �����Ѵ�.
    // ����Ÿ������ ����� ����ϰڴ�
    hr = m_p3dDevice->CreateRenderTargetView(pBackBuffer, NULL, m_pRTV.GetAddressOf());   
    assert(SUCCEEDED(hr));// ����Ÿ���� �ϳ� �����.
    // ������ ����Ÿ�ٿ� �Ѹ��� ����ü�� 0�����ۿ� �Ѹ��°��̴�.
    pBackBuffer->Release();                                                             //dx������ Get�� �ϸ� �ݵ�� ��������� �Ѵ�.

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

HRESULT DxDevice::ResizeDevice(UINT width, UINT height)
{
    HRESULT hr;
     /* 1. ���� ������ ����Ÿ�ٰ� ���� ���ٽ� ������ ���� �� �Ҹ�
        2. ���汭 �������� ũ�⸦ ��� �� ������ ũ�⸦ ������
        (����۴� ��������)
        3. ����� �� ������ ũ�⸦ ��� ����Ÿ�� �並 �ٽ� ���� �� ����
        4. �Ҹ��ߴ� ���� ���ٽ� ���ۿ� ���� ���ٽ� �� �ٽ� ���� �� ����
        5. ����Ʈ ������*/

    // ó�� ������ ����̽��� �����Ƿ� ������ ���ش�.
    if (m_p3dDevice == nullptr) return S_OK;
    // ���� ������ ����Ÿ�� ���� �� �Ҹ�
    DeleteDXResource();
    m_pImmediateContext->OMSetRenderTargets(0, nullptr, NULL);
    m_pRTV.ReleaseAndGetAddressOf();
    // ����� �������� ũ�⸦ ��� �� ������ ũ�⸦ ������
    // ������� ũ�⸦ �����Ѵ�.
    DXGI_SWAP_CHAIN_DESC CurrentSD, AfterSD;
    m_pSwapChain->GetDesc(&CurrentSD);
    hr = m_pSwapChain->ResizeBuffers(CurrentSD.BufferCount, width, height,
        CurrentSD.BufferDesc.Format, 0);
    if (FAILED(hr))
    {
        assert(false);
        return false;
    }
    // ����� �� ������ ũ�⸦ ��� ����Ÿ�� �並 �ٽ� ���� �� ����
    // ����Ʈ ������
    if (FAILED(hr = CreateRenderTargetView()))
    {
        return false;
    }
    CreateViewPort();
    CreateDXResource();
    return S_OK;
}
