#include "SceneInGame.h"

bool SceneInGame::Init()
{
    /*m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&m_pBackBuffer);
    m_wWriter = new Writer;
    m_wWriter->Init();
    m_wWriter->Set(m_pBackBuffer);*/
    I_Sprite.SetDevice(m_pd3dDevice, m_pImmediateContext);
    I_Sprite.Load(L"Sprite.txt", L"../../data/bitmap1.bmp");
    I_Sprite.Load(L"tankState.prn", L"../../data/TankState.png");
    I_Sprite.Load(L"MushState.txt", L"../../data/Enemy.png");
    SetPlayer();
    SetMap();
    SetTile();
    SetObject();
    m_vCamera = m_pPlayer->m_vPosition;
    SetUI();
    m_pPlayer->m_iMissileCount = m_pMissileUiList.size();
    m_pPlayer->m_fMoveEnergyGage = 350;
    return true;
}

bool SceneInGame::Frame()
{
    if (m_bGravityUse)
    {
        m_pPlayer->m_vPosition.y += 100 * I_Timer.m_fDeltaTime;  
    }
    // 충돌 체크
    m_bGravityUse = PlayerCollision();
    m_pPlayer->Frame();
    m_vCamera = m_pPlayer->m_vCurrCameraPos;
    // 맵 오브젝트 프레임
    m_pMapObject->SetCameraPos(m_vCamera);
    m_pMapObject->Frame();
    // 풍선 오브젝트 프레임
    for (auto iter = m_pBalloonObjList.begin(); iter != m_pBalloonObjList.end(); iter++)
    {
        (*iter)->SetCameraPos(m_vCamera);
        (*iter)->Frame();
    }
    // 아이템 상자 프레임
    for (auto iter = m_pItemBoxList.begin(); iter != m_pItemBoxList.end(); iter++)
    {
        (*iter)->SetCameraPos(m_vCamera);
        (*iter)->Frame();
    }
    // 적 프레임
    for (auto iter = m_pEnemyList.begin(); iter != m_pEnemyList.end(); iter++)
    {
        //(*iter)->m_pSprite->SetPosition(m_pPlayer->m_vCurrCameraPos, m_vCamera);
        (*iter)->SetCameraPos(m_vCamera);
        if (!(*iter)->Frame())
        {
            m_pEnemyList.erase(iter);
            break;
        }
    }
    // 땅 오브젝트 프레임
    std::list<MapObject*>::iterator iter;
    for (iter = GroundObjList.begin(); iter != GroundObjList.end(); iter++)
    {
        (*iter)->SetCameraPos(m_vCamera);
        (*iter)->Frame();
    }
    // 미사일 UI 계산
    if (m_pMissileUiList.size() > m_pPlayer->m_iMissileCount)
    {
        m_pMissileUiList[m_pPlayer->m_iMissileCount]->Release();
        delete m_pMissileUiList[m_pPlayer->m_iMissileCount];
        m_pMissileUiList.pop_back();
    }
    else if (m_pPlayer->m_iMissileCount > m_pMissileUiList.size())
    {
        if (m_pPlayer->m_iMissileCount <= 10)
        {
            Interface* newMissieUI = new Interface;
            newMissieUI->SetDevice(m_pd3dDevice, m_pImmediateContext);
            newMissieUI->Create(L"../../shader/DefaultShader.txt", L"../../data/UI/BulletUI.png");
            newMissieUI->SetRect({ 0,0,25,25 });

            if (m_pPlayer->m_iMissileCount > 5)
            {
                int i = m_pPlayer->m_iMissileCount - 6;
                newMissieUI->SetPosition({ m_pMissileUI->m_vPosition.x + 17 + (i * 30), m_pMissileUI->m_vPosition.y + 52 });
            }
            if (m_pPlayer->m_iMissileCount <= 5)
            {
                newMissieUI->SetPosition({ m_pMissileUI->m_vPosition.x + 17 + ((m_pPlayer->m_iMissileCount - 1) * 30), m_pMissileUI->m_vPosition.y + 15 });
            }
            m_pMissileUiList.push_back(newMissieUI);
        }
    }
    m_pBarList[0]->SetRect({ 0, 0, m_pPlayer->m_fFireGage, 30 });
    m_pBarList[0]->SetPosition({ 300, 512 });
    m_pBarList[1]->SetRect({ 0,68,m_pPlayer->m_fMoveEnergyGage, 30 });
    m_pBarList[1]->SetPosition({ 300, 552 });
    // 충돌처리
    CheckCollision();
    // 클리어 조건
    m_bClear = ClearCheck();
    return true;
}

