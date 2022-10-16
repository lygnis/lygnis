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
    m_pBG = new BObject;
    m_pBG->SetDevice(m_p3dDevice, m_pImmediateContext);
    m_pBG->Create(L"../../shader/DefaultShader.txt", L"../../data/1KGCABK.bmp");
    return true;
}
bool Sample::Frame()
{
    MyMatrix4X4 m, s, t, c;
    float fScale = cos(I_Timer.m_fGameTime) * 0.5f + 0.5f;
    s = s.Scale(fScale, fScale, fScale);
    m = m.RotationZ(I_Timer.m_fGameTime*5.0f);
    t = t.Translation(cos(I_Timer.m_fGameTime), 0, 0);
    c = t*s*m;
    for (int i = 0; i < m_pBG->m_pInitVertexBuffer.size(); i++)
    {
        Vector3D _vec = m_pBG->m_pInitVertexBuffer[i].position;
        _vec = _vec * c;
        m_pBG->m_pVertexList[i].position = _vec;
    }
    m_pBG->UpdateVertexBuffer();
    return true;
}
bool Sample::Render()
{
    //m_pDevice->m_pImmediateContext->PSSetSamplers(0, 1, &DxState::g_pDefaultSS);
    m_pBG->Render();
    return true;
}

bool Sample::Release()

{
    //DxState::Release();
    return true;
}


