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
    float fCellDistance = 10.0f;
    for (int iRow = 0; iRow < m_iNumRow; iRow++)
    {
        for (int iCol = 0; iCol < m_iNumCol; iCol++)
        {
            m_VertexList[iRow * m_iNumCol + iCol].p.x = { (float)(iCol - fHalfWidth) * fCellDistance *1 };
            m_VertexList[iRow * m_iNumCol + iCol].p.y = 0;
            m_VertexList[iRow * m_iNumCol + iCol].p.z = { (float)(fHalfHeight - iRow) * fCellDistance *1};
            m_VertexList[iRow * m_iNumCol + iCol].c = { 1,1,1,1 };
            m_VertexList[iRow * m_iNumCol + iCol].t.x = { ((float)iCol / (float)m_iCellCols) * 1 };
            m_VertexList[iRow * m_iNumCol + iCol].t.y = { ((float)iRow / (float)m_iCellRows) * 1 };
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