bool SceneInGame::Render()
{
    /*_pPos = L"플레이어좌표\n";
    _pPos += std::to_wstring(m_pPlayer->m_vPosition.x);
    _pPos += L" ";
    _pPos += std::to_wstring(m_pPlayer->m_vPosition.y);
    _pPos += L"\n";
    _pPos += L"맵 좌표\n";
    _pPos += std::to_wstring(m_pMapObject->m_vCameraPos.x);
    _pPos += L" ";
    _pPos += std::to_wstring(m_pMapObject->m_vCameraPos.y);
    */
    //m_wWriter->Draw(600, 0, _pPos, {0,0,0,1});
    //std::wstring _pPos;
    
    // 렌더링 순서
    // 1. 배경 오브젝트-> 지형 오브젝트->  동적 (파괴가능)오브젝트-> 플레이어 -> UI -> 동적 UI
    // 맵 오브젝트 렌더링
    m_pMapObject->Render();
    // 지형 오브젝트 렌더링
    std::list<MapObject*>::iterator iter;
    for (iter = GroundObjList.begin(); iter != GroundObjList.end(); iter++)
    {
        (*iter)->Render();
    }
    // 동적 오브젝트 렌더링
    for (auto iter = m_pBalloonObjList.begin(); iter != m_pBalloonObjList.end(); iter++)
    {
        (*iter)->Render();
    }
    for (auto iter = m_pItemBoxList.begin(); iter != m_pItemBoxList.end(); iter++)
    {
        (*iter)->Render();
    }
    for (auto iter = m_pEnemyList.begin(); iter != m_pEnemyList.end(); iter++)
    {
        (*iter)->Render();
    }
    // 플레이어 렌더링
    m_pPlayer->Render();
    // UI 바탕 렌더링
    m_pMissileUI->Render();
    m_pInterface->Render();
    // 동적 UI렌더링
    for (int i = 0; i < m_pBarList.size(); i++)
    {
        m_pBarList[i]->Render();
    }
    for (int i =0; i<m_pMissileUiList.size(); i++)
    {
        m_pMissileUiList[i]->Render();
    }
    return true;
}

