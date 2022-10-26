#include "MActor.h"

bool MActor::Create(ID3D11Device* pDevice, const TCHAR* pLoadShaderFile, const TCHAR* pLoadTextureString)
{
    m_pd3dDevice = pDevice;
    if (FAILED(LoadShaderFile(pDevice, pLoadShaderFile)))
    {
        return 0;
    }
    if (FAILED(SetInputLayout()))
    {
        return 0;
    }
    if (!CreateVertexData())
    {

    }
    if (!CreateIndexData())
    {

    }
    if (FAILED(CreateVertexBuffer()))
    {

    }
    if (FAILED(CreateIndexBuffer()))
    {

    }
    if (FAILED(CreateConstantBuffer()))
    {

    }
    if (FAILED(LoadTextures(pDevice, pLoadTextureString)))
    {

    }
    if (!UpdateBuffer())
    {

    }
    if (FAILED(CreateResource()))
    {

    }
    return 0; //Init();
}

HRESULT MActor::LoadShaderFile(ID3D11Device* _pDevice, const TCHAR* _pShaderFile)
{
    m_dxObj.g_pVertexShader.Attach(DX::LoadVertexShaderFile(_pDevice, _pShaderFile, m_dxObj.g_pVSBlob.GetAddressOf()));
    m_dxObj.g_pPixelShader.Attach(DX::LoadPixelShaderFile(_pDevice, _pShaderFile));
    return S_OK;
}

HRESULT MActor::SetInputLayout()
{
    HRESULT hr;
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT NumElements = sizeof(ied) / sizeof(ied[0]);
    m_dxObj.g_pInputlayout.Attach(DX::CreateInputlayout(m_pd3dDevice, (DWORD)m_dxObj.g_pVSBlob.Get()->GetBufferSize()
        , m_dxObj.g_pVSBlob.Get()->GetBufferPointer(), ied, NumElements));

    return hr;
}

bool MActor::CreateVertexData()
{
    return false;
}

bool MActor::CreateIndexData()
{
    return false;
}

HRESULT MActor::CreateVertexBuffer()
{
    if (m_dxObj.m_iNumVertex <= 0)
        return S_OK;
    void** pData = nullptr;
    if (m_VertexList.size() > 0)
        pData = (void**)&m_VertexList.at(0);
    m_dxObj.g_pVertexBuffer.Attach(DX::CreateVertexBuffer(m_pd3dDevice, pData, m_dxObj.m_iNumVertex, m_dxObj.m_iVertexSize));
    return S_OK;
}

HRESULT MActor::CreateIndexBuffer()
{

    return E_NOTIMPL;
}

HRESULT MActor::CreateConstantBuffer()
{
    return E_NOTIMPL;
}

HRESULT MActor::LoadTextures(ID3D11Device* _pDevice, const TCHAR* _pTextureFile)
{
    return E_NOTIMPL;
}

bool MActor::UpdateBuffer()
{
    return false;
}

HRESULT MActor::CreateResource()
{
    return E_NOTIMPL;
}
