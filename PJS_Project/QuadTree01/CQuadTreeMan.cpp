#include "CQuadTreeMan.h"

void CQuadTreeMan::Create(float fWidth, float fHeight)
{
	m_pRootNode = CreateNode(nullptr, 0, 0, fWidth, fHeight);
	BuildTree(m_pRootNode);
}

CNode* CQuadTreeMan::CreateNode(CNode* pParent, float fX, float fY, float fWidth, float fHeight)
{
	CNode* pNode = new CNode(pParent, fX, fY, fWidth, fHeight);
	return pNode;
}


// (0,0)		0	(50,0)		1		(100,0)
// (0,50)		(50,50)				(100,50)
// (0,100)   3    (50,100)		2		(100,100)
void CQuadTreeMan::BuildTree(CNode* pParent)
{
	if (pParent->m_iDepth >= 2) return;
	if (pParent == nullptr) return;
	float x, y, w, h;
	x = pParent->m_tRect.o_Px;
	y = pParent->m_tRect.o_Py;
	w = pParent->m_tRect.w/2.0f;
	h = pParent->m_tRect.h/2.0f;
	pParent->m_pChild[0] = CreateNode(pParent, x, y, w, h);

	x = pParent->m_tRect.o_Px + w;
	y = pParent->m_tRect.o_Py;
	pParent->m_pChild[1] = CreateNode(pParent, x, y, w, h);

	x = pParent->m_tRect.o_Px + w;
	y = pParent->m_tRect.o_Py + h;
	pParent->m_pChild[2] = CreateNode(pParent, x, y, w, h);

	x = pParent->m_tRect.o_Px;
	y = pParent->m_tRect.o_Py + h;
	pParent->m_pChild[3] = CreateNode(pParent, x, y, w, h);
	for (int iCount = 0; iCount < 4; iCount++)
	{
		BuildTree(pParent->m_pChild[iCount]);
	}
}

void CQuadTreeMan::AddStaticObject(CObject* pObj)
{
	CNode* fNode = FindNode(m_pRootNode, pObj);
	if (fNode == nullptr)
		return;
	fNode->m_StaticObjectlist.push_back(pObj);
}

void CQuadTreeMan::AddDyanaminObject(CObject* pObj)			// 노드랑 교차하는 오브젝트를 찾는다.
{
	CNode* fNode = FindNode(m_pRootNode, pObj);
	if (fNode == nullptr)
		return;
	fNode->m_DynamicObjectlist.push_back(pObj);				// 찾은 오브젝트를 리스트에 추가한다.
}

CNode* CQuadTreeMan::FindNode(CNode* pNode, CObject* pObj)
{
	std::queue<CNode*> g_queue;
	do
	{
		for (int i = 0; i < 4; i++)
		{
			if (pNode->m_pChild[i] != nullptr)
			{
				bool rect  = CColision::RectToInRect(pNode->m_pChild[i]->m_tRect, pObj->m_rect);		// 교차하거나 포함이면 1, 2반환
				if (rect ==true)
				{
					g_queue.push(pNode->m_pChild[i]);
					break;
				}
			}
		}
		if (g_queue.empty())
			break;
		pNode = g_queue.front();
		g_queue.pop();
	} while (pNode);
	return pNode;
}

void CQuadTreeMan::DyanmicObjectReset(CNode* pNode)
{
	if (pNode == nullptr)
		return;
	pNode->m_DynamicObjectlist.clear();				// 초기화
	DyanmicObjectReset(pNode->m_pChild[0]);
	DyanmicObjectReset(pNode->m_pChild[1]);
	DyanmicObjectReset(pNode->m_pChild[2]);
	DyanmicObjectReset(pNode->m_pChild[3]);
}

std::vector<CObject*> CQuadTreeMan::Collision(CObject* pObj)
{
	std::vector<CObject*> o_Collision;
	GetCollision(this->m_pRootNode, pObj, o_Collision);
	return o_Collision;
}

void CQuadTreeMan::GetCollision(CNode* pNode, CObject* pObj, std::vector<CObject*>& objList)
{
	if (pNode->m_pChild[0] == nullptr)
		return;
	// 충돌된 오브젝트(static, Dynamic)를 오브젝트 리스트에 추가한다.
	for (int i = 0; i < pNode->m_StaticObjectlist.size(); i++)				// 정적 오브젝트 추가
	{
		if (CColision::RectToRect(pNode->m_StaticObjectlist[i]->m_rect, pObj->m_rect))
		{
			objList.push_back(pNode->m_StaticObjectlist[i]);
		}
	}
	for (int i = 0; i < pNode->m_DynamicObjectlist.size(); i++)				// 동적 오브젝트 추가
	{
		if (CColision::RectToRect(pNode->m_DynamicObjectlist[i]->m_rect, pObj->m_rect))
		{
			objList.push_back(pNode->m_DynamicObjectlist[i]);
		}
	}
	if (pNode->m_pChild[0] != nullptr)													// 재귀 호출로 오브젝트랑 겹치거나 포함 노드가 있으면 자식노드로 내려
	{																	// 가서 충돌체크를 한다.
		for (int i = 0; i < 4; i++)
		{
			if (CColision::RectToRect(pNode->m_pChild[i]->m_tRect, pObj->m_rect))
			{
				GetCollision(pNode->m_pChild[i], pObj, objList);
			}
		}
	}

}
