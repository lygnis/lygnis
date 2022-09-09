#include "Matrix4X4.h"

Matrix4X4::Matrix4X4()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			v[i][j] = 0;
		}
	}
}

Matrix4X4::Matrix4X4(float _a00, float _a01, float _a02, float _a03, float _a10, float _a11, float _a12, float _a13, float _a20, float _a21, float _a22, float _a23, float _a30, float _a31, float _a32, float _a33)
{
	v[0][0] = _a00;	v[0][1] = _a01;	v[0][2] = _a02;	v[0][3] = _a03;
	v[1][0] = _a10;	v[1][1] = _a11;	v[1][2] = _a12;	v[1][3] = _a13;
	v[2][0] = _a20;	v[2][1] = _a21;	v[2][2] = _a22;	v[2][3] = _a23;
	v[3][0] = _a30;	v[3][1] = _a31;	v[3][2] = _a32;	v[3][3] = _a33;
}

Matrix4X4::Matrix4X4(const Vector3D& _vec)
{
	v[0][0] = 1;	v[0][1] = 0;	v[0][2] = 0;	v[0][3] = _vec.x;
	v[1][0] = 0;	v[1][1] = 1;	v[1][2] = 0;	v[1][3] = _vec.y;
	v[2][0] = 0;	v[2][1] = 0;	v[2][2] = 1;	v[2][3] = _vec.z;
	v[3][0] = 0;	v[3][1] = 0;	v[3][2] = 0;	v[3][3] = 1;
}

Matrix4X1 Matrix4X4::Product4X1(const Matrix4X1& _mat)
{
	Matrix4X1 temp;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp.v[i] = temp.v[i]+ (this->v[i][j] * _mat.v[j]);
		}
	}
	return temp;
}
