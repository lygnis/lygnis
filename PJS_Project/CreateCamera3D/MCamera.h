#pragma once
#include "BObject.h"
class MCamera : public BObject
{
	Vector3D		m_vCameraPos;
	Vector3D		m_vTarget = { 0,0,0 };
	Vector3D		m_vUp = { 0,1,0 };
	float			m_fNear;
	float			m_fFar;
	float			m_fFovY;
	float			m_fAspectRatio;
public:
	virtual void CreateViewMatrix(Vector3D _vEye, Vector3D _vAt, Vector3D _vUp);
	virtual void CreateProjMatrix(float _fNear, float _fFar, float fFovY, float fAspecRatio);
	virtual bool Frame();
};

