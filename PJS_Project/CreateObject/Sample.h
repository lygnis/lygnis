#pragma once
#include "GameCore.h"
#include "FirePos.h"
class Sample : public GameCore
{
public:
	BObject m_object;
	FirePos* m_bFire;
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

