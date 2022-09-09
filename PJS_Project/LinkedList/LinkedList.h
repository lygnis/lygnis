#pragma once

typedef struct _tagNode
{
	// 노드안에는 저장하고자하는 데이터도 있어야하지만 다음노드의 주소도 필요
	int iData;			// int type 데이터
	struct _tagNode* pNextNode;		// 다음 노드

}tNode;




typedef struct _tagList
{
	//리스트 본인은 첫번째 노드만 알고있으면 된다.
	tNode* pHeadNode;		// 리스트는 첫노드의 주소를 알아야 된다.

	int iCount;			//data 기록 갯수


}tLinkedList;



// 연결형 리스트 초기화
void InitList(tLinkedList* _pList);

// 연결형 리스트 데이터 추가
void PushBack(tLinkedList* _pList, int _iData);

void PushFront(tLinkedList* _pList, int _iData);

// 연결형 리스트 메모리 해제
void ReleaseList(tLinkedList* _pList);


// 1. 리스트 초기화
// 2. 리스트 데이터 추가하기
// 3. 다 쓴 리스트 데이터 초기화 하기


