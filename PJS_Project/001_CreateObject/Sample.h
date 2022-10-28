#pragma once
#include "GameCore.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "BObject.h"
#include "MyMatrix.h"
#include "MyShape.h"
#include "DebugCamera.h"
#include "MyMap.h"
#include "MShapeLine.h"
#include "MShape.h"
class Sample : public GameCore
{
	//BObject*	m_pBG;
	//ShapeBox*	m_pBoxA;
	//ShapeBox*	m_pBoxB;
	DebugCamera*	m_pCamera;
	//MyMap*		m_pMap;
	ShapeDirectLine m_DirLine;
	MBoxShape m_pBox;
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

