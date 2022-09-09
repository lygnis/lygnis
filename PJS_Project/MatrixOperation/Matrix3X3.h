#pragma once
#include <math.h>
#include <iostream>
class Matrix3X3
{
public:
	float index[3][3];
	int iarray[5];
public:
	Matrix3X3() ;
	Matrix3X3(int _seed);		// 公累困 青纺积己
	Matrix3X3(float _a00, float _a01, float _a02,
			float _a10, float _a11, float _a12,
			float _a20, float _a21, float _a22);
	~Matrix3X3() {};
public:
	bool operator == (const Matrix3X3& _mat);
	Matrix3X3 operator+(const Matrix3X3& _mat);
	Matrix3X3 operator- (const Matrix3X3& _mat);
	Matrix3X3 operator*(const float _scalar);
public:
	Matrix3X3 MatOperator(const Matrix3X3 _matA, const Matrix3X3 _matB);
	Matrix3X3 TransPos(Matrix3X3 _mat);
};

