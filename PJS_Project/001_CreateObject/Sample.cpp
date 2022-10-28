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
    /*m_pMap = new MyMap;
    m_pMap->SetDevice(m_p3dDevice, m_pImmediateContext);
    m_pMap->Build(512 + 1, 512 + 1);
    m_pMap->Create(L"DefaultObject.txt", L"../../data/wall.bmp");
    m_pMap->m_matWorld.Translation(0, 0, 0);*/

    //m_pBox.Create(m_p3dDevice, L"../../shader/Box.hlsl", L"../../data/RTS_Crate.png");
    m_pBox.Create(m_p3dDevice, L"DefaultObject.txt", nullptr);//L"../../data/RTS_Crate.png");
   /* m_pBoxA = new ShapeBox;
    m_pBoxA->SetDevice(m_p3dDevice, m_pImmediateContext);
    m_pBoxA->Init();
    m_pBoxA->Create(L"DefaultObject.txt", L"../../data/1KGCABK.bmp");
    m_pBoxA->m_matWorld.Translation(-2,0,5);*/

   /* m_pBoxB = new ShapeBox;
    m_pBoxB->SetDevice(m_p3dDevice, m_pImmediateContext);
    m_pBoxB->Init();
    m_pBoxB->Create(L"DefaultObject.txt", L"../../data/RTS_Crate.png");
    m_pBoxB->m_matWorld.Translation(2, 0, -5);*/

    m_pCamera = new DebugCamera;
    // 카메라 시작 위치, 카메라 타겟 위치 , 가상 업벡터
    m_pCamera->CreateViewMatrix(Vector3D(0, 0, -10), Vector3D(0, 0, 0), Vector3D(0, 1, 0));
    m_pCamera->CreateProjMatrix(1.0f, 1000.0f, PI * 0.5f, (float)g_rtClient.right / (float)g_rtClient.bottom);

    m_DirLine.SetDevice(m_p3dDevice, m_pImmediateContext);
    m_DirLine.Create(L"DefaultShape.txt", L"");
    m_DirLine.m_matWorld.Scale(1000.f, 1000.f, 1000.f);
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
    TMatrix mMatWorld =*(TMatrix*)&m_pCamera->m_matView;
    TMatrix matProj = *(TMatrix*)&m_pCamera->m_matProj;
    m_pBox.SetMatrix(&mWorld, &mMatWorld, &matProj);
    m_pBox.Render(m_pImmediateContext);
    DebugCamera* pCame = (DebugCamera*)m_pCamera;


    //bool bRender = pCame->m_vFrustum.ClassifyPoint(m_pBoxA->m_vPos);
   /* if (bRender)
    {
		m_pBoxA->SetMatrix(&m_pBoxA->m_matWorld, &m_pCamera->m_matView, &m_pCamera->m_matProj);
		m_pBoxA->Render();
    }
    bRender = pCame->m_vFrustum.ClassifyPoint(m_pBoxB->m_vPos);
    if (bRender)
    {
		m_pBoxB->SetMatrix(&m_pBoxB->m_matWorld, &m_pCamera->m_matView, &m_pCamera->m_matProj);
		m_pBoxB->Render();
    }*/
   /* m_pMap->SetMatrix(&m_pMap->m_matWorld, &m_pCamera->m_matView, &m_pCamera->m_matProj);
    m_pMap->Render();*/

    m_DirLine.SetMatrix(nullptr, &m_pCamera->m_matView, &m_pCamera->m_matProj);
    m_DirLine.Render();
    return true;
}

bool Sample::Release()
{
    /*m_pBoxA->Release();
    m_pBoxB->Release();*/
    m_pCamera->Release();
    //m_pMap->Release();
    //delete m_pMap;
    delete m_pCamera;
    /*delete m_pBoxA;
    delete m_pBoxB;*/
    //DxState::Release();
    return true;
}


