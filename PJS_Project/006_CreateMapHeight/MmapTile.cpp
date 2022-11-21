#include "MmapTile.h"

bool MmapTile::SetDevice(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pContext)
{
    m_pd3dDevice = _p3dDevice;
    m_pImmediateContext = _pContext;
    return false;
}

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
    for (int iRow = 0; iRow < m_iNumRow; iRow++)
    {
        for (int iCol = 0; iCol < m_iNumCol; iCol++)
        {
            m_VertexList[iRow * m_iNumCol + iCol].p.x = { (float)(iCol - fHalfWidth) * m_fCellDistance };
            m_VertexList[iRow * m_iNumCol + iCol].p.y = m_fHeightList[iRow*m_iNumCol + iCol]* m_fScaleHeight;
            m_VertexList[iRow * m_iNumCol + iCol].p.z = { (float)(fHalfHeight - iRow) * m_fCellDistance };
            m_VertexList[iRow * m_iNumCol + iCol].c = { 1,1,1,1 };
            m_VertexList[iRow * m_iNumCol + iCol].t.x = { ((float)iCol / (float)m_iCellCols) *10};
            m_VertexList[iRow * m_iNumCol + iCol].t.y = { ((float)iRow / (float)m_iCellRows) * 10};
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
    GetnVertexNormal();
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
                    m_fHeightList[row * desc.Width + col] = (float)uRed / 255.0f;
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

float MmapTile::GetHeightOfVertex(UINT Index)
{
    return m_fHeightList[Index];
}

float MmapTile::GetHeight(float posX, float posZ)
{
    // fPosX/ fPosZ의 위치에 해당하는 높이 맵셀을 찾는다.
    // iNum, iCol은 가로/세로의 실제 크기 값이다.
    float fCellX = (float)(m_iCellRows * m_fCellDistance / 2.0f + posX);
    float fCellZ = (float)(m_iCellCols * m_fCellDistance / 2.0f + posZ);
    
    // 셀의 크기로 나누어 0~1 단위의 값으로 바꾸어 높이 맵 배열에 접근한다.
    fCellX /= (float)m_fCellDistance;
    fCellZ /= (float)m_fCellDistance;

    // 각각의 값보다 작거나 같은 최대 정수중 소수부분을 잘라낸다.
    float fVertexCol = ::floorf(fCellX);
    float fVertexRow = ::floorf(fCellZ);

    // 높이맵의 범위를 벗어나면 강제로 초기화한다.
    if (fVertexCol < 0.0f)
        fVertexCol = 0.0f;
    if (fVertexRow < 0.0f)
        fVertexRow = 0.0f;
    if ((float)(m_iNumCol - 2) < fVertexCol)
        fVertexCol = (float)(m_iNumCol - 2);
    if ((float)(m_iNumRow - 2) < fVertexRow)
        fVertexRow = (float)(m_iNumRow - 2);
    // 계산된 셀의 플랜을 구성하는 4개 정점의 높이값을 찾는다. 
    //  A   B
    //  *---*
    //  | / |
    //  *---*  
    //  C   D
    float A = GetHeightMap((int)fVertexRow, (int)fVertexCol);
    float B = GetHeightMap((int)fVertexRow, (int)fVertexCol +1);
    float C = GetHeightMap((int)fVertexRow +1, (int)fVertexCol);
    float D = GetHeightMap((int)fVertexRow +1, (int)fVertexCol+1);
    // A 정점의 위치에서 떨어진 값을 계산한다. 0~1.0f
    float fDeltaX = fCellX - fVertexCol;
    float fDeltaZ = fCellZ - fVertexRow;
    // 보간작업을 위한 기준 페이스를 찾는다.
    float fHeight = 0.0f;
    // 위페이스를 기준으로 보간한다.
    // fDeltaZ +fDeltaX <1.0f
    if (fDeltaZ < (1.0f - fDeltaX))
    {
        // ABC
        float uy = B - A;
        float vy = C - A;
        // 두정점의 높이값의 차이를 비교하여 델타 X의 값에 따라 보간값을 찾는다.
        fHeight = A + Lerp(0.0f, uy, fDeltaX) + Lerp(0.0f, vy, fDeltaZ);
    }
    // 아래페이스를 기준으로 보간한다./
    else
    {
        float uv = C - D;
        float vy = B - D;
        // 델타 Z의 값에 따라 보간값을 찾는다.
        fHeight = D + Lerp(0.0f, uv, 1.0f - fDeltaX)+ Lerp(0.0f, vy,1.0f-fDeltaZ);
    }
    return fHeight;
}

float MmapTile::GetHeightMap(int row, int col)
{
    return m_VertexList[row*m_iNumRow +col].p.y;
}

float MmapTile::Lerp(float start, float end, float fTangent)
{
    return start - (start * fTangent) + (end * fTangent);
}

void MmapTile::GetnVertexNormal()
{
    std::vector<TVector3> m_FaceNormal;
    m_FaceNormal.resize(m_iNumFace);
    UINT iFace = 0;
    for (UINT i = 0; i < m_IndexList.size(); i += 3)
    {
        UINT i0 = m_IndexList[i + 0];
        UINT i1 = m_IndexList[i + 1];
        UINT i2 = m_IndexList[i + 2];
        m_FaceNormal[iFace++] = ComputeFaceNormal(i0,i1,i2);
    }
    struct tVertexInfo
    {
        std::vector<UINT> faceIndexArray;
        TVector3 vNormal;
    };
    std::vector<tVertexInfo>m_VertexInfo;
    m_VertexInfo.resize(m_iNumCol* m_iNumRow);
    for (UINT iFace = 0; iFace < m_iNumFace; iFace++)
    {
        for (UINT i = 0; i < 3; i++)
        {
            UINT i0 = m_IndexList[iFace * 3 + 1];
            m_VertexInfo[i0].faceIndexArray.push_back(iFace);
        }
    }
    for (UINT iVertex = 0; iVertex < m_VertexInfo.size(); iVertex++)
    {
        for (UINT i = 0; i < m_VertexInfo[iVertex].faceIndexArray.size(); i++)
        {
            m_VertexInfo[iVertex].vNormal += m_FaceNormal[m_VertexInfo[iVertex].faceIndexArray[i]];
        }
        D3DXVec3Normalize(&m_VertexInfo[iVertex].vNormal, &m_VertexInfo[iVertex].vNormal);
        m_VertexList[iVertex].n = m_VertexInfo[iVertex].vNormal;
        TVector3 vLight = { 1,1,0 };
        float fDot = D3DXVec3Dot(&vLight, &m_VertexList[iVertex].n);
        m_VertexList[iVertex].c = { fDot,fDot,fDot,1 };
    }
}

TVector3 MmapTile::ComputeFaceNormal(UINT i0, UINT i1, UINT i2)
{
    TVector3 vNormal;
    TVector3 e0 = m_VertexList[i1].p - m_VertexList[i0].p;
    TVector3 e1 = m_VertexList[i2].p - m_VertexList[i0].p;
    D3DXVec3Cross(&vNormal, &e0, &e1);
    D3DXVec3Normalize(&vNormal, &vNormal);
    return vNormal;
}
