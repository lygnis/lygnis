#include "Sample.h"


bool		Sample::Init()
{
    m_bObject.Create(m_p3dDevice, m_pImmediateContext,L"D:/C_PRJ/data/1KGCABK.bmp", 
        L"D:/C_PRJ/PJS_Project/CreateTexture_03/DefaultShader.txt");
    return true;
}
bool		Sample::Frame()
{
    m_bObject.Frame();
    return true;
}
bool		Sample::Render()
{
    m_bObject.Render();
    return true;
}
bool		Sample::Release()
{   
     m_bObject.Release();
     return true;
}



GAME_RUN(P2_CreateDevice_01, 1024, 768)