bool SceneInGame::SetObject()
{
    {
        EnemyBalloon* newBalloon = new EnemyBalloon;
        newBalloon->SetDevice(m_pd3dDevice, m_pImmediateContext);
        newBalloon->m_iHp = 1;
        newBalloon->Init();
        newBalloon->Create(L"../../shader/DefaultShader.txt", L"../../data/Balloon_Red.png");
        newBalloon->SetRect({ 3,6,67,110 });
        m_pBalloonObjList.push_back(newBalloon);
    }
    {
        EnemyBalloon* newBalloon = new EnemyBalloon;
        newBalloon->SetDevice(m_pd3dDevice, m_pImmediateContext);
        newBalloon->m_iHp = 2;
        newBalloon->Init();
        newBalloon->Create(L"../../shader/DefaultShader.txt", L"../../data/Green_balloon.png");
        newBalloon->SetRect({ 3,128,67,112 });
        m_pBalloonObjList.push_back(newBalloon);
    }
    {
        ItemBox* pBox = new ItemBox;
        pBox->SetDevice(m_pd3dDevice, m_pImmediateContext);
        pBox->Init();
        pBox->Create(L"../../shader/DefaultShader.txt", L"../../data/RTS_Crate.png");
        pBox->SetRect({ 0,0,55,55 });
        pBox->SetPosition({ 2710, 1266.f });
        m_pItemBoxList.push_back(pBox);
    }
    {
        ItemBox* pBox = new ItemBox;
        pBox->SetDevice(m_pd3dDevice, m_pImmediateContext);
        pBox->Init();
        pBox->Create(L"../../shader/DefaultShader.txt", L"../../data/RTS_Crate.png");
        pBox->SetRect({ 0,0,55,55 });
        pBox->SetPosition({ 2310, 1450.f });
        m_pItemBoxList.push_back(pBox);
    }
    {
        ItemBox* pBox = new ItemBox;
        pBox->SetDevice(m_pd3dDevice, m_pImmediateContext);
        pBox->Init();
        pBox->Create(L"../../shader/DefaultShader.txt", L"../../data/RTS_Crate.png");
        pBox->SetRect({ 0,0,55,55 });
        pBox->SetPosition({ 2500, 1587.f });
        m_pItemBoxList.push_back(pBox);
    }
    {
        ItemBox* pBox = new ItemBox;
        pBox->SetDevice(m_pd3dDevice, m_pImmediateContext);
        pBox->Init();
        pBox->Create(L"../../shader/DefaultShader.txt", L"../../data/RTS_Crate.png");
        pBox->SetRect({ 0,0,55,55 });
        pBox->SetPosition({ 1920, 1587.f });
        m_pItemBoxList.push_back(pBox);
    }
    {
        ItemBox* pBox = new ItemBox;
        pBox->SetDevice(m_pd3dDevice, m_pImmediateContext);
        pBox->Init();
        pBox->Create(L"../../shader/DefaultShader.txt", L"../../data/RTS_Crate.png");
        pBox->SetRect({ 0,0,55,55 });
        pBox->SetPosition({ 1920, 1532.f });
        m_pItemBoxList.push_back(pBox);
    }
    {
        ItemBox* pBox = new ItemBox;
        pBox->SetDevice(m_pd3dDevice, m_pImmediateContext);
        pBox->Init();
        pBox->Create(L"../../shader/DefaultShader.txt", L"../../data/RTS_Crate.png");
        pBox->SetRect({ 0,0,55,55 });
        pBox->SetPosition({ 1798, 1587.f });
        m_pItemBoxList.push_back(pBox);
    }
    {
        ItemBox* pBox = new ItemBox;
        pBox->SetDevice(m_pd3dDevice, m_pImmediateContext);
        pBox->Init();
        pBox->Create(L"../../shader/DefaultShader.txt", L"../../data/RTS_Crate.png");
        pBox->SetRect({ 0,0,55,55 });
        pBox->SetPosition({ 1688, 1587.f });
        m_pItemBoxList.push_back(pBox);
    }
    {
        ItemBox* pBox = new ItemBox;
        pBox->SetDevice(m_pd3dDevice, m_pImmediateContext);
        pBox->Init();
        pBox->Create(L"../../shader/DefaultShader.txt", L"../../data/RTS_Crate.png");
        pBox->SetRect({ 0,0,55,55 });
        pBox->SetPosition({ 1743, 1532.f });
        m_pItemBoxList.push_back(pBox);
    }
    for(int i =0; i<4; i++)
    {
        if (i == 2)
        {
            EnemyPig* pEnemy1 = new EnemyPig;
            pEnemy1->SetDevice(m_pd3dDevice, m_pImmediateContext);
            pEnemy1->Create(L"../../shader/DefaultShader.txt", L"../../data/Enemy.png");
            pEnemy1->Init();
            pEnemy1->SetPosition({ 1660.f , 1290.f });
            pEnemy1->SetCameraSize({ 800,600 });
            m_pEnemyList.push_back(pEnemy1);
        }
        else
        {
            EnemyPig* pEnemy1 = new EnemyPig;
            pEnemy1->SetDevice(m_pd3dDevice, m_pImmediateContext);
            pEnemy1->Create(L"../../shader/DefaultShader.txt", L"../../data/Enemy.png");
            pEnemy1->Init();
            //pEnemy1->SetRect({ 0,0,4080,2448 });
            pEnemy1->SetPosition ({ 1860.f - (i * 120.f), 1587.f });
            pEnemy1->SetCameraSize({ 800,600 });
            m_pEnemyList.push_back(pEnemy1);
        }
       
    }
    {
        EnemyPig* pEnemy1 = new EnemyPig;
        pEnemy1->SetDevice(m_pd3dDevice, m_pImmediateContext);
        pEnemy1->Create(L"../../shader/DefaultShader.txt", L"../../data/Enemy.png");
        pEnemy1->Init();
        //pEnemy1->SetRect({ 0,0,4080,2448 });
        pEnemy1->SetPosition({ 1920.f, 1477.f });
        pEnemy1->SetCameraSize({ 800,600 });
        m_pEnemyList.push_back(pEnemy1);
    }
    return true;
}

