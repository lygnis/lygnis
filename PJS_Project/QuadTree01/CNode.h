#pragma once
#include"CColision.h"
#include <vector>
#include "CObject.h"
class CNode
{
public:
	CNode(CNode* pParent, float fX, float fY, float fWidht, float fHeight);
	~CNode();
public:
	int		m_iDepth;
	CNode*	m_pChild[4];
	CNode*	m_pParent;
	TRect	m_tRect;
public:
	std::vector<CObject*> m_StaticObjectlist;			// ���� ������Ʈ ����Ʈ
	std::vector<CObject*> m_DynamicObjectlist;			// ���� ������Ʈ ����Ʈ
};

