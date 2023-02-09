#pragma once
#include "MCamera.h"
class ThirdPersonCamera : public MCamera
{
public:
	float target_distance_ = 16.0f;
	TVector3 current_camera_rot;
public:
	virtual bool Frame()override;
	bool Update();
};

