#include "Sample.h"
#include "Player.h"
#include "Bullet.h"
#include "SpriteManager.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    Sample game;
    game.SetWindow(hInstance, L"TestDeviceCore", 800, 600);
    game.Run();
    //_CrtDumpMemoryLeaks();

    return 1;
}

bool Sample::Init()
{
    bool hr;
    I_Sprite.SetDevice(m_pDevice->m_p3dDevice, m_pDevice->m_pImmediateContext);
    I_Sprite.Load(L"Sprite.txt");

    DxState::SetState(m_pDevice->m_p3dDevice);
    hr = SetMapObject();
    hr = SetPlayer();
    if (hr == false) { return false; }
   
    return true;
}
bool Sample::Frame()
{
    m_bPlayer->Frame();
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
bool Sample::Render()
{
    m_pDevice->m_pImmediateContext->PSSetSamplers(0, 1, &DxState::g_pDefaultSS);
    m_object->Render();
    m_bPlayer->Render();
    for (auto pEffect : m_pEffecList)
    {
        pEffect->m_pSprite->SetRect(pEffect->m_tRect);
        pEffect->m_pSprite->SetPosition(pEffect->m_vPos);
        pEffect->m_pSprite->Render();
    }
    return true;
}

bool Sample::Release()
{
    DxState::Release();
    m_object->Release();
    m_bPlayer->Release();
    m_bPlayer->m_pBulletList.clear();
    delete m_object;
    delete m_bPlayer;
    
    return true;
}


bool Sample::SetPlayer()
{
    bool hr;
    m_bPlayer = new Player;
    hr = m_bPlayer->SetDevice(m_pDevice->m_p3dDevice, m_pDevice->m_pImmediateContext);
    if (hr == false) { return false; }
    m_bPlayer->Init();
    hr = m_bPlayer->Create(L"D:/Git_PJS_C/PJS_Project/CreateObject/DefaultShader.txt", L"D:/Git_PJS_C/data/TankIdle.png");
    if (hr == false) { return false; }
    m_bPlayer->SetRect({ 91,72,50,45 });
    m_bPlayer->SetPosition({ g_rtClient.right / 2.0f, g_rtClient.bottom - 100.0f });
    return true;
}

bool Sample::SetMapObject()
{
    bool hr;
    m_object = new BObject;
    hr = m_object->SetDevice(m_pDevice->m_p3dDevice, m_pDevice->m_pImmediateContext);
    if (hr == false) { return false; }
    hr = m_object->Create(L"D:/Git_PJS_C/PJS_Project/CreateObject/DefaultShader.txt", L"D:/Git_PJS_C/data/1KGCABK.bmp");
    if (hr == false) { return false; }
    return true;
}

bool Sample::AddEffect()
{
    Efeect* pEffect = new Efeect;
    pEffect->m_pSprite = I_Sprite.GetPtr(L"rtExplosion");
    pEffect->m_fEffectTimer = 0.0f;
    Rect rt = pEffect->m_pSprite->m_uvArray[0];
    pEffect->m_tRect = rt;
    pEffect->m_iIndex = 0;
    pEffect->m_fLifeTime = 1.0f;
    pEffect->m_vPos = { 400,300};
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
