#pragma once

typedef struct _Node {
	char m_name[4];
	int m_index;
	_Node* m_Next;
	
}tNode;


tNode* g_ptrHead = NULL;
tNode* g_ptrNext = NULL;
int g_iCount = 1;

void InitData();
void Connect(tNode* newNode);
tNode* NewNode();
tNode* DieNode(tNode* dNode);
void erase(int count);