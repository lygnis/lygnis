#include "bTree.h"


bTree* g_pRootNode = nullptr;
int g_iMaxDepth = 3;
int g_iCount = 0;
bTree* g_pArray[15];
int g_iArray[15] = { 5,67,2,1,34,9,10,26,84,25, 21,24,58,38,7 };

std::queue<bTree*> g_Queue;		// ť �ڷᱸ��
int g_iNum = 0;
int g_iNumb = 0;

void main()
{
	g_pRootNode = CreateNode(nullptr);
	
	BuildNode(g_pRootNode);
	g_pArray[0] = g_pRootNode;
	Print(g_pRootNode);
	std::cout << " " << std::endl;
	LevelOrderPrint(g_pRootNode);
	QuickSort(g_iArray, 0, 14);
	//ReBuild(g_pArray);
	delete g_pRootNode;

	
	//delete g_ppArray;
}

bTree* CreateNode(bTree* _pParent)
{
	bTree* NewNode = new bTree;
	NewNode->m_iIndex = g_iCount++;
	if (_pParent != nullptr)
	{
		NewNode->m_iDepth = _pParent->m_iDepth + 1;
	}
	//g_pArrayCp[g_iNum++] = NewNode;
	return NewNode;
}

// �ε����� �迭�� �ε����� �����Ѵ�.

void BuildNode(bTree* pNode)
{
	if (pNode->m_iDepth >= g_iMaxDepth)
	{
		//g_pArray[g_iNum++] = pNode;
		return;
	}
	pNode->m_pChild[0] = CreateNode(pNode);
	pNode->m_pChild[1] = CreateNode(pNode);

	BuildNode(pNode->m_pChild[0]);
	BuildNode(pNode->m_pChild[1]);

}

void Print(bTree* pNode)
{
	if (pNode == nullptr) return;
	Print(pNode->m_pChild[0]);
	Print(pNode->m_pChild[1]);
	std::cout << " " << pNode->m_iIndex;
}

void LevelOrderPrint(bTree* pNode)
{
	if (pNode == nullptr)
		return;
	std::cout << " " << pNode->m_iIndex;
	for (int i = 0; i < 2; i++)
	{
		if (pNode->m_pChild[i] != nullptr)
		{
			g_Queue.push(pNode->m_pChild[i]);		// ť ������ �ڽ�Ʈ�� 2���� �ִ´�.
		}
	}
	if (!g_Queue.empty())							// ���� ť ������ ������� ������
	{
		bTree* tNode =g_Queue.front();				// ���� Ʈ��, ���� Ʈ�� ������� ���ư���.
		g_pArray[++g_iNum] = tNode;
		//g_pArray[g_iNumb]->m_iIndex = g_iArray[g_iNumb++];
		g_Queue.pop();
		LevelOrderPrint(tNode);
	}
}

void QuickSort(int* _pArray, int start, int end)
{
	int iPivot, j, i;
	iPivot = start;
	i = iPivot + 1;
	j = end;
	int temp;
	// 
	if (start >= end)
		return;
	while (i<=j)
	{
		// i�� iPivot���� ū���� ã�´�.
		while (_pArray[iPivot] >= _pArray[i] && i <= end)
		{
			i++;
		}
		// j�� iPovot���� �������� ã�´�.
		while (_pArray[iPivot] <= _pArray[j] && j>start)
		{
			j--;
		}
		// j�� i ���� ������ pivot�� j�� ��ġ�� �ٲ۴�
		if (i > j)
		{
			temp = _pArray[iPivot];
			_pArray[iPivot] = _pArray[j];
			_pArray[j] = temp;
		}
		// 
		else
		{
			temp = _pArray[i];
			_pArray[i] = _pArray[j];
			_pArray[j] = temp;
		}
	}
	// �Ǻ��� �̵��� �� ����
	QuickSort(_pArray, start , j-1);
	// �Ǻ��� �̵��� �� ����
	QuickSort(_pArray, j+1, end);

}

void Swap(bTree* _aData, bTree* _bData)
{
	bTree* temp = _aData;
	_aData = _bData;
	_bData = temp;
}