bool SceneInGame::SetPlayer()
{
    bool hr;
    m_pPlayer = new Player;
    m_pPlayer->Init();
    hr = m_pPlayer->SetDevice(m_pd3dDevice, m_pImmediateContext);
    if (hr == false) { return false; }  
    return true;
}

bool SceneInGame::SetMap()
{
    bool hr;
    m_pMapObject = new MapObject;
    hr = m_pMapObject->SetDevice(m_pd3dDevice, m_pImmediateContext);
    if (hr == false) { return false; }
    hr = m_pMapObject->Create(L"../../shader/DefaultShader.txt", L"../../data/Blue Sky.png");
    m_pMapObject->SetRect({ 0,0,4080,2448 });
    m_pMapObject->SetPosition({ 2040.f, 1224.f });
    m_pMapObject->SetCameraSize({ 800,600 });
    if (hr == false) { return false; }
    return true;
}

bool SceneInGame::SetTile()
{
    bool hr;
    for (int i = 0; i < 3; i++)
    {
        MapObject* pData = new MapObject;
        hr = pData->SetDevice(m_pd3dDevice, m_pImmediateContext);
        pData->Create(L"../../shader/DefaultShader.txt", L"../../data/GroundObj.png");
        pData->SetRect({ 784, 444, 270, 180 });
        pData->SetPosition({ 3100 - (270.f * i), 1900.f });
        pData->SetCameraSize({ 800.0f, 600.0f });
        GroundObjList.push_back(pData);
    }
    for (int i = 0; i < 3; i++)
    {
        MapObject* pData = new MapObject;
        hr = pData->SetDevice(m_pd3dDevice, m_pImmediateContext);
        pData->Create(L"../../shader/DefaultShader.txt", L"../../data/GroundObj.png");
        pData->SetRect({ 19, 416, 270, 213 });
        pData->SetPosition({ 3100 - (270.f * i), 1720.f });
        pData->SetCameraSize({ 800.0f, 600.0f });
        GroundObjList.push_back(pData);
    }
    for(int i =0; i<2; i++)
    {
        MapObject* pData = new MapObject;
        hr = pData->SetDevice(m_pd3dDevice, m_pImmediateContext);
        pData->Create(L"../../shader/DefaultShader.txt", L"../../data/GroundObj.png");
        pData->SetRect({ 784, 444, 270, 180 });
        pData->SetPosition({ 3370 , 1900.f -(i* 180) });
        pData->SetCameraSize({ 800.0f, 600.0f });
        GroundObjList.push_back(pData);
    }
    {
        MapObject* pData1 = new MapObject;
        hr = pData1->SetDevice(m_pd3dDevice, m_pImmediateContext);
        pData1->Create(L"../../shader/DefaultShader.txt", L"../../data/GroundObj.png");
        pData1->SetRect({ 367, 291, 335, 336 });
        pData1->SetPosition({ 3370 , 1540.f });
        pData1->SetCameraSize({ 800.0f, 600.0f });
        GroundObjList.push_back(pData1);
        m_pWallList.push_back(pData1);
    }
	for (int i = 0; i < 2; i++)
	{
		MapObject* pData = new MapObject;
		hr = pData->SetDevice(m_pd3dDevice, m_pImmediateContext);
		pData->Create(L"../../shader/DefaultShader.txt", L"../../data/GroundObj.png");
		pData->SetRect({ 784, 444, 270, 180 });
		pData->SetPosition({ 2290 , 1900.f - (i * 180) });
		pData->SetCameraSize({ 800.0f, 600.0f });
		GroundObjList.push_back(pData);
	}
    {
        MapObject* pData1 = new MapObject;
        hr = pData1->SetDevice(m_pd3dDevice, m_pImmediateContext);
        pData1->Create(L"../../shader/DefaultShader.txt", L"../../data/GroundObj.png");
        pData1->SetRect({ 367, 291, 335, 336 });
        pData1->SetPosition({ 2290 , 1640.f });
        pData1->SetCameraSize({ 800.0f, 600.0f });
        GroundObjList.push_back(pData1);
        m_pWallList.push_back(pData1);
    }
    for (int i = 0; i < 3; i++)
    {
        MapObject* pData = new MapObject;
        hr = pData->SetDevice(m_pd3dDevice, m_pImmediateContext);
        pData->Create(L"../../shader/DefaultShader.txt", L"../../data/GroundObj.png");
        pData->SetRect({ 784, 444, 270, 180 });
        pData->SetPosition({ 2020 - (270.f * i), 1900.f });
        pData->SetCameraSize({ 800.0f, 600.0f });
        GroundObjList.push_back(pData);
    }
    for (int i = 0; i < 3; i++)
    {
        MapObject* pData = new MapObject;
        hr = pData->SetDevice(m_pd3dDevice, m_pImmediateContext);
        pData->Create(L"../../shader/DefaultShader.txt", L"../../data/GroundObj.png");
        pData->SetRect({ 19, 416, 270, 213 });
        pData->SetPosition({ 2020 - (270.f * i), 1720.f });
        pData->SetCameraSize({ 800.0f, 600.0f });
        GroundObjList.push_back(pData);
    }
    {
        MapObject* pData = new MapObject;
        hr = pData->SetDevice(m_pd3dDevice, m_pImmediateContext);
        pData->Create(L"../../shader/DefaultShader.txt", L"../../data/GroundObj.png");
        pData->SetRect({ 161, 208, 180, 116 });
        pData->SetPosition({ 2700 , 1350.f });
        pData->SetCameraSize({ 800.0f, 600.0f });
        GroundObjList.push_back(pData);
    }
    {
        MapObject* pData = new MapObject;
        hr = pData->SetDevice(m_pd3dDevice, m_pImmediateContext);
        pData->Create(L"../../shader/DefaultShader.txt", L"../../data/GroundObj.png");
        pData->SetRect({ 23, 209, 90, 66 });
        pData->SetPosition({ 1660 , 1350.f });
        pData->SetCameraSize({ 800.0f, 600.0f });
        GroundObjList.push_back(pData);
    }

    return false;
}

