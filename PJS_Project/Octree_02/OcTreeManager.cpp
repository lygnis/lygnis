#include "OcTreeManager.h"

void OcTreeManager::Create()
{
	Vector3D _vPtemp(0,0,0);
	Vector3D _vStemp(100.0f, 100.0f, 100.0f);
	m_pRootNode = CreateNode(m_pRootNode,_vPtemp, _vStemp );
	BuildNode(m_pRootNode);
}

void OcTreeManager::BuildNode(Node* pNode)
{
	if (pNode->m_iDepth >= 3)
		return;
	if (pNode == nullptr)
		return;
	Vector3D _ctPoint;
	Vector3D _Size;
	_ctPoint = pNode->m_vBox.v_ctPoint;		// �������� ����� ����
	_Size = pNode->m_vBox.v_Size / 2.0f;		// ũ�⸦ ������
	pNode->m_pChild[0] = CreateNode(pNode, _ctPoint, _Size);		// 0,0,0 -> 50,50,50

	_ctPoint.x = pNode->m_vBox.v_ctPoint.x + _Size.x;
	pNode->m_pChild[1] = CreateNode(pNode, _ctPoint, _Size);		// 50,0,0->100,50,50

	_ctPoint.x = pNode->m_vBox.v_ctPoint.x;
	_ctPoint.y = pNode->m_vBox.v_ctPoint.y + _Size.y;
	pNode->m_pChild[2] = CreateNode(pNode, _ctPoint, _Size);		// 0,50,0->0,100,0

	_ctPoint.x = pNode->m_vBox.v_ctPoint.x + _Size.x;
	_ctPoint.y = pNode->m_vBox.v_ctPoint.y + _Size.y;
	pNode->m_pChild[3] = CreateNode(pNode, _ctPoint, _Size);
	// z�� ����
	_ctPoint.x = pNode->m_vBox.v_ctPoint.x;
	_ctPoint.y = pNode->m_vBox.v_ctPoint.y;
	_ctPoint.z = pNode->m_vBox.v_ctPoint.z + _Size.z;
	pNode->m_pChild[4] = CreateNode(pNode, _ctPoint, _Size);

	_ctPoint.x = pNode->m_vBox.v_ctPoint.x + _Size.x;
	pNode->m_pChild[5] = CreateNode(pNode, _ctPoint, _Size);

	_ctPoint.x = pNode->m_vBox.v_ctPoint.x;
	_ctPoint.y = pNode->m_vBox.v_ctPoint.y + _Size.y;
	pNode->m_pChild[6] = CreateNode(pNode, _ctPoint, _Size);

	_ctPoint.x = pNode->m_vBox.v_ctPoint.x + _Size.x;
	_ctPoint.y = pNode->m_vBox.v_ctPoint.y + _Size.y;
	pNode->m_pChild[7] = CreateNode(pNode, _ctPoint, _Size);

	for (int i = 0; i < pNode->m_pChild.size(); i++)
	{
		BuildNode(pNode->m_pChild[i]);
	}
}

Node* OcTreeManager::CreateNode(Node* _pParent, Vector3D _point, Vector3D _size)
{
	Node* newNode = new Node(_pParent, _point, _size);
	newNode->m_pChild.resize(8);						// �ڽ��� �ּҸ� ���ͷ� �����߱� ������ ������� 8���� ���ش�. (8�� Ʈ��)
	return newNode;
}

Node* OcTreeManager::FindNode(Node* pNode, Object* pObj)
{
	std::queue<Node*> g_queue;
	do
	{
		for (int i = 0; i < pNode->m_pChild.size(); i++)
		{
			if (pNode->m_pChild[i] != nullptr)
			{
				int cType = Collision::BoxToBox(pNode->m_pChild[i]->m_vBox, pObj->m_Coor); // ���� ����� �ڽ��� ������Ʈ�� ���Խ�Ű��
				if (cType == CollisionType::BoxIn)
				{
					g_queue.push(pNode->m_pChild[i]);									// ť�� ����� �ڽ��� �ִ´�.
					break;
				}
			}
		}																				
		if (g_queue.empty())															// ť�� ���������
			break;
		pNode = g_queue.front();														// pNode�� ť�� �������� �� ù��°�� ����
		g_queue.pop();																// �� ����
	} while (pNode);
	return pNode;
}

void OcTreeManager::AddStaticObject(Object* pObj)
{
	Node* fNode = FindNode(m_pRootNode, pObj);
	if (fNode == nullptr)
		return;
	fNode->m_StaticObject.push_back(pObj);
}

void OcTreeManager::AddDynamicObject(Object* pObj)
{
	Node* fNode = FindNode(m_pRootNode, pObj);
	if (fNode == nullptr)
		return;
	fNode->m_DynamicObject.push_back(pObj);
}

void OcTreeManager::DynamicObjectReset(Node* pNode)
{
	if (pNode == nullptr)
		return;
	pNode->m_DynamicObject.clear();
	DynamicObjectReset(pNode->m_pChild[0]);
	DynamicObjectReset(pNode->m_pChild[1]);
	DynamicObjectReset(pNode->m_pChild[2]);
	DynamicObjectReset(pNode->m_pChild[3]);
	DynamicObjectReset(pNode->m_pChild[4]);
	DynamicObjectReset(pNode->m_pChild[5]);
	DynamicObjectReset(pNode->m_pChild[6]);
	DynamicObjectReset(pNode->m_pChild[7]);
}

std::vector<Object*> OcTreeManager::Collision(Object* pObj)
{
	std::vector<Object*> v_CollsionList;
	GetCollsion(this->m_pRootNode, pObj, v_CollsionList);
	return v_CollsionList;
}

void OcTreeManager::GetCollsion(Node* pNode, Object* pObj, std::vector<Object*>& objList)
{
	if (pNode->m_pChild[0] == nullptr)
		return;
	// �浹�� ������Ʈ�� ������Ʈ ����Ʈ�� �߰��Ѵ�.
	for (int i = 0; i < pNode->m_StaticObject.size(); i++)
	{
		if (Collision::BoxToBox(pNode->m_StaticObject[i]->m_Coor, pObj->m_Coor))
		{
			objList.push_back(pNode->m_StaticObject[i]);
		}
	}
	for (int i = 0; i < pNode->m_DynamicObject.size(); i++)
	{
		if (Collision::BoxToBox(pNode->m_DynamicObject[i]->m_Coor, pObj->m_Coor))
		{
			objList.push_back(pNode->m_DynamicObject[i]);
		}
	}
	//��� ȣ��� ������Ʈ�� ��ġ�ų� ���Գ�尡 ������ �ڽĳ��� �������� �浹üũ�� �Ѵ�.
	if (pNode->m_pChild[0] != nullptr)
	{
		for (int i = 0; i < pNode->m_pChild.size(); i++)
		{
			if (Collision::BoxToBox(pNode->m_pChild[i]->m_vBox, pObj->m_Coor))
			{
				GetCollsion(pNode->m_pChild[i], pObj, objList);
			}
		}
		for (int i = 0; i < pNode->m_pChild.size(); i++)
		{
			if (Collision::BoxToBox(pNode->m_pChild[i]->m_vBox, pObj->m_Coor))
			{
				GetCollsion(pNode->m_pChild[i], pObj, objList);
			}
		}
	}
}
