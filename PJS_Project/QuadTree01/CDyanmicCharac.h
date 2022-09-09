#pragma once
#include "CObject.h"
class CDyanmicCharac :public CObject
{
public:
	void Frame(float fDeltaTime, float fGameTime)override;
};

