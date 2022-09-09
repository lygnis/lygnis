#pragma once
#include "CQuadTreeMan.h"
#include "CObject.h"
#include <vector>
#include <map>
#include "CPlayerObj.h"
#include "mapStaticObj.h"
#include "CDyanmicCharac.h"
#include <iostream>
class GameCore
{
public:
	CQuadTreeMan QuadTree;
	CPlayerObj gamePlayer;
	std::map<int, CObject*>	npcList;			// 동적 오브젝트 리스트
	std::map<int, CObject*>	AllObjectList;		// 모든 오브젝트 리스트
	std::vector<CObject*>		DrawList;				// 충돌 처리발생한 오브젝트
public:
	bool Init();			// 초기화
	bool Frame(float fDeltaTime, float fGmaeTime);			// 실시간 프레임(게임계산)
	bool Render();										// 화면에 나타내기
	bool Run();		// 실행
	void Realese();
};

