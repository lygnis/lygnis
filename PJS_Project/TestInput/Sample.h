#pragma once
#include "GameCore.h"
class Sample : public GameCore
{
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

