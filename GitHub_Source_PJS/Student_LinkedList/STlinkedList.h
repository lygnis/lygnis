#pragma once
#include <stdlib.h>


// ����Ʈ �ۼ�
// 1. ���� ��� ������ ���� ��Ҹ� �ۼ��Ѵ�.
// 2. ����Ʈ�� �ܹ������� �ۼ��ؼ� ������ ���� �����ּҴ� pNext�� ����



// ��� ����ü ������		�̸�, ����, ����, ����, ���	�����ּ�
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
	stNode* ptrHead;		// ���� ����� �ּ�
	stNode* ptrTail;		// ������ ����� �ּ�
	int iCount;			// ���� ����� ����

}stLinkedList;

// ���۳�� �ʱ�ȭ
void Init(stLinkedList* _pList);
// ������ ����
stNode* NewNode();

// ������ �߰��ϱ�
void PushBack(stLinkedList* _pList, stNode* _NewData);

// �޸� �����
void ReleaseList(stLinkedList* _pList);

void Print(stNode* _pData);

void PrintAll(stLinkedList* _pList);

