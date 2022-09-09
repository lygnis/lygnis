#include "Matrix3X3.h"


int main()
{
	Matrix3X3 A(1, 0, 75, 0, 1, 93, 0, 0, 1);
	Matrix3X3 B(0, -1, 0, 1, 0, 0, 0, 0, 1);
	Matrix3X3 C = A.MatOperator(A,B);
	return 0;
}