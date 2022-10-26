#pragma once
#include "MCamera.h"
#include "MFrustum.h"
class DebugCamera : public MCamera
{
public:
	MFrustum m_vFrustum;
public:
	virtual bool Frame()override;
	bool Update();
};

