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
	//*a = &dataA;				// const�� �ڷ��� ���ʿ� ������ ����ġ�� ���� ������ ���ȭ���ȴ� ������ �� ���� �Ұ���

	int* const b = &dataA;
	//b = &dataB;
	*b = dataA;					// ������ ������ �����ʿ� ������ ������ ������ ���ȭ�� �ȴ� ������ �� ���� ����
	const int* const a1 = &dataA;	// ������ ������ ���̶� �Ѵ� ���ȭ
	//a1 = &dataB;
	//*a1 = dataA;

	TRegion p1(0, 0), p2, p3, p4;
	p2 = p1++;
	p3 = ++p1;
	




	return 0;
}