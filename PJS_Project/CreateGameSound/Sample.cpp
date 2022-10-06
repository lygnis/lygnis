#include "Sample.h"
#include "Player.h"
#include "Bullet.h"
#include "SpriteManager.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    //_CrtSetBreakAlloc(215);
    
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    Sample game;
    game.SetWindow(hInstance, L"TestDeviceCore", 800, 600);
    game.Run();
    //_CrtDumpMemoryLeaks();

    int  a = 0;
    return 1;
}

bool Sample::Init()
{
    bool hr;
    DxState::SetState(m_pDevice->m_p3dDevice);
    m_pStartScene = new SceneTitle;
    m_pGameScene = new SceneInGame;
    m_pGameClearScene = new SceneEnd;
    m_pGameOverScene = new SceneGameover;
    m_pGameClearScene->SetDevice(m_pDevice->m_p3dDevice, m_pDevice->m_pImmediateContext);
    m_pGameOverScene->SetDevice(m_pDevice->m_p3dDevice, m_pDevice->m_pImmediateContext);
    m_pGameClearScene->Init();
    m_pGameOverScene->Init();
    m_pStartScene->SetDevice(m_pDevice->m_p3dDevice, m_pDevice->m_pImmediateContext);
    m_pGameScene->SetDevice(m_pDevice->m_p3dDevice, m_pDevice->m_pImmediateContext);
    m_pStartScene->GetSwapChain(m_pDevice->m_pSwapChain);
    m_pGameScene->GetSwapChain(m_pDevice->m_pSwapChain);
    m_pStartScene->Init();
    m_pGameScene->Init();
    
    m_pCurrScene = m_pStartScene;
    return true;
}
bool Sample::Frame()
{
    if (I_Input.GetKey(VK_F1)==KEY_PUSH)
    {
        m_pStartScene->m_pWallSound->Stop();
        m_pCurrScene = m_pGameScene;
        m_pGameScene->m_pWallSound->Play(true);
    }
    if (I_Input.GetKey(VK_F2) == KEY_PUSH)
    {
        m_pCurrScene = m_pGameOverScene;
    }
    if (I_Input.GetKey(VK_F3) == KEY_PUSH)
    {
        m_pCurrScene = m_pGameClearScene;
    }
    m_pCurrScene->Frame();
    if (m_pGameScene->m_bClear==GameClear::GAME_CLEAR)
    {

        m_pGameScene->m_pWallSound->Stop();
        m_pGameClearScene->m_pWallSound->Play(true);
        m_pCurrScene = m_pGameClearScene;
    }
    if (m_pGameScene->m_bClear == GameClear::GAME_OVER)
    {
        //m_pGameScene->m_pWallSound->Stop();
        m_pGameOverScene->m_pWallSound->Play(true);
        m_pCurrScene = m_pGameOverScene;
    }
    if (m_pCurrScene == m_pGameOverScene)
    {
        if (I_Input.GetKey('R') == KEY_PUSH)
        {
            m_pGameOverScene->m_pWallSound->Stop();
            SceneReload();
            m_pCurrScene = m_pGameScene;
            m_pGameScene->m_pWallSound->Play(true);
        }
    }
        

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
    m_pGameClearScene->Release();
    m_pGameOverScene->Release();

    delete m_pGameClearScene;
    delete m_pGameOverScene;
    delete m_pStartScene;
    delete m_pGameScene;
    I_Sprite.Release();
    return true;
}

bool Sample::SceneReload()
{
    m_pGameScene->Release();
    m_pGameScene->Init();
    return true;
}
