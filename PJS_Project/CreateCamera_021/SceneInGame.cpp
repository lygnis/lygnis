#include "SceneInGame.h"

bool SceneInGame::Init()
{
    I_Sprite.SetDevice(m_pd3dDevice, m_pImmediateContext);
    I_Sprite.Load(L"Sprite.txt", L"../../data/bitmap1.bmp");
    I_Sprite.Load(L"tankState.prn", L"../../data/TankState.png");
    SetPlayer();
    SetMap();
    SetTile();
    m_vCamera = m_pPlayer->m_vPosition;
    m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&m_pBackBuffer);
    m_wWriter = new Writer;
    m_wWriter->Init();
    m_wWriter->Set(m_pBackBuffer);
    //m_pMapObject->SetCameraSize({ 800,800 });
    return true;
}

bool SceneInGame::Frame()
{
    if (m_bGravityUse)
    {
        m_pPlayer->m_vPosition.y += m_fGravity * I_Timer.m_fDeltaTime;  
    }
    m_bGravityUse = PlayerCollision();
    m_pPlayer->Frame();
    m_vCamera = m_pPlayer->m_vCurrCameraPos;
    m_pMapObject->SetCameraPos(m_vCamera);
    m_pMapObject->Frame();
    std::list<MapObject*>::iterator iter;
    for (iter = GroundObjList.begin(); iter != GroundObjList.end(); iter++)
    {
        (*iter)->SetCameraPos(m_vCamera);
        (*iter)->Frame();
    }
    CheckCollision();
    return true;
}

bool SceneInGame::Render()
{
    std::wstring _pPos;
    _pPos = L"ÇÃ·¹ÀÌ¾îÁÂÇ¥\n";
    _pPos += std::to_wstring(m_pPlayer->m_vPosition.x);
    _pPos += L" ";
    _pPos += std::to_wstring(m_pPlayer->m_vPosition.y);
    _pPos += L"\n";
    _pPos += L"¸Ê ÁÂÇ¥\n";
    _pPos += std::to_wstring(m_pMapObject->m_vCameraPos.x);
    _pPos += L" ";
    _pPos += std::to_wstring(m_pMapObject->m_vCameraPos.y);
    
    m_pMapObject->Render();
    m_pPlayer->Render();
    std::list<MapObject*>::iterator iter;
    for (iter = GroundObjList.begin(); iter != GroundObjList.end(); iter++)
    {
        (*iter)->Render();
    }
    m_wWriter->Draw(600, 0, _pPos, {0,0,0,1});
    //m_pPlayer->m_pSprite->Render();
    return true;
}

bool SceneInGame::Release()
{
    m_pPlayer->Release();
    m_pMapObject->Release();
    std::list<MapObject*>::iterator iter;
    for (iter = GroundObjList.begin(); iter != GroundObjList.end(); iter++)
    {
        (*iter)->Release();
        delete *iter;
    }
    GroundObjList.clear();
    delete m_pPlayer;
    delete m_pMapObject;
    delete m_wWriter;
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
    hr = m_pMapObject->Create(L"../../shader/DefaultShader.txt", L"../../data/Skybox.png");
    m_pMapObject->SetRect({ 0,0,2000,800 });
    m_pMapObject->SetPosition({ 1000.0f, 400.0f });
    m_pMapObject->SetCameraSize({ 800,600 });
    if (hr == false) { return false; }
    return true;
}

bool SceneInGame::SetTile()
{
    bool hr;
    for (int i = 0; i < 5; i++)
    {
        MapObject* pData = new MapObject;
        hr = pData->SetDevice(m_pd3dDevice, m_pImmediateContext);
        pData->Create(L"../../shader/DefaultShader.txt", L"../../data/GroundObj.png");
        pData->SetRect({ 19, 416, 266, 213 });
        pData->SetPosition({ 1600.0f - (266.0f * i), 600.0f });
        pData->SetCameraSize({ 800.0f, 600.0f });
        GroundObjList.push_back(pData);
    }
    return false;
}

bool SceneInGame::CheckCollision()
{
    // Ãæµ¹Ã³¸®
    // ÇÃ·¹ÀÌ¾îÀÇ ÃÑ¾Ë ¸®½ºÆ®¶û ¶¥ ¸®½ºÆ®¶û Ãæµ¹Ã¼Å©¸¦ ÇÑ´Ù.
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
    
    for (auto iter = m_pPlayer->m_pBulletList.begin(); iter != m_pPlayer->m_pBulletList.end(); iter++)
    {
        if ((*iter)->m_vPosition.x < 200 || (*iter)->m_vPosition.y > 800.0f)
        {
            m_pPlayer->m_bCollsionCheck = false;
        }
        if ((*iter)->m_vPosition.x > 1700.0f || (*iter)->m_vPosition.y < 0)
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

