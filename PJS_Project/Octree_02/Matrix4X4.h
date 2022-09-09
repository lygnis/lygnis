#pragma once
#include "Vector3D.h"
#include "Matrix4X1.h"
struct Matrix
{
	union
	{
		struct
		{
			float a00; float a01; float a02; float a03;
			float a10; float a11; float a12; float a13;
			float a20; float a21; float a22; float a23;
			float a30; float a31; float a32; float a33;

		};
		float v[4][4];
	};
};

class Matrix4X4 :public Matrix
{
public:
	Matrix4X4();
	Matrix4X4(float _a00, float _a01, float _a02, float _a03,
			float _a10, float _a11, float _a12, float _a13,
			float _a20, float _a21, float _a22, float _a23,
			float _a30, float _a31, float _a32, float _a33);
	Matrix4X4(const Vector3D& _vec);
	~Matrix4X4() {};
public:
	Matrix4X1 Product4X1(const Matrix4X1& _mat);
};

