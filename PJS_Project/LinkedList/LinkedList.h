#pragma once

typedef struct _tagNode
{
	// ���ȿ��� �����ϰ����ϴ� �����͵� �־�������� ��������� �ּҵ� �ʿ�
	int iData;			// int type ������
	struct _tagNode* pNextNode;		// ���� ���

}tNode;




typedef struct _tagList
{
	//����Ʈ ������ ù��° ��常 �˰������� �ȴ�.
	tNode* pHeadNode;		// ����Ʈ�� ù����� �ּҸ� �˾ƾ� �ȴ�.

	int iCount;			//data ��� ����


}tLinkedList;



// ������ ����Ʈ �ʱ�ȭ
void InitList(tLinkedList* _pList);

// ������ ����Ʈ ������ �߰�
void PushBack(tLinkedList* _pList, int _iData);

void PushFront(tLinkedList* _pList, int _iData);

// ������ ����Ʈ �޸� ����
void ReleaseList(tLinkedList* _pList);


// 1. ����Ʈ �ʱ�ȭ
// 2. ����Ʈ ������ �߰��ϱ�
// 3. �� �� ����Ʈ ������ �ʱ�ȭ �ϱ�


