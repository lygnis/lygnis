#pragma once
#include "CNode.h"
#include "CObject.h"
#include <vector>
#include <queue>
// Ʈ������ ���� ���� Ŭ����
class CQuadTreeMan
{
public:
	CNode* m_pRootNode;

public:
	void Create(float fWidth, float fHeight);			// ũ�� �Ҵ�
	CNode* CreateNode(CNode* pParent, float fX, float fY, float fWidth, float fHeight);
	void BuildTree(CNode* pParent);

public:
	void AddStaticObject(CObject* pObj);					// ���� ������Ʈ �߰�
	void AddDyanaminObject(CObject* pObj);					// ���� ������Ʈ �߱�
	CNode* FindNode(CNode* pNode, CObject* pObj);			// ������Ʈ �߰��Ҷ� ��� ã�� 
	void DyanmicObjectReset(CNode* pNode);					// ���� ������Ʈ �ʱ�ȭ
	std::vector<CObject*> Collision(CObject* pObj);
	void GetCollision(CNode* pNode, CObject* pObj, std::vector<CObject*>& objList);

};