bool SceneInGame::SetUI()
{
    m_pInterface = new Interface;
    m_pInterface->SetDevice(m_pd3dDevice, m_pImmediateContext);
    m_pInterface->Create(L"../../shader/DefaultShader.txt", L"../../data/UI/popup_box3.png");
    m_pInterface->SetRect({ 0,0,539,108 });
    m_pInterface->SetPosition({269,492});

	Interface* pData = new Interface;
	pData->SetDevice(m_pd3dDevice, m_pImmediateContext);
	pData->Create(L"../../shader/DefaultShader.txt", L"../../data/UI/bar.png");
	pData->SetRect({ 0,0,10,30 });
    pData->SetPosition({ 300, 512 });
    m_pBarList.push_back(pData);
    Interface* pData2 = new Interface;
    pData2->SetDevice(m_pd3dDevice, m_pImmediateContext);
    pData2->Create(L"../../shader/DefaultShader.txt", L"../../data/UI/bar.png");
    pData2->SetRect({ 0,68,350,30 });
    pData2->SetPosition({ 300, 552 });
    m_pBarList.push_back(pData2);
    m_pMissileUI = new Interface;
    m_pMissileUI->SetDevice(m_pd3dDevice, m_pImmediateContext);
    m_pMissileUI->Create(L"../../shader/DefaultShader.txt", L"../../data/UI/panel_mid.png");
    m_pMissileUI->SetRect({ 0,0,180,90 });
    m_pMissileUI->SetPosition({ 48,500 });
    for (int i = 0; i < 5; i++)
    {
        Interface* newMissieUI = new Interface;
        newMissieUI->SetDevice(m_pd3dDevice, m_pImmediateContext);
        newMissieUI->Create(L"../../shader/DefaultShader.txt", L"../../data/UI/BulletUI.png");
        newMissieUI->SetRect({ 0,0,25,25 });
        newMissieUI->SetPosition({ m_pMissileUI->m_vPosition.x + 17 + (i * 30), m_pMissileUI->m_vPosition.y+15 });
        m_pMissileUiList.push_back(newMissieUI);
    }
    for (int i = 0; i < 5; i++)
    {
        Interface* newMissieUI = new Interface;
        newMissieUI->SetDevice(m_pd3dDevice, m_pImmediateContext);
        newMissieUI->Create(L"../../shader/DefaultShader.txt", L"../../data/UI/BulletUI.png");
        newMissieUI->SetRect({ 0,0,25,25 });
        newMissieUI->SetPosition({ m_pMissileUI->m_vPosition.x + 17 + (i * 30), m_pMissileUI->m_vPosition.y + 52 });
        m_pMissileUiList.push_back(newMissieUI);
    }
    return true;
}

