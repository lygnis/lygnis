#include "SceneInGame.h"

bool SceneInGame::Init()
{
    I_Sprite.SetDevice(m_pd3dDevice, m_pImmediateContext);
    I_Sprite.Load(L"Sprite.txt", L"../../data/bitmap1.bmp");
    I_Sprite.Load(L"tankState.prn", L"../../data/TankState.png");
    SetPlayer();
    SetMap();
    m_vCamera = m_pPlayer->m_vPosition;
    m_pMapObject->SetCameraSize({ 750,500 });
    return true;
}

bool SceneInGame::Frame()
{
    m_pPlayer->Frame();
    m_vCamera = m_pPlayer->m_vPosition;
    
    m_pMapObject->SetCameraPos(m_vCamera);
    //m_pMapObject->SetPosition(m_pPlayer->m_vPosition, m_vCamera );
    m_pMapObject->Frame();
    
    return true;
}

bool SceneInGame::Render()
{
    m_pMapObject->Render();
    m_pPlayer->Render();
    //m_pPlayer->m_pSprite->Render();
    return true;
}

bool SceneInGame::Release()
{
    m_pPlayer->Release();
    m_pMapObject->Release();
    delete m_pPlayer;
    delete m_pMapObject;
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
    hr = m_pMapObject->Create(L"../../shader/DefaultShader.txt", L"../../data/backGround.png");
    m_pMapObject->SetRect({ 0,0,1686,600 });
    /*m_pMapObject->m_rtInit.xSize = 900.0f;
    m_pMapObject->m_rtInit.ySize = 700.0f;*/
    m_pMapObject->SetPosition({ 843.0f, 300.0f });
    if (hr == false) { return false; }
    return true;
}

