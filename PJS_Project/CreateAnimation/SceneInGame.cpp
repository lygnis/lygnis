#include "SceneInGame.h"

bool SceneInGame::Init()
{
    I_Sprite.SetDevice(m_pd3dDevice, m_pImmediateContext);
    I_Sprite.Load(L"Sprite.txt", L"../../data/bitmap1.bmp");
    I_Sprite.Load(L"tankState.prn", L"../../data/TankState.png");
    SetPlayer();
    SetMap();
    return true;
}

bool SceneInGame::Frame()
{
    m_pPlayer->Frame();
    m_fCurrTime += I_Timer.m_fDeltaTime;
    if (I_Input.GetKey('V') == KEY_HOLD)
    {
        if (m_fCurrTime >= 0.1f)
        {
            AddEffect();
            m_fCurrTime = 0;
        }
    }
    for (auto iter = m_pEffecList.begin();
        iter != m_pEffecList.end(); )
    {
        Efeect* pEffect = *iter;
        if (pEffect->Updata() == false)
        {
            delete pEffect;
            iter = m_pEffecList.erase(iter);
            continue;
        }
        iter++;
    }
    return true;
}

bool SceneInGame::Render()
{
    m_pMapObject->Render();
    m_pPlayer->Render();
    //m_pPlayer->m_pSprite->Render();
    for (auto pEffect : m_pEffecList)
    {
        pEffect->m_pSprite->SetRect(pEffect->m_tRect);
        pEffect->m_pSprite->SetPosition(pEffect->m_vPos);
        pEffect->m_pSprite->Render();
    }
    return true;
}

bool SceneInGame::Release()
{
    m_pPlayer->Release();
    m_pMapObject->Release();
    delete m_pPlayer;
    delete m_pMapObject;
    for (auto data : m_pEffecList)
    {
        delete data;
    }
    m_pEffecList.clear();
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
    if (hr == false) { return false; }
    return true;
}

bool SceneInGame::AddEffect()
{
    Efeect* pEffect = new Efeect;
    pEffect->m_pSprite = I_Sprite.GetPtr(L"rtExplosion");
    pEffect->m_fEffectTimer = 0.0f;
    Rect rt = pEffect->m_pSprite->m_uvArray[0];
    pEffect->m_tRect = rt;
    pEffect->m_iIndex = 0;
    pEffect->m_fLifeTime = 1.0f;
    pEffect->m_vPos = { 400,300 };
    pEffect->m_fStep = pEffect->m_fLifeTime / pEffect->m_pSprite->m_uvArray.size();
    pEffect->m_iMaxIndex = pEffect->m_pSprite->m_uvArray.size();

    pEffect->m_pSprite->SetRect(pEffect->m_tRect);
    pEffect->m_pSprite->SetPosition(pEffect->m_vPos);

    pEffect->m_rtCollision = pEffect->m_pSprite->m_rtCollision;
    pEffect->m_rtCollision.x0 = pEffect->m_vPos.x;
    pEffect->m_rtCollision.y0 = pEffect->m_vPos.y;
    m_pEffecList.push_back(pEffect);
    return true;
}
