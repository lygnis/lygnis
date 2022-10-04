#include "ItemBox.h"

bool ItemBox::Init()
{
    /*int i;
    i = rand() % 300;
    m_vPosition.x = 2000.f+ i;
    m_vPosition.y = 1090.f;*/
    m_iCountItem = rand()%4;
    SetCameraSize({ 800,600 });
    return true;
}

bool ItemBox::Frame()
{
    SetPosition(m_vPosition, m_vCameraPos);
    return true;
}
