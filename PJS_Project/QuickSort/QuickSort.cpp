



#include <iostream>
#include "QuickSort.h"


int main()
{
    int iArr[15] = { 5,67,2,1,34,9,10,26,84,25, 21,24,58,38,7 };

    PrintData(iArr);
    QuickSort(iArr, 0, 14);
    PrintData(iArr);
    
}

void PrintData(int arr[])
{
    for (int i = 0; i < 14; i++)
    {
        std::cout << arr[i]<<" ";
    }
    std::cout << " " << std::endl;
}

void QuickSort(int* data,int start, int end)
{
    // 각 인덱스 위치 초기화
    int iPivot, i, j;
    iPivot = start;
    i = iPivot + 1;         // 왼쪽 출발지점
    j = end;               // 오른쪽 출발지점
    int temp;
    if (start >= end)
        return;
    // i가 iPivot보다 큰값을 찾는다.
    // j가 iPovot보다 작은값을 찾는다.
    while (i<=j)
    {
        while (data[i]<=data[iPivot]&&i<=end)
        {
            i++;
        }
        while (data[j]>=data[iPivot]&&j>start)
        {
            j--;
        }
        if (i > j)
        {
            Swap(&data[j], &data[iPivot]);
        }
        else
        {
            Swap(&data[i], &data[j]);
        }
    }

    PrintData(data);
    QuickSort(data, start, j - 1);      // 피봇이 이동한 후 좌측
    QuickSort(data, j + 1, end);        // 피봇이 이동한 후 우측
}
void Swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
