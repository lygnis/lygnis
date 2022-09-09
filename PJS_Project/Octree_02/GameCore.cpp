#include "GameCore.h"
bool GameCore::Init()
{
	Vector3D m_Ppos(50, 50, 50);
	Vector3D m_Psize(10, 10, 10);
	m_Player.SetPosition(m_Ppos, m_Psize);
	m_Octree.Create();
	for (int i = 0; i < 10; i++)
	{
		Object* pObj = new EnemyObj;
		m_NpcList.insert(std::make_pair(i, pObj));
		m_AllObjectList.insert(std::make_pair(i, pObj));
		m_Octree.AddDynamicObject(pObj);
	}
	for (int i = 0; i < 10; i++)
	{
		Object* pObj = new MapObj;
		m_AllObjectList.insert(std::make_pair(10 + i, pObj));
		m_Octree.AddStaticObject(pObj);
	}
	return false;
}
bool GameCore::Frame(float _fDeltaTime, float _fGameTime)
{
	m_Octree.DynamicObjectReset(m_Octree.m_pRootNode);
	int index = 0;
	for (auto dObj : m_NpcList)
	{
		Object* pObj = dObj.second;
		pObj->Frame(_fDeltaTime, _fGameTime);
		m_Octree.AddDynamicObject(pObj);
		index++;
	}
	m_Player.Frame(_fDeltaTime, _fGameTime);
	m_CollsionObject = m_Octree.Collision(&m_Player);
	return false;
}
bool GameCore::Render()
{
	std::cout << "player " << ": " << m_Player.m_Coor.v_ctPoint.x << ", " << m_Player.m_Coor.v_ctPoint.y << ", " << m_Player.m_Coor.v_ctPoint.z << ", "
		<< m_Player.m_Coor.v_Size.x << std::endl;
	std::cout << " " << std::endl;
	if (!m_CollsionObject.empty())		// 충돌된 오브젝트가 비어있지않다면
	{
		for (int i = 0; i < m_CollsionObject.size(); i++)
		{
			std::cout << "Collision Object! : " << " x : " << m_CollsionObject[i]->m_Coor.v_ctPoint.x << "y : " << m_CollsionObject[i]->m_Coor.v_ctPoint.y
				<< " z : " << m_CollsionObject[i]->m_Coor.v_ctPoint.z << " x Size :" << m_CollsionObject[i]->m_Coor.v_Size.x << " y Size :" <<
				m_CollsionObject[i]->m_Coor.v_Size.y<< " z Size :" << m_CollsionObject[i]->m_Coor.v_Size.z <<std::endl;
				std::cout << " " << std::endl;
		}
	}
	if (!m_AllObjectList.empty())
	{
		for (int i = 0; i < m_AllObjectList.size(); i++)
		{
			std::cout << "AllObject " << ": " << m_AllObjectList[i]->m_Coor.v_ctPoint.x << ", " << m_AllObjectList[i]->m_Coor.v_ctPoint.y
				<< ", " << m_AllObjectList[i]->m_Coor.v_ctPoint.z << std::endl;
		}
	}
	return false;
}

bool GameCore::Run()
{
	Init();
	float fGameTime = 0.0f;
	float fDelay = 100.0f;
	while (fGameTime < 60.0f)
	{
		Frame(fDelay / 1000.0f, fGameTime);
		Render();
		Sleep(fDelay);
		//system("cls");
		fGameTime += fDelay / 1000.0f;
	}
	return true;
}
void GameCore::Realase()
{
	for (auto obj : m_AllObjectList)
	{
		delete obj.second;
	}
	m_AllObjectList.clear();
	m_NpcList.clear();
	return;
}