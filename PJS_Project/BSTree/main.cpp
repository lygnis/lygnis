#include <iostream>
#include <queue>
// �ڽĳ�� 2���� �����ϰ�
// ��Ʈ ��忡 �����Ѵ�.
class bTree
{
public:
	bTree();
	~bTree();

public:
	int m_iValue;			// ����� �ε���
	bTree* m_pChild[2];	// 2��Ʈ�� �ڽ� 2��
	int m_iDepth;			// ����
	bTree* m_pParent = nullptr;
};

bTree::bTree()
	
{
	m_pChild[0] = nullptr;
	m_pChild[1] = nullptr;
}
bTree::~bTree()
{
	//delete m_pChild[0];
	//delete m_pChild[1];
}
void CreateBST(bTree* _pParent, int _iData);
bTree* BinarySearchTree(bTree* _pParent, const int _iData);
void BTreeInsert(bTree* _pParent, const int _iData);
void BSTdelete(bTree* _pParent, int _iData);
bTree* BSTwhile(bTree* pNode, int _iData);



bTree* g_pRootNode = nullptr;
int g_iArray[10] = { 5,3,7,2,4,1,6,9,8,10 };

void CreateBST(bTree* _pParent, int _iData)
{
	// data�� ���� ��Ʈ���� ������ ����
	if (_pParent->m_iValue >= _iData)
	{
		if (_pParent->m_pChild[0] == nullptr)		// ���� �ڽĳ�尡 ���������
		{
			_pParent->m_pChild[0] = new bTree();
			_pParent->m_pChild[0]->m_iValue = _iData;
			_pParent->m_pChild[0]->m_iDepth = _pParent->m_iDepth + 1;
			_pParent->m_pChild[0]->m_pParent = _pParent;
		}
		else										// �ڽĳ�尡 �������������
		{
			CreateBST(_pParent->m_pChild[0], _iData);		// �� �ڽĳ���� �ڽĳ�带 �θ� ���� �Է��� �Լ��� ���ȣ���Ѵ�.
		}
	}
	// data�� ���� ��Ʈ���� ũ�� ������
	else
	{
		// ���� ������ �ڽĳ�尡 ���������
		if (_pParent->m_pChild[1] == nullptr)
		{
			_pParent->m_pChild[1] = new bTree();
			_pParent->m_pChild[1]->m_iValue = _iData;
			_pParent->m_pChild[1]->m_iDepth = _pParent->m_iDepth + 1;
			_pParent->m_pChild[1]->m_pParent = _pParent;
		}
		// ���� ������ �ڽĳ�尡 ���������
		else
		{
			CreateBST(_pParent->m_pChild[1], _iData);
		}
	}
}
bTree* BinarySearchTree(bTree* _pParent, const int _iData)
{
	// ���� ��尡 null �ΰ��� ã�°��� ���ٴ°Ͱ� ���ٴ°�
	if (_pParent == nullptr) return nullptr;
	if (_pParent->m_iValue == _iData) return _pParent;
	// ã�°��� ���� ��� ������ �۰ų� ������
	if (_pParent->m_iValue >= _iData)
	{
		BinarySearchTree(_pParent->m_pChild[0], _iData);
	}
	// ã�°��� ���� ��� ������ ũ��
	else
	{
		BinarySearchTree(_pParent->m_pChild[1], _iData);
	}
}
void BTreeInsert(bTree* _pParent, const int _iData)
{
	bTree* newNode = new bTree;
	newNode->m_iValue = _iData;
	while (_pParent != nullptr)
	{
		if (_pParent->m_iValue >= _iData)				// �����ҷ��� �����Ͱ� �θ� ��庸�� ������
		{
			if (_pParent->m_pChild[0] == nullptr)
			{
				_pParent->m_pChild[0] = newNode;
				newNode->m_pParent = _pParent;
				break;
			}
			else
				_pParent = _pParent->m_pChild[0];
		}
		else if (_pParent->m_iValue < _iData)
		{
			if (_pParent->m_pChild[1] == nullptr)
			{
				_pParent->m_pChild[1] = newNode;
				newNode->m_pParent = _pParent;
				break;
			}
			else
				_pParent = _pParent->m_pChild[1];
		}
	}
}
void BSTdelete(bTree* _pParent, int _iData)
{
	bTree* delNode = BSTwhile(_pParent, _iData);
	bTree* delpNode;
	bTree* cddNode, *cddpNode;
	if (delNode->m_pChild[1] == nullptr)		// ������ ����� ������ �ڽ��� ���� ���
	{
		delpNode = delNode->m_pParent;
		cddNode = delNode->m_pChild[0];
		if (cddNode->m_iValue > delpNode->m_iValue && delNode->m_pChild[0] != nullptr)
		{
			delpNode->m_pChild[1] = cddNode;		// ������ ����� �����ڽ��� ������� �θ����� �����ʿ��ٰ� ��ġ�Ѵ�.
			cddNode->m_pParent = delpNode;
			delete delNode;
		}
		else if (cddNode->m_iValue <= delpNode->m_iValue && delNode->m_pChild[0] != nullptr)
		{
			delpNode->m_pChild[0] = cddNode;
			cddNode->m_pParent = delpNode;
			delete delNode;									// ��������� ���� �ڽĵ� ���� ��� �׳� ��� ����
		}
		else
			delete delNode;
	}
	else if (delNode->m_pChild[0] == nullptr)		// ������ ����� ���� �ڽ��� ���� ���
	{
		delpNode = delNode->m_pParent;
		cddNode = delNode->m_pChild[1];
		if (delNode->m_pChild[0] == nullptr && delNode->m_pChild[1] != nullptr)
		{
			delpNode->m_pChild[1] = cddNode;
			cddNode->m_pParent = delpNode;
			delete delNode;
		}
		else
			delete delNode;
	}
	else														// ������ ����� ������ ���� �Ѵ� ������ 
	{
		delpNode = delNode->m_pParent;
		cddNode = delNode->m_pChild[1];
		while (cddNode->m_pChild[0]!=nullptr)
			cddNode = cddNode->m_pChild[0];
		
		cddpNode = cddNode->m_pParent;
		if (cddNode->m_pChild[1] != nullptr)					// ��������� ��ü ����� �����ʿ� ��尡 �������
		{
			cddpNode->m_pChild[0] = cddNode->m_pChild[1];
			cddNode->m_pChild[0]->m_pParent = cddpNode;
		}
		cddpNode->m_pChild[0] = nullptr;

		cddNode->m_pChild[0] = delNode->m_pChild[0];			// ������ ��ü��带 �ø���.
		cddNode->m_pChild[1] = delNode->m_pChild[1];

		if (delpNode == nullptr)
		{
			g_pRootNode = cddNode;
			delete delNode;
		}
		else if (delpNode->m_iValue < cddNode->m_iValue)
		{
			delpNode->m_pChild[1] = cddNode;
			delete delNode;
		}
		else if (delpNode->m_iValue >= cddNode->m_iValue)
		{
			delpNode->m_pChild[0] = cddNode;
			delete delNode;
		}
	}
}
bTree* BSTwhile(bTree* pNode, int _iData)
{
	while (pNode!=nullptr)
	{
		if (pNode->m_iValue == _iData)
			return pNode;
		else if (pNode->m_iValue >= _iData)
			pNode = pNode->m_pChild[0];
		else if (pNode->m_iValue < _iData)
			pNode = pNode->m_pChild[1];
	}
	return nullptr;
}
void CreateData()
{
	for (int i = 0; i < _countof(g_iArray); i++)
	{
		g_iArray[i] = 1+ (rand() % 20);
	}
}
void main()
{
	srand(time(NULL));
	//CreateData();
	// ��Ʈ����� ���� �̸� �Ҵ��Ѵ�.
	g_pRootNode = new bTree();
	g_pRootNode->m_iValue = g_iArray[0];
	for (int i = 1; i < _countof(g_iArray); i++)
	{
		CreateBST(g_pRootNode, g_iArray[i]);
	}
	//BTreeInsert(g_pRootNode, 7);
	BSTdelete(g_pRootNode, 5);
	int iFindData = rand() % _countof(g_iArray);
	//bTree* pFindData = BinarySearchTree(g_pRootNode, g_iArray[iFindData]);
	bTree* pFindData = BSTwhile(g_pRootNode, 23);
	if (pFindData != nullptr)
	{
		std::cout << g_iArray[iFindData] << std::endl;
	}
	else
	{
		return;
	}
	delete g_pRootNode;

}