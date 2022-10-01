#include "SceneInGame.h"

bool SceneInGame::Init()
{
    I_Sprite.SetDevice(m_pd3dDevice, m_pImmediateContext);
    I_Sprite.Load(L"Sprite.txt", L"../../data/bitmap1.bmp");
    I_Sprite.Load(L"tankState.prn", L"../../data/TankState.png");
    SetPlayer();
    SetMap();
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
    m_pPlayer->Frame();
    m_vCamera = m_pPlayer->m_vCurrCameraPos;
    m_pMapObject->SetCameraPos(m_pPlayer->m_vCurrCameraPos);
    m_pMapObject->Frame();
    
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
    m_wWriter->Draw(600, 0, _pPos, {0,0,0,1});
    //m_pPlayer->m_pSprite->Render();
    return true;
}

bool SceneInGame::Release()
{
    m_pPlayer->Release();
    m_pMapObject->Release();
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

