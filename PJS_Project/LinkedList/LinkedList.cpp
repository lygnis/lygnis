// LinkedList.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "LinkedList.h"



void InitList(tLinkedList* _pList)
{
    _pList->pHeadNode = nullptr;
    _pList->iCount = 0;
}


void PushBack(tLinkedList* _pList, int _iData)
{
    // 데이터를 저장할 노드 생성
    // 데이터 복사
    tNode* pNode = (tNode*)malloc(sizeof(tNode));

    pNode->iData = _iData;
    pNode->pNextNode = nullptr;     // pushBack 은 맨마지막 노드기 때문에 다음을 가리킬 곳이 없다.

    // 추가한 데이터가 처음인지 아닌지
    if (_pList->iCount == 0)
    {
        _pList->pHeadNode = pNode;
    }
    else
    {
        // 현재 가장 마지막 노드를 찾아서
        // 해당 노드의 pNext 를 생성시킨 지금노드의 주소로 채움

        tNode* pCurFinalNode = _pList->pHeadNode;
        while (pCurFinalNode->pNextNode != nullptr)
        {
            
            pCurFinalNode = pCurFinalNode->pNextNode;
        }
        pCurFinalNode->pNextNode = pNode;
    }
    ++_pList->iCount;
}

void ReleaseList(tLinkedList* _pList)
{
    // 메모리를 지우기전에 다음 노드의 주소를 받는다.
    tNode* pDeletNode = _pList->pHeadNode;
    
    while (pDeletNode !=nullptr)
    {
        tNode* pNext = pDeletNode->pNextNode;
        free(pDeletNode); 
        pDeletNode = pNext;
    }
}

// pushfront 함수 만들어보디

