#include"TRegion.h"

// Const
int dataA = 1;
int dataB = 2;
int dataC = 3;
int dataD = 4;



int main()
{
	const int* a = &dataA;
	a = &dataB;
	//*a = &dataA;				// const가 자료형 왼쪽에 있으면 가르치는 곳의 변수가 상수화가된다 역참조 값 수정 불가능

	int* const b = &dataA;
	//b = &dataB;
	*b = dataA;					// 포인터 연산자 오른쪽에 있으면 포인터 변수가 상수화가 된다 역참조 값 수정 가능
	const int* const a1 = &dataA;	// 포인터 변수랑 값이랑 둘다 상수화
	//a1 = &dataB;
	//*a1 = dataA;

	TRegion p1(0, 0), p2, p3, p4;
	p2 = p1++;
	p3 = ++p1;
	




	return 0;
}