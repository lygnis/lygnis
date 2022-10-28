#pragma once
#include "MActor.h"

class MCamera : public MActor
{
public:
	TVector3		m_vCameraPos;
	TVector3		m_vTarget = { 0,0,0 };
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
	void CreateViewMatrix(TVector3 _vEye, TVector3 _vAt, TVector3 _vUp);
	void CreateProjMatrix(float _fNear, float _fFar, float fFovY, float fAspecRatio);
	virtual bool Frame();
	TMatrix ViewLookAt(TVector3& _vPosition, TVector3& _vTarget, TVector3& _vUp);
	TMatrix PerspectiveFovLH(TMatrix&_mat, float _fNearplane, float _fFarPlane, float _fOvy, float _Aspect);
};

