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
        return 0;
    }
    if (!CreateIndexData())
    {
        return 0;
    }
    if (FAILED(CreateVertexBuffer()))
    {
        return 0;
    }
    if (FAILED(CreateIndexBuffer()))
    {
        return 0;
    }
    if (FAILED(CreateConstantBuffer()))
    {
        return 0;
    }
    if (FAILED(LoadTextures(pDevice, pLoadTextureString)))
    {
        return 0;
    }
    if (!UpdateBuffer())
    {
        return 0;
    }
    if (FAILED(CreateResource()))
    {
        return 0;
    }
    SetCollisionData(m_matWorld);
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
    HRESULT hr = S_OK;
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
    return true;
}

bool MActor::CreateIndexData()
{
    return true;
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
    if (m_dxObj.m_iNumIndex <= 0)
        return S_OK;
    void** pData = nullptr;
    if (m_IndexList.size() > 0)
        pData = (void**)&m_IndexList.at(0);

    m_dxObj.g_pIndexBuffer.Attach(DX::CreateIndexBuffer(m_pd3dDevice, pData, m_dxObj.m_iNumIndex, m_dxObj.m_iIndexSize));
    return S_OK;
}

HRESULT MActor::CreateConstantBuffer()
{
    m_cbDatas.Color = TVector4(1, 1, 1, 1);
    m_dxObj.g_pConstantBuffer.Attach(DX::CreateConstantBuffer(m_pd3dDevice, &m_cbDatas, 1, sizeof(VS_CONSTANT_BUFFER)));
    return S_OK;
}

HRESULT MActor::LoadTextures(ID3D11Device* _pDevice, const TCHAR* _pTextureFile)
{
    HRESULT hr = S_OK;
    m_dxObj.g_pTextureSRV.Attach(DX::CreateShaderResourceView(_pDevice, m_pImmediateContext, _pTextureFile));
    return S_OK;
}

bool MActor::UpdateBuffer()
{
    return true;
}

HRESULT MActor::CreateResource()
{
    m_dxObj.m_iPrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    return S_OK;
}

void MActor::UpdateConstantBuffer(ID3D11DeviceContext* pContext, MActor* pParent)
{
    if (pParent != NULL && pParent->m_dxObj.g_pConstantBuffer != nullptr)
    {
        pContext->UpdateSubresource(pParent->m_dxObj.g_pConstantBuffer.Get(), 0, NULL, &pParent->m_cbDatas, 0, 0);
    }
    else
    {
        if (m_dxObj.g_pConstantBuffer != nullptr)
        {
            pContext->UpdateSubresource(m_dxObj.g_pConstantBuffer.Get(), 0, NULL, &m_cbDatas, 0, 0);
        }
    }
}

void MActor::SetMatrix(TMatrix* pWorld, TMatrix* pView, TMatrix* pProj, ID3D11DeviceContext* pContext)
{
    if (pWorld != NULL)
    {
        m_matWorld = *pWorld;
        m_vCenter.x = pWorld->_41;
        m_vCenter.y = pWorld->_42;
        m_vCenter.z = pWorld->_43;
    }
    if (pView != NULL)
    {
        m_matView = *pView;
    }
    if (pProj != NULL)
    {
        m_matProj = *pProj;
    }
    UpdateConstantBuffer(pContext);
    D3DXMatrixTranspose(&m_cbDatas.matWorld, &m_matWorld);
    D3DXMatrixTranspose(&m_cbDatas.matView, &m_matView);
    D3DXMatrixTranspose(&m_cbDatas.matProj, & m_matProj);
    if (m_bUpdateCollision)
    {
        SetCollisionData(m_matWorld);
    }
}

void MActor::SetCollisionData(TMatrix& matWorld)
{
    m_matWorld = matWorld;
    m_vCenter.x = m_matWorld._41;
    m_vCenter.y = m_matWorld._42;
    m_vCenter.z = m_matWorld._43;

    m_vLook.x = m_matWorld._31;
    m_vLook.y = m_matWorld._32;
    m_vLook.z = m_matWorld._33;

    m_vUp.x = m_matWorld._21;
    m_vUp.x = m_matWorld._22;
    m_vUp.x = m_matWorld._23;

    m_vRight.x = m_matWorld._11;
    m_vRight.x = m_matWorld._12;
    m_vRight.x = m_matWorld._13;
}

bool MActor::PreRender(ID3D11DeviceContext* _pContext)
{
    _pContext->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)m_dxObj.m_iPrimitiveType);
    m_dxObj.PreRender(_pContext, m_dxObj.m_iVertexSize);
    return true;
}

bool MActor::PostRender(ID3D11DeviceContext* _pContext)
{
    //UpdateConstantBuffer(_pContext);
    m_dxObj.PostRender(_pContext, m_dxObj.m_iNumIndex);
    return true;
}

bool MActor::Render(ID3D11DeviceContext* _pContext)
{
    PreRender(_pContext);
    PostRender(_pContext);
    return true;
}

bool MActor::Release()
{
    m_IndexList.clear();
    m_VertexList.clear();
    return true;
}
