#pragma once
#include "Vector.h"
#include "TStd.h"
struct float3X3
{
	union
	{
		struct 
		{
			float _11, _12, _13;
			float _21, _22, _23;
			float _31, _32, _33;
		};
		float m[3][3];
	};
};
struct float4X4
{
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};
class MyMatrix3X3 : public float3X3
{
public:
	MyMatrix3X3();
	// 단위행렬
	void Identity();
	// 전치행렬
	MyMatrix3X3 Transpose();
	MyMatrix3X3 Rotation(float _fRadian);
	MyMatrix3X3 Scale(float _x, float _y);
	MyMatrix3X3 Translate(float _x, float _y);
public:
	MyMatrix3X3 operator *(MyMatrix3X3& _mat);
};


class MyMatrix4X4 : public float4X4
{
public:
	MyMatrix4X4();

	// 단위 (직교행렬) 생성
	void Identity();
	// 전치 행렬 생성
	MyMatrix4X4 Transpose();
	// 회전 어느 축으로 할지..
	MyMatrix4X4 RotationX(float _fRadian);
	MyMatrix4X4 RotationY(float _fRadian);
	MyMatrix4X4 RotationZ(float _fRadian);
	// 이동
	MyMatrix4X4 Translation(float _x, float _y, float _z);
	// 크기 조정
	MyMatrix4X4 Scale(float _x, float _y, float _z);
	void ObjectLookAt(Vector3D& _vPosition, Vector3D& _vTarget, Vector3D& _vUp);
	//MyMatrix4X4 ViewLookAt(Vector3D& _vPosition, Vector3D& _vTarget, Vector3D& _vUp);
	//MyMatrix4X4 PerspectiveFovLH(float _fNearplane, float _fFarPlane, float _fOvy, float _Aspect);
	MyMatrix4X4 OrthoLH(MyMatrix4X4& _mat, float _w, float _h, float _n, float _f);
	MyMatrix4X4 OrthoOffCenterLH(MyMatrix4X4& _mat, float _l, float _r, float _b, float _t, float _n, float _f);
public:
	MyMatrix4X4 operator*(MyMatrix4X4& _mat);
};
