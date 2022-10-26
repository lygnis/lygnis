#include "DxDevice.h"
#include <cassert>
bool DxDevice::Init()
{
        // 매크로 필수 -어떤 메소드를 사용했을때 성공했는지 실패했는지 리턴값이 0이면 성공
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

        return true;      // 디바이스 만들고 Init()호출
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
    // 매프레임마다 이 랜더 타겟에 뿌린다. (m_pRTV에)
    // 백버퍼를 렌더 타겟으로 지정
    m_pImmediateContext->OMSetRenderTargets(1, m_pRTV.GetAddressOf(), m_pDepthStencilView.Get());
    float color[4] = { 1.0f, 1.0f, 1.0f,1.0f };
    m_pImmediateContext->ClearRenderTargetView(m_pRTV.Get(), color);      // 지우고 렌더타겟뷰(백버퍼)를 출력한다.
    // 프리렌더는 클리어 까지만
    // 깊이 스텐실버퍼를 같이 클리어 시켜준다.
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
    m_pSwapChain->Present(0, 0);    // 백버퍼랑 프론트 버퍼랑 바꿔라 * 필수 뿌린다.
    return true;
}

bool DxDevice::Release()
{
    // 인터페이스는 사용하면 무조건 삭제한다.
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
    D3D_FEATURE_LEVEL pFeatureLevel;                            // 다이렉트 버전을 하드웨어 지원이 되게끔 인터페이스 생성

    ////////////////////////////////////// CreateDevice 설정
    IDXGIAdapter* pAdapter = nullptr;                           // Nullptr로 설정 (그래픽카드 인터페이스)
    D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;      // 하드웨어 성능을 무엇으로 할거냐 (GPU처리로 한다.) 만약 GPU가 지원을 안하면 CPU사용인데 속도 감소
    HMODULE Software = NULL;                                    // DX말고 다른 엔진의 모듈을 사용하겠다
    UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;              // 플래그로 write 설정 매우중요
    D3D_FEATURE_LEVEL pFeatureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_12_0,
    };
    UINT FeatureLevels = 2;                 // 레벨 수
    UINT SDKVersion = D3D11_SDK_VERSION;
    //1) 디바이스를 생성한다.
    hr = D3D11CreateDevice(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion,        
        &m_p3dDevice, &pFeatureLevel, &m_pImmediateContext);    // 디바이스, 다이렉트 버전지원 인터페이스,   를 리턴해라
    assert(SUCCEEDED(hr));


    return hr;
}

HRESULT DxDevice::CreateDXGIDevice()
{
    // 2) 팩토리 생성
    //IDXGIFactory* m_pGIFactory = nullptr;		// swapChain 사용을 위해생성
    //IDXGISwapChain* m_pSwapChain = nullptr;
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pGIFactory);      // __uuidof(IDXGIFactory)를 할당해서 넘겨준다
    assert(SUCCEEDED(hr));

    return hr;
}

