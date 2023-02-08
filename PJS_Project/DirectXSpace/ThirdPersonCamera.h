#pragma once
#include "MCamera.h"
class ThirdPersonCamera : public MCamera
{
public:
	TVector3 target_pos_;
	float target_distance_ = 16.0f;
public:
	virtual bool Frame()override;
	bool Update();
};

