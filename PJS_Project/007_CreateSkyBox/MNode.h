#pragma once
#include "MmapTile.h"
class MNode
{
public:
	int			m_iDepth;
	bool		m_bLeaf;
	// ³¡ ºÎºÐ ÁÂÇ¥
	DWORD		m_dCorner[4];
	RECT		m_rt;
	DWORD		m_dwFace;
	M_BOX		m_tBox;

	ID3D11Buffer* m_pIndexBuffer;
	std::vector<DWORD>	m_IndexList;
	std::vector<MNode*> m_pChildNode;
public:
	void CreateChildNode(MNode* pParent, MmapTile* pMap, DWORD dwNumCols, DWORD dwNumRows);
	void CreateIndexData(MmapTile* pMap, DWORD dwNumRows, DWORD dwNumCols);
	HRESULT CreateIndexBuffer(MmapTile* pMap, DWORD dwNumRows, DWORD dwNumCols);
public:
	MNode() {}
	MNode(MNode* pParent, MmapTile* pMap, DWORD dwLT, DWORD dwRT, DWORD dwRB, DWORD dwLB, DWORD dwNumRows, DWORD dwNumCols);
	~MNode();
};

