#include "Vector3D.h"




int main()
{
	Vector3D A(5, -2, 0);
	Vector3D B(1, 2, 3);
	Vector3D C = A.OuterProduct(B);
	C.m_fLength = C.GetLength(C.x, C.y, C.z);
	float angle = A.BetweenAngelVec(B);
	Vector3D re = C.Nomalized(C);
	return 0;
}