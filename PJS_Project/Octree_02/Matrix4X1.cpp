#include "Matrix4X1.h"

Matrix4X1::Matrix4X1()
{
	for (int i = 0; i <4; i++)
	{
		v[i] = 0;
	}
}

Matrix4X1::Matrix4X1(const Vector3D& _vec)
{
	a00 = _vec.x;
	a10 = _vec.y;
	a20 = _vec.z;
	a30 = 1;
}
