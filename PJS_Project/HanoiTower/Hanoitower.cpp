#include <stdio.h>
#include "Hanoitower.h"


// 하노이 타워 만들기
// 1. 그릇이 3개 필요 (A, B, C)
// 2. 시작 그릇은 A로 설정 끝나는 그릇은 C 로설정
// 3. 위에 놓는 그릇은 아래보다 작아야 한다.


// if 3 A->C(1) A->B(2) C(1)-> B(2) A(3)->C B(1)->A B(2)-> C(2) A(1)->C(2) 3(7) #7번
// 
// if 4 A(1)->C(1)  A(2)->B(2)  C(1)->B(1,2) A(3,4)->C(3) B(1)->A(1,4) B(2)->C(2,3) 

// hanoi(n) 은 두번의 hanoi(n-1)재귀 과정을 수반한다.
// 한 번의 재귀 후 가장 큰 원반을 목적지로 옮기고 다시 마지막 재귀를 통해 나머지 n-1개의 원반을 목적지에 옮긴다.
// hanoi(n)은 세번의 과정으로 나눌 수 있다.

// 변수를 받는다. A. 출발지, B. 경유지 C. 도착지

// hanoi(3, 'A','C','B')	hanoi(n개 start to via) start에서 via를 거쳐 to 까지
// 1. hanoi(2,A,B,C) 3번 원반을 C로 옮기기 위해서는 먼저 위의 두 원반을 B로 옮겨야 한다.
// 2. 이후 3번 원반을 C로 옮긴다
// 3. hanoi(2,B,C,A) 3번을 C로 옮긴 후 B에 있는 두개의 원반을 V로 옮긴다. 이때 A를 경유한다.
// 4. n == 1일때 자신의 위에  원반이 없기 때문에 재귀가 필요없고 바로 원반을 옮기고 종료한다.	(재귀 함수의 탈출 조건 또는 기저사례)



int main()
{
	int iNum = 0;
	scanf_s("%d \n", &iNum);

	hanoi(iNum, 'A','C','B');		//개수 , 시작점 종착점 경유지


	return 0;
}

void hanoi(int n, char start, char to, char via)
{
	if (n == 1)
	{
		Move(1, start, to);
	}
	else
	{
		hanoi(n - 1, start, via, to);
		Move(n, start ,to);
		hanoi(n - 1, via, to, start);
	}

	
}

void Move(int n, char start, char to)
{
	printf("%d번 원반을%c에서 %c 로 이동 \n", n,start,to);
}


// 결론: 재귀함수식에서 일반항을 도출해본다.
// hanoi(n) = hanoi(n-1)*2 -1
// hanoi(n) = 2^n -1;
// 2의 지수식 도출