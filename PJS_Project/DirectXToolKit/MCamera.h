#pragma once
#include "MStd.h"
#include "Timer.h"
#include "Input.h"
class MCamera 
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
	TVector3		m_vLook;
	TVector3		m_vUp;
	TVector3		m_vRight;
	TMatrix			m_matView;
	TMatrix			m_matProj;
	TMatrix			_matWorld;
	TMatrix			mat_ortho_;
	float			m_fYaw;
	float			m_fRoll;
	float			m_fPitch;
	float			m_fDistance;
	float			m_fSpeed = 100.0f;
public:
	TMatrix GetCameraTraslation();
	void CreateViewMatrix(TVector3 _vEye, TVector3 _vAt, TVector3 _vUp);
	void CreateProjMatrix(float _fNear, float _fFar, float fFovY, float fAspecRatio);
	void CreateOrthoLH(float view_right, float view_bottom, float near_z, float far_z);
	virtual bool Frame();
	TMatrix ViewLookAt(TVector3& _vPosition, TVector3& _vTarget, TVector3& _vUp);
	TMatrix PerspectiveFovLH(TMatrix&_mat, float _fNearplane, float _fFarPlane, float _fOvy, float _Aspect);
};

