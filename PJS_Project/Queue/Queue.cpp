// Queue.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

// 원형 큐 이기 때문에 한바퀴를 돌아도 인덱스 값을 찾아야 한다.
// 그렇기 때문에 (현재 인덱스 +1)%(배열사이즈) == front 면 가득찬다
// 첫번째나 마지막은 처음에 비워둔다.


#include <iostream>
#define MAX 5
// 시작과 현재 인덱스 설정
int front;
int rear;
int iArr[MAX] = {};

void Init()     // 초기화
{
    front = rear = 0;
}
void ClearData()
{

}


void Enqueue(int iCount)      // 추가
{
    if ((rear+1)%MAX == front)             // rear+1이 배열의 끝이고 포화 상테가 아니라면 배열의 첫번째 인덱스를 증가시킨다.
        printf("stackOver");
    else
    {
        iArr[rear++] = iCount;
        rear = rear % MAX;
    }
}

void Dequeue()      // 삭제
{
    if (rear == front)
        printf("arr is Empty");
    else
    {
        iArr[front++] = 0;
        front = front % MAX;
    }
}

void ClearDatas()
{
    rear = front;
}




int main()
{
    Enqueue(3);
    Enqueue(2);
    Enqueue(1);
    Enqueue(5);
    Enqueue(4);

    Dequeue();
    Dequeue();
    Enqueue(4);
    Enqueue(2);
    ClearDatas();

    return 0;
}