bool SceneInGame::CheckCollision()
{
    // 충돌처리
    // 플레이어의 총알 리스트랑 땅 리스트랑 충돌체크를 한다.
    for (auto iter = m_pPlayer->m_pBulletList.begin(); iter != m_pPlayer->m_pBulletList.end(); iter++)
    {
        for (auto jter = GroundObjList.begin(); jter != GroundObjList.end(); jter++)
        {
            if (Collision::BoxToBox((*iter)->m_rtCollision, (*jter)->m_rtCollision))
            {
                m_pPlayer->m_bCollsionCheck = false;
            }
        }
    }
    if (!m_pBalloonObjList.empty())
    {
        for (auto iter = m_pPlayer->m_pBulletList.begin(); iter != m_pPlayer->m_pBulletList.end(); iter++)
        {
            for (auto jter = m_pBalloonObjList.begin(); jter != m_pBalloonObjList.end(); jter++)
            {
                if (Collision::BoxToBox((*iter)->m_rtCollision, (*jter)->m_rtCollision))
                {
                    if ((*jter)->m_iHp <= 1)
                    {
                        m_pPlayer->m_bCollsionCheck = false;
                        (*jter)->Release();
                        delete (*jter);
                        m_pBalloonObjList.erase(jter);
                        break;
                    }
                    else
                    {
                        (*jter)->m_iHp--;
                        m_pPlayer->m_bCollsionCheck = false;
                    }
                }
            }
        }
    }
    if (!m_pItemBoxList.empty())
    {
        for (auto iter = m_pPlayer->m_pBulletList.begin(); iter != m_pPlayer->m_pBulletList.end(); iter++)
        {
            for (auto jter = m_pItemBoxList.begin(); jter != m_pItemBoxList.end(); jter++)
            {
                if (Collision::BoxToBox((*iter)->m_rtCollision, (*jter)->m_rtCollision))
                {
                    m_pPlayer->m_bCollsionCheck = false;
                    if ((*jter)->m_iCountItem == 3)
                    {
                        m_pPlayer->m_iMissileCount++;
                    }
                    (*jter)->Release();
                    delete (*jter);
                    m_pItemBoxList.erase(jter);
                    break;
                }
            }
        }
    }

    for (auto iter = m_pPlayer->m_pBulletList.begin(); iter != m_pPlayer->m_pBulletList.end(); iter++)
    {
        for (auto jter = m_pEnemyList.begin(); jter != m_pEnemyList.end(); jter++)
        {
            if (Collision::BoxToBox((*iter)->m_rtCollision, (*jter)->m_rtCollision))
            {
                m_pPlayer->m_bCollsionCheck = false;
                (*jter)->m_bEnemyDead = true;
                //m_pEnemyList.erase(jter);
                break;
            }
        }
    }
    for (auto iter = m_pPlayer->m_pBulletList.begin(); iter != m_pPlayer->m_pBulletList.end(); iter++)
    {
        if ((*iter)->m_vPosition.x < 500 || (*iter)->m_vPosition.y > 2000.f)
        {
            m_pPlayer->m_bCollsionCheck = false;
        }
        if ((*iter)->m_vPosition.x > 3600 || (*iter)->m_vPosition.y < 350.f)
        {
            m_pPlayer->m_bCollsionCheck = false;
        }
    }
    return true;
}

