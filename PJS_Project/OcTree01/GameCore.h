#pragma once
#include "OcTreeManager.h"
#include "PlayerObj.h"
#include "EnemyObj.h"
#include "MapObj.h"
#include <map>
#include <Windows.h>

class GameCore
{
	OcTreeManager			m_Octree;
	PlayerObj			m_Player;
	std::map<int,Object*>	m_NpcList;
	std::map<int, Object*>m_AllObjectList;
	std::vector<Object*>	m_CollsionObject;
public:
	bool Init();
	bool Frame(float _fDeltaTime, float _fGameTime);
	bool Render();
	void Realase();
	bool Run();
};

