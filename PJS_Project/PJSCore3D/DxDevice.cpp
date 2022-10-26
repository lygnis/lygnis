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
        if (FAILED(hr = CreateDepthStencilView()))
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
    m_pImmediateContext->OMSetRenderTargets(1, m_pRTV.GetAddressOf(), m_pDepthStencilView.Get());
    float color[4] = { 1.0f, 1.0f, 1.0f,1.0f };
    m_pImmediateContext->ClearRenderTargetView(m_pRTV.Get(), color);      // ����� ����Ÿ�ٺ�(�����)�� ����Ѵ�.
    // ���������� Ŭ���� ������
    // ���� ���ٽǹ��۸� ���� Ŭ���� �����ش�.
    m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_pImmediateContext->PSSetSamplers(0, 1, &DxState::g_pDefaultSSMirror);
    m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pImmediateContext->RSSetViewports(1, &m_vp);
    m_pImmediateContext->RSSetState(DxState::g_pDefaultRSSolid);
    m_pImmediateContext->OMSetBlendState(DxState::g_pAlphaBlend, 0, -1);
    m_pImmediateContext->OMSetDepthStencilState(DxState::g_pDefaultDepthStencil,0xff);

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
    m_vp.Width = g_rtClient.right;
    m_vp.Height = g_rtClient.bottom;
    m_vp.TopLeftX = 0;
    m_vp.TopLeftY = 0;
    m_vp.MinDepth = 0.0f;
    m_vp.MaxDepth = 1.0f;

    m_pImmediateContext->RSSetViewports(1, &m_vp);
}

HRESULT DxDevice::CreateDepthStencilView()
{
    HRESULT hr;
    D3D11_RENDER_TARGET_VIEW_DESC rtvd;
    m_pRTV->GetDesc(&rtvd);
    DXGI_SWAP_CHAIN_DESC scd;
    m_pSwapChain->GetDesc(&scd);

    // 1�� �ؽ�ó�� �����Ѵ�.
    ComPtr<ID3D11Texture2D>  pDSTexture;
    D3D11_TEXTURE2D_DESC td;
    ZeroMemory(&td, sizeof(td));
    td.Width = scd.BufferDesc.Width;
    td.Height = scd.BufferDesc.Height;
    td.MipLevels = 1;
    td.ArraySize = 1;
    td.Format = DXGI_FORMAT_R24G8_TYPELESS;
    td.SampleDesc.Count = 1;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.CPUAccessFlags = 0;
    td.MiscFlags = 0;
    td.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    hr = m_p3dDevice->CreateTexture2D(&td, NULL, pDSTexture.GetAddressOf());
    // 2�� ���̽��ٽ� ��� �����Ѵ�.
    D3D11_DEPTH_STENCIL_VIEW_DESC dtvd;
    ZeroMemory(&dtvd, sizeof(dtvd));
    dtvd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dtvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    hr = m_p3dDevice->CreateDepthStencilView(pDSTexture.Get(), &dtvd, m_pDepthStencilView.GetAddressOf());
    // 3�� �� ����
    //m_pImmediateContext->OMSetRenderTargets(1, m_pRTV.GetAddressOf(),
       //m_pDepthStencilView.Get());
       // �������� ����Ÿ�ٿ� ���� ���۸� �־��ش�.
    // 4�� ���̽��ٽ� �� ���� ��ü �����ؼ� ����
    // ���� ���¿��� �������ش����� �����ҋ� ��������ش�.
    return hr;
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
    if (FAILED(hr = CreateDepthStencilView()))
    {
        return false;
    }
    CreateViewPort();
    CreateDXResource();
    return S_OK;
}
