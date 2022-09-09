#pragma once
#include "CObject.h"
class CPlayerObj : public CObject
{
public:
	void Frame(float fDeltaTime, float fGameTime)override;
};

