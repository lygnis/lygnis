#include "Sample.h"
#include "FirePos.h"
#include "Bullet.h"
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    Sample game;
    game.SetWindow(hInstance, L"TestDeviceCore", 800, 600);
    game.Run();


    return 1;
}

bool Sample::Init()
{
    //m_object.SetDevice(m_pDevice->m_p3dDevice, m_pDevice->m_pImmediateContext);
    //m_object.Create(L"D:/Git_PJS_C/PJS_Project/CreateObject/DefaultShader.txt", L"D:/Git_PJS_C/data/1KGCABK.bmp");
    m_bFire = new FirePos;
    m_bFire->SetDevice(m_pDevice->m_p3dDevice, m_pDevice->m_pImmediateContext);
    m_bFire->Create(L"D:/Git_PJS_C/PJS_Project/CreateObject/DefaultShader.txt", L"D:/Git_PJS_C/data/Fortress.png");
    m_bFire->SetRect({ 40,148,32,32 });
    m_bFire->SetPosition({ g_rtClient.right / 2.0f, g_rtClient.bottom - 100.0f });
    return true;
}
bool Sample::Frame()
{
    m_bFire->Frame();
    return true;
}
bool Sample::Render()
{
    //m_object.Render();
    m_bFire->Render();
    if (!m_bFire->m_pBulletList.empty())
    {
        for (int i = 0; i< m_bFire->m_pBulletList.size(); i++)
        {
            if(m_bFire->m_pBulletList[i]!=nullptr)
                m_bFire->m_pBulletList[i]->Render();
        }
    }
    return true;
}
bool Sample::Release()
{
    //m_object.Release();
    m_bFire->Release();
    m_bFire->m_pBulletList.clear();
   /* m_bFire->m_bBullet->Release();
    delete m_bFire->m_bBullet;*/
    delete m_bFire;
    
    return true;
}
