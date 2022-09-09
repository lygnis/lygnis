#include "Node.h"

Node::Node()
{
	
}

Node::Node(Node* _pParent, Vector3D _vCtPoint, Vector3D _vSize)
{
	m_vBox.SetPosition(_vCtPoint, _vSize);
	m_iDepth = 0;

	if (_pParent != nullptr)
	{
		m_pParentNode = _pParent;
		m_iDepth = _pParent->m_iDepth + 1;
	}
}

Node::~Node()
{
	for (int i = 0; i < 8; i++)
	{
		delete m_pChild[i];
	}
}
