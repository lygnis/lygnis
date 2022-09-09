#pragma once
#include <stdlib.h>


// 리스트 작성
// 1. 먼저 노드 데이터 구성 요소를 작성한다.
// 2. 리스트는 단방향으로 작성해서 데이터 안의 다음주소는 pNext로 설정



// 노드 구조체 데이터		이름, 나이, 과목, 총점, 평균	다음주소
typedef struct stuNode
{
	char m_strName[4];
	int i_age;
	int i_Kor;
	int i_Eng;
	int i_Mat;
	int i_total;
	float i_average;
	stuNode* ptNext;

}stNode;

typedef struct stLinkedList
{
	stNode* ptrHead;		// 시작 노드의 주소
	stNode* ptrTail;		// 마지막 노드의 주소
	int iCount;			// 현재 노드의 개수

}stLinkedList;

// 시작노드 초기화
void Init(stLinkedList* _pList);
// 데이터 생성
stNode* NewNode();

// 데이터 추가하기
void PushBack(stLinkedList* _pList, stNode* _NewData);

// 메모리 지우기
void ReleaseList(stLinkedList* _pList);

void Print(stNode* _pData);

void PrintAll(stLinkedList* _pList);

