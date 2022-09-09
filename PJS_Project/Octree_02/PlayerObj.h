#pragma once
#include "Object.h"
class PlayerObj : public Object 
{
public:
	void Frame(float _fDeltaTime, float fGameTime);			// 플레이어 프레임마다 이동 계산
};

