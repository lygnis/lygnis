// Stack.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <stdio.h>
#define MAX 5
int top = 0;
int size[MAX] = {};

void Init()
{
    top = -1;
}
void pop()
{
    // 빼기
    if (top < 0)
        printf("StackUnder");
    else
    {
        size[top--] = 0;
        
    }
}
void push(int iCount)
{
    // 추가하기
    if (top >= MAX)
        printf("StackOver\n");
    else
    {
        size[++top] = iCount;
    }
}


int main()
{
    Init();
    push(2);
    push(3);
    push(1);
    push(5);
    push(7);
    push(1);
    push(8);
    push(9);
    push(4);

    pop();
    pop();
    pop();
    Init();
    push(8);
    push(9);
    push(4);
    push(5);
    push(7);
    push(1);
    pop();
    pop();
    push(7);
    push(1);
    return 0;
}
