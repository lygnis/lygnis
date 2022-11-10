#include "Sample.h"


int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    //_CrtSetBreakAlloc(215);
    
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    Sample game;
    game.SetWindow(hInstance, L"DeviceResize", 1000, 800);
    game.Run();
    //_CrtDumpMemoryLeaks();

    return 1;
}

bool Sample::Init()
{
    m_fbxLoad = new FbxLoader;
    m_fbxLoad->Init();
    m_fbxLoad->Load("../../fbxdata/Turret_Deploy/Turret_Deploy1.fbx");
    W_STR szDefaultDir = L"../../fbxdata/";
    for (int i = 0; i < m_fbxLoad->m_pObjectList.size(); i++)
    {
        MFbxObject* pObj = m_fbxLoad->m_pObjectList[i];
        std::wstring szLoad = szDefaultDir + pObj->m_szTextureName;
        pObj->Create(m_p3dDevice, L"DefaultObject.txt", szLoad.c_str());
    }

    m_pBox = new MBoxShape;
    m_pBox->Create(m_p3dDevice, L"DefaultObject.txt", L"../../data/circle_violet.dds");//L"../../data/RTS_Crate.png");
    m_pCamera = new DebugCamera;
    m_pMap = new MmapTile;
    m_pMap->CreateMap(4 + 1, 4 + 1);
    m_pMap->Create(m_p3dDevice, L"DefaultObject.txt", L"../../data/020.bmp");
    // 카메라 시작 위치, 카메라 타겟 위치 , 가상 업벡터
    m_pCamera->CreateViewMatrix(TVector3(0, 0, -10), TVector3(0, 0, 0), TVector3(0, 1, 0));
    m_pCamera->CreateProjMatrix(1.0f, 10000.0f, PI * 0.5f, (float)g_rtClient.right / (float)g_rtClient.bottom);
    m_QuadTree.Create( m_pImmediateContext, m_pCamera, m_pMap,3 );
    return true;
}
bool Sample::Frame()
{
    MyMatrix4X4 m, s, t, c;
    s = s.Scale(1, 1, 5);
    t = t.Translation(0, 2, 5);
    c = s*t;
    //m_pBoxA->Frame();
    //m_pBoxA->m_matWorld;
    //m_pBoxB->Frame();
    m_pCamera->Frame();
    return true;
}
bool Sample::Render()
{
    if (I_Input.GetKey('V') == KEY_HOLD)
    {
        m_pImmediateContext->RSSetState(DxState::g_pDefaultRSWireFrame);
    }
    //m_pImmediateContext->OMSetDepthStencilState(DxState::g_pDefaultDepthStencil,0xff);
    TMatrix mWorld;

    D3DXMatrixIdentity(&mWorld);
    mWorld._11 = 0.1;
    mWorld._22 = 0.1;
    mWorld._33 = 0.1;
    TMatrix gWorld;
    gWorld._11 = 10;
    gWorld._22 = 10;
    gWorld._33 = 10;
    bool bRender = m_pCamera->m_vFrustum.ClassifyPoint(m_pBox->m_vCenter);
    /*if(bRender)
    {
		m_pBox->SetMatrix(nullptr, &m_pCamera->m_matView, &m_pCamera->m_matProj, m_pImmediateContext);
		m_pBox->Render(m_pImmediateContext);
    }*/
    m_QuadTree.m_pMap->SetMatrix(&gWorld, &m_pCamera->m_matView, &m_pCamera->m_matProj, m_pImmediateContext);
    for (int i = 0; i < m_fbxLoad->m_pObjectList.size(); i++)
    {
        MFbxObject* pObj = m_fbxLoad->m_pObjectList[i];
        pObj->SetMatrix(&mWorld, &m_pCamera->m_matView, &m_pCamera->m_matProj, m_pImmediateContext);
        pObj->Render(m_pImmediateContext);
    }
    m_QuadTree.Frame();
    m_QuadTree.Render();
    DebugCamera* pCame = (DebugCamera*)m_pCamera;
    return true;
}

bool Sample::Release()
{
    for (int i = 0; i < m_fbxLoad->m_pObjectList.size(); i++)
    {
        MFbxObject* pObj = m_fbxLoad->m_pObjectList[i];
        pObj->Release();
    }
    m_QuadTree.Release();
    delete m_fbxLoad;
    m_pBox->Release();
    delete m_pCamera;
    /*delete m_pBoxA;
    delete m_pBoxB;*/
    DxState::Release();
    return true;
}


