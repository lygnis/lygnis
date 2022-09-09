#include <iostream>
#include <queue>
// 자식노드 2개를 생성하고
// 루트 노드에 연결한다.
class bTree
{
public:
	bTree();
	~bTree();

public:
	int m_iValue;			// 노드의 인덱스
	bTree* m_pChild[2];	// 2진트리 자식 2개
	int m_iDepth;			// 깊이
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
	// data의 값이 루트보다 작으면 왼쪽
	if (_pParent->m_iValue >= _iData)
	{
		if (_pParent->m_pChild[0] == nullptr)		// 왼쪽 자식노드가 비어있으면
		{
			_pParent->m_pChild[0] = new bTree();
			_pParent->m_pChild[0]->m_iValue = _iData;
			_pParent->m_pChild[0]->m_iDepth = _pParent->m_iDepth + 1;
			_pParent->m_pChild[0]->m_pParent = _pParent;
		}
		else										// 자식노드가 비어있지않으면
		{
			CreateBST(_pParent->m_pChild[0], _iData);		// 그 자식노드의 자식노드를 부모 노드로 입력해 함수를 재귀호출한다.
		}
	}
	// data의 값이 루트보다 크면 오른쪽
	else
	{
		// 만약 오른쪽 자식노드가 비어있으면
		if (_pParent->m_pChild[1] == nullptr)
		{
			_pParent->m_pChild[1] = new bTree();
			_pParent->m_pChild[1]->m_iValue = _iData;
			_pParent->m_pChild[1]->m_iDepth = _pParent->m_iDepth + 1;
			_pParent->m_pChild[1]->m_pParent = _pParent;
		}
		// 만약 오른쪽 자식노드가 비어있으면
		else
		{
			CreateBST(_pParent->m_pChild[1], _iData);
		}
	}
}
bTree* BinarySearchTree(bTree* _pParent, const int _iData)
{
	// 들어온 노드가 null 인것은 찾는값이 없다는것과 같다는것
	if (_pParent == nullptr) return nullptr;
	if (_pParent->m_iValue == _iData) return _pParent;
	// 찾는값이 현재 노드 값보다 작거나 같으면
	if (_pParent->m_iValue >= _iData)
	{
		BinarySearchTree(_pParent->m_pChild[0], _iData);
	}
	// 찾는값이 현재 노드 값보다 크면
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
		if (_pParent->m_iValue >= _iData)				// 삽입할려는 데이터가 부모 노드보다 작을때
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
	if (delNode->m_pChild[1] == nullptr)		// 삭제할 노드의 오른쪽 자식이 없는 경우
	{
		delpNode = delNode->m_pParent;
		cddNode = delNode->m_pChild[0];
		if (cddNode->m_iValue > delpNode->m_iValue && delNode->m_pChild[0] != nullptr)
		{
			delpNode->m_pChild[1] = cddNode;		// 삭제한 노드의 왼쪽자식을 삭제노드 부모노드의 오른쪽에다가 배치한다.
			cddNode->m_pParent = delpNode;
			delete delNode;
		}
		else if (cddNode->m_iValue <= delpNode->m_iValue && delNode->m_pChild[0] != nullptr)
		{
			delpNode->m_pChild[0] = cddNode;
			cddNode->m_pParent = delpNode;
			delete delNode;									// 삭제노드의 왼쪽 자식도 없을 경우 그냥 노드 삭제
		}
		else
			delete delNode;
	}
	else if (delNode->m_pChild[0] == nullptr)		// 삭제할 노드의 왼쪽 자식이 없는 경우
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
	else														// 삭제할 노드의 오른쪽 왼쪽 둘다 있을때 
	{
		delpNode = delNode->m_pParent;
		cddNode = delNode->m_pChild[1];
		while (cddNode->m_pChild[0]!=nullptr)
			cddNode = cddNode->m_pChild[0];
		
		cddpNode = cddNode->m_pParent;
		if (cddNode->m_pChild[1] != nullptr)					// 삭제노드의 대체 노드의 오른쪽에 노드가 있을경우
		{
			cddpNode->m_pChild[0] = cddNode->m_pChild[1];
			cddNode->m_pChild[0]->m_pParent = cddpNode;
		}
		cddpNode->m_pChild[0] = nullptr;

		cddNode->m_pChild[0] = delNode->m_pChild[0];			// 없으면 대체노드를 올린다.
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
	// 루트노드의 값을 미리 할당한다.
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