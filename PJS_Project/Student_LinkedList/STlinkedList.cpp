#include "STlinkedList.h"
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdio.h>

void Init(stLinkedList* _pList)
{
	_pList->ptrHead = nullptr;
	_pList->ptrTail = (stNode*)malloc(sizeof(stNode));
	_pList->iCount = 0;
}

void PushBack(stLinkedList* _pList, stNode* _NewData)
{
	stNode* pNode = (stNode*)malloc(sizeof(stNode));
	pNode = _NewData;		// 노드 생성
	pNode->ptNext = _pList->ptrTail;
	if (_pList->iCount == 0)
	{
		_pList->ptrHead = pNode;
	}
	// 가장 마지막 노드를 찾는다.
	else
	{
		stNode* stFinalNode = _pList->ptrHead;
		while (stFinalNode->ptNext != _pList->ptrTail)
		{
			stFinalNode = stFinalNode->ptNext;
		}
		stFinalNode->ptNext = pNode;
	}
	_pList->iCount++;


}

void ReleaseList(stLinkedList* _pList)
{
	// 메모리 지우기
	stNode* p_DeleteNode = _pList->ptrHead;
	while (p_DeleteNode!=_pList->ptrTail)
	{
		// 다음 노드 주소 미리 복사
		stNode* p_Next = p_DeleteNode->ptNext;
		free(p_DeleteNode);
		p_DeleteNode = p_Next;
	}
	free(_pList->ptrTail);
}

void Print(stNode* _pData)
{
	printf("%s %d %d %d %d %d %10.4f \n",
		_pData->m_strName,
		_pData->i_age,
		_pData->i_Kor,
		_pData->i_Eng,
		_pData->i_Mat,
		_pData->i_total,
		_pData->i_average);
}

void PrintAll(stLinkedList* _pList)
{
	for (stNode* p_NodeData = _pList->ptrHead;
		p_NodeData != _pList->ptrTail;
		p_NodeData = p_NodeData->ptNext)
	{
		Print(p_NodeData);
	}
}


stNode* NewNode()
{
	
	stNode* pNode = (stNode*)malloc(sizeof(stNode));
	memset(pNode, 0, sizeof(stNode));
	pNode->m_strName[0] = 65 + rand() % 26;
	pNode->m_strName[1] = 65 + rand() % 26;
	pNode->m_strName[2] = 65 + rand() % 26;
	pNode->m_strName[3] = 0;
	pNode->i_Kor = 0 + rand() % 101;
	pNode->i_Eng = 0 + rand() % 101;
	pNode->i_Mat = 0 + rand() % 101;
	pNode->i_total = pNode->i_Kor + pNode->i_Eng + pNode->i_Mat;
	pNode->i_average = pNode->i_total/3.0f;

	return pNode;
}