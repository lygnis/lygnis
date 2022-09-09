#pragma once
#include "CNode.h"
#include "CObject.h"
#include <vector>
#include <queue>
// 트리구조 생성 구축 클래스
class CQuadTreeMan
{
public:
	CNode* m_pRootNode;

public:
	void Create(float fWidth, float fHeight);			// 크기 할당
	CNode* CreateNode(CNode* pParent, float fX, float fY, float fWidth, float fHeight);
	void BuildTree(CNode* pParent);

public:
	void AddStaticObject(CObject* pObj);					// 정적 오브젝트 추가
	void AddDyanaminObject(CObject* pObj);					// 동적 오브젝트 추기
	CNode* FindNode(CNode* pNode, CObject* pObj);			// 오브젝트 추가할때 노드 찾기 
	void DyanmicObjectReset(CNode* pNode);					// 동적 오브젝트 초기화
	std::vector<CObject*> Collision(CObject* pObj);
	void GetCollision(CNode* pNode, CObject* pObj, std::vector<CObject*>& objList);

};

