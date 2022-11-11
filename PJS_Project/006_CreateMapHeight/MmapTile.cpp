#include "MmapTile.h"

bool MmapTile::CreateMap(UINT col, UINT row)
{
    m_iNumCol = col;
    m_iNumRow = row;
    m_iCellRows = m_iNumRow - 1;
    m_iCellCols = m_iNumCol - 1;
    m_iNumVertices = col * row;
    m_iNumFace = m_iCellCols * m_iCellRows * 2;
    return true;
}

bool MmapTile::CreateVertexData()
{
    m_VertexList.resize(m_iNumVertices);
    float fHalfWidth = m_iNumCol /2;
    float fHalfHeight = m_iNumRow /2;
    float fCellDistance = 1.0f;
    for (int iRow = 0; iRow < m_iNumRow; iRow++)
    {
        for (int iCol = 0; iCol < m_iNumCol; iCol++)
        {
            m_VertexList[iRow * m_iNumCol + iCol].p.x = { (float)(iCol - fHalfWidth) * fCellDistance };
            m_VertexList[iRow * m_iNumCol + iCol].p.y = 0;
            m_VertexList[iRow * m_iNumCol + iCol].p.z = { (float)(fHalfHeight - iRow) * fCellDistance };
            m_VertexList[iRow * m_iNumCol + iCol].c = { 1,1,1,1 };
            m_VertexList[iRow * m_iNumCol + iCol].t.x = { ((float)iCol / (float)m_iCellCols) *1};
            m_VertexList[iRow * m_iNumCol + iCol].t.y = { ((float)iRow / (float)m_iCellRows) * 1};
        }
    }
    m_dxObj.m_iNumVertex = (UINT)m_VertexList.size();
    m_dxObj.m_iVertexSize = sizeof(PNCT_VERTEX);
    return true;
}

bool MmapTile::CreateIndexData()
{
    m_IndexList.resize(m_iNumFace * 3);
    UINT iIndex = 0;
    for (int iRow = 0; iRow < m_iCellRows; iRow++)
    {
        for (int iCol = 0; iCol < m_iCellCols; iCol++)
        {
            m_IndexList[iIndex + 0] = iRow * m_iNumCol + iCol;
            m_IndexList[iIndex + 1] = m_IndexList[iIndex + 0] +1;
            m_IndexList[iIndex + 2] = (iRow + 1) * m_iNumCol + iCol;
            m_IndexList[iIndex + 3] = m_IndexList[iIndex + 2];
            m_IndexList[iIndex + 4] = m_IndexList[iIndex + 1];
            m_IndexList[iIndex + 5] = m_IndexList[iIndex + 3] + 1;
            iIndex += 6;
        }
    }
    m_dxObj.m_iNumIndex = (UINT)m_IndexList.size();
    m_dxObj.m_iIndexSize = sizeof(UINT);
    return true;
}

bool MmapTile::CreateHeightMap(const TCHAR* _texName)
{
    HRESULT hr;
    ComPtr<ID3D11Resource> pTexture;
    ID3D11ShaderResourceView* pSRV = nullptr;
    if(FAILED(hr = CreateWICTextureFromFileEx(m_pd3dDevice,_texName, 0, D3D11_USAGE_STAGING,0, 
        D3D11_CPU_ACCESS_WRITE| D3D11_CPU_ACCESS_READ, 0, WIC_LOADER_DEFAULT, pTexture.GetAddressOf(), nullptr)))
    {
        assert(false);
    }
    ID3D11Texture2D* pTexture2D = NULL;
    if (FAILED(pTexture->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&pTexture2D)))
    {
        assert(false);
    }
    D3D11_TEXTURE2D_DESC desc;
    pTexture2D->GetDesc(&desc);
    
    m_fHeightList.resize(desc.Height * desc.Width);
    if (pTexture2D)
    {
        D3D11_MAPPED_SUBRESOURCE mappedFaceDest;
        if (SUCCEEDED(m_pImmediateContext->Map((ID3D11Resource*)pTexture2D, D3D11CalcSubresource(0, 0, 1), D3D11_MAP_READ, 0, &mappedFaceDest)))
        {
            UCHAR* pTexels = (UCHAR*)mappedFaceDest.pData;
            for (UINT row = 0; row < desc.Height; row++)
            {
                UINT rowStart = row * mappedFaceDest.RowPitch;
                for (UINT col = 0; col < desc.Width; col++)
                {
                    UINT colStart = col * 4;
                    UINT uRed = pTexels[rowStart + colStart + 0];
                    m_fHeightList[row * desc.Width + col] = (float)uRed;
                }
            }
            m_pImmediateContext->Unmap(pTexture2D, D3D11CalcSubresource(0, 0, 1));
        }
    }
    m_iNumRow = desc.Height;
    m_iNumCol = desc.Width;
    SAFE_RELEASE(pTexture2D);
    return true;
}
