#include "BaseObject.h"


bool BaseObject::SetDevice(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext)
{
    m_p3dDevice = _p3dDevice;
    m_pImmediateContext = _pImmediateContext;
    m_shManger.SetDevice(m_p3dDevice, m_pImmediateContext);
    m_txManager.SetDvice(m_p3dDevice, m_pImmediateContext);
    if (m_p3dDevice == nullptr || m_pImmediateContext == nullptr)
        return false;
    return true;
}
HRESULT BaseObject::CreateVertexBuffer()
{
    HRESULT hr;
    // NDC 공간 투영좌표계
    // x-> -1 ~ +1
    // y-> -1 ~ +1
    // z-> 0 ~+1
    m_pVertexList.resize(6);
    m_pVertexList[0].p = { -1.0f, 1.0f, 0.0f };
    m_pVertexList[1].p = { 1.0f, 1.0f, 0.0f };
    m_pVertexList[2].p = { -1.0f, -1.0f, 0.0f };
    m_pVertexList[3].p = { -1.0f, -1.0f, 0.0f };
    m_pVertexList[4].p = { 1.0f, 1.0f, 0.0f };
    m_pVertexList[5].p = { 1.0f, -1.0f, 0.0f };

    m_pVertexList[0].c = { -1.0f, 1.0f, 0.0f, 1.0f };
    m_pVertexList[1].c = { -1.0f, 1.0f, 0.0f , 1.0f };
    m_pVertexList[2].c = { -1.0f, 1.0f, 0.0f , 1.0f };
    m_pVertexList[3].c = { -1.0f, 1.0f, 0.0f , 1.0f };
    m_pVertexList[4].c = { -1.0f, 1.0f, 0.0f , 1.0f };
    m_pVertexList[5].c = { -1.0f, 1.0f, 0.0f, 1.0f };

    m_pVertexList[0].t = { 0.0f, 0.0f };
    m_pVertexList[1].t = { 1.0f, 0.0f };
    m_pVertexList[2].t = { 0.0f, 1.0f };
    m_pVertexList[3].t = { 0.0f, 1.0f };
    m_pVertexList[4].t = { 1.0f, 0.0f };
    m_pVertexList[5].t = { 1.0f, 1.0f };
    UINT NumVertex = m_pVertexList.size();

    D3D11_BUFFER_DESC        bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(SimpleVertex)*NumVertex;                    // 바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT;                             // 버퍼의 할당 장소내지는 버퍼용도 당분간은 디폴트
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;                    // 이 버퍼가 어떤것인지 gpu공간에 바이트 용량을 버퍼를 할당해준다.
    //bd.CPUAccessFlags = 0;                                    // cpu가 GPU에 접근할 수 없다.
    //bd.MiscFlags = 0;                                         // 잡동사니
    //bd.StructureByteStride = 0;
    //CPU가 읽을수도 없고 쓸수도 없다.

    D3D11_SUBRESOURCE_DATA   sd;
    sd.pSysMem = &m_pVertexList.at(0);                          // 시스템 메모리 만든 버퍼의 주소를 넘겨준다.
    sd.SysMemPitch = 0;                                         // 2차원 3차원 갈때 사용
    sd.SysMemSlicePitch = 0;
    hr = m_p3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer);          // 버퍼를 생성
    // bd = 버퍼 할당
    // sd = 초기 할당된 버퍼를 체우는 CPU메모리 주소 sd가 널이면 메모리만 생성 나중에 GPU메모리를 채워야 한다.
    // 할당된 VertexBuffer는 절대 CPU가 접근 못한다.
    return hr;
}
HRESULT BaseObject::CreateShader(std::wstring _shName)
{
    m_pShader = m_shManger.LoadShader(_shName);
    if (m_pShader)
        return true;
    return false;
}
HRESULT BaseObject::LoadTexture(std::wstring _fileName)
{
    
    m_pTexture = m_txManager.LoadTexture(_fileName);
    if (m_pTexture)
        return true;
    return false;
}
bool BaseObject::Create(ID3D11Device* p3dDevice, ID3D11DeviceContext* _pImmediateContext, const wchar_t* _texName, const wchar_t* _shName)
{
    if ((SetDevice(p3dDevice, _pImmediateContext)) == false)
    {
        return false;
    }
    if (FAILED(CreateVertexBuffer()))
    {
        return false;
    }
    if (FAILED(CreateShader(_shName)))
    {
        return false;
    }
    if (FAILED(CreateVertexLayout()))
    {
        return false;
    }
    if (FAILED(LoadTexture(_texName)))
    {
        return false;
    }
    return true;
}
bool BaseObject::Init()
{
    return true;
}
bool BaseObject::Frame()
{
    return true;
}
bool BaseObject::Render()
{
    UINT stride = sizeof(SimpleVertex);         // 정점한개의 바이트 용량
    UINT offset = 0;                            // 정점버퍼에서 출발지점(바이트)
    // 삼각형 렌더링
    // Get은 절대 사용하지 않는다.
    // 버텍스 버퍼의 수 1, 0번째 슬롯으로(레지스터리)
    // 각각의 정점이 어떻게 처리되는지 세팅
    m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
    m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    m_pImmediateContext->VSSetShader(m_pShader->m_pVS, NULL, 0);
    m_pImmediateContext->HSSetShader(NULL, NULL, 0);        // 세팅할 필요는 없다
    m_pImmediateContext->DSSetShader(NULL, NULL, 0);
    m_pImmediateContext->GSSetShader(NULL, NULL, 0);
    m_pImmediateContext->PSSetShader(m_pShader->m_pPS, NULL, 0);      // 픽쉘쉐이더는 필수

    // 드로우 명령이 떨어지면 파이프라인에 따라 구동된다.
    // 위 순서는 중요하지 않다.
    //m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);    
    m_pImmediateContext->PSSetShaderResources(0, 1, &m_pTexture->m_pSrvTexture);
    m_pImmediateContext->Draw(m_pVertexList.size(), 0);
    return true;
}
bool BaseObject::Release()
{
    if (m_pVertexBuffer)
        m_pVertexBuffer->Release();
    if (m_pVertexLayout)
        m_pVertexLayout->Release();
    if(m_pShader)m_pShader->Release();

    return true;
}
HRESULT BaseObject::CreateVertexLayout()
{
    HRESULT hr;

    // 정점레이아웃은 정점쉐이더랑 밀접한 관련이 있다.
    // 이 버텍스 버퍼에있는 성분이 뭐가 있나?
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },       // 위치 Float 3개
        {"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },           // 만약 색깔이 있으면 Float 4개
        {"Texture", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0},
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
        m_pShader->m_pVSCode->GetBufferPointer(),
        m_pShader->m_pVSCode->GetBufferSize(),
        &m_pVertexLayout);
    return hr;
}