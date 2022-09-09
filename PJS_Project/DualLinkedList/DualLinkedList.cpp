// DualLinkedList.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include"DualLinkedList.h"
#include<crtdbg.h>

void stclear()
{
	system("cls");
	printf("===================================\n");
	printf("====   성적 관리 프로그램      ====\n");
	printf("===================================\n");
	printf("이름\t번호\t국어\t영어\t수학\t총점\t평균\n");
}

int main()
{
	int iNum = 0;
	Initi();
	srand(time(NULL));
	EnQueueBack(NewData());
	EnQueueBack(NewData());
	EnQueueBack(NewData());
	EnQueueBack(NewData());
	EnQueueBack(NewData());


	AllPrint();
	DeQueue();
	DeQueue();
	DeQueue();
	AllPrint();
	EnQueueBack(NewData());
	EnQueueBack(NewData());
	AllPrint();


	//while (true)
	//{
	//	printf("\n->[0:Create],[1:Print],[2:Find],[3:Del],[4:insert],[Quit:999]  : ");
	//	scanf_s("%d", &iNum);
	//	if (iNum == 999)
	//		break;
	//	stclear();

	//	switch (iNum)
	//	{
	//		case 0:
	//		{
	//			NewNode(3);
	//		}break;
	//		case 1:
	//		{
	//			sort();
	//			//AllPrint();
	//		}break;
	//		case 2:
	//		{
	//			AllPrint();
	//			//Find(2);
	//		}break;
	//		case 3:
	//		{
	//			// 삭제
	//			Delete(Find(3));
	//		}break;
	//		case 4:
	//		{
	//			// 삽입
	//			PushFront(NewData(), Find(2));
	//		}break;
	//	
	//	}
	//}

	clear();
	return 0;
}

void Initi()
{
    // 시작과 끝을 이어준다.
    // 빈공간에 시작을 받아둔다.
	g_ptrHead = (tStudent*)malloc(sizeof(tStudent));
	g_ptrTail = (tStudent*)malloc(sizeof(tStudent));
    g_ptrHead->m_ptrNext = g_ptrTail;
    g_ptrTail->m_ptrPrev = g_ptrHead;
	g_ptrRear = g_ptrHead;
	g_ptrFront = g_ptrHead;
}
tStudent* NewData()
{
    // 새로운 노드를 만든다(동적할당)
    tStudent* pNode = (tStudent*)malloc(sizeof(tStudent));
    // 데이터 생성
	pNode->m_iIndex = g_iIndexCount + 1;
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
	pNode->m_iAverage = pNode->m_iTotal / 3;
	return pNode;
}

void NewNode(int iCount)
{
	for (int i = 0; i < iCount; i++)
	{
		PushBack(NewData());
	}

}

// 뒤에서부터 정렬
void PushBack(tStudent* newNode)
{
	_ASSERT(newNode);
	//head- > data -> tail => data -> newnod-> tail
	tStudent* tNode = g_ptrTail->m_ptrPrev;		// 빈그릇이 종착 전 주소를 가르킨다.
	g_ptrTail->m_ptrPrev = newNode;			// 종착 앞에 새로운 데이터를 넣는다

	newNode->m_ptrPrev = tNode;				// 새로운데이터의 앞에 빈그릇을 둔다.
	tNode->m_ptrNext = newNode;				// 빈그릇의 다음에 새노드를 배치한다.

	newNode->m_ptrNext = g_ptrTail;			// 새로운노드 뒤에 종착점
	
	g_iIndexCount++;
}
void PushBack(tStudent* newNode, tStudent* tLinkNode)
{
	_ASSERT(tLinkNode);
	if (tLinkNode == NULL)
	{
		PushBack(newNode);
	}
	else 
	{	// tlink->pPrev => tlink-> newNode-> pPrev
		tStudent* pPrev = tLinkNode->m_ptrNext;			//tlink 다음 노드 주소를 받는다
		newNode->m_ptrNext = pPrev;					//새로운 노드 다음에 pPrev를 둔다.
		tLinkNode->m_ptrNext = newNode;
		pPrev->m_ptrPrev = newNode;
		newNode->m_ptrPrev = tLinkNode;

		g_iIndexCount++;
	}
}

void PushFront(tStudent* newNode)
{
	// head ->data ->tail => head-> newNode-> data
	tStudent* pNode = g_ptrHead->m_ptrNext;		// 빈그릇에 시작다음부분 주소
	g_ptrHead->m_ptrNext = newNode;			// 시작다음에 새로운노드

	newNode->m_ptrNext = pNode;				// 새로운노드 다음에 전 데이터
	pNode->m_ptrPrev = newNode;
	
	newNode->m_ptrPrev = g_ptrHead;
	g_iIndexCount++;
}

