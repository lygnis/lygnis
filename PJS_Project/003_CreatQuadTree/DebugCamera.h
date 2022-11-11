#pragma once
#include "MCamera.h"
class DebugCamera : public MCamera
{
public:
	
public:
	virtual bool Frame()override;
	bool Update();
};

