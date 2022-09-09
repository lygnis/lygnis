#include "Sample.h"
bool		Sample::Init()
{
    DxDevice::Init();
    return true;
}
bool		Sample::Frame()
{
    DxDevice::Frame();
    return true;
}
bool		Sample::Render()
{
    DxDevice::Render();
    return true;
}
bool		Sample::Release()
{   
    DxDevice::Release();
    return true;
}



GAME_RUN(P2_CreateDevice_01, 1024, 768)
