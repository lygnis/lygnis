#pragma once
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
	int m_iIndex;			// ����� �ε���
	bTree* m_pChild[2];	// 2��Ʈ�� �ڽ� 2��
	int m_iDepth;			// ����
	bTree* m_pParent = nullptr;
};

bTree::bTree()
	: m_iIndex(-1), m_iDepth(0)
{
	for (int i = 0; i < 2; i++)
	{
		m_pChild[i] = nullptr;
	}
}
bTree::~bTree()
{
	for (int i = 0; i < 2; i++)
	{
		delete m_pChild[i];
	}
}


bTree* CreateNode(bTree* _pParent);
void BuildNode(bTree* pNode);
void Print(bTree* pNode);
void LevelOrderPrint(bTree* pNode);
void Swap(bTree* _aData, bTree* _bData);
void QuickSort(int* _pArray, int start, int end);