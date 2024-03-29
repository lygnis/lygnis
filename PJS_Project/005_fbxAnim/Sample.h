#pragma once
#include "GameCore.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "MyMatrix.h"
#include "DebugCamera.h"
#include "MShapeLine.h"
#include "MShape.h"
#include "MQuadTree.h"
#include "FbxLoader.h"
class Sample : public GameCore
{
	//BObject*	m_pBG;
	//ShapeBox*	m_pBoxA;
	//ShapeBox*	m_pBoxB;
	DebugCamera*	m_pCamera;
	//MyMap*		m_pMap;
	//ShapeDirectLine m_DirLine;
	MBoxShape* m_pBox;
	MmapTile* m_pMap;
	MQuadTree m_QuadTree;
	//std::vector<FbxLoader*> m_fbxList;
	FbxLoader* m_fbxLoad;
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

