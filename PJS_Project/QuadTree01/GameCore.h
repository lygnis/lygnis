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
	std::map<int, CObject*>	npcList;			// ���� ������Ʈ ����Ʈ
	std::map<int, CObject*>	AllObjectList;		// ��� ������Ʈ ����Ʈ
	std::vector<CObject*>		DrawList;				// �浹 ó���߻��� ������Ʈ
public:
	bool Init();			// �ʱ�ȭ
	bool Frame(float fDeltaTime, float fGmaeTime);			// �ǽð� ������(���Ӱ��)
	bool Render();										// ȭ�鿡 ��Ÿ����
	bool Run();		// ����
	void Realese();
};

