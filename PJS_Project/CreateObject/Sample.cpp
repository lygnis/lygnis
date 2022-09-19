#include "Sample.h"
#include "Player.h"
#include "Bullet.h"
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
    hr = SetMapObject();
    hr = SetPlayer();
    if (hr == false) { return false; }
   
    return true;
}
bool Sample::Frame()
{
    m_bPlayer->Frame();
    return true;
}
bool Sample::Render()
{
    m_object->Render();
    m_bPlayer->Render();
    
    return true;
}
bool Sample::Release()
{
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
    hr = m_bPlayer->Create(L"D:/Git_PJS_C/PJS_Project/CreateObject/DefaultShader.txt", L"D:/Git_PJS_C/data/Fortress.png");
    if (hr == false) { return false; }
    m_bPlayer->SetRect({ 40,148,32,32 });
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
