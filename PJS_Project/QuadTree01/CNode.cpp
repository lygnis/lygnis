#include "CNode.h"

CNode::CNode(CNode* pParent, float fX, float fY, float fWidht, float fHeight)
{
	m_tRect.Set(fX, fY, fWidht, fHeight);

	m_iDepth = 0;
	if (pParent != nullptr)
	{
		m_pParent = pParent;
		m_iDepth = pParent->m_iDepth + 1;
	}
}

CNode::~CNode()
{
	delete m_pChild[0];
	delete m_pChild[1];
	delete m_pChild[2];
	delete m_pChild[3];
}
