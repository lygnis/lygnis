#pragma once
#include "MNode.h"
#include "DebugCamera.h"


class MQuadTree
{
public:
	MNode* m_pRootNode;
	int m_iMaxDepth;
	DebugCamera* m_Camera;
	MmapTile* m_pMap;
	std::vector<MNode*>		m_pLeafNodeList;
	std::vector<MNode*>		m_pDrawLeafNodeList;
	ID3D11DeviceContext*	m_pImmediateContext;
public:
	bool Create(ID3D11DeviceContext* pContext, DebugCamera* pMainCamera, MmapTile* pMap, int iMaxDepth = 3);
	void BuildTree(MNode* pNode);
	bool Frame();
	bool Render();
	MNode* VisibleNode(MNode* pNode);
	bool IsSubDivide(MNode* pNode);
};

