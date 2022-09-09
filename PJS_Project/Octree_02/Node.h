#pragma once
#include "Vector3D.h"
#include <vector>
#include "Object.h"
#include "Coordinate.h"
// 노드의 구성
// 노드의 크기, 노드의 현재 깊이 단계, 그 노드 안에 있는 오브젝트, 노드의 자식 
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

