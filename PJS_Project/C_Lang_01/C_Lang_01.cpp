// C_Lang_01.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <stdio.h>

struct mySt
{
    int a;
    char b;
    char c;
    char d;
    short f;
    
}s;


int main()
{
    //ppPoint 라는 이중포인터 변수 선언
    int** ppPoint = 0;
    ppPoint = (int**)malloc(sizeof(intptr_t) * 3);
    

    for (int iCnt = 0; iCnt < 3; iCnt++)
    {
        ppPoint[iCnt] = (int*)malloc(sizeof(int) * 3);

    }
    for (int iCnt = 0; iCnt < 3; iCnt++)
    {
        for (int jCnt = 0; jCnt < 3; jCnt++)
        {
            ppPoint[iCnt][jCnt] = iCnt * 3 + jCnt;
            int a = ppPoint[iCnt][jCnt];

        }
    }
    for (int iCnt = 0; iCnt < 3; iCnt++)
    {
        printf("\n");
        for (int jCnt = 0; jCnt < 3; jCnt++)
        {
            printf("[%d,%d] =%d:%d",
                iCnt, jCnt,
                ppPoint[iCnt][jCnt],
                *(ppPoint[iCnt] + jCnt));
        }
    }
    for (int iCnt = 0; iCnt < 3; iCnt++)
    {
        free(ppPoint[iCnt]);
    }
    free(ppPoint);

    // -------------------------
    // 포인터 배열 변수 할당
    // -------------------------

    printf("\n===============\n");
    int* ipPoint[10];
    for (int iCnt = 0; iCnt < 10; iCnt++)
    {
        ipPoint[iCnt] = (int*)malloc(sizeof(int));
        *ipPoint[iCnt] = iCnt * 33;
        printf("\n0x%08X번지 : %d", ipPoint + iCnt, *ipPoint[iCnt]);
    }
    for (int i = 0; i < 10; i++)
    {
        free(ipPoint[i]);
    }
    printf("\n============\n");


    // ================================
    int _iData = sizeof(s);



    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
