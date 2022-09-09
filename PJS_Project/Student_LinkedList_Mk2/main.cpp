#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>


// 전역변수를 사용해 구조체 한개로 노드를 연결해본다.
// 전역변수를 노드의 시작점 종착점으로 정의한다.
// 구조체(Data, 다음주소)

typedef struct stNode {
	char m_strName[6];
	int m_iage;
	int m_iKor;
	int m_iEng;
	int m_iMat;
	int m_iTotal;
	float m_fAverage;
	stNode* m_NextNode;

	// 현재 노드 앞주소
	stNode* m_PrevNode;

}stNode;

stNode* g_ptrHead;		// 노드 시작주소
stNode* g_ptrTail;		// 노드 종착주소
stNode* g_ptrNext;		// 임시 노드 그릇
int g_iCount;				// 노드 데이터 개수

// 1. 노드를 초기화한다.
void Init();

// 2. 노드안에 넣을 데이터를 만든다.
stNode* NewNode();

// 3. 만든 데이터를 원하는 수만큼 노드를 만들어 넣는다.
void InitData(int iCount);

// 4. 노드를 뒤쪽으로 정렬한다.
void PushBack(stNode* newNode);
void PushBack(stNode* newNode, stNode* _pLinkedList);



// 5. 만든데이터를 출력해본다.
void Print(stNode* _pList);

void PrintAll();

void AllFree();

// 특정 노드를 넘기면 삭제
void Erase(stNode* pNode);


void sort()
{

	// 1. 리스트에서 가장 작은 노드 검색
	// 2. 맨앞에 추가한다. 기존 데이터 이동
	// 3. 반복한다. 
	// 4. 추가노드의 pNext == g_ptail  
}

int main()
{
	srand(time(NULL));
	
	

		

	Init();
	
		
	InitData(5);
	
	PrintAll();
		



	

	AllFree();
	return 0;
}


// 메모리 초기화
void Init()
{
	g_ptrHead = (stNode*)malloc(sizeof(stNode));
	g_ptrTail = (stNode*)malloc(sizeof(stNode));
	memset(g_ptrHead, 0, sizeof(stNode));
	memset(g_ptrTail, 0, sizeof(stNode));
	
	g_ptrHead->m_NextNode = g_ptrTail;
	// 머리부분의 앞은 널	(꼬리면 원형)

	// 꼬리의 다음은 널	(다음이 머리면 원형)

	// 꼬리의 앞은 머리
	g_ptrNext = g_ptrHead;

}

// 노드 데이터 생성
stNode* NewNode()
{
	stNode* pNode = (stNode*)malloc(sizeof(stNode));
	memset(pNode, 0, sizeof(stNode));
	pNode->m_iage = g_iCount + 1;
	pNode->m_strName[0] = 65 + rand() % 26;
	pNode->m_strName[1] = 65 + rand() % 26;
	pNode->m_strName[2] = 65 + rand() % 26;
	pNode->m_strName[3] = 0;
	pNode->m_iKor = 0 + rand() % 101;
	pNode->m_iEng = 0 + rand() % 101;
	pNode->m_iMat = 0 + rand() % 101;
	pNode->m_iTotal = pNode->m_iKor +
		pNode->m_iEng +
		pNode->m_iMat;
	pNode->m_fAverage = pNode->m_iTotal / 3.0f;
	g_iCount++;
	return pNode;


}

void InitData(int iCount)
{
	for (int i = 0; i < iCount; i++)
	{
		PushBack(NewNode());
	}

}


void PushBack(stNode* newNode)
{
	g_ptrNext->m_NextNode = newNode;		// 저장해둔 빈 그릇 노드에는 헤드부분 노드가 있다.
	newNode->m_NextNode = g_ptrTail;		// 저장 그릇에 새로운 노드를 가리키게 하고 새로운 노드는 꼬리 노드를 가리킨다.

	// 꼬리를 연결해준다. 꼬리의 앞은 신규데이터
	g_ptrTail->m_PrevNode = newNode;
	// 신규데이터의 앞은 
	newNode->m_PrevNode = g_ptrNext;

	g_ptrNext = newNode;					// 저장노드에 새로운 노드 데이터를 넣는다.
										// 다음 노드가 오면 저장 그릇에는 이전 노드가 있어 새로운 노드의 주소는 이전노드가 가리킨다.


	// pPrev-> pLinknode => pPrev->pNewnode->pLinkNode


}

// 앞에다 넣기


void Print(stNode* _pList)
{
	printf("%s %d %d %d %d %d %10.4f \n",
		_pList->m_strName,
		_pList->m_iage,
		_pList->m_iKor,
		_pList->m_iEng,
		_pList->m_iMat,
		_pList->m_iTotal,
		_pList->m_fAverage);
	
}
void PrintAll() 
{
	for (stNode* pNode = g_ptrHead->m_NextNode; pNode->m_NextNode != NULL ;pNode = pNode->m_NextNode )
	{
		Print(pNode);
	}
}


void AllFree()
{
	stNode* pNode = g_ptrHead->m_NextNode;
	while (pNode!=g_ptrTail)
	{
		g_ptrNext = pNode->m_NextNode;
		free(pNode);
		pNode = g_ptrNext;
	}
}

void Erase(stNode* pNode)
{
	// pNode가 널이면 에러발생!
	// 시작점 종착점은 접근못하게 무조건 막는다.
	// 예외처리
	// 
	// 앞 뒤를 미리 temp 변수를 만들어 빼둔다.
	free(pNode);
	// 뺀 앞뒤를 서로 연결해준다.

}

// 앞으로 넣고 앞에서 뺀다. (스택)

