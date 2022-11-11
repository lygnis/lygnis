#include "MNode.h"

void MNode::CreateChildNode(MNode* pParent, MmapTile* pMap, DWORD dwNumCols, DWORD dwNumRows)
{
	// 0  1   2   3   4
	// 5  6   7   8   9
	// 10 11  12  13  14
	// 15 16  17  18  19
	// 20  21 22  23  24
	RECT rt = pParent->m_rt;
	DWORD dwLT = pParent->m_dCorner[0];
	DWORD dwRT = pParent->m_dCorner[1];
	DWORD dwRB = pParent->m_dCorner[2];
	DWORD dwLB = pParent->m_dCorner[3];
	DWORD dwTopCenter = (dwLT + dwRT) / 2;
	DWORD dwRightCenter = (dwRT + dwRB) / 2;
	DWORD dwLeftCenter = (dwLT + dwLB) / 2;
	DWORD dwBottomCenter = (dwLB + dwRB) / 2;
	DWORD dwCenter = (dwRT + dwLT + dwRB + dwLB) / 4;
	m_pChildNode[0] = new MNode(pParent, pMap, dwLT, dwTopCenter, dwLeftCenter, dwCenter, dwNumCols, dwNumRows);
	m_pChildNode[1] = new MNode(pParent, pMap, dwTopCenter, dwRT, dwCenter, dwRightCenter, dwNumCols, dwNumRows);
	m_pChildNode[2] = new MNode(pParent, pMap, dwLeftCenter, dwCenter, dwLB, dwBottomCenter, dwNumCols, dwNumRows);
	m_pChildNode[3] = new MNode(pParent, pMap, dwCenter, dwRightCenter, dwBottomCenter, dwRB, dwNumCols, dwNumRows);
}

void MNode::CreateIndexData(MmapTile* pMap, DWORD dwNumRows, DWORD dwNumCols)
{
	// 0  1   2   3   4
	// 5  6   7   8   9
	// 10 11  12  13  14
	// 15 16  17  18  19
	// 20  21 22  23  24
	DWORD dwLT = m_dCorner[0];
	DWORD dwRT = m_dCorner[1];
	DWORD dwLB = m_dCorner[2];
	DWORD dwRB = m_dCorner[3];
	DWORD dwNumRowCell = (dwLB - dwLT) / dwNumCols;
	DWORD dwNUmColCell = (dwRT - dwLT);
	DWORD dwNumCells = dwNumRowCell * dwNUmColCell;
	m_IndexList.resize(dwNumCells * 2 * 3);
	int iIndex = 0;

	m_tBox.vMin.x = pMap->m_VertexList[dwLT].p.x;
	m_tBox.vMin.y = 10000.0f;
	m_tBox.vMin.z = pMap->m_VertexList[dwLB].p.z;
	m_tBox.vMax.x = pMap->m_VertexList[dwRT].p.x;
	m_tBox.vMax.y = -10000.0f;
	m_tBox.vMax.z = pMap->m_VertexList[dwLT].p.z;

	for (int dwRow = 0; dwRow < dwNumRowCell; dwRow++)
	{
		for (int dwCol = 0; dwCol < dwNUmColCell; dwCol++)
		{
			m_IndexList[iIndex + 0] = dwLT + dwCol + (dwRow * dwNumCols);
			m_IndexList[iIndex + 1] = m_IndexList[iIndex + 0] + 1;
			m_IndexList[iIndex + 2] = dwLT + dwCol + ((dwRow + 1) * dwNumCols);
			m_IndexList[iIndex + 3] = m_IndexList[iIndex + 2];
			m_IndexList[iIndex + 4] = m_IndexList[iIndex + 1];
			m_IndexList[iIndex + 5] = m_IndexList[iIndex + 2]+1;
			for (DWORD dwVertex = 0; dwVertex < 6; dwVertex++)
			{
				if (m_tBox.vMin.y > pMap->m_VertexList[m_IndexList[iIndex + dwVertex]].p.y)
				{
					m_tBox.vMin.y = pMap->m_VertexList[m_IndexList[iIndex + dwVertex]].p.y;
				}
				if (m_tBox.vMax.y < pMap->m_VertexList[m_IndexList[iIndex + dwVertex]].p.y)
				{
					m_tBox.vMax.y = pMap->m_VertexList[m_IndexList[iIndex + dwVertex]].p.y;
				}
			}
			iIndex += 6;
		}
	}
	m_dwFace = m_IndexList.size() / 3;
	m_tBox.vCenter = (m_tBox.vMax + m_tBox.vMin) * 0.5f;
	m_tBox.vAxis[0] = { 1,0,0 };
	m_tBox.vAxis[1] = { 0,1,0 };
	m_tBox.vAxis[2] = { 0,0,1 };
	m_tBox.fExtent[0] = m_tBox.vMax.x - m_tBox.vCenter.x;
	m_tBox.fExtent[1] = m_tBox.vMax.y - m_tBox.vCenter.y;
	m_tBox.fExtent[2] = m_tBox.vMax.z - m_tBox.vCenter.z;

	pMap->m_dxObj.m_iNumIndex = (UINT)m_IndexList.size();
	pMap->m_dxObj.m_iIndexSize = sizeof(UINT);
}

HRESULT MNode::CreateIndexBuffer(MmapTile* pMap, DWORD dwNumRows, DWORD dwNumCols)
{
	HRESULT hr;
	CreateIndexData(pMap, dwNumRows, dwNumCols);
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(DWORD) * m_IndexList.size();		// 바이트 용량
	bd.Usage = D3D11_USAGE_DEFAULT;							// 버퍼의 할당 장소 내지는 용도
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &m_IndexList.at(0);
	hr = pMap->m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pIndexBuffer);
	return hr;
}

MNode::MNode(MNode* pParent, MmapTile* pMap, DWORD dwLT, DWORD dwRT, DWORD dwRB, DWORD dwLB, DWORD dwNumRows, DWORD dwNumCols)
{
	if (pParent != nullptr)
	{
		m_iDepth = pParent->m_iDepth + 1;
	}
	m_dCorner[0] = dwLT;
	m_dCorner[1] = dwRT;
	m_dCorner[2] = dwLB;
	m_dCorner[3] = dwRB;
	m_bLeaf = false;
	m_pChildNode.resize(4);
	CreateIndexBuffer(pMap, dwNumCols, dwNumRows);
}

MNode::~MNode()
{
	if (m_pIndexBuffer)
		m_pIndexBuffer->Release();
	delete m_pChildNode[0];
	delete m_pChildNode[1];
	delete m_pChildNode[2];
	delete m_pChildNode[3];
	m_pChildNode[0] = nullptr;
	m_pChildNode[1] = nullptr;
	m_pChildNode[2] = nullptr;
	m_pChildNode[3] = nullptr;
}