void StackFrontPush(tStudent* newNode)
{
	g_ptrNext = g_ptrHead->m_ptrNext;
	g_ptrHead->m_ptrNext = newNode;
	newNode->m_ptrNext = g_ptrNext;
	g_iIndexCount++;
	front = newNode;

}

void StackPop()
{
	if (g_ptrHead->m_ptrNext ==nullptr)
	{
		printf("Node is Empty\n");
	}
	else
	{
		tStudent* tNode = front->m_ptrNext;
		g_ptrHead->m_ptrNext = tNode;
		free(front);
		front = tNode;
	}
}

void EnQueueBack(tStudent* newNode)
{
	g_ptrRear->m_ptrNext = newNode;
	newNode->m_ptrNext = nullptr;
	g_ptrRear = newNode;
	g_iIndexCount++;
}

void DeQueue()
{
	g_ptrFront = g_ptrHead->m_ptrNext;
	tStudent* pNode = g_ptrFront->m_ptrNext;
	if (g_ptrFront->m_ptrNext == nullptr)
	{
		printf("No Queue\n");
	}
	g_ptrHead->m_ptrNext = pNode;
	free(g_ptrFront);
	g_ptrFront = g_ptrHead->m_ptrNext;
}

void PushFront(tStudent* newNode, tStudent* tLinkNode)
{
	if (tLinkNode == NULL)
	{
		PushFront(NewData());
	}
	else
	{	// pPrev->pLinkNode => pPrev->pNewNode->pLinkNode
		tStudent* pNode = tLinkNode->m_ptrPrev;
		pNode->m_ptrNext = newNode;
		tLinkNode->m_ptrPrev = newNode;
		newNode->m_ptrNext = tLinkNode;
		newNode->m_ptrPrev = pNode;
		g_iIndexCount++;
	}
}

void clear()
{
	tStudent* pNode = g_ptrHead->m_ptrNext;
	while (pNode != g_ptrTail)
	{	
		tStudent* pNext = pNode->m_ptrNext;
		free(pNode);
		pNode = pNext;
	}
	free(g_ptrHead);
	free(g_ptrTail);
}

void Print(tStudent* pNode)
{
	printf("%s\t%d\t%d\t%d\t%d\t%d\t%-6.2f\n",
		pNode->m_strName,
		pNode->m_iIndex,
		pNode->m_iKor,
		pNode->m_iEng,
		pNode->m_iMat,
		pNode->m_iTotal,
		pNode->m_iAverage);

}
void AllPrint()
{
	for (tStudent* iNode = g_ptrHead->m_ptrNext;
		 iNode!=nullptr;
		iNode = iNode->m_ptrNext)
	{
		Print(iNode);
	}
}

tStudent* Find(int iCount)
{
	tStudent* fNode = g_ptrHead->m_ptrNext;
	while (fNode->m_iIndex !=iCount)
	{
		fNode = fNode->m_ptrNext;
	}
	Print(fNode);
	return fNode;
}
void Delete(tStudent* dNode)
{
	tStudent* dPrev = dNode->m_ptrPrev;
	tStudent* dNext = dNode->m_ptrNext;
	free(dNode);
	dNode = nullptr;
	dPrev->m_ptrNext = dNext;
	dNext->m_ptrPrev = dPrev;
}

void sort()
{
	// 성적이 가장 작은 노드를 찾는다.
	tStudent* pNode = g_ptrHead->m_ptrNext;			// 시작 다음 노드를 피봇 노드로 설정
	tStudent** arrNode = (tStudent**)malloc(sizeof(tStudent*) * g_iIndexCount);		// 노드 포인터를 보관할 포인터배열을 생성
	tStudent** arrNodeCp = arrNode;
	for (pNode;									// 포인터 배열이기 때문에 이중포인터로 접근한다.
		pNode != g_ptrTail;
		pNode = pNode->m_ptrNext)
	{
		*arrNodeCp++ = pNode;
	}
	int least = 0;
	tStudent* temp;
	for (int i = 0; i < g_iIndexCount-1; i++)		// 마지막 값은 정렬 할 필요가 없다.
	{
		least = i;
		for (int j = i+1; j < g_iIndexCount; j++)	// 정렬한 인덱스에서 한칸 증가
		{
			// 최솟값을 찾는다.
			if (arrNode[j]->m_iAverage > arrNode[least]->m_iAverage)		// [0] 을 반보해서 확인한다.
			{
				least = j;
			}
		}
		if (i != least)			// 최솟값이 같으면 옮길 필요가 없다.
		{
			temp = arrNode[i];
			arrNode[i] = arrNode[least];
			arrNode[least] = temp;
		}
	}
	for (int i = 0; i < g_iIndexCount; i++)
	{
		Print(arrNode[i]);
	}
	free(arrNode);
}