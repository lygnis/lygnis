#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>


// ���������� ����� ����ü �Ѱ��� ��带 �����غ���.
// ���������� ����� ������ ���������� �����Ѵ�.
// ����ü(Data, �����ּ�)

typedef struct stNode {
	char m_strName[6];
	int m_iage;
	int m_iKor;
	int m_iEng;
	int m_iMat;
	int m_iTotal;
	float m_fAverage;
	stNode* m_NextNode;

	// ���� ��� ���ּ�
	stNode* m_PrevNode;

}stNode;

stNode* g_ptrHead;		// ��� �����ּ�
stNode* g_ptrTail;		// ��� �����ּ�
stNode* g_ptrNext;		// �ӽ� ��� �׸�
int g_iCount;				// ��� ������ ����

// 1. ��带 �ʱ�ȭ�Ѵ�.
void Init();

// 2. ���ȿ� ���� �����͸� �����.
stNode* NewNode();

// 3. ���� �����͸� ���ϴ� ����ŭ ��带 ����� �ִ´�.
void InitData(int iCount);

// 4. ��带 �������� �����Ѵ�.
void PushBack(stNode* newNode);
void PushBack(stNode* newNode, stNode* _pLinkedList);



// 5. ���絥���͸� ����غ���.
void Print(stNode* _pList);

void PrintAll();

void AllFree();

// Ư�� ��带 �ѱ�� ����
void Erase(stNode* pNode);


void sort()
{

	// 1. ����Ʈ���� ���� ���� ��� �˻�
	// 2. �Ǿտ� �߰��Ѵ�. ���� ������ �̵�
	// 3. �ݺ��Ѵ�. 
	// 4. �߰������ pNext == g_ptail  
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


// �޸� �ʱ�ȭ
void Init()
{
	g_ptrHead = (stNode*)malloc(sizeof(stNode));
	g_ptrTail = (stNode*)malloc(sizeof(stNode));
	memset(g_ptrHead, 0, sizeof(stNode));
	memset(g_ptrTail, 0, sizeof(stNode));
	
	g_ptrHead->m_NextNode = g_ptrTail;
	// �Ӹ��κ��� ���� ��	(������ ����)

	// ������ ������ ��	(������ �Ӹ��� ����)

	// ������ ���� �Ӹ�
	g_ptrNext = g_ptrHead;

}

// ��� ������ ����
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
	g_ptrNext->m_NextNode = newNode;		// �����ص� �� �׸� ��忡�� ���κ� ��尡 �ִ�.
	newNode->m_NextNode = g_ptrTail;		// ���� �׸��� ���ο� ��带 ����Ű�� �ϰ� ���ο� ���� ���� ��带 ����Ų��.

	// ������ �������ش�. ������ ���� �űԵ�����
	g_ptrTail->m_PrevNode = newNode;
	// �űԵ������� ���� 
	newNode->m_PrevNode = g_ptrNext;

	g_ptrNext = newNode;					// �����忡 ���ο� ��� �����͸� �ִ´�.
										// ���� ��尡 ���� ���� �׸����� ���� ��尡 �־� ���ο� ����� �ּҴ� ������尡 ����Ų��.


	// pPrev-> pLinknode => pPrev->pNewnode->pLinkNode


}

// �տ��� �ֱ�


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
	// pNode�� ���̸� �����߻�!
	// ������ �������� ���ٸ��ϰ� ������ ���´�.
	// ����ó��
	// 
	// �� �ڸ� �̸� temp ������ ����� ���д�.
	free(pNode);
	// �� �յڸ� ���� �������ش�.

}

// ������ �ְ� �տ��� ����. (����)

