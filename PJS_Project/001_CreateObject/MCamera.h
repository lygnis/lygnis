#pragma once
#include "BObject.h"
class MCamera : public BObject
{
public:
	Vector3D		m_vCameraPos;
	Vector3D		m_vTarget = { 0,0,0 };
	//Vector3D		m_vUp = { 0,1,0 };
	float			m_fNear;
	float			m_fFar;
	float			m_fFovY;
	float			m_fAspectRatio;
public:
	TBASIS_EX::TVector3		m_vLook;
	TBASIS_EX::TVector3		m_vUp;
	TBASIS_EX::TVector3		m_vRight;
	float			m_fYaw;
	float			m_fRoll;
	float			m_fPitch;
	float			m_fDistance;
	float			m_fSpeed;
public:
	void CreateViewMatrix(Vector3D _vEye, Vector3D _vAt, Vector3D _vUp);
	void CreateProjMatrix(float _fNear, float _fFar, float fFovY, float fAspecRatio);
	virtual bool Frame() override;
	MyMatrix4X4 ViewLookAt(Vector3D& _vPosition, Vector3D& _vTarget, Vector3D& _vUp);
	MyMatrix4X4 PerspectiveFovLH(MyMatrix4X4&_mat, float _fNearplane, float _fFarPlane, float _fOvy, float _Aspect);
};

