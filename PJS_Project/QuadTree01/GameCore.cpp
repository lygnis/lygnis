#include "GameCore.h"

bool GameCore::Init()
{
	gamePlayer.SetPosition(50, 50, 10, 10);			// �÷��̾� ������Ʈ ��ġ�� ����
	QuadTree.Create(100.0f, 100.0f);				// ����Ʈ�� ����
	for (int sObj = 0; sObj < 10; sObj++)
	{
		CObject* pObj = new mapStaticObj;					// ������Ʈ ����
		AllObjectList.insert(std::make_pair(sObj, pObj));	// ������ ������Ʈ ����Ʈ�� �ε��� �߰��� �ֱ�
		QuadTree.AddStaticObject(pObj);
	}
	for (int dObj = 0; dObj < 10; dObj++)
	{
		CObject* pObj = new CDyanmicCharac;
		npcList.insert(std::make_pair(dObj, pObj));			// ���� ������Ʈ ������ �ֱ�
		AllObjectList.insert(std::make_pair(10+dObj, pObj));
		QuadTree.AddDyanaminObject(pObj);
	}

	return false;
}

bool GameCore::Frame(float fDeltaTime, float fGmaeTime)
{
	QuadTree.DyanmicObjectReset(QuadTree.m_pRootNode);		// ���� ������Ʈ �ʱ�ȭ
	for (auto obj : npcList)								// npcList ��ȯ�ϱ�
	{
		CObject* pObj = obj.second;						// npcList ������Ʈ �� �ޱ�
		pObj->Frame(fDeltaTime, fGmaeTime);					// ���� ������Ʈ frame ����
		QuadTree.AddDyanaminObject(pObj);
	}
	gamePlayer.Frame(fDeltaTime, fGmaeTime);				// �÷��̾� ������Ʈ frame ����

	DrawList = QuadTree.Collision(&gamePlayer);				// �÷��̾�� �浹�� ����Ʈ�� ��� ����Ʈ�� �޴´�.
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
	if (!DrawList.empty())		// �浹�� ������Ʈ�� ��������ʴٸ�
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
	float fGameTimer = 0.0f;						// ���� �ð�(sec)
	float fDelay = 100.0f;							// ������ 10��
	while(fGameTimer<60.0f)						// 60�ʵ��� �ݺ�
	{
		Frame(fDelay / 1000.0f, fGameTimer);		// ������ ���
		Render();								// �׸���
		Sleep(fDelay);							// ȭ�鿡 ��� �ð�
		system("cls");			
		fGameTimer += fDelay / 1000.0f;			// ���ӽð� ���� �ѹ��������� 1/100�� ���� 100�� ���ƾ� 1�� ����
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
