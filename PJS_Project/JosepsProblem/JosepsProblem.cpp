// JosepsProblem.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "JosepsProblem.h"
#include <time.h>

int main()
{
    srand(time(NULL));
    InitData();
    Connect(NewNode());
    Connect(NewNode());
    Connect(NewNode());
    Connect(NewNode());
    Connect(NewNode());
    Connect(NewNode());


    erase(3);
    return 0;
}

void InitData()
{
    g_ptrHead = (tNode*)malloc(sizeof(tNode));
    memset(g_ptrHead, 0, (sizeof(tNode)));
    g_ptrHead->m_name[0] = 65 + rand() % 26;
    g_ptrHead->m_name[1] = 65 + rand() % 26;
    g_ptrHead->m_name[2] = 65 + rand() % 26;
    g_ptrHead->m_name[3] = 0;
    g_ptrHead->m_index = g_iCount;
    g_ptrNext = g_ptrHead;
    g_iCount++;
}
tNode* NewNode()
{
    tNode* pNode = (tNode*)malloc(sizeof(tNode));
    pNode->m_name[0] = 65 + rand() % 26;
    pNode->m_name[1] = 65 + rand() % 26;
    pNode->m_name[2] = 65 + rand() % 26;
    pNode->m_name[3] = 0;
    pNode->m_index = g_iCount;
    g_iCount++;
    return pNode;
}
void Connect(tNode* newNode)
{
    
    g_ptrNext->m_Next = newNode;
    newNode->m_Next = g_ptrHead;
    g_ptrNext = newNode;
    
}
void erase(int count)
{
    tNode* dNode = g_ptrHead;
    while (dNode->m_Next != dNode)
    {
        // 1 2 3 4 5 6 7 점프 3번
        // 3x 6x 기준으로 점프 n번이면 n-1칸 이동

        for (int i = 0; i < count-1; i++)
        {
            dNode = dNode->m_Next;
        }
        printf("%d 번이 죽었습니다 %s\n",dNode->m_index, dNode->m_name);
        dNode = DieNode(dNode);     // 죽은 노드 다음노드를 받는다
        
    }
    printf("%s 가 살아남았습니다. %d번 \n", dNode->m_name, dNode->m_index);

}
tNode* DieNode(tNode* dNode)
{
    tNode* prevNode = g_ptrHead;
    while (prevNode->m_Next !=dNode)
    {
        prevNode = prevNode->m_Next;
    }
    prevNode->m_Next = dNode->m_Next;
    free(dNode);
    return prevNode->m_Next;
}

// 요셉의 문제
// 1. 기준을 잡는다 (g_ptrHead)
// 2. 숫자를 입력받아 입력받은 숫자만큼 사람을 추가한다 (총인원은 n+1)
// 3. 마지막 사람은 다음번이 기준이다.
