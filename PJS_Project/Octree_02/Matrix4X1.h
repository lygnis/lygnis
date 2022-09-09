#pragma once
#include "Vector3D.h"

struct vecMat
{
	union
	{
		struct
		{
			float a00;
			float a10;
			float a20;
			float a30;
		};
		float v[4];
	};
};

class Matrix4X1 : public vecMat
{
public:
	Matrix4X1();
	Matrix4X1(const Vector3D& _vec);
	~Matrix4X1() {};
};

