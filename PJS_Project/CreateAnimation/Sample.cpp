#include "Sample.h"
#include "Player.h"
#include "Bullet.h"
#include "SpriteManager.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    Sample game;
    game.SetWindow(hInstance, L"TestDeviceCore", 800, 600);
    game.Run();
    _CrtDumpMemoryLeaks();

    return 1;
}

bool Sample::Init()
{
    bool hr;
    DxState::SetState(m_pDevice->m_p3dDevice);
    m_pStartScene = new SceneTitle;
    m_pGameScene = new SceneInGame;
    m_pStartScene->SetDevice(m_pDevice->m_p3dDevice, m_pDevice->m_pImmediateContext);
    m_pGameScene->SetDevice(m_pDevice->m_p3dDevice, m_pDevice->m_pImmediateContext);
    m_pStartScene->Init();
    m_pGameScene->Init();
    m_pCurrScene = m_pStartScene;
    return true;
}
bool Sample::Frame()
{
    if (I_Input.GetKey(VK_F1)==KEY_PUSH)
    {
        m_pCurrScene = m_pGameScene;
    }
    m_pCurrScene->Frame();
    return true;
}
bool Sample::Render()
{
    m_pDevice->m_pImmediateContext->PSSetSamplers(0, 1, &DxState::g_pDefaultSS);
    m_pCurrScene->Render();
    return true;
}

bool Sample::Release()
{
    DxState::Release();
    m_pStartScene->Release();
    m_pGameScene->Release();
    delete m_pStartScene;
    delete m_pGameScene;
    I_Sprite.Release();
    return true;
}
