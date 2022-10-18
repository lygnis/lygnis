#pragma once
#include "GameCore.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "DxState.h"
#include "BObject.h"
#include "MyMatrix.h"
#include "MyShape.h"
class Sample : public GameCore
{
	BObject* m_pBG;
	ShapeBox* m_pBox;
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

