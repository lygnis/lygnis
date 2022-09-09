#include "DxDevice.h"

bool DxDevice::Init()
{
        // 매크로 필수 -어떤 메소드를 사용했을때 성공했는지 실패했는지 리턴값이 0이면 성공
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

        return true;      // 디바이스 만들고 Init()호출
}
   
bool DxDevice::Frame()
{
    return Frame();
}

bool DxDevice::PreRender()
{
    // 매프레임마다 이 랜더 타겟에 뿌린다. (m_pRTV에)
    // 백버퍼를 렌더 타겟으로 지정
    m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL);
    float color[4] = { 1.0f, 1.0f, 1.0f,1.0f };
    m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);      // 지우고 렌더타겟뷰(백버퍼)를 출력한다.
    // 프리렌더는 클리어 까지만
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
    if (m_pRTV)
        m_pRTV->Release();
	return true;
}
HRESULT DxDevice::CreateDevice()
{
    HRESULT hr;                 // 모든 DX의 반환값은 HRESULT
    D3D_FEATURE_LEVEL pFeatureLevel;        // 다이렉트 버전을 하드웨어 지원이 되게끔 인터페이스 생성

    ////////////////////////////////////// CreateDevice 설정
    IDXGIAdapter* pAdapter = nullptr;                   // Nullptr로 설정 (그래픽카드 인터페이스)
    D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;                             // 하드웨어 성능을 무엇으로 할거냐 (GPU처리로 한다.) 만약 GPU가 지원을 안하면 CPU사용인데 속도 감소
    HMODULE Software = NULL;                                // DX말고 다른 엔진의 모듈을 사용하겠다
    UINT Flags = 0;
    D3D_FEATURE_LEVEL pFeatureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_12_0,
    };
    UINT FeatureLevels = 2;                 // 레벨 수
    UINT SDKVersion = D3D11_SDK_VERSION;

    //1) 디바이스를 생성한다.
    hr = D3D11CreateDevice(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion,        // 이렇게 만들어서
        &m_p3dDevice, &pFeatureLevel, &m_pImmediateContext);  // 디바이스, 다이렉트 버전지원 인터페이스,   를 리턴해라

    //m_p3dDevice 다른 인터페이스 생성시 사용한다.
    // m_pImmediateContext 생성된 인터페이스를 사용(관리, 제어)할 때.

    return hr;

}

HRESULT DxDevice::CreateDXGIDevice()
{

    // 2) 팩토리 생성
    //IDXGIFactory* m_pGIFactory = nullptr;		// swapChain 사용을 위해생성
    //IDXGISwapChain* m_pSwapChain = nullptr;
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pGIFactory);      // __uuidof(IDXGIFactory)를 할당해서 넘겨준다
    return hr;
}

HRESULT DxDevice::CreateSwapChain()
{
    // 3) 후면(백) 버퍼 생성 -> 전면 버퍼
    DXGI_SWAP_CHAIN_DESC pDesc;         // DX시스템은 어떤 구조체를 채워서 넘겨 결과를 리턴을 받는다 
    ZeroMemory(&pDesc, sizeof(pDesc));
    pDesc.BufferCount = 1;  // 버퍼 하나를 만든다. 버퍼는 하나만 있어도 충분하다.
    pDesc.BufferDesc.Width = g_rtClient.right;          // 클라이언트 영역이랑 똑같이 만든다
    pDesc.BufferDesc.Height = g_rtClient.bottom;
    pDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;       // 픽셀이 4바이트인 클라이언트영역 버퍼를 하나 만든다.
    pDesc.BufferDesc.RefreshRate.Numerator = 60;                // 주사율
    pDesc.BufferDesc.RefreshRate.Denominator = 1;               // 1/60 으로 지정한다. 60Mhz
    pDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;            // 출력을 하는 대상 -이 버퍼가 렌더링 대상인데 어디다가 출력을 할것이냐
    pDesc.SampleDesc.Count = 1;             // 샘플링을 안쓰겠다
    pDesc.SampleDesc.Quality = 0;           // 샘플링 : 뿌리는거 또 뿌리고 해서 퀄리티를 상승시킨다. 대신 속도는 감소 계단형상을 완화 시킨다.
    pDesc.OutputWindow = g_hWnd;      // 윈도우 클라이언트에 사용
    pDesc.Windowed = true;          // 윈도우기반으로로 띄운다.
    pDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    HRESULT hr = m_pGIFactory->CreateSwapChain(m_p3dDevice, &pDesc, &m_pSwapChain);      // swapchain 리턴받는다.
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
    ID3D11Texture2D* pBackBuffer = nullptr;             // 가로 새로 이미지
    m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);     // 버퍼가 한개밖에 없기 때문에 0번을 갖고온다
    // 만들어진 백버퍼에 텍스쳐로 리턴한다.
    // 랜더타겟으로 만들어 사용하겠다
    hr = m_p3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRTV);       // 랜더타겟을 하나 만든다.
    // 앞으로 랜더타겟에 뿌리면 스왑체인 0번버퍼에 뿌리는것이다.
    pBackBuffer->Release();         //dx에서는 Get을 하면 반드시 삭제해줘야 한다.

    return hr;
}

void DxDevice::CreateViewPort()
{
    //5) 뷰 포트 생성
    D3D11_VIEWPORT vp;
    vp.Width = g_rtClient.right;
    vp.Height = g_rtClient.bottom;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 0.0f;

    m_pImmediateContext->RSSetViewports(1, &vp);
}
