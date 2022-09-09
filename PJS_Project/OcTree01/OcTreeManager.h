#pragma once
#include "Node.h"
#include "Vector3D.h"
#include "Object.h"
#include <queue>
class OcTreeManager
{
	// ��Ʈ�� 8�� ��带 ������ ������ �����Ѵ�.
public:
	Node* m_pRootNode;			// ��Ʈ ��� ����
	
public:
	void Create();
	void BuildNode(Node* pNode);
	Node* CreateNode(Node* _pParent, Vector3D _point, Vector3D _size);
	Node* FindNode(Node* pNode, Object* pObj);
	void AddStaticObject(Object* pObj);
	void AddDynamicObject(Object* pObj);
	void DynamicObjectReset(Node* pNode);
	std::vector<Object*> Collision(Object* pObj);
	void GetCollsion(Node* pNode, Object* pObj, std::vector<Object*>& objList);
};

