#include "Sample.h"
HRESULT Sample::CreateVertexBuffer()
{
    HRESULT hr;
    // NDC 공간 투영좌표계
    // x-> -1 ~ +1
    // y-> -1 ~ +1
    // z-> 0 ~+1
    SimpleVertex vertices[] =
    {
        -0.5f, 0.5f, 0.0,  1.0f, 0.0f, 0.0f,0.5f,       // v0
         0.5f, 0.5f, 0.0,  0.0f, 1.0f, 0.0f,0.5f,       // v1
        -0.5f, -0.5f, 0.0, 0.0f, 0.0f, 1.0f,0.5f         // v2
    };
    D3D11_BUFFER_DESC        bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(SimpleVertex)*3;        // 바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT;               // 버퍼의 할당 장소내지는 버퍼용도 당분간은 디폴트
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;      // 이 버퍼가 어떤것인지 gpu공간에 바이트 용량을 버퍼를 할당해준다.
    //bd.CPUAccessFlags = 0;                          // cpu가 GPU에 접근할 수 없다.
    //bd.MiscFlags = 0;                           // 잡동사니
    //bd.StructureByteStride = 0;
    //CPU가 읽을수도 없고 쓸수도 없다.

    D3D11_SUBRESOURCE_DATA   sd;
    sd.pSysMem = vertices;              // 시스템 메모리 만든 버퍼의 주소를 넘겨준다.
    sd.SysMemPitch = 0;                 // 2차원 3차원 갈때 사용
    sd.SysMemSlicePitch =0;
    hr = m_p3dDevice->CreateBuffer(&bd,  &sd,&m_pVertexBuffer);          // 버퍼를 생성
    // bd = 버퍼 할당
    // sd = 초기 할당된 버퍼를 체우는 CPU메모리 주소 sd가 널이면 메모리만 생성 나중에 GPU메모리를 채워야 한다.
    // 할당된 VertexBuffer는 절대 CPU가 접근 못한다.
    return hr;
}
HRESULT Sample::CreateShader()
{
    HRESULT hr;
    // 정점레이아웃을 만들려면 정점쉐이더 반드시 컴파일이 필요하다.

    ID3DBlob* pErrorCode = nullptr;
    hr = D3DCompileFromFile(L"VertexShader.txt", NULL, NULL, "VS", "vs_5_0", 0, 0, &m_pVSCode, &pErrorCode);            // 쉐이더파일 이름, Nll, Null,함수이름, 버텍스 쉐이더 컴파일러vs_5_0
    // Blob으로 반환된다. pVSCode,  오류가 생기면 pErrorCode 
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return false;
    }
    // 쉐이더 생성
    m_p3dDevice->CreateVertexShader(
        m_pVSCode->GetBufferPointer(),
        m_pVSCode->GetBufferSize(),
        NULL,
        &m_pVS);

    //픽셀 쉐이더 컴파일

    hr = D3DCompileFromFile(L"PixelShader.txt", NULL, NULL, "PS", "ps_5_0", 0, 0, &m_pPSCode, &pErrorCode);    // 쉐이더파일 이름, Nll, Null,함수이름, 버텍스 쉐이더 컴파일러vs_5_0
    // Blob으로 반환된다. pVSCode,  오류가 생기면 pErrorCode 
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return false;
    }
    // 쉐이더 생성
    m_p3dDevice->CreatePixelShader(
        m_pPSCode->GetBufferPointer(),
        m_pPSCode->GetBufferSize(),
        NULL,
        &m_pPS);
    if (FAILED(hr))
    {
        OutputDebugStringA((char*)pErrorCode->GetBufferPointer());      // 반드시 에러코드 삽입
        pErrorCode->Release();
        return false;
    }
}
HRESULT Sample::CreateVertexLayout()
{
    HRESULT hr;

    // 정점레이아웃은 정점쉐이더랑 밀접한 관련이 있다.
    // 이 버텍스 버퍼에있는 성분이 뭐가 있나?
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },       // 위치 Float 3개
        {"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 }           // 만약 색깔이 있으면 Float 4개
    };
    // 정점 레이아웃 생성시 사전에 정점쉐이더 생성이 필요하다.
    // 쉐이더에 넘길때 쉐이더에서 반환하는것보다 더 많으면 안된다. 짝이 맞아야한다.
    UINT NumElements = sizeof(ied) / sizeof(ied[0]);
    // float 0~7
    // pos 0~3, 0~11
    // color 4~7 12~28
    // 각 버텍스의 플롯수 즉 바이트 수

    /*ied.SemanticName = "POSITION";
    ied.SemanticIndex = 0;
    ied.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    ied.InputSlot = 0;
    ied.AlignedByteOffset = 0;
    ied.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    ied.InstanceDataStepRate = 0;*/

    hr = m_p3dDevice->CreateInputLayout(
        ied, NumElements, 
        m_pVSCode->GetBufferPointer(),
        m_pVSCode->GetBufferSize(),
        &m_pVertexLayout);
    return hr;
}

bool		Sample::Init()
{
    if (FAILED(CreateVertexBuffer()))
    {
        return false;
    }
    if (FAILED(CreateShader()))
    {
        return false;
    }
    if (FAILED(CreateVertexLayout()))
    {
        return false;
    }
    return true;
}
bool		Sample::Frame()
{
    return true;
}
bool		Sample::Render()
{
    UINT stride = sizeof(SimpleVertex);         // 정점한개의 바이트 용량
    UINT offset = 0;                            // 정점버퍼에서 출발지점(바이트)
    // 삼각형 렌더링
    // Get은 절대 사용하지 않는다.
    // 버텍스 버퍼의 수 1, 0번째 슬롯으로(레지스터리)
    // 각각의 정점이 어떻게 처리되는지 세팅
    m_pImmediateContext->IASetVertexBuffers(0,1,& m_pVertexBuffer, &stride, &offset);
    m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    m_pImmediateContext->VSSetShader(m_pVS, NULL, 0);
    m_pImmediateContext->HSSetShader(NULL, NULL, 0);        // 세팅할 필요는 없다
    m_pImmediateContext->DSSetShader(NULL, NULL, 0);
    m_pImmediateContext->GSSetShader(NULL, NULL, 0);
    m_pImmediateContext->PSSetShader(m_pPS, NULL, 0);      // 픽쉘쉐이더는 필수

    // 드로우 명령이 떨어지면 파이프라인에 따라 구동된다.
    // 위 순서는 중요하지 않다.
    //m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);             //fkdlsfltmxm
    m_pImmediateContext->Draw(3, 0);
    return true;
}
bool		Sample::Release()
{   
    if (m_pVertexBuffer)
       m_pVertexBuffer->Release();
    if (m_pVertexLayout)
        m_pVertexLayout->Release();
    if (m_pVS)
        m_pVS->Release();
    if (m_pPS)
        m_pPS->Release();
    if (m_pVSCode)
        m_pVSCode->Release();
    if (m_pPSCode)
        m_pPSCode->Release();

     return true;

}



GAME_RUN(P2_CreateDevice_01, 1024, 768)
