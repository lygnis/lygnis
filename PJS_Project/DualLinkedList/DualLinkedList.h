#pragma once

// 노드 정의
typedef struct tStudent {
	char m_strName[6];
	int m_iIndex;
	int m_iKor;
	int m_iEng;
	int m_iMat;
	int m_iTotal;
	float m_iAverage;

	tStudent* m_ptrNext;
	tStudent* m_ptrPrev;
}tStudent;

int g_iIndexCount;
tStudent* g_ptrHead = NULL;
tStudent* g_ptrTail = NULL;
tStudent* g_ptrNext = NULL;

tStudent* front = NULL;

tStudent* g_ptrFront;
tStudent* g_ptrRear;
void stclear();


void Initi();

tStudent* NewData();


void PushBack(tStudent* newNode);

void PushBack(tStudent* newNode, tStudent* tLinkNode);
void PushFront(tStudent* newNode, tStudent* tLinkNode);
void NewNode(int iCount);
void clear();

void Print(tStudent* pNode);
void AllPrint();
tStudent* Find(int iCount);
void Delete(tStudent* dNode);
void sort();

void StackFrontPush(tStudent* newNode);
void StackPop();

void EnQueueBack(tStudent* newNode);
void DeQueue();