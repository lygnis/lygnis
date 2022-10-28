#include "MFrustum.h"

void MFrustum::CreateFrustum(TMatrix* _matView, TMatrix* _matProj)
{
	TBASIS_EX::TMatrix view = *(TBASIS_EX::TMatrix*)_matView;
	TBASIS_EX::TMatrix proj = *(TBASIS_EX::TMatrix*)_matProj;
	// ������� ����İ� ��������� ������� ���� �����ش�.
	TBASIS_EX::TMatrix matInvViewProj = view * proj;
	TBASIS_EX::D3DXMatrixInverse(&matInvViewProj, NULL, &matInvViewProj);
	// m_vFrustum = v * world * (view * proj);
	// m_vFrustum = v * world * view*invView * proj * invproj;
	// m_vFrustum /= v.w     x,y= -1~+1,   z= 0~1;
	m_vFrustum[0] = TBASIS_EX::TVector3(-1.0f, -1.0f, 0.0f);
	m_vFrustum[1] = TBASIS_EX::TVector3(-1.0f, 1.0f, 0.0f);
	m_vFrustum[2] = TBASIS_EX::TVector3(1.0f, 1.0f, 0.0f);
	m_vFrustum[3] = TBASIS_EX::TVector3(1.0f, -1.0f, 0.0f);
	m_vFrustum[4] = TBASIS_EX::TVector3(-1.0f, -1.0f, 1.0f);
	m_vFrustum[5] = TBASIS_EX::TVector3(-1.0f, 1.0f, 1.0f);
	m_vFrustum[6] = TBASIS_EX::TVector3(1.0f, 1.0f, 1.0f);
	m_vFrustum[7] = TBASIS_EX::TVector3(1.0f, -1.0f, 1.0f);

	for (int iVer = 0; iVer < 8; iVer++)
	{
		TBASIS_EX::D3DXVec3TransformCoord(&m_vFrustum[iVer], &m_vFrustum[iVer], &matInvViewProj);
	}
	// 5    6  
	// 4    7
	// ->   <-
	// 1    2
	// 0    3 
	// ��� 6���� �����.
	// ����� ������ �������� ���� �ٱ����� ���� ���ؾ��Ѵ�.
	// �������� �Ѵ�.
	m_Plane[0].Create(m_vFrustum[5], m_vFrustum[0], m_vFrustum[1]);	// ����
	m_Plane[1].Create(m_vFrustum[3], m_vFrustum[6], m_vFrustum[2]); // ������
	m_Plane[2].Create(m_vFrustum[5], m_vFrustum[2], m_vFrustum[6]); // ��
	m_Plane[3].Create(m_vFrustum[0], m_vFrustum[7], m_vFrustum[3]); // �Ʒ�
	m_Plane[4].Create(m_vFrustum[0], m_vFrustum[3], m_vFrustum[1]); // ��
	m_Plane[5].Create(m_vFrustum[5], m_vFrustum[6], m_vFrustum[4]);	// ��
}

bool MFrustum::ClassifyPoint(TVector3 _v)
{
	for (int iPlane = 0; iPlane < 6; iPlane++)
	{
		float fDistance = m_Plane[iPlane].a * _v.x + m_Plane[iPlane].b * _v.y + m_Plane[iPlane].c * _v.z + m_Plane[iPlane].d;
		if (fDistance < 0)
			return false;
	}

	return true;
}
