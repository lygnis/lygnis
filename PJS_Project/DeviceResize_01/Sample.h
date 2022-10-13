#pragma once
#include "GameCore.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "DxState.h"

class Sample : public GameCore
{
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

