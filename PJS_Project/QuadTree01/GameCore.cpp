#include "GameCore.h"

bool GameCore::Init()
{
	gamePlayer.SetPosition(50, 50, 10, 10);			// 플레이어 오브젝트 위치값 세팅
	QuadTree.Create(100.0f, 100.0f);				// 쿼드트리 생성
	for (int sObj = 0; sObj < 10; sObj++)
	{
		CObject* pObj = new mapStaticObj;					// 오브젝트 생성
		AllObjectList.insert(std::make_pair(sObj, pObj));	// 생성된 오브젝트 리스트에 인덱스 추가해 넣기
		QuadTree.AddStaticObject(pObj);
	}
	for (int dObj = 0; dObj < 10; dObj++)
	{
		CObject* pObj = new CDyanmicCharac;
		npcList.insert(std::make_pair(dObj, pObj));			// 동적 오브젝트 관리에 넣기
		AllObjectList.insert(std::make_pair(10+dObj, pObj));
		QuadTree.AddDyanaminObject(pObj);
	}

	return false;
}

bool GameCore::Frame(float fDeltaTime, float fGmaeTime)
{
	QuadTree.DyanmicObjectReset(QuadTree.m_pRootNode);		// 동적 오브젝트 초기화
	for (auto obj : npcList)								// npcList 순환하기
	{
		CObject* pObj = obj.second;						// npcList 오브젝트 값 받기
		pObj->Frame(fDeltaTime, fGmaeTime);					// 동적 오브젝트 frame 실행
		QuadTree.AddDyanaminObject(pObj);
	}
	gamePlayer.Frame(fDeltaTime, fGmaeTime);				// 플레이어 오브젝트 frame 실행

	DrawList = QuadTree.Collision(&gamePlayer);				// 플레이어랑 충돌된 리스트를 출력 리스트에 받는다.
	return false;
}

bool GameCore::Render()
{
	std::cout << "player " << ": " << gamePlayer.m_rect.o_Px << ", " << gamePlayer.m_rect.o_Py << ", " << gamePlayer.m_rect.f_x << ", "
		<< gamePlayer.m_rect.f_y<< std::endl;
	if (!AllObjectList.empty())
	{
		for (int i =0 ; i<AllObjectList.size(); i++)
		{
			std::cout << "AllObject " << ": " << AllObjectList[i]->m_rect.o_Px << ", " << AllObjectList[i]->m_rect.o_Py 
				<< ", " << AllObjectList[i]->m_rect.f_x << ", "
				<< AllObjectList[i]->m_rect.f_y << std::endl;
		}
	}
	if (!DrawList.empty())		// 충돌된 오브젝트가 비어있지않다면
	{
		for (int i = 0; i < DrawList.size(); i++)
		{
			std::cout << "Collision Object! : " << " x : " << DrawList[i] << "y : " << DrawList[i]->m_rect.o_Py
				<< " x2 : " << DrawList[i]->m_rect.f_x << " y2 :" << DrawList[i]->m_rect.f_y << std::endl;
		}
	}
	return false;
}

bool GameCore::Run()
{
	Init();
	float fGameTimer = 0.0f;						// 게임 시간(sec)
	float fDelay = 100.0f;							// 딜레이 10초
	while(fGameTimer<60.0f)						// 60초동안 반복
	{
		Frame(fDelay / 1000.0f, fGameTimer);		// 프레임 출력
		Render();								// 그리기
		Sleep(fDelay);							// 화면에 출력 시간
		system("cls");			
		fGameTimer += fDelay / 1000.0f;			// 게임시간 증가 한번돌때마다 1/100씩 증가 100번 돌아야 1초 증가
	}
	return true;
}

void GameCore::Realese()
{
	for (auto obj : AllObjectList)
	{
		delete obj.second;
	}
	AllObjectList.clear();
	npcList.clear();
	return;
}