HRESULT DxDevice::CreateSwapChain()
{
    // 3) 후면(백) 버퍼 생성 -> 전면 버퍼
    DXGI_SWAP_CHAIN_DESC pDesc;                                         // DX시스템은 어떤 구조체를 채워서 넘겨 결과를 리턴을 받는다 
    ZeroMemory(&pDesc, sizeof(pDesc));
    pDesc.BufferCount = 1;                                              // 버퍼 하나를 만든다. 버퍼는 하나만 있어도 충분하다.
    pDesc.BufferDesc.Width = g_rtClient.right;                          // 클라이언트 영역이랑 똑같이 만든다
    pDesc.BufferDesc.Height = g_rtClient.bottom;
    pDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;               // 픽셀이 4바이트인 클라이언트영역 버퍼를 하나 만든다.
    pDesc.BufferDesc.RefreshRate.Numerator = 60;                        // 주사율
    pDesc.BufferDesc.RefreshRate.Denominator = 1;                       // 1/60 으로 지정한다. 60Mhz
    pDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;                // 출력을 하는 대상 -이 버퍼가 렌더링 대상인데 어디다가 출력을 할것이냐
    pDesc.SampleDesc.Count = 1;                                         // 샘플링을 안쓰겠다
    pDesc.SampleDesc.Quality = 0;                                       // 샘플링 : 퀄리티를 상승시킨다. 대신 속도는 감소 계단형상을 완화 시킨다.
    pDesc.OutputWindow = g_hWnd;                                        // 윈도우 클라이언트에 사용
    pDesc.Windowed = true;                                              // 윈도우기반으로로 띄운다.
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
    // 4) 렌더타겟 뷰 생성
    ID3D11Texture2D* pBackBuffer = nullptr;                                             // 가로 새로 이미지
    m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);        // 버퍼가 한개밖에 없기 때문에 0번을 갖고온다
    // 만들어진 백버퍼에 텍스쳐로 리턴한다.
    // 랜더타겟으로 만들어 사용하겠다
    hr = m_p3dDevice->CreateRenderTargetView(pBackBuffer, NULL, m_pRTV.GetAddressOf());   
    assert(SUCCEEDED(hr));// 랜더타겟을 하나 만든다.
    // 앞으로 랜더타겟에 뿌리면 스왑체인 0번버퍼에 뿌리는것이다.
    pBackBuffer->Release();                                                             //dx에서는 Get을 하면 반드시 삭제해줘야 한다.

    return hr;
}

void DxDevice::CreateViewPort()
{
    //5) 뷰 포트 생성
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

    // 1번 텍스처를 생성한다.
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
    // 2번 깊이스텐실 뷰로 생성한다.
    D3D11_DEPTH_STENCIL_VIEW_DESC dtvd;
    ZeroMemory(&dtvd, sizeof(dtvd));
    dtvd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dtvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    hr = m_p3dDevice->CreateDepthStencilView(pDSTexture.Get(), &dtvd, m_pDepthStencilView.GetAddressOf());
    // 3번 뷰 적용
    //m_pImmediateContext->OMSetRenderTargets(1, m_pRTV.GetAddressOf(),
       //m_pDepthStencilView.Get());
       // 렌더에서 렌더타겟에 깊이 버퍼를 넣어준다.
    // 4번 깊이스텐실 뷰 상태 객체 생성해서 적용
    // 렌더 상태에서 설정해준다음에 렌더할떄 적용시켜준다.
    return hr;
}

HRESULT DxDevice::ResizeDevice(UINT width, UINT height)
{
    HRESULT hr;
     /* 1. 현재 설정된 랜더타겟과 갚이 스텐실 버퍼의 해제 및 소멸
        2. 변경괸 윈도우의 크기를 얻고 백 버퍼의 크기를 재조정
        (백버퍼는 리사이즈)
        3. 변경된 백 버퍼의 크기를 얻고 랜더타겟 뷰를 다시 생성 및 적용
        4. 소멸했던 깊이 스텐실 버퍼와 깊이 스텐실 뷰 다시 생성 및 적용
        5. 뷰포트 재지정*/

    // 처음 생성시 디바이스가 없으므로 리턴을 해준다.
    if (m_p3dDevice == nullptr) return S_OK;
    // 현재 설정된 랜더타겟 해제 및 소멸
    DeleteDXResource();
    m_pImmediateContext->OMSetRenderTargets(0, nullptr, NULL);
    m_pRTV.ReleaseAndGetAddressOf();
    // 변경된 윈도우의 크기를 얻고 백 버퍼의 크기를 재조정
    // 백버퍼의 크기를 조정한다.
    DXGI_SWAP_CHAIN_DESC CurrentSD, AfterSD;
    m_pSwapChain->GetDesc(&CurrentSD);
    hr = m_pSwapChain->ResizeBuffers(CurrentSD.BufferCount, width, height,
        CurrentSD.BufferDesc.Format, 0);
    if (FAILED(hr))
    {
        assert(false);
        return false;
    }
    // 변경된 백 버퍼의 크기를 얻고 렌더타겟 뷰를 다시 생성 및 적용
    // 뷰포트 재지정
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
