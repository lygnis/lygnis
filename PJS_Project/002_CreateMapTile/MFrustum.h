#pragma once
#include "MActor.h"
struct Plane
{
	// ��� ������
	float a, b, c, d;
	void Create(TBASIS_EX::TVector3 v0, TBASIS_EX::TVector3 v1, TBASIS_EX::TVector3 v2)
	{
		// ������ �μ��� �����.
		TBASIS_EX::TVector3 vE0 = v1 - v0;
		TBASIS_EX::TVector3 vE1 = v2 - v0;
		TBASIS_EX::TVector3 vNormal = vE0.Cross(vE1);
		vNormal.Normalize();
		a = vNormal.x;
		b = vNormal.y;
		c = vNormal.z;
		d = -(vNormal.Dot(v0));
	}
	void Create(TBASIS_EX::TVector3 _normal, TBASIS_EX::TVector3 v0)
	{
		_normal.Normalize();
		a = _normal.x;
		b = _normal.y;
		c = _normal.z;
		d = -(_normal.Dot(v0));
	}
};
class MFrustum
{
	// ���������� ī�޶� ���� ���������. (ī�޶� �������� ����� ���� �ִ�.)
	TMatrix m_matView;
	TMatrix m_matProj;
public:
	TBASIS_EX::TVector3 m_vFrustum[8];
	Plane m_Plane[6];
public:
	void CreateFrustum(TMatrix* _matView, TMatrix* _matProj);
	bool ClassifyPoint(TVector3 _v);
};

