#pragma once
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
	int m_iIndex;			// 노드의 인덱스
	bTree* m_pChild[2];	// 2진트리 자식 2개
	int m_iDepth;			// 깊이
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