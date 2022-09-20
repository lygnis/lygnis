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
    
    DataLoad(L"Sprite.txt");                                            // 텍스트 스프라이트 데이터를 읽는다.
    DxState::SetState(m_pDevice->m_p3dDevice);
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
    m_pDevice->m_pImmediateContext->PSSetSamplers(0, 1, &DxState::g_pDefaultSS);
    m_object->Render();
    m_bPlayer->Render();
    
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

bool Sample::DataLoad(const TCHAR* _fileLoad)
{
    

    //FILE* fp_src;
    //int u = true;
    ////u = fopen(&fp_src, _fileLoad, _T("rt"));
    //if (fp_src == NULL) return false;
    //_fgetts(pBuffer, sizeof(pBuffer)*256, fp_src);
    //OutputDebugString(pBuffer);
    //u = _stscanf_s(pBuffer, _T("%s%d%s"), pTemp, (unsigned int)_countof(pTemp), &iNumSprite);
    //m_rtSpriteList.resize(iNumSprite);

    //for (int iCnt = 0; iCnt < iNumSprite; iCnt++)
    //{
    //    int iNumFrame = 0;
    //    _fgetts(pBuffer, _countof(pBuffer), fp_src);
    //    _stscanf_s(pBuffer, _T("%s %d"), pTemp, (unsigned int)_countof(pTemp), &iNumFrame);
    //    //m_rtSpriteList[iCnt].resize(iNumFrame);

    //    Rect rt;
    //    for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
    //    {
    //        _fgetts(pBuffer, _countof(pBuffer), fp_src);
    //        _stscanf_s(pBuffer, _T("%s %d %d %d %d"), pTemp, (unsigned int)_countof(pTemp),
    //            &rt.x0, &rt.y0, &rt.xSize, &rt.ySize);
    //        m_rtSpriteList[iCnt].push_back(rt);
    //    }
    //}
    //fclose(fp_src);
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
    Rect rt = m_rtSpriteList[0][0];
    m_bPlayer->SetRect(rt);
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
