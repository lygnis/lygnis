#pragma once
#include "MStd.h"
#include "Timer.h"
#include "Input.h"
class MCamera 
{
public:
	TVector3		camera_pos_;
	TVector3		target_ = { 0,0,0 };
	//Vector3D		v_up_ = { 0,1,0 };
	float			near_;
	float			far_;
	float			fov_Y_;
	float			aspectratio_;
public:
	TVector3		v_look_;
	TVector3		v_up_;
	TVector3		v_right_;
	TMatrix			mat_view_;
	TMatrix			mat_proj_;
	TMatrix			mat_world_;
	float			yaw_;
	float			roll_;
	float			pitch_;
	float			distance_;
	float			speed_ = 100.0f;
public:
	TMatrix GetCameraTraslation();
	void CreateViewMatrix(TVector3 _vEye, TVector3 _vAt, TVector3 _vUp);
	void CreateProjMatrix(float _fNear, float _fFar, float fFovY, float fAspecRatio);
	virtual bool Frame();
	TMatrix ViewLookAt(TVector3& _vPosition, TVector3& _vTarget, TVector3& _vUp);
	TMatrix PerspectiveFovLH(TMatrix&_mat, float _fNearplane, float _fFarPlane, float _fOvy, float _Aspect);
};