bool SceneInGame::PlayerCollision()
{
    for (auto iter = GroundObjList.begin(); iter != GroundObjList.end(); iter++)
    {
        if (Collision::BoxToBox((*iter)->m_rtCollision, m_pPlayer->m_pSprite->m_rtCollision))
        {
            return false;
        }
    }
    
    return true;
}

GameClear SceneInGame::ClearCheck()
{
    if (m_pEnemyList.empty())
    {
        return GameClear::GAME_CLEAR;
    }
    if (m_pMissileUiList.empty())
    {
        return GameClear::GAME_OVER;
    }
    //return false;
}

bool SceneInGame::Release()
{
    m_pPlayer->Release();
    m_pMapObject->Release();
    m_pInterface->Release();
    m_pMissileUI->Release();
    for (auto iter= m_pBalloonObjList.begin(); iter != m_pBalloonObjList.end(); iter++)
    {
        (*iter)->Release();
        delete* iter;
    }
    m_pBalloonObjList.clear();
    for (auto iter = m_pItemBoxList.begin(); iter != m_pItemBoxList.end(); iter++)
    {
        (*iter)->Release();
        delete* iter;
    }
    m_pItemBoxList.clear();
    std::list<MapObject*>::iterator iter;
    for (iter = GroundObjList.begin(); iter != GroundObjList.end(); iter++)
    {
        (*iter)->Release();
        delete* iter;
    }
    GroundObjList.clear();
    for (int i = 0; i < m_pBarList.size(); i++)
    {
        m_pBarList[i]->Release();
        delete m_pBarList[i];
    }
    for (auto iter = m_pMissileUiList.begin(); iter != m_pMissileUiList.end(); iter++)
    {
        (*iter)->Release();
        delete* iter;
    }
    m_pMissileUiList.clear();
    for (auto iter = m_pEnemyList.begin(); iter != m_pEnemyList.end(); iter++)
    {
        (*iter)->Release();
        delete* iter;
    }
    m_pEnemyList.clear();
    m_pBarList.clear();
    delete m_pPlayer;
    delete m_pMapObject;
    delete m_pInterface;
    delete m_pMissileUI;
    return true;
}