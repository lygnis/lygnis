#pragma once
#include "Vector3D.h"
#include <vector>
#include "Object.h"
#include "Coordinate.h"
// ����� ����
// ����� ũ��, ����� ���� ���� �ܰ�, �� ��� �ȿ� �ִ� ������Ʈ, ����� �ڽ� 
class Node
{
public:
	std::vector<Node*>	m_pChild;
	Node*				m_pParentNode;
	int					m_iDepth;
	Coor					m_vBox;
	std::vector<Object*>	m_StaticObject;
	std::vector<Object*>	m_DynamicObject;

public:
	Node();
	Node(Node* _pParent, Vector3D _vCtPoint, Vector3D _vSize);
	~Node();
};

