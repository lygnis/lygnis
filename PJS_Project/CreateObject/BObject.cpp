#include "BObject.h"

bool BObject::Init()
{
    return true;
}

bool BObject::Frame()
{
    return true;
}

bool BObject::Render()
{
    UINT stride = sizeof(ObjectVertex);     // 정점 1개의 바이트 용량
    UINT offset = 0;                        // 정점버퍼에서 출발지점(바이트)
    m_pImmediateContext->PSSetShaderResources(0, 1, &m_pTextureSRV);
    m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
    m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    m_pImmediateContext->VSSetShader(m_pVS, NULL, 0);
    m_pImmediateContext->PSSetShader(m_pPS, NULL, 0);
    m_pImmediateContext->DrawIndexed(m_pIndexList.size(), 0, 0);

    return true;
}

bool BObject::Release()
{
   /* if (m_p3dDevice)m_p3dDevice->Release();
    if (m_pImmediateContext)m_pImmediateContext->Release();*/
    if (m_pVertexBuffer)m_pVertexBuffer->Release();
    if (m_pIndexBuffer)m_pIndexBuffer->Release();
    if (m_pVertexLayout)m_pVertexLayout->Release();
    if (m_pVS)m_pVS->Release();
    if (m_pPS)m_pPS->Release();
    if (m_pVScode)m_pVScode->Release();
    if (m_pPScode)m_pPScode->Release();
    if (m_pTexture)m_pTexture->Release();
    if (m_pTextureSRV)m_pTextureSRV->Release();
    
    return true;
}

bool BObject::SetDevice(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext)
{
    m_p3dDevice = _p3dDevice;
    m_pImmediateContext = _pImmediateContext;
    if (m_p3dDevice && m_pImmediateContext)
        return true;
    else
        return false;
}

bool BObject::Create(const wchar_t* _shName, const wchar_t* _texName)
{
    if (FAILED(CreateVertexBuffer()))
        return false;
    if (FAILED(CreateIndexBuffer()))
        return false;
    if (FAILED(CreateVertexShader(_shName)))
        return false;
    if (FAILED(CreatePixelShader(_shName)))
        return false;
    if (FAILED(CreateVertexLayout()))
        return false;
    if (FAILED(LoadTexture(_texName)))
        return false;

    return true;
}

HRESULT BObject::CreateVertexBuffer()
{
    // 버텍스 4개로 4각형을 생성해본다.
    HRESULT hr;
    CreateVertexData();
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(ObjectVertex)* m_pVertexList.size();
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    /*bd.CPUAccessFlags;
    bd.MiscFlags;
    bd.StructureByteStride;*/

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem= &m_pVertexList.at(0);
    hr = m_p3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
    /*sd.SysMemPitch;
    sd.SysMemSlicePitch;*/
    return hr;
}

HRESULT BObject::CreateIndexBuffer()
{
    HRESULT hr;
    CreateIndexData();
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(ObjectVertex) * m_pIndexList.size();
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    /*bd.CPUAccessFlags;
    bd.MiscFlags;
    bd.StructureByteStride;*/

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &m_pIndexList.at(0);
    hr = m_p3dDevice->CreateBuffer(&bd, &sd, &m_pIndexBuffer);
    /*sd.SysMemPitch;
    sd.SysMemSlicePitch;*/
    return hr;
}

HRESULT BObject::CreateVertexLayout()
{
    HRESULT hr;
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0, D3D11_INPUT_PER_VERTEX_DATA,0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,12, D3D11_INPUT_PER_VERTEX_DATA,0},
        {"TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0,28, D3D11_INPUT_PER_VERTEX_DATA,0}
    };
    UINT NumElements = sizeof(ied) / sizeof(ied[0]);
    hr = m_p3dDevice->CreateInputLayout(ied, NumElements, m_pVScode->GetBufferPointer(), m_pVScode->GetBufferSize(), &m_pVertexLayout);
    return hr;
}

HRESULT BObject::CreateVertexShader(std::wstring _shFile)
{
    HRESULT hr;
    // 정점쉐이더 생성
    ID3DBlob* pErrorCode = nullptr;
    hr = D3DCompileFromFile(_shFile.c_str(), NULL, NULL, "VS", "vs_5_0", 0, 0, &m_pVScode, &pErrorCode);
    if (FAILED(hr) && pErrorCode)
    {
        OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
        pErrorCode->Release();
        return hr;
    }
    hr = m_p3dDevice->CreateVertexShader(m_pVScode->GetBufferPointer(), m_pVScode->GetBufferSize(), NULL, &m_pVS);
    if (FAILED(hr) && pErrorCode)
    {
        OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
        pErrorCode->Release();
        return hr;
    }
    return hr;
}

HRESULT BObject::CreatePixelShader(std::wstring _shFile)
{
    HRESULT hr;
    // 정점쉐이더 생성
    ID3DBlob* pErrorCode = nullptr;
    hr = D3DCompileFromFile(_shFile.c_str(), NULL, NULL, "PS", "ps_5_0", 0, 0, &m_pPScode, &pErrorCode);
    if (FAILED(hr) && pErrorCode)
    {
        OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
        pErrorCode->Release();
        return hr;
    }
    hr = m_p3dDevice->CreatePixelShader(m_pPScode->GetBufferPointer(), m_pPScode->GetBufferSize(), NULL, &m_pPS);
    if (FAILED(hr) && pErrorCode)
    {
        OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
        pErrorCode->Release();
        return hr;
    }
    return hr;
}

HRESULT BObject::LoadTexture(std::wstring name)
{
    HRESULT hr = DirectX::CreateWICTextureFromFile(m_p3dDevice, m_pImmediateContext, name.c_str(), (ID3D11Resource**)&m_pTexture, &m_pTextureSRV);
    m_pTexture->GetDesc(&m_Desc);
    return hr;
}


void BObject::CreateVertexData()
{
    // 버텍스 데이터 생성
    m_pVertexList.resize(4);
    m_pVertexList[0].position = { -1.0f, 1.0f, 1.0f };
    m_pVertexList[1].position = { 1.0f, 1.0f, 1.0f };
    m_pVertexList[2].position = { -1.0f, -1.0f, 1.0f };
    m_pVertexList[3].position = {  1.0f, -1.0f, 1.0f };

    m_pVertexList[0].color = { 1.0f, 1.0f, 1.0f,1.0f };
    m_pVertexList[1].color = { 1.0f, 1.0f, 1.0f,1.0f };
    m_pVertexList[2].color = { 1.0f, 1.0f, 1.0f,1.0f };
    m_pVertexList[3].color = { 1.0f, 1.0f, 1.0f,1.0f };

    m_pVertexList[0].texture = { 0.0f, 0.0f };
    m_pVertexList[1].texture = { 1.0f, 0.0f };
    m_pVertexList[2].texture = { 0.0f, 1.0f };
    m_pVertexList[3].texture = { 1.0f, 1.0f };
}

void BObject::CreateIndexData()
{
    m_pIndexList.resize(6);
    m_pIndexList[0] = 0;
    m_pIndexList[1] = 1;
    m_pIndexList[2] = 2;
    m_pIndexList[3] = 2;
    m_pIndexList[4] = 1;
    m_pIndexList[5] = 3;
}
